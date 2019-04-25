#include <esp8266wifi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"
#include "secrets.h"
#include "display.h"
#include "debug.h"

StaticJsonDocument<1024> doc;
float extTemp, extHumidity, extPressure, extPM10, extPM25;
HTTPClient http;

void getLuftdatenData(){
  http.begin(luftdaten_json_path);
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

  //for some reason data is always ordered like that
  extTemp=doc["sensordatavalues"][4]["value"];
  extHumidity=doc["sensordatavalues"][5]["value"];
  extPressure=doc["sensordatavalues"][6]["value"];
  extPM10=doc["sensordatavalues"][0]["value"];
  extPM25=doc["sensordatavalues"][1]["value"];

  debugLog("getLuftdatenData()", "PM10="+String(extPM10)+", PM2.5="+String(extPM25)+", temp="+String(extTemp)+", humidity="+String(extHumidity)+", pressure="+String(extPressure));
  
  http.end();
}
