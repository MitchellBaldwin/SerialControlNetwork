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

		// 0x10 - ox1F : Request report commands
		static const uint8_t GetMRSStatus = 0x00;
		
		static const uint8_t GetDSMCUStatus = 0x04;

		// 0x20 - 0x2F : Power System commands

		// 0x40 - ox4F : Drive Ssytem commands
		static const uint8_t DSMCUDriveSettings = 0x40;
		static const uint8_t DSMCUDriveConfiguration = 0x41;

		// 0xF0 - oxFF : Diagnostic / test commands
		static const uint8_t ToggleBuiltInLED = 0xF8;
		static const uint8_t TestPacketTransfer = 0xF9;
		static const uint8_t GetTestTextMessage = 0xFA;
		static const uint8_t TestLocalDisplay = 0xFB;
		static const uint8_t TestMotors = 0xFC;

};
