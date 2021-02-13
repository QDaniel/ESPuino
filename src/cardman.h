#include "base64url.h"

typedef struct { // Mifare Data Holder Pos: Sector/Block/BytePosition
    uint8_t cardType;      // cardType - Pos: 0/1/8
    uint8_t playMode;      // playMode / CMD - Pos: 0/1/9
    uint8_t trackNr;       // trackNr for PlayMode single title  - Pos: 0/1/10
    uint8_t uuid[16];         // Uuid : Unique ID for this Web-Card use as folder name (hex) - Pos: 0/2 , Size: 1 Block
    char uuid64[23];         // Uuid : base64url encoded
    char uri[241];         // Uri : File or Webaddress, Pos: 1/0 , Size 4 Sectors 1-5: 3 Blocks * 16 bytes * 4 Sectors 
} cardmanData;

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

MFRC522::MIFARE_Key cardman_key; //create a MIFARE_Key struct named 'key', which will hold the card information

void cardman_init() {
        for (byte i = 0; i < 6; i++) {
                cardman_key.keyByte[i] = 0xFF; //keyByte is defined in the "MIFARE_Key" 'struct' definition in the .h file of the library
        }
}

int cardman_readBlock(MFRC522 *frc, int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector

  /*****************************************authentication of the desired block for access***********************************************************/
  MFRC522::StatusCode status = frc->PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &cardman_key, &(frc->uid));
  //byte PCD_Authenticate(byte command, byte blockAddr, MIFARE_Key *key, Uid *uid);
  //this method is used to authenticate a certain block for writing or reading
  //command: See enumerations above -> PICC_CMD_MF_AUTH_KEY_A = 0x60 (=1100000),    // this command performs authentication with Key A
  //blockAddr is the number of the block from 0 to 15.
  //MIFARE_Key *key is a pointer to the MIFARE_Key struct defined above, this struct needs to be defined for each block. New cards have all A/B= FF FF FF FF FF FF
  //Uid *uid is a pointer to the UID struct that contains the user ID of the card.
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed (read): ");
         Serial.println(frc->GetStatusCodeName(status));
         frc->PICC_DumpToSerial(&(frc->uid));
         return 3;//return "3" as error message
  }
  //it appears the authentication needs to be made before every block read/write within a specific sector.
  //If a different sector is being authenticated access to the previous one is lost.


  /*****************************************reading a block***********************************************************/
        
  byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size... 
  status = frc->MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
          Serial.print("MIFARE_read() failed: ");
          Serial.println((const char*)frc->GetStatusCodeName(status));
          return 4;//return "4" as error message
  }
  Serial.print("block was read: ");
  Serial.println(blockNumber);
  return 0;
}

int cardman_filldata(MFRC522 *frc, cardmanData *data) {

    byte blockbuffer[18];
    if(cardman_readBlock(frc, 4, blockbuffer) != 0) return 1;
    data->cardType = blockbuffer[8];
    if(data->cardType == 0) return 0;

    data->playMode = blockbuffer[9];
    data->trackNr  = blockbuffer[10];

    if(data->cardType == 17 || data->cardType == 18) {
        if(cardman_readBlock(frc, 5, blockbuffer) != 0) return 1;
        memcpy(&data->uuid, &blockbuffer, 16);
        base64url_encode((unsigned char *)data->uuid, 16, data->uuid64);  
        Serial.print("Cardman UUID: ");
        Serial.println(data->uuid64);
    }
    if(data->cardType != 173) {
        int pos = 0;
        for (int s = 2; s <= 6; s++) {
            for (int b = 0; b <= 2; b++) {           
                if(pos>=192) return 2;
                if(cardman_readBlock(frc, (s * 4) + b , blockbuffer) != 0) return 1;
                memcpy(&data->uri[pos], &blockbuffer, 16);          
                if(blockbuffer[0] == 0) return 0;
                if(blockbuffer[15] == 0) return 0;
                pos+=16;
            }
        }
        Serial.print("Cardman URI: ");
        Serial.println(data->uri);
    }

    return 0; 
}