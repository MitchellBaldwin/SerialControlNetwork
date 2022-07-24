// 
// 
// 

#include "LEDControl.h"

void BuiltinLEDOFF(void)
{
	digitalWrite(LED_BUILTIN, LOW);
}

void BuiltinLEDON(void)
{
	digitalWrite(LED_BUILTIN, HIGH);
}

void BuiltinLEDToggle(void)
{
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void BuiltinLEDTest(void)
{
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
