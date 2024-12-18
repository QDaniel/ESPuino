#include "Cloud.h"

#include "ArduinoJson.h"
#include "AsyncJson.h"
#include "AudioPlayer.h"
#include "Cmd.h"
#include "Log.h"
#include "MemX.h"
#include "Playlist.h"
#include "Rfid.h"
#include "SdCard.h"
#include "Wlan.h"

#include <HTTPClient.h>
#include <deque>
#include <stdint.h>

struct SpiRamCAllocator {
	void *allocate(size_t size) {
		return ps_malloc(size);
	}
	void deallocate(void *pointer) {
		free(pointer);
	}
};
using SpiRamJsonDocument = BasicJsonDocument<SpiRamCAllocator>;

#ifdef CLOUD_INFO_URL

	#define CLOUD_DL_CHUNK_SIZE 1024
const char *m3uext = ".m3u";
String CloudDataDir = "/CloudCache";
const char *DirDelim = "/";
std::deque<String> dlList;
TaskHandle_t dlTaskHandle = NULL;

void Cloud_Init(void) {
	if (!gFSystem.exists(CloudDataDir)) {
		gFSystem.mkdir(CloudDataDir);
	}
}

bool DownloadFile(HTTPClient *http, const char *uri, const char *path, const char *temp, const char *etag) {
	bool ret;
	Log_Print("DownloadFile http uri: ", LOGLEVEL_INFO, true);
	Log_Print(uri, LOGLEVEL_INFO, false);
	Log_Print(" -> ", LOGLEVEL_INFO, false);
	Log_Print(path, LOGLEVEL_INFO, false);
	Log_Print("\n", LOGLEVEL_INFO, false);
	Log_Print(" ETAG: ", LOGLEVEL_INFO, false);
	Log_Print(etag, LOGLEVEL_INFO, false);
	Log_Print("\n", LOGLEVEL_INFO, false);
	http->begin(uri);
	if (String(etag).startsWith("\"")) {
		http->addHeader("If-None-Match", etag);
	}
	http->addHeader("X-Ident", Wlan_GetMacAddress());

	int httpCode = http->GET();
	Log_Printf(LOGLEVEL_INFO, "http result: %d", httpCode);

	if (httpCode == 200) {
		File file = gFSystem.open(temp, FILE_WRITE);

		// ********************* DOWNLOAD PROCESS *********************
		uint8_t *data = static_cast<uint8_t *>(x_malloc(CLOUD_DL_CHUNK_SIZE));

		const size_t TOTAL_SIZE = http->getSize();
		size_t downloadRemaining = TOTAL_SIZE;
		Log_Println("Download START", LOGLEVEL_DEBUG);
		Log_Printf(LOGLEVEL_DEBUG, "Total Size: %d", TOTAL_SIZE);

		WiFiClient *stream = http->getStreamPtr();
		auto start_ = millis();
		size_t data_size;
		while (downloadRemaining > 0 && http->connected()) {
			data_size = stream->available();
			if (data_size > 0) {
				auto read_count = stream->read(data, ((data_size > CLOUD_DL_CHUNK_SIZE) ? CLOUD_DL_CHUNK_SIZE : data_size));
				// If one chunk of data has been accumulated, write to SD card
				if (read_count > 0) {
					downloadRemaining -= read_count;
					file.write(data, read_count);
				}
			}
			vTaskDelay(1);
		}

		size_t time_ = (millis() - start_);
		file.close();
		Log_Println("Download END", LOGLEVEL_DEBUG);
		gFSystem.rename(temp, path);
		Log_Printf(LOGLEVEL_DEBUG, "Speed: %d bytes/sec\n", TOTAL_SIZE / time_ / 1000);
		ret = true;
	} else {
		Log_Printf(LOGLEVEL_INFO, "HTTP Failed, Status: %d\n", httpCode);
		ret = false;
	}
	http->end();
	return ret;
}
bool DownloadFileM3U(HTTPClient *http, const char *uri, const char *path, const char *temp, const char *etag) {
	bool ret;
	Log_Print("DownloadFileM3U http uri: ", LOGLEVEL_INFO, true);
	Log_Print(uri, LOGLEVEL_INFO, false);
	Log_Print(" -> ", LOGLEVEL_INFO, false);
	Log_Print(path, LOGLEVEL_INFO, false);
	Log_Print("\n", LOGLEVEL_INFO, false);
	Log_Print(" ETAG: ", LOGLEVEL_INFO, false);
	Log_Print(etag, LOGLEVEL_INFO, false);
	Log_Print("\n", LOGLEVEL_INFO, false);
	http->begin(uri);
	if (String(etag).startsWith("\"")) {
		http->addHeader("If-None-Match", etag);
	}
	http->addHeader("X-Ident", Wlan_GetMacAddress());

	int httpCode = http->GET();
	Log_Printf(LOGLEVEL_INFO, "http result: %d", httpCode);

	if (httpCode == 200) {
		http->headers();
		String etagStr = http->header("ETag");

		if (etagStr.isEmpty() || etagStr.compareTo(etag) != 0) {
			File file = gFSystem.open(temp, FILE_WRITE);
			file.print("#");
			file.println(etagStr.c_str());

			// ********************* DOWNLOAD PROCESS *********************
			uint8_t *data = static_cast<uint8_t *>(x_malloc(CLOUD_DL_CHUNK_SIZE));

			const size_t TOTAL_SIZE = http->getSize();
			size_t downloadRemaining = TOTAL_SIZE;
			Log_Println("Download START", LOGLEVEL_DEBUG);
			Log_Printf(LOGLEVEL_DEBUG, "Total Size: %d", TOTAL_SIZE);

			WiFiClient *stream = http->getStreamPtr();
			auto start_ = millis();
			size_t data_size;
			while (downloadRemaining > 0 && http->connected()) {
				data_size = stream->available();
				if (data_size > 0) {
					auto read_count = stream->read(data, ((data_size > CLOUD_DL_CHUNK_SIZE) ? CLOUD_DL_CHUNK_SIZE : data_size));
					// If one chunk of data has been accumulated, write to SD card
					if (read_count > 0) {
						downloadRemaining -= read_count;
						file.write(data, read_count);
					}
				}
				vTaskDelay(1);
			}

			size_t time_ = (millis() - start_);
			file.close();
			Log_Println("Download END", LOGLEVEL_DEBUG);
			gFSystem.rename(temp, path);
			Log_Printf(LOGLEVEL_DEBUG, "Speed: %d bytes/sec\n", TOTAL_SIZE / time_ / 1000);
		}
		ret = true;
	} else {
		Log_Printf(LOGLEVEL_INFO, "HTTP Failed, Status: %d\n", httpCode);
		ret = false;
	}
	http->end();
	return ret;
}

const char *tempCl = "/cloud_dl.tmp";
const char *tempUp = "/cloud_up.tmp";
const char *tempSc = "/cloud_sc.tmp";
HTTPClient httpClDl;
HTTPClient httpClSc;

void Cloud_Dl(void *parameter) {

	if (!gFSystem.exists(CloudDataDir)) {
		gFSystem.mkdir(CloudDataDir);
	}

	while (!dlList.empty()) {
		char *rfid;
		char *etag;
		char *path;
		char *uri;
		char *url = x_strdup(dlList.front().c_str());
		Log_Println(url, LOGLEVEL_INFO);

		dlList.pop_front();
		rfid = strsep(&url, ";");
		etag = strsep(&url, ";");
		path = strsep(&url, ";");
		uri = strsep(&url, ";");
		Log_Println(rfid, LOGLEVEL_INFO);
		Log_Println(etag, LOGLEVEL_INFO);
		Log_Println(path, LOGLEVEL_INFO);
		Log_Println(uri, LOGLEVEL_INFO);

		if (DownloadFile(&httpClDl, uri, path, tempCl, etag)) {

			File fileO = gFSystem.open(rfid, FILE_READ);
			File fileT = gFSystem.open(tempUp, FILE_WRITE);
			while (fileO.available()) {
				String line = fileO.readStringUntil('\n');
				line.trim();
				fileT.println(!line.compareTo(uri) == 0 ? path : line);
			}
			fileO.close();
			fileT.close();
			gFSystem.remove(rfid);
			gFSystem.rename(tempUp, rfid);
			// gPlayProperties.playlist
		}
	}

	dlTaskHandle = NULL;
	vTaskDelete(NULL);
}

static bool Cloud_allocAndSave(std::deque<String> *playlist, const String &s) {
	const size_t len = s.length() + 1;
	char *entry = static_cast<char *>(x_malloc(len));
	if (!entry) {
		return false;
	}
	s.toCharArray(entry, len);
	playlist->push_back(entry);
	return true;
}

bool Cloud_Scan(const char *rfidId) {
	char buf[30];
	bool checked = false;
	strcpy(buf, CloudDataDir.c_str());
	strcat(buf, DirDelim);
	strcat(buf, rfidId);
	strcat(buf, m3uext);

	String url = String(CLOUD_INFO_URL) + rfidId;
	if (!gFSystem.exists(buf)) {
		if (!gFSystem.exists(CloudDataDir)) {
			gFSystem.mkdir(CloudDataDir);
		}
		DownloadFileM3U(&httpClSc, url.c_str(), buf, tempSc, "*");
		checked = true;
	}

	if (gFSystem.exists(buf)) {
		Log_Printf(LOGLEVEL_INFO, "File Exists: %s checking file ...", buf);

		File file = gFSystem.open(buf, FILE_READ);
		bool incomplete = false;
		int Command = 0;

		char etag[100];
		etag[0] = '*';

		if (file.available()) {
			Log_Println("file.available. reading ...", LOGLEVEL_INFO);
			String lineh = file.readStringUntil('\n');
			lineh.trim();
			Log_Println(lineh.c_str(), LOGLEVEL_INFO);
			if (lineh.length() < 40) {
				strcpy(etag, lineh.substring(1).c_str());
				Log_Printf(LOGLEVEL_INFO, "ETag Found: %s", etag);
				Log_Println(etag, LOGLEVEL_INFO);
			}

			String dirName = "";
			String fileName = "";
			String fileSizeStr = "";
			int fileSize = -1;

			while (file.available() || Command != 0) {
				lineh = file.readStringUntil('\n');
				lineh.trim();
				if (lineh.startsWith("#CMD:")) {
					Command = lineh.substring(5).toInt();
				} else {
					if (lineh.startsWith("#DL-FILE:")) {
						char *line = x_strdup(lineh.substring(8).c_str());
						dirName = strsep(&line, ";");
						fileName = strsep(&line, ";");
						fileSizeStr = strsep(&line, ";");
						if (!fileSizeStr.isEmpty()) {
							fileSize = fileSizeStr.toInt();
						}
					} else if (!fileName.isEmpty() && (lineh.startsWith("http://") || lineh.startsWith("https://"))) {
						if (!dirName.isEmpty() && !gFSystem.exists(dirName)) {
							gFSystem.mkdir(dirName);
						}
						bool mustDl = true;
						if (fileSize > 0 && gFSystem.exists(dirName + fileName)) {
							File rf = gFSystem.open(dirName + fileName);
							mustDl = rf.size() != fileSize;
							rf.close();
						}

						String line = String(buf) + ";*;" + dirName + fileName + ";" + line;
						Log_Printf(LOGLEVEL_INFO, "DL-Queueing: %s", line);
						if (std::find(dlList.begin(), dlList.end(), line.c_str()) == dlList.end()) {
							Cloud_allocAndSave(&dlList, line);
						}
					}
				}

				if (!lineh.startsWith("#")) {
					dirName = "";
					fileName = "";
					fileSizeStr = "";
					fileSize = -1;
				}
			}
			file.close();

			if (dlTaskHandle == NULL && dlList.size() > 0) {
				xTaskCreate(Cloud_Dl, "DownloadUri", 6000, NULL, 1, &dlTaskHandle);
			}
		}

		if (Command > 0) {
			Cmd_Action(Command);
		} else {
			AudioPlayer_TrackQueueDispatcher(buf, 0, LOCAL_M3U, 0);
		}
		if (!checked) {
			Log_Printf(LOGLEVEL_DEBUG, "ReCheck: %s  %s", buf, etag);
			DownloadFileM3U(&httpClSc, url.c_str(), buf, tempSc, etag);
		}
		return true;
	}

	return false;
}

#else
void Cloud_Init(void) {
}
bool Cloud_Scan(const char *rfidId) {
	return false;
#endif

#ifdef CLOUD_STAT_URL

JsonObject Cloud_BuildStatus(void) {

	#ifdef BOARD_HAS_PSRAM
	SpiRamJsonDocument doc(1024);
	#else
	StaticJsonDocument<1024> doc;
	#endif
	JsonObject object = doc.to<JsonObject>();
	object["rfidId"] = gCurrentRfidTagId;
	object["rssi"] = Wlan_GetRssi();
	object["ssid"] = Wlan_GetCurrentSSID();
	object["hostname"] = Wlan_GetHostname();
	object["address"] = Wlan_GetIpAddress();
	object["volume"] = AudioPlayer_GetCurrentVolume();

	JsonObject entry = object.createNestedObject("trackinfo");
	entry["pausePlay"] = gPlayProperties.pausePlay;
	entry["currentTrackNumber"] = gPlayProperties.currentTrackNumber + 1;
	entry["numberOfTracks"] = (gPlayProperties.playlist) ? gPlayProperties.playlist->size() : 0;
	entry["name"] = gPlayProperties.title;
	entry["posPercent"] = gPlayProperties.currentRelPos;
	entry["playMode"] = gPlayProperties.playMode;
	entry["posPercent"] = gPlayProperties.currentRelPos;
	entry["time"] = AudioPlayer_GetCurrentTime();
	entry["duration"] = AudioPlayer_GetFileDuration();
	return object;
}

String updateUrl = String(CLOUD_STAT_URL) + Wlan_GetMacAddress();
void Cloud_SendStatusInfo(void) {
	uint8_t *buf = static_cast<uint8_t *>(x_malloc(1024));
	JsonObject obj = Cloud_BuildStatus();
	size_t l = serializeJson(obj, buf, 1024);
	httpClSc.begin(updateUrl);
	httpClSc.addHeader("X-Ident", Wlan_GetMacAddress());
	httpClSc.addHeader("Content-Type", "application/json");
	httpClSc.POST(buf, l);
}

#else
	void Cloud_SendStatusInfo(void) {
	}
#endif
