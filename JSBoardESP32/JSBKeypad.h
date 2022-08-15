/*	JSBKeypadClass - Base class for interfacing with keypads such as the 
*	Adafruit Trellis 4x4 lighted keypad the RobotDyn 4x4 analog keypad
*
*
*
*
*	Mitchell Baldwin copyright 2022
*
*	v 0.00:	Initial command set
*	v
*
*/

#ifndef _JSBKEYPAD_h
#define _JSBKEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class JSBKeypadClass
{
	protected:


	public:
		enum KeyTypes
		{
			ClearKey,
			SystemKey,
			PowerKey,
			CommsKey,
			EnterKey,
			I2CKey,
			EnableKey,
			nRF24L01Key,
			NextKey,
			NineKey,
			WiFiKey,
			SWSerialKey,
			PreviousKey,
			DKey,
			BacklightKey,
			HWSerialKey
		};
	 
		//void Init();
};

//extern JSBKeypadClass JSBKeypad;

#endif

