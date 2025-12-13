#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <Arduino.h>
#include <WebServer.h>
const char WIFI_SSID[11] =  "PhyllisAnn";
const char WIFI_PASSWORD[14]= "MichaelGordon";
extern WebServer server;
extern String spotifyCode;
extern bool authComplete;
extern String IP_ADDRESS;

void setupWifi(void);
void setupWebServerForAuth(void);
void handleAuthCallback(void);

#endif