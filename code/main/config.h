#ifndef config_h
#define config_h

//OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//NTP
#define ntpServerName "0.pool.ntp.org"
#define timeZone 1
#define UDP_LOCAL_PORT 9999
#define NTP_CONSEQ_REQ_LIMIT 64

//IO Pinout
#define ANALOG_PIN 0
#define IR_PIN 14
#define THM_PIN 16

//Other
#define LIGHT_THRESHOLD 300
#define TIME_BETWEEN_DATA_PUSHPULL 300

//45s is time set in luftdaten sensor, setting 1m here

#endif
