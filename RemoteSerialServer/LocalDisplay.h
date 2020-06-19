/*	LocalDisplayClass - Class implementing handlers for a local display associated with and likely
*	located with the MCU controlling communications with an embedded module
*
*	Supported displays include:
*		Sparkfun Micro OLED Breakout (Qwiic) LCD-14532
*
*	Mitchell Baldwin copyright 2020
*
*	v 0.00:	Initial command set
*	v
*
*/

#ifndef _LOCALDISPLAY_h
#define _LOCALDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <wire.h>
#include <SFE_MicroOLED.h>

// The SFE_MicroOLED library assumes a reset pin is necessary. 
// The Qwiic OLED has RST hard-wired, so pick an arbitrarty IO pin that is NOT BEING USED
#define PIN_RESET 9  

// The DC_JUMPER is the I2C Address Select jumper. 
// Set to 1 if the jumper is open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1

class LocalDisplayClass
{
 protected:

	 MicroOLED oled = MicroOLED(PIN_RESET, DC_JUMPER);


 public:
	void init();

	bool RunFont0Demo();

	void Print(String);

};

extern LocalDisplayClass LocalDisplay;

#endif

