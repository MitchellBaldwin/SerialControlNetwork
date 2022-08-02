/*
 Name:		JSBoardProMini.ino
 Created:	7/23/2022 3:55:16 PM
 Author:	Mitchell Baldwin
*/
#include "JSBLocalDisplay.h"
#include "Trellis.h"
#include "LEDControl.h"
#include <Tasks.h>
#include <Wire.h>

//uint16_t DrvJSX, DrvJSY, PTJSX, PTJSY;

constexpr auto PPM5VENAPIN = 4;
constexpr auto DRVJSBTNPIN = 6;
constexpr auto PTJSBTNPIN = 5;

#define LOCALDISPLAY_I2C_ADDRESS 0x3C

void ReadAndUpdateControls(void)
{
	ReadJoysticks();
	
	JSBLocalDisplay.Update();
	
	if (MODE == MOMENTARY) {
		// If a button was just pressed or released...
		if (trellis.readSwitches()) {
			// go through every button
			for (uint8_t i = 0; i < numKeys; i++) {
				// if it was pressed, turn it on
				if (trellis.justPressed(i)) {
					Serial.print("v"); Serial.println(i);
					trellis.setLED(i);
				}
				// if it was released, turn it off
				if (trellis.justReleased(i)) {
					Serial.print("^"); Serial.println(i);
					trellis.clrLED(i);
				}
			}
			// tell the trellis to set the LEDs we requested
			trellis.writeDisplay();
		}
	}

	if (MODE == LATCHING) {
		// If a button was just pressed or released...
		if (trellis.readSwitches()) {
			// go through every button
			for (uint8_t i = 0; i < numKeys; i++) {
				// if it was pressed...
				if (trellis.justPressed(i)) {
					Serial.print("v"); Serial.println(i);
					// Alternate the LED
					if (trellis.isLED(i))
						trellis.clrLED(i);
					else
						trellis.setLED(i);
					if (i == 0)
					{
						JSBLocalDisplay.Control(JSBLocalDisplayClass::Clear);
					}
					else if (i == 1)
					{
						JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);
					}
					//else if (i == 2)
					//{
					//	JSBLocalDisplay.Control(JSBLocalDisplayClass::POWPage);
					//}
				}
			}
			// tell the trellis to set the LEDs we requested
			trellis.writeDisplay();
		}
	}
}

void ReadJoysticks()
{
	JSPkt.DrvJSX = analogRead(A0) - 512;
	JSPkt.DrvJSY = analogRead(A1) - 512;
	JSPkt.PTJSX = analogRead(A6) - 512;
	JSPkt.PTJSY = analogRead(A7) - 512;

	if (!digitalRead(DRVJSBTNPIN))
	{
		trellis.setLED(0);
		trellis.writeDisplay();
	}

}

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PPM5VENAPIN, OUTPUT);
	digitalWrite(PPM5VENAPIN, HIGH);		// Enable power from Pololu regulator by default

	// Initialize joystick buttons
	pinMode(DRVJSBTNPIN, INPUT_PULLUP);		// Check whther joystick buttons have their own pull-up resistors
	pinMode(PTJSBTNPIN, INPUT_PULLUP);

	JSBLocalDisplay.Init(LOCALDISPLAY_I2C_ADDRESS);
	// Normal operation; blink LED at 0.5 Hz:
	int16_t BuiltinLEDOnTime = 1000;
	//if (!JSBLocalDisplay.Test())
	//{
	//	// Local display initialization failed; blink LED at 2 Hz:
	//	BuiltinLEDOnTime = 250;
	//}
	//JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);

	Serial.begin(115200);
	while (!Serial);
	Serial.println("JS Board");

	// Initialize Trellis INT pin; requires a pullup
	pinMode(TRELLISINTPIN, INPUT);
	digitalWrite(TRELLISINTPIN, HIGH);

	//begin() with the addresses of each panel in order
	//I find it easiest if the addresses are in order
	trellis.begin(0x70);  // only one
	//trellis.begin(0x70, 0x71, 0x72, 0x73);  // or four!

	// light up all the LEDs in order
	for (uint8_t i = 0; i < numKeys; i++) {
		trellis.setLED(i);
		trellis.writeDisplay();
		delay(50);
	}
	// then turn them off
	for (uint8_t i = 0; i < numKeys; i++) {
		trellis.clrLED(i);
		trellis.writeDisplay();
		delay(50);
	}

	Tasks_Init();
	Tasks_Add((Task)BuiltinLEDToggle, BuiltinLEDOnTime, 0);
	Tasks_Add((Task)ReadAndUpdateControls, 100, 0);
	Tasks_Start();

}
void loop()
{
  
}
