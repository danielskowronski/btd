#include <SPI.h> //analogRead defined there
#include "config.h"

int readLight(){
  int val=analogRead(ANALOG_PIN);
  return val;
}
bool shallScreenBeDarker(){
  return readLight()<LIGHT_THRESHOLD;
}
