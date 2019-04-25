#include "config.h"
#include "debug.h"

void debugLog(String unit, String msg, int levelNeeded){
	if (levelNeeded>DEBUG_LEVEL) return;
	Serial.println(unit+": "+msg);
	//TODO: something more ambitious
}