/*	MRSCommandTypes - Class mapping command codes for MRS commands
*	
*
*	Mitchell Baldwin copyright 2020
*
*	v 0.00:	Initial command set
*	v
*
*/

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class MRSCommandTypes
{
	private:

	protected:

	public:

		static const uint8_t ToggleBuiltInLED = 0xF8;
		static const uint8_t TestPacketTransfer = 0xF9;
		static const uint8_t GetTestTextMessage = 0xFA;
		static const uint8_t TestLocalDisplay = 0xFB;

};
