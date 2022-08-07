/*
 Name:		JSBoardProMini.ino
 Created:	7/23/2022 3:55:16 PM
 Author:	Mitchell Baldwin
*/
#include "TrellisKeypad.h"
#include "JSBLocalDisplay.h"
#include "LEDControl.h"
#include <MemoryFree.h>
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
	
	if (TrellisKeypad.KeyPressed())
	{
		switch (TrellisKeypad.GetLastKeyPressed())
		{
			case 0:
				JSBLocalDisplay.Control(JSBLocalDisplayClass::Clear);
				break;
			case 1:
				JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);
				break;
			case 2:
				JSBLocalDisplay.Control(JSBLocalDisplayClass::POWPage);
				break;
			default:
				break;
		}
	}
	
	JSBLocalDisplay.Update();
}

void ReadJoysticks()
{
	JSPkt.DrvJSX = analogRead(A0) - 512;
	JSPkt.DrvJSY = analogRead(A1) - 512;
	JSPkt.PTJSX = analogRead(A6) - 512;
	JSPkt.PTJSY = analogRead(A7) - 512;

	if (!digitalRead(DRVJSBTNPIN))
	{
		TrellisKeypad.Keypad.setLED(0);
		TrellisKeypad.Keypad.writeDisplay();
	}

}

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PPM5VENAPIN, OUTPUT);
	digitalWrite(PPM5VENAPIN, HIGH);		// Enable power from Pololu regulator by default

	// Initialize joystick buttons
	pinMode(DRVJSBTNPIN, INPUT_PULLUP);		// Check whther joystick buttons have their own pull-up resistors
	pinMode(PTJSBTNPIN, INPUT_PULLUP);

	// Normal operation; blink LED at 0.5 Hz:
	int16_t BuiltinLEDOnTime = 1000;
	JSBLocalDisplay.Init(LOCALDISPLAY_I2C_ADDRESS);
	//if (!JSBLocalDisplay.Test())
	//{
	//	// Local display initialization failed; blink LED at 2 Hz:
	//	BuiltinLEDOnTime = 250;
	//}
	//JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);

	Serial.begin(115200);
	while (!Serial);
	Serial.println(F("JS Board"));

	TrellisKeypad.Init();
	TrellisKeypad.Test();

	Serial.print(F("Free memory = "));
	Serial.println(getFreeMemory());

	Tasks_Init();
	Tasks_Add((Task)BuiltinLEDToggle, BuiltinLEDOnTime, 0);
	Tasks_Add((Task)ReadAndUpdateControls, 100, 0);
	Tasks_Start();

}
void loop()
{
  
}
