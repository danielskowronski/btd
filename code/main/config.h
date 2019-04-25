#ifndef config_h
#define config_h

#include <Timezone.h> 

//OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//NTP
#define ntpServerName "0.pool.ntp.org"
#define UDP_LOCAL_PORT 9999
#define NTP_CONSEQ_REQ_LIMIT 128
static TimeChangeRule summerRule = {"CEST", Last, Sun, Mar, 2, +120};
static TimeChangeRule winterRule = { "CET", Last, Sun, Oct, 3, +60};
static Timezone userTZ(winterRule, summerRule);

//IO Pinout
#define ANALOG_PIN 0
#define IR_PIN 14
#define THM_PIN 2 //only one for OneWire on this board? definitely 16 is broken

//Other
#define LIGHT_THRESHOLD 300
#define TIME_BETWEEN_DATA_PUSHPULL 300
#define DEBUG_LEVEL -1

#endif
