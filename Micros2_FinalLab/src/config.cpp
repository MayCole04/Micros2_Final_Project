#include "config.h"




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