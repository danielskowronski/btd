#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"
#include "debug.h"

OneWire oneWire(THM_PIN);
DallasTemperature sensors(&oneWire);

void startThm(){
  sensors.begin();
  delay(100);
  debugLog("startThm()",String(sensors.getDeviceCount(), DEC)+" devices");
}
float getThm(){
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  debugLog("getThm()","THM= "+String(tempC), 2);
  if(tempC != DEVICE_DISCONNECTED_C){
    return tempC;
  } 
  else{
    return 0.0/0.0;
  }
}
