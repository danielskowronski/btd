#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef ntp_h
#define ntp_h

#define byte uint8_t
extern int ntpLimiter;
#define NTP_PACKET_SIZE 48
extern byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
extern WiFiUDP Udp;

void startTime();
time_t getNtpTime();
void sendNTPpacket(IPAddress &address);

#endif
