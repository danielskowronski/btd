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
#include "data_get.h"

void startWiFi(){
  displayText("WiFi init",true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    displayText("WiFi connect...",true);
  }
  displayText("WiFi OK",true);
}

#define sceneModulo 2
enum displayScene{
  clockScene=0,aboutScene=1
} currentScene;

void setup() {
  timeInitiated=false;
  
  Serial.begin(115200);
  startRemoteControl();
  startDisplay();
  startWiFi();  
  
  delay(250);
  clearDisplay();
  
  startTime();
}


int loopSkipCounterDataGet=999999; int loopSkipCounterDataGetLimit=5*60; //45s is time set in luftdaten sensor, setting 1m here
void loop() {
  if (analogRead(0)<300) setBrightness(0x00); else setBrightness(0xff);
  
  parseRemoteControl();
       if (nextCommand==prev) currentScene=(displayScene)(((int)currentScene-1)%sceneModulo);
  else if (nextCommand==next) currentScene=(displayScene)(((int)currentScene+1)%sceneModulo);
  if (currentScene<0) currentScene=(displayScene)(sceneModulo+currentScene);
  if (nextCommand!=noop) clearDisplay();
  nextCommand=noop;

  if (currentScene==clockScene) displayTime();
  if (currentScene==aboutScene) displayAbout();

  if (loopSkipCounterDataGet>loopSkipCounterDataGetLimit){
    getLuftdatenData();
    
    loopSkipCounterDataGet=0;
  }
  else{
    loopSkipCounterDataGet++;
  }
  
  delay(200);
}
