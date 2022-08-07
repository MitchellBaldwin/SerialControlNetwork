/*	TrellisKeypadClass - Base class for interfacing with the Adafruit Trellis 4x4 lighted keypad
*
*
*
*
*	Mitchell Baldwin copyright 2022
*
*/

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

bool TrellisKeypadClass::KeyPressed()
{
	// If a button was just pressed or released...
	if (Keypad.readSwitches()) {
		// go through every button
		for (uint8_t i = 0; i < numKeys; i++) {
			// if it was pressed...
			if (Keypad.justPressed(i)) {
				//Serial.print("v"); Serial.println(i);
				// Alternate the LED
				if (Keypad.isLED(i))
					Keypad.clrLED(i);
				else
					Keypad.setLED(i);
				lastKeyPressed = i;
			}
		}
		// tell the trellis to set the LEDs we requested
		Keypad.writeDisplay();
		return true;
	}
	else return false;
}

uint8_t TrellisKeypadClass::GetLastKeyPressed()
{
	return lastKeyPressed;
}


TrellisKeypadClass TrellisKeypad;

