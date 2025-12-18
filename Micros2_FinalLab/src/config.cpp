#include "config.h"


const char *CLIENT_ID = "6b6b83e6cbce408c8dfee7b4739aec11";
const char *CLIENT_SECRET = "2d16240be38c4a0996c6635615cd77a4";
const char *RESPONSE_TYPE = "code";
const char *SCOPE = "user-modify-playback-state+user-read-playback-state+user-read-currently-playing";

const char *SPOTIFY_API_URL = "https://api.spotify.com/v1/playlists/0Oq2zrT5mCjR2iVjFl1eEN";

const char *GRANT_TYPE = "authorization_code";

void config_LCD(TFT_eSPI tft){
      // Invoke custom library
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    pinMode(MOSI_pin, OUTPUT);
    pinMode(SCK_pin, OUTPUT);
    pinMode(CS_pin, OUTPUT);
    pinMode(DC_pin, OUTPUT);
    pinMode(LED_pin, OUTPUT);
    pinMode(RESET_pin, OUTPUT);
    
    pinMode(CS_PIN, OUTPUT);
    
    digitalWrite(CS_PIN, HIGH);
    digitalWrite(LED_pin, HIGH);
    tft.init();
    
}

void config_IO(){
  pinMode(button3_pin, INPUT);
  pinMode(button2_pin, INPUT);
  pinMode(button1_pin, INPUT);
  pinMode(pot_pin, INPUT);



}