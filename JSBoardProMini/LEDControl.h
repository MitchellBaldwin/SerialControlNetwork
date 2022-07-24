// LEDControl.h

#ifndef _LEDCONTROL_h
#define _LEDCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void BuiltinLEDOFF(void);
void BuiltinLEDON(void);
void BuiltinLEDToggle(void);

void BuiltinLEDTest(void);

#endif