// 
// 
// 

#include "TrellisKeypad.h"

void TrellisKeypadClass::Init()
{
	// Initialize Trellis INT pin; requires a pullup
	pinMode(TRELLISINTPIN, INPUT);
	digitalWrite(TRELLISINTPIN, HIGH);

	// Create single instance of the Trellis keypad class
	Keypad = Adafruit_Trellis();

	TrellisKeypad.Keypad.begin(0x70);  // only one
	
}

bool TrellisKeypadClass::Test()
{
	// light up all the LEDs in order
	for (uint8_t i = 0; i < numKeys; i++) {
		Keypad.setLED(i);
		Keypad.writeDisplay();
		delay(50);
	}
	// then turn them off
	for (uint8_t i = 0; i < numKeys; i++) {
		Keypad.clrLED(i);
		Keypad.writeDisplay();
		delay(50);
	}

	return true;
}


TrellisKeypadClass TrellisKeypad;

