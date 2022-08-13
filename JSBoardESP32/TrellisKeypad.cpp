/*	TrellisKeypadClass - Base class for interfacing with the Adafruit Trellis 4x4 lighted keypad
*
*
*
*
*	Mitchell Baldwin copyright 2022
*
*/

#include "TrellisKeypad.h"

void TrellisKeypadClass::Init(uint8_t address)
{
	// Initialize Trellis INT pin; requires a pullup
	pinMode(TRELLISINTPIN, INPUT);
	digitalWrite(TRELLISINTPIN, HIGH);

	// Create single instance of the Trellis keypad class
	Keypad = Adafruit_Trellis();

	I2CAddress = address;
	Keypad.begin(I2CAddress);  // only one
	
}

bool TrellisKeypadClass::Test()
{
	Wire.beginTransmission(I2CAddress);
	bool error = Wire.endTransmission();
	if (error) return false;

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
	bool newKeyPressed = false;
	// If a button was just pressed or released...
	if (Keypad.readSwitches())
	{
		// go through every button
		for (uint8_t i = 0; i < numKeys; i++) {
			// if it was pressed...
			if (Keypad.justPressed(i)) {
				// Toggle the LED for the key just pressed:
				if (Keypad.isLED(i))
					Keypad.clrLED(i);
				else
					Keypad.setLED(i);
				newKeyPressed = true;
				lastKeyPressed = i;
			}
		}
		//// DEBUG - Show key code in serial monitor:
		////String keypadMessage = "Key pressed: " + lastKeyPressed;
		//if (newKeyPressed)
		//{
		//	Serial.printf("Key pressed: %d", lastKeyPressed);
		//	Serial.println();

		//}

		// Tell the trellis to set the LEDs we requested
		Keypad.writeDisplay();
	}
	return newKeyPressed;
}

JSBKeypadClass::KeyTypes TrellisKeypadClass::GetLastKeyPressed()
{
	return (KeyTypes)lastKeyPressed;
}


TrellisKeypadClass TrellisKeypad;

