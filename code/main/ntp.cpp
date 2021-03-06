// based ojn example from TimeLib.h -> https://github.com/PaulStoffregen/Time/blob/master/examples/TimeNTP_ESP8266WiFi/TimeNTP_ESP8266WiFi.ino

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include <TimeLib.h>
#include "config.h"
#include "secrets.h"
#include "global.h"
#include "display.h"
#include "ntp.h"
#include "ir.h"
#include "debug.h"

int ntpLimiter=0;
bool timeInitiated=false;
WiFiUDP Udp;
byte packetBuffer[NTP_PACKET_SIZE];

void startTime(){
  Udp.begin(UDP_LOCAL_PORT);
  setSyncProvider(getNtpTime);
  setSyncInterval(3600);
}

time_t getNtpTime(){
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  displayText("NTP requested         ");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  debugLog("getNtpTime()",String(ntpServerName),0,true); //see "preNTP note" in debug.cpp
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 2500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      displayText("NTP received    ");
      delay(500);
      displayText("                ");
      timeInitiated=true;
      ntpLimiter=0;
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      debugLog("getNtpTime()","secsSince1900="+String(secsSince1900),0,true); //see "preNTP note" in debug.cpp
      return secsSince1900 - 2208988800UL; //+ timeZone * SECS_PER_HOUR;
    }
  }
  displayText("NTP failed!                  ");
  debugLog("getNtpTime()","no NTP response",0,true); //see "preNTP note" in debug.cpp
  ntpLimiter++; 
  if (ntpLimiter<=NTP_CONSEQ_REQ_LIMIT) {
    delay(ntpLimiter*500);
    getNtpTime();
  }
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address){
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
