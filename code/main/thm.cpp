#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"

OneWire oneWire(THM_PIN);
DallasTemperature sensors(&oneWire);

void startThm(){
  sensors.begin();
  delay(100);
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");
}
float getThm(){
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  if(tempC != DEVICE_DISCONNECTED_C){
    return tempC;
  } 
  else{
    return 0.0/0.0;
  }
}
