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


void startWiFi(){
  displayText("WiFi init",true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    displayText("WiFi connect...",true);
  }
  displayText("WiFi OK",true);
}

void setup() {
  timeInitiated=false;
  
  Serial.begin(115200);
  startDisplay();
  startWiFi();  
  
  delay(250);
  clearDisplay();
  
  startTime();
}


void loop() {
  displayTime();
  if (analogRead(0)<300) setBrightness(0x00); else setBrightness(0xff);
  
  delay(100);
}
