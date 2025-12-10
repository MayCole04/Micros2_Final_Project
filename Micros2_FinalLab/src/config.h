#ifndef CONFIG_H
    #define CONFIG_H

    #include <HardwareSerial.h>
#include <SPI.h>
#include <TFT_eSPI.h>       // Hardware-specific library

#define CS_PIN 5 // GPIO 5
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


    #endif // CONFIG_H