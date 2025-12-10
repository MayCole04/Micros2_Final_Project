#include "config.h"
#include "TJpg_Decoder.h"
#include "Wifi_setup.h"
#include "images.h"
#include "SPIFFS.h"


 TFT_eSPI tft = TFT_eSPI();
bool play = false;
 
 void setup(){
  config_LCD(tft);
  //setupWifi();
  tft.setTextColor(TFT_BLACK);
  tft.fillScreen(TFT_WHITE);
  //tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN);
  

  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
 
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
      while(digitalRead(button2_pin)==1); 
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
   


  
}






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