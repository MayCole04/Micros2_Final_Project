#ifndef CONFIG_H
#define CONFIG_H

#include <HardwareSerial.h>
#include <SPI.h>
#include <TFT_eSPI.h> 
#include <Arduino.h>
#include "Wifi_Setup.h"      // Hardware-specific library
#define CS_PIN 5 // GPIO 5


// Spotify credentials for authorization
extern const char* CLIENT_ID;
extern const char* CLIENT_SECRET;
extern String REDIRECT_URI;
extern const char* RESPONSE_TYPE;
extern const char* SCOPE;
extern const char* SPOTIFY_API_URL;
extern String SPOTIFY_ACCESS_TOKEN;
extern const char* GRANT_TYPE;
extern String deviceId;
extern String authorizeUrl;
extern uint16_t analogInputValue;
extern uint16_t currentVolumeValue;

const int ledPin = 2;
const int button3_pin =4;
const int MOSI_pin =23;
const int SCK_pin =18;
const int CS_pin = 5;
const int DC_pin =22;
const int LED_pin =14;
const int RESET_pin =27;
const int button2_pin = 16;
const int button1_pin = 17;
const int pot_pin = 15;

void config_LCD(TFT_eSPI tft);
void config_IO();


    #endif // CONFIG_H