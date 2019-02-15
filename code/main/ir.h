#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#ifndef ir_h
#define ir_h

extern decode_results results;

enum irCommand {
  noop,
  prev,next
};
extern irCommand nextCommand;

void parseRemoteControl();
void startRemoteControl();

#endif
