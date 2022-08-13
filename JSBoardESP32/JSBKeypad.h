// JSBKeypad.h

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
	 
		//void init();
};

//extern JSBKeypadClass JSBKeypad;

#endif

