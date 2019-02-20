#include <Wire.h>
#include <stdio.h>
#include <TimeLib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "secrets.h"
#include "global.h"
#include "display.h"
#include "ntp.h"
#include "ir.h"
#include "thm.h"
#include "light.h"
#include "data_get.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void startDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c, (uint8_t)0x8f);
  display.setRotation(2);
  display.fillScreen(BLACK);
  display.display();
}
void setBrightness(uint8_t val){
  display.ssd1306_command(129);
  display.ssd1306_command(10);
}
void setScreenDark(){
  setBrightness(0x00); 
}
void setScreenBright(){
  setBrightness(0xff);
}
void clearDisplay(){
  display.fillScreen(BLACK);
  display.display();
}
void displayText(String txt, bool entireScreen){
  if (entireScreen){
    display.fillScreen(BLACK);
    display.setTextSize(2);
    display.setCursor(0,0);
  }
  else{
    display.setTextSize(1);
    display.setCursor(0,55);
  }
  display.setTextColor(WHITE,BLACK);
  display.print(txt);
  display.display();
}
void displayTime(){  
  int h=hour();   String hh=String(h); if (h<10) hh=" "+hh;
  int m=minute(); String mm=String(m); if (m<10) mm="0"+mm;
  
  display.setCursor(0,0);
  display.setTextColor(WHITE,BLACK);
  display.setTextSize(5);
  display.setTextWrap(true);
  
  if (!timeInitiated){
    display.setTextSize(4);
    display.setCursor(0,0); 
    display.print("NTP  error");
    display.display();
    return;
  }

  display.setCursor(0,0); display.print(hh);
  display.setCursor(68,0); display.print(mm);
  display.fillRect(59,10,6,6,WHITE);
  display.fillRect(59,22,6,6,WHITE);
  display.display();
}

void displayExtSensors(){  
  String pm10 = String(int(extPM10));
  if (int(extPM10)<100) pm10=" "+pm10;
  if (int(extPM10)<10)  pm10=" "+pm10;
  if (int(extPM10)>999) pm10="!!!";
  
  String thm = String(int(extTemp));
  if (int(extTemp)<10)  thm=" "+thm;
  if (int(extTemp)>999) thm="!!!";
  if (int(extTemp)<0 && int(extTemp)>-10)  thm=" "+thm;
  
  int curPosX=0;
  display.setCursor(curPosX, 8); display.setTextSize(2);display.print("PM10"); curPosX+=2*6*4;
  display.setCursor(curPosX, 0); display.setTextSize(3);display.print(pm10);   curPosX+=3*6*3;
  display.setCursor(curPosX, 8); display.setTextSize(1);display.print(""+String(char(0xe5))+"g"); curPosX+=1*6*1;
  display.setCursor(curPosX,16); display.setTextSize(1);display.print("/m3"); 
  
  curPosX=0;
  display.setCursor(curPosX, 32+8); display.setTextSize(2);display.print("OUT "); curPosX+=2*6*4;
  display.setCursor(curPosX, 32);   display.setTextSize(3);display.print(thm+char(0xf7)+"C");
  
  display.display();
}

void displayIntSensors(){  
  int light=readLight();
  String lightStr = String(light);
  if (light<1000) lightStr=" "+lightStr;
  if (light<100)  lightStr=" "+lightStr;
  if (light<10)   lightStr=" "+lightStr;

  int curPosX=0;
  display.setCursor(0, 8); display.setTextSize(2);display.print("LUX "); curPosX+=2*6*4;
  display.setCursor(curPosX, 0); display.setTextSize(3);display.print(lightStr); 

  display.setCursor(0, 32+8); display.setTextSize(2);display.print("BED "); curPosX+=2*6*4;
  display.setCursor(curPosX, 32); display.setTextSize(3);display.print(String(int(getThm()))+char(0xf7)+"C  ");
  Serial.println(getThm());
  display.display();
}

void displayAbout(){
  displayText("BTD by dskowronski",true);
}
