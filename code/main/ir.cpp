#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <stdio.h>

#include "config.h"
#include "ir.h"

irCommand nextCommand = noop;
IRrecv irrecv(IR_PIN);
decode_results results;
void startRemoteControl(){
  irrecv.enableIRIn();
}
void parseRemoteControl(){
  if (irrecv.decode(&results)) {
    if (results.decode_type == NEC){
      long sv = results.value;
      Serial.println((long)sv, HEX);
           if (sv==(long)0xFFE21D) nextCommand=next; //row 1, right
      else if (sv==(long)0xFFA25D) nextCommand=prev; //row 1, left
      else                         nextCommand=noop;
      
    }
    irrecv.resume();
  }
 
}
