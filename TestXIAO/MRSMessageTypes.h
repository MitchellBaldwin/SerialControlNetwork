/*	MRSMessageTypes - Class mapping identifier codes for MRS messages
*
*
*	Mitchell Baldwin copyright 2020
*
*	v 0.00:	Initial message code set
*	v
*
*/

#ifndef _MRSMESSAGETYPES_h
#define _MRSMESSAGETYPES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class MRSMessageTypes
{
	private:

	protected:

	 public:

		 static const uint8_t MRSStatusPacket = 0x00;

		 static const uint8_t DSMCUStatusPacket = 0x04;

		 static const uint8_t MRSTextMessage = 0x0F;
		 
};

#endif

