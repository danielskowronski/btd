#include <Adafruit_SSD1306.h>

#ifndef display_h
#define display_h

extern Adafruit_SSD1306 display;

void startDisplay();
void setBrightness(uint8_t val);
void setScreenDark();
void setScreenBright();
void clearDisplay();
void displayText(String txt, bool entireScreen=false);
void displayTime();
void displayExtSensors();
void displayIntSensors();

void displayAbout();

#endif
