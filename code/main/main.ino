#include <ESP8266WiFi.h>
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
#include "thm.h"
#include "light.h"

void startWiFi(){
  displayText("WiFi init",true);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    displayText("WiFi connect...",true);
  }
  displayText("WiFi OK",true);
}

#define sceneModulo 4
enum displayScene{
  clockScene=0,extSensorScene=1,intSensorScene=2,aboutScene=3
} currentScene;

void setup() {
  timeInitiated=false;
  int val=analogRead(ANALOG_PIN);
  Serial.begin(115200);
  startThm();
  startRemoteControl();
  startDisplay();
  startWiFi();  
  
  delay(250);
  clearDisplay();
  
  startTime();
}


int loopSkipCounterDataGet=999999; 

void loop() {
  if (shallScreenBeDarker()) setScreenDark(); else setScreenBright();
  
  parseRemoteControl();
       if (nextCommand==prev) currentScene=(displayScene)(((int)currentScene-1)%sceneModulo);
  else if (nextCommand==next) currentScene=(displayScene)(((int)currentScene+1)%sceneModulo);
  if (currentScene<0) currentScene=(displayScene)(sceneModulo+currentScene);
  if (nextCommand!=noop) clearDisplay();
  nextCommand=noop;

  if (currentScene==clockScene)     displayTime();
  if (currentScene==extSensorScene) displayExtSensors();
  if (currentScene==intSensorScene) displayIntSensors();
  if (currentScene==aboutScene)     displayAbout();

  if (loopSkipCounterDataGet>TIME_BETWEEN_DATA_PUSHPULL){
    getLuftdatenData();
    
    loopSkipCounterDataGet=0;
  }
  else{
    loopSkipCounterDataGet++;
  }
  
  delay(200);
}
