#include <ESP8266HTTPClient.h>
#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <SPI.h>
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


void displayAbout(){
  displayText("BTD by dskowronski",true);
}
