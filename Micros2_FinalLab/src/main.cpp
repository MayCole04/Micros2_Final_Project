#include "config.h"
#include "TJpg_Decoder.h"
#include "Wifi_setup.h"
#include "images.h"
#include "SPIFFS.h"
#include "authorizeSpotify.h"
#include "fetchSpotify.h"
#include "landingPage.h"
#include "jsonParse.h"
#include "player.h"
#include "mechanics.h"
#include <TFT_eSPI.h>
#include <SPI.h>




 TFT_eSPI tft = TFT_eSPI();
bool play = false;
 
void setup(){
  config_LCD(tft);
  //setupWifi();
  tft.setTextColor(TFT_BLACK);
  tft.fillScreen(TFT_WHITE);
  tft.pushImage(25, 90, 30, 29, rewind_button);
  tft.pushImage(75, 90, 30, 29, foward_button);
   tft.pushImage(50, 90, 30, 29, play_button);
  
   
   
}




int vol;
int temp_vol;

void loop(){
 

if(digitalRead(button2_pin) ==1){
  delay(10);
  if(digitalRead(button2_pin) ==1){
    bool press = 1;
    while(press){
      if(digitalRead(button2_pin) ==0){
        delay(10);
        if(digitalRead(button2_pin) ==0)
          press =0;
    }
  }
    play = !play;
    if(play){
      tft.pushImage(50, 90, 30, 29, pause_button);
      delay(25);
    }
    if(!play){
      tft.pushImage(50, 90, 30, 29, play_button);
      delay(25);
    }
  }
  }
 vol =(analogRead(pot_pin)+1)/40.96;
  if(vol != temp_vol){
    tft.setTextColor(TFT_WHITE);
    tft.printf("Volume: %d", temp_vol );
    temp_vol = vol;

  }
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(0, 0, 2);
  tft.printf("Volume: %d", vol );
  tft.setCursor(0, 0, 2);
   


  







  // Set "cursor" at top left corner of display (0,0) and select font 2
 
   

 

  /* // Set the font colour to be white with a black background
  tft.setTextColor(TFT_WHITE);

  // We can now plot text on screen using the "print" class
  tft.println(" Initialised default\n");
  tft.println(" White text");
  
  tft.setTextColor(TFT_RED);
  tft.println(" Red text");
  
  tft.setTextColor(TFT_GREEN);
  tft.println(" Green text");
  
  tft.setTextColor(TFT_BLUE);
  tft.println(" Blue text");
  */ 
}


void setup() {
  Serial.begin(115200);
  while (!Serial) { // Wait for serial to initialize
    delay(100);
  }

  requestUserAuthorization(); //Request user authorization from the Spotify API

  configureLandingPage(); //Configure landing page for user to navigate to to authorize the app
  tft.drawString("Type the following" , 10, 10);
  tft.drawString("IP address into your", 10, 20);
  tft.drawString("browser: ", 10, 30);
  tft.drawString(IP_ADDRESS, 10, 50); 

  setupWebServerForAuth(); //Setup the web server

  while (!authComplete) { //Wait for the user to authorize the app
    server.handleClient();
  }

  requestAccessToken(spotifyCode); //Request an access token from the Spotify API
  parseAvailableDevices(fetchAvailableDevices());

}

void loop() {
  static unsigned long lastPlayPauseTime = 0; // Cooldown period in milliseconds
  static unsigned long lastPreviousTime = 0;
  static unsigned long lastNextTime = 0;
  static unsigned long lastVolumeChangeTime = 0;

  static uint16_t lastVolumeValue = 100; // previously
  static String lastSong = "";
  const unsigned long apiCooldown = 500; // Cooldown period in milliseconds

  playbackStateJson = getCachedPlaybackState(); // Constantly update/cache the playback state from the Spotify API

  if (songChange(lastSong, playbackStateJson)) {
    updateScreen(playbackStateJson);
  }

  currentVolumeValue = readAndMapVolumeValue();

  if (abs(lastVolumeValue - currentVolumeValue) > 10) {
    putVolumeChange(currentVolumeValue); //Make request to spotify to change the volume
    lastVolumeValue = currentVolumeValue; //Update the last volume value
  }

  lastSong = parseLastSong(playbackStateJson);

  if (previousButtonPressed()) {
      unsigned long currentTime = millis();
      if (currentTime - lastPreviousTime > apiCooldown) {
          previousSong();
          playbackStateJson = fetchPlaybackState(); // Get updated playback-state when song is changed
          lastPreviousTime = currentTime;
      } else {
          Serial.println("API call ignored due to cooldown");
      }
  }

  if (playPauseButtonPressed()) {
      unsigned long currentTime = millis();
      if (currentTime - lastPlayPauseTime > apiCooldown) {
          playPauseSong(playbackStateJson);
          playBox(tft.width() / 2 - 10, tft.height() - 30, spriteX, spriteY, isPlaying);
          lastPlayPauseTime = currentTime;
      } else {
          Serial.println("API call ignored due to cooldown");
      }
  }

  if (nextButtonPressed()) {
      unsigned long currentTime = millis();
      if (currentTime - lastNextTime > apiCooldown) {
          nextSong();
          playbackStateJson = fetchPlaybackState(); // Get updated playback-state when song is changed
          lastNextTime = currentTime;
      } else {
          Serial.println("API call ignored due to cooldown");
      }
  }
  
}

bool outputTFT(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
 if (x > tft.width() || y > tft.height()) {
   return false;
 }
 tft.pushImage(x, y, w, h, bitmap);
 return true;
}

void displayJPEG() {
  if (imageBuffer) {
    TJpgDec.setCallback(outputTFT);
    TJpgDec.setSwapBytes(true);
    TJpgDec.drawJpg(tft.width() / 4, tft.height() / 10, imageBuffer, imageSize);

    free(imageBuffer);
    imageBuffer = nullptr;
  } 
}

void playBox(int x, int y, int spritex, int spritey, bool isPlaying) {
  Serial.println("isPlaying in playBox: " + String(isPlaying));
  playPauseImg.createSprite(spritex, spritey);

  if (isPlaying) {
    playPauseImg.fillSprite(TFT_BLACK);

    uint8_t rectWidth = spritex / 5;
    uint8_t rectSpacing = spritex / 8;

    playPauseImg.fillRect(rectSpacing, 0, spritey / 3, spritey, TFT_WHITE);
    playPauseImg.fillRect(spritex - rectWidth - rectSpacing, 0, spritey / 3, spritey, TFT_WHITE);
  } else {
    playPauseImg.fillSprite(TFT_BLACK);
    playPauseImg.fillTriangle(0, 0, 0, spritex, spritey, spritey / 2, TFT_WHITE);
  }

  playPauseImg.pushSprite(x, y);
  playPauseImg.deleteSprite();
} 

void updateScreen(String playbackStateJson) {

  //parseAvailableDevices(fetchAvailableDevices());
  tft.fillScreen(TFT_BLACK);
  parseImageUrl(playbackStateJson);

  if (fetchAndStoreImage(imageUrl)) {
    displayJPEG();
  }

  parseSong(playbackStateJson);
  parseArtists(playbackStateJson);
  
  tft.drawString(song, (tft.width() / 2) - (song.length() / 2) * 6, tft.height() - 55);
  tft.drawString(artists, (tft.width() / 2) - (artists.length() / 2) * 6, tft.height() - 43);
  playBox(tft.width() / 2 - 10, tft.height() - 30, spriteX, spriteY, isPlaying);
}