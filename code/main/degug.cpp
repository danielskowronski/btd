#include <TimeLib.h>
#include <stdio.h>
#include "config.h"
#include "debug.h"

void debugLog(String unit, String msg, int levelNeeded, bool preNTP){
	if (levelNeeded>DEBUG_LEVEL) return;
	
	char datetime[18]={0};
	if (!preNTP){
		/* preNTP note:
		   if we set getTimePtr to getNtpTime in TimeLib then 
		   getNtpTime may be called when this func is run
		   (especially on first time retrieval)
		   which leads to endless recursion
		*/
		sprintf(datetime,"[%02d/%02d %02d:%02d:%02d] ",month(),day(),hour(),minute(),second());
	}

	Serial.println(String(datetime)+unit+": "+msg);
}