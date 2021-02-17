#ifndef __ESPUINO_VALUES_H__
#define __ESPUINO_VALUES_H__

// Operation Mode
#define OPMODE_NORMAL                   0           // Normal mode
#define OPMODE_BLUETOOTH                1           // Bluetooth mode. WiFi is deactivated. Music from SD and webstreams can't be played.

// Track-Control
#define STOP                            1           // Stop play
#define PLAY                            2           // Start play (currently not used)
#define PAUSEPLAY                       3           // Pause/play
#define NEXTTRACK                       4           // Next track of playlist
#define PREVIOUSTRACK                   5           // Previous track of playlist
#define FIRSTTRACK                      6           // First track of playlist
#define LASTTRACK                       7           // Last track of playlist

// Playmodes
#define NO_PLAYLIST                     0           // If no playlist is active
#define SINGLE_TRACK                    1           // Play a single track
#define SINGLE_TRACK_LOOP               2           // Play a single track in infinite-loop
#define AUDIOBOOK                       3           // Single track, can save last play-position
#define AUDIOBOOK_LOOP                  4           // Single track as infinite-loop, can save last play-position
#define ALL_TRACKS_OF_DIR_SORTED        5           // Play all files of a directory (alph. sorted)
#define ALL_TRACKS_OF_DIR_RANDOM        6           // Play all files of a directory (randomized)
#define ALL_TRACKS_OF_DIR_SORTED_LOOP   7           // Play all files of a directory (alph. sorted) in infinite-loop
#define ALL_TRACKS_OF_DIR_RANDOM_LOOP   9           // Play all files of a directory (randomized) in infinite-loop
#define WEBSTREAM                       8           // Play webradio-stream
#define BUSY                            10          // Used if playlist is created


// RFID-modifcation-types
#define CMD_NOTHING                       0         // Do Nothing
#define LOCK_BUTTONS_MOD                100         // Locks all buttons and rotary encoder
#define SLEEP_TIMER_MOD_15              101         // Puts uC into deepsleep after 15 minutes + LED-DIMM
#define SLEEP_TIMER_MOD_30              102         // Puts uC into deepsleep after 30 minutes + LED-DIMM
#define SLEEP_TIMER_MOD_60              103         // Puts uC into deepsleep after 60 minutes + LED-DIMM
#define SLEEP_TIMER_MOD_120             104         // Puts uC into deepsleep after 120 minutes + LED-DIMM
#define SLEEP_AFTER_END_OF_TRACK        105         // Puts uC into deepsleep after track is finished + LED-DIMM
#define SLEEP_AFTER_END_OF_PLAYLIST     106         // Puts uC into deepsleep after playlist is finished + LED-DIMM
#define SLEEP_AFTER_5_TRACKS            107         // Puts uC into deepsleep after five tracks
#define REPEAT_PLAYLIST                 110         // Changes active playmode to endless-loop (for a playlist)
#define REPEAT_TRACK                    111         // Changes active playmode to endless-loop (for a single track)
#define DIMM_LEDS_NIGHTMODE             120         // Changes LED-brightness
#define TOGGLE_WIFI_STATUS              130         // Toggles WiFi-status
#define TOGGLE_BLUETOOTH_MODE           140         // Toggles Normal/Bluetooth Mode
#define ENABLE_FTP_SERVER               150         // Enables FTP-server

#define CMD_PLAYPAUSE                   170         // Admin-Cmd Play/Pause
#define CMD_PREVTRACK                   171         // Admin-Cmd Prev Track
#define CMD_NEXTTRACK                   172         // Admin-Cmd Next Track
#define CMD_FIRSTTRACK                  173         // Admin-Cmd Prev Track
#define CMD_LASTTRACK                   174         // Admin-Cmd Next Track
#define CMD_VOLUMEINIT                  175         // Set Volume to Initial
#define CMD_VOLUMEUP                    176         // Set Volume up
#define CMD_VOLUMEDOWN                  177         // Set Volume down
#define CMD_MEASUREBATTERY              178         // Measure Battery Voltage
#define CMD_SLEEPMODE                   179         // Goto Sleepmode

// Repeat-Modes
#define NO_REPEAT                       0           // No repeat
#define TRACK                           1           // Repeat current track (infinite loop)
#define PLAYLIST                        2           // Repeat whole playlist (infinite loop)
#define TRACK_N_PLAYLIST                3           // Repeat both (infinite loop)

// Button-helper
typedef struct {
    uint button;
    uint8_t action;
} t_btn_action;

#define BUTTON_01                        1           // Bit mask - Button 1
#define BUTTON_02                        2           // Bit mask - Button 2
#define BUTTON_03                        4           // Bit mask - Button 3
#define BUTTON_04                        8           // Bit mask - Button 4
#define BUTTON_05                       16           // Bit mask - Button 5
#define BUTTON_06                       32           // Bit mask - Button 6
#define BUTTON_07                       64           // Bit mask - Button 7
#define BUTTON_08                      128           // Bit mask - Button 8
#define BUTTON_09                      246           // Bit mask - Button 9
#define BUTTON_10                      512           // Bit mask - Button 10
#define BUTTON_11                     1024           // Bit mask - Button 11
#define BUTTON_12                     2048           // Bit mask - Button 12
#define BUTTON_13                     4096           // Bit mask - Button 13
#define BUTTON_14                     8192           // Bit mask - Button 14
#define BUTTON_15                    16384           // Bit mask - Button 15
#define BUTTON_16                    32768           // Bit mask - Button 16
#define BUTTON_LP               2147483648           // Bit mask - Button Longpress (bit 32)

#endif 