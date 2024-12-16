#include "Cloud.h"
#include "SdCard.h"
#ifdef CLOUD_URL
#include "Cmd.h"
#include "AudioPlayer.h"
#include "Playlist.h"
#include "MemX.h"
#include "Wlan.h"
#include "Log.h"
#include <stdint.h>
#include <deque>
#include <HTTPClient.h>
#include "ArduinoJson.h"
#include "AsyncJson.h"
#include "Rfid.h"

struct SpiRamCAllocator {
	void *allocate(size_t size) {
		return ps_malloc(size);
	}
	void deallocate(void *pointer) {
		free(pointer);
	}
};
using SpiRamJsonDocument = BasicJsonDocument<SpiRamCAllocator>;


/*
cardType (dec / hex)
  0 / 0x00 = Device Only / Saved in old Tagfile
  1 / 0x01 = Reuseable / Old Style
 17 / 0x11 = Web Card / Single File 
 18 / 0x12 = Web Card / Catalog File 
173 / 0xAD = Admin Card (playMode = Cmd)
*/

/* 
Admin - CMDs
100 / 0x64 = LOCK_BUTTONS                   // Locks all buttons and rotary encoder
101 / 0x65 = SLEEP_TIMER_MOD_15             // Puts uC into deepsleep after 15 minutes + LED-DIMM
102 / 0x66 = SLEEP_TIMER_MOD_30             // Puts uC into deepsleep after 30 minutes + LED-DIMM
103 / 0x67 = SLEEP_TIMER_MOD_60             // Puts uC into deepsleep after 60 minutes + LED-DIMM
104 / 0x68 = SLEEP_TIMER_MOD_120            // Puts uC into deepsleep after 120 minutes + LED-DIMM
105 / 0x69 = SLEEP_AFTER_END_OF_TRACK       // Puts uC into deepsleep after track is finished + LED-DIMM
106 / 0x6A = SLEEP_AFTER_END_OF_PLAYLIST    // Puts uC into deepsleep after playlist is finished + LED-DIMM
107 / 0x6B = SLEEP_AFTER_5_TRACKS           // Puts uC into deepsleep after five tracks
110 / 0x6E = REPEAT_PLAYLIST                // Changes active playmode to endless-loop (for a playlist)
111 / 0x6F = REPEAT_TRACK                   // Changes active playmode to endless-loop (for a single track)
120 / 0x78 = DIMM_LEDS_NIGHTMODE            // Changes LED-brightness
130 / 0x82 = WIFI_STATUS_TOGGLE             // Toggles WiFi-status
131 / 0x83 = WIFI_STATUS_ENABLE             // Enable WiFi
132 / 0x84 = TOGGLE_WIFI_DISABLE            // Disable WiFi
140 / 0x8C = PAUSE_PLAY                     // Pause / Play Button
141 / 0x8D = PREV_TRACK                     // Prev Button
142 / 0x8E = NEXT_TRACK                     // Next Button
*/
#define CLOUD_DL_CHUNK_SIZE      1024
const char* m3uext = ".m3u";
String CloudDataDir = "/CloudCache";
const char* DirDelim = "/";
String DataBaseDir = "/";
String Escape = "\"";
std::deque<String> dlList;
TaskHandle_t dlTaskHandle = NULL;

void Cloud_Init(void)
{
  if(!gFSystem.exists(CloudDataDir)) gFSystem.mkdir(CloudDataDir);
}

bool DownloadFile(HTTPClient* http,  const char* uri,  const char* path,  const char* temp,  const char* etag) {
    bool ret = true;
    Log_Print("DownloadFile http uri: ", LOGLEVEL_INFO, true);
    Log_Print(uri,LOGLEVEL_INFO ,false);
    Log_Print(" -> ",LOGLEVEL_INFO ,false);
    Log_Print(path, LOGLEVEL_INFO, false);
    Log_Print("\n", LOGLEVEL_INFO, false);
    Log_Print(" ETAG: ", LOGLEVEL_INFO, false);
    Log_Print(Escape.c_str(), LOGLEVEL_INFO, false);
    Log_Print(etag, LOGLEVEL_INFO, false);
    Log_Print(Escape.c_str(), LOGLEVEL_INFO, false);
    Log_Print("\n", LOGLEVEL_INFO, false);
    http->begin(uri);
    http->addHeader("If-None-Match", Escape + etag + Escape);
    http->addHeader("X-Ident", Wlan_GetMacAddress());
    
    int httpCode = http->GET();
    Log_Printf(LOGLEVEL_INFO, "http result: %d", httpCode);

    if(httpCode == 200) {
        File file = gFSystem.open(temp, FILE_WRITE);

        // ********************* DOWNLOAD PROCESS *********************
        uint8_t* data  = static_cast<uint8_t *>(x_malloc(CLOUD_DL_CHUNK_SIZE));

        const size_t TOTAL_SIZE = http->getSize();
        Serial.print("TOTAL SIZE : ");
        Serial.println(TOTAL_SIZE);
        size_t downloadRemaining = TOTAL_SIZE;
        Serial.println("Download START");
        WiFiClient* stream = http->getStreamPtr();
        auto start_ = millis();
        size_t data_size;
        while ( downloadRemaining > 0 && http->connected() ) {
            data_size = stream->available();
            if (data_size > 0) {
                auto read_count = stream->read(data, ((data_size > CLOUD_DL_CHUNK_SIZE) ? CLOUD_DL_CHUNK_SIZE : data_size));                    
                // If one chunk of data has been accumulated, write to SD card
                if (read_count > 0) 
                {
                    downloadRemaining -= read_count;
                    file.write(data, read_count);                   
                }
            }
            vTaskDelay(1);
        }

        size_t time_ = (millis() - start_);
        file.close();
        Serial.println("Download END");
        gFSystem.rename(temp, path);
        String speed_ = String(TOTAL_SIZE / time_ / 1000);
        Serial.println("Speed: " + speed_ + " bytes/sec");
        ret = true;
    } else {
        Serial.print("HTTP Failed, Status: ");
        Serial.println(httpCode);
        ret = false;
    }
    http->end();
    return ret;
    
}

const char* tempCl = "/cloud_dl.tmp";
const char* tempUp = "/cloud_up.tmp";
const char* tempSc = "/cloud_sc.tmp";
HTTPClient httpClDl;
HTTPClient httpClSc;

void Cloud_Dl(void * parameter) {


    if(!gFSystem.exists(CloudDataDir)) gFSystem.mkdir(CloudDataDir);

    while (!dlList.empty()) {
        char* rfid;
        char* etag;
        char* path;
        char* uri;
        char* url = x_strdup(dlList.front().c_str());
        Log_Println(url, LOGLEVEL_INFO);

        dlList.pop_front();
        rfid = strsep(&url,";");
        etag = strsep(&url,";");
        path = strsep(&url,";");
        uri  = strsep(&url,";");
        Log_Println(rfid, LOGLEVEL_INFO);
        Log_Println(etag, LOGLEVEL_INFO);
        Log_Println(path, LOGLEVEL_INFO);
        Log_Println(uri, LOGLEVEL_INFO);

        if(DownloadFile(&httpClDl, uri, path, tempCl, etag)){

            File fileO = gFSystem.open(rfid, FILE_READ);
            File fileT = gFSystem.open(tempUp, FILE_WRITE);
            bool incomplete = false;

            while (fileO.available())
            {
                String line = fileO.readStringUntil('\n');  
                line.trim();          
                fileT.println(line.startsWith(uri) ? path: line);
                if(!line.startsWith(uri))
                    incomplete = incomplete || line.startsWith("http:") || line.startsWith("https:");
            }
            fileO.close();
            fileT.close();
            gFSystem.remove(rfid);
            gFSystem.rename(tempUp, rfid);
            
            if(!incomplete) {
                fileO = gFSystem.open(rfid, FILE_READ);
                fileT = gFSystem.open(tempUp, FILE_WRITE);

                while (fileO.available())
                {
                    String line = fileO.readStringUntil('\n');
                    line.trim();   
                    fileT.println(line.startsWith("#INCOMPLETE") ? "#COMPLETED": line);
                }
                fileO.close();
                fileT.close();
                gFSystem.remove(rfid);
                gFSystem.rename(tempUp, rfid);
            }
            //gPlayProperties.playlist
        }
    }

    dlTaskHandle = NULL;
    vTaskDelete(NULL);
}

static bool Cloud_allocAndSave(std::deque<String> *playlist, const String &s) {
	const size_t len = s.length() + 1;
	char *entry = static_cast<char *>(x_malloc(len));
	if (!entry) return false;
	s.toCharArray(entry, len);
	playlist->push_back(entry);
	return true;
}

bool Cloud_Scan(const char *rfidId)
{
    char buf[30];
    bool checked = false; 
    strcpy(buf, CloudDataDir.c_str());
    strcat(buf, DirDelim);
    strcat(buf, rfidId);
    strcat(buf, m3uext);

    String url = String(CLOUD_URL) +"/api/rfid/info/" + rfidId;
    if(!gFSystem.exists(buf))
    {
        if(!gFSystem.exists(CloudDataDir)) gFSystem.mkdir(CloudDataDir);
        DownloadFile(&httpClSc, url.c_str(), buf, tempSc, "*" );
        checked=true;
    }

    if(gFSystem.exists(buf))
    {
        Log_Printf(LOGLEVEL_INFO, "File Exists: %s checking file ...", buf);
 
        File file = gFSystem.open(buf, FILE_READ);
        bool incomplete = false;
        int Command = 0;

        char etag[100]; etag[0]='*';
        
        
        if (file.available()) {
            Log_Println("file.available. reading ...", LOGLEVEL_INFO);
            String lineh = file.readStringUntil('\n');
            lineh.trim();
            Log_Println(lineh.c_str(), LOGLEVEL_INFO);
            if(lineh.length()<40){
                strcpy(etag, lineh.substring(1).c_str());
                Log_Printf(LOGLEVEL_INFO, "ETag Found: %s", etag);
                Log_Println(etag, LOGLEVEL_INFO);
            }
            lineh = file.readStringUntil('\n');
            incomplete = lineh.startsWith("#INCOMPLETE");
            if(lineh.startsWith("#CMD:")) Command = lineh.charAt(5);

            if(incomplete) {
            Log_Println("IS INCOMPLETE", LOGLEVEL_INFO);
                if(!gFSystem.exists( DataBaseDir + rfidId)) gFSystem.mkdir(DataBaseDir + rfidId);

                int row = 0;
                char str[10];
                while (file.available()) {
                    String line = file.readStringUntil('\n');                
                    if (!line.startsWith("#"))
                    {
                        row++;
                        if(!line.startsWith("/")) {
                        // this something we have to save
                        line.trim();
                        sprintf(str, "/%03d.mp3;", row);
                        line = String(buf) +";*;"+ DataBaseDir + rfidId + str + line;
                        Log_Printf(LOGLEVEL_INFO, "DLQueueing: %s", line);
                        if(std::find(dlList.begin(), dlList.end(), line.c_str())==dlList.end()) {
                            Cloud_allocAndSave(&dlList, line);
                        }
                        }
                    }
                }
                if(dlTaskHandle == NULL) xTaskCreate(Cloud_Dl, "DownloadUri", 6000, NULL, 1, &dlTaskHandle);
            }
        }
        file.close();
        Log_Println("FILECLOSED", LOGLEVEL_INFO);
        if(Command>0){
            Cmd_Action(Command);
        }else {
            AudioPlayer_TrackQueueDispatcher(buf, 0, LOCAL_M3U, 0);
        }
        if(!checked){
            Log_Println("NOT CHECKED . recheck tag", LOGLEVEL_INFO);

            Log_Printf(LOGLEVEL_INFO, "ReCheck: %s  %s", buf, etag);

            DownloadFile(&httpClSc, url.c_str(), buf, tempSc, etag);
        }
        return true;
    }

    return false;
}


#ifdef CLOUD_STATUSUPDATE_ENABLE

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

String updateUrl = String(CLOUD_URL) + "/api/device/" + Wlan_GetMacAddress();
void Cloud_SendStatusInfo(void) {
    uint8_t* buf = static_cast<uint8_t *>(x_malloc(1024));
    JsonObject obj = Cloud_BuildStatus();
    size_t l = serializeJson(obj, buf, 1024);
    httpClSc.begin(updateUrl);
    httpClSc.addHeader("X-Ident", Wlan_GetMacAddress());
    httpClSc.addHeader("Content-Type", "application/json");
    httpClSc.POST(buf, l);
}


#else
void Cloud_SendStatusInfo(void) { }
#endif

#else
void Cloud_Init(void) { }
bool Cloud_Scan(const char *rfidId) { return false; }
void Cloud_SendStatusInfo(void) { }
#endif