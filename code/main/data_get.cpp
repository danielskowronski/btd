#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"
#include "secrets.h"
#include "display.h"
#include "debug.h"

StaticJsonDocument<1024> doc;
float extTemp, extPM10;
HTTPClient http;

void getLuftdatenData(){
  http.begin(get_influxdb_path);
  int httpCode = http.GET();
  if (httpCode!=200){
    debugLog("getLuftdatenData()","Luftdaten HTTP "+String(httpCode));
    return;
  }
  String payload = http.getString();
  
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    debugLog("deserializeJson()", error.c_str());
    return;
  }

  extTemp=doc["results"][0]["series"][0]["values"][0][2];
  extPM10=doc["results"][0]["series"][0]["values"][0][1];

  debugLog("getLuftdatenData()", "PM10="+String(extPM10)+", temp="+String(extTemp));
  debugLog("getLuftdatenData()", doc["results"][0]["series"][0]["values"][0]);
  
  http.end();
}
