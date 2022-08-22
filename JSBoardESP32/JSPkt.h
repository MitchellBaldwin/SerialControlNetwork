/*	JSBPktClass - Base class for maintaining dynamic measurements and user control states
*
*
*
*
*	Mitchell Baldwin copyright 2022
*
*	v 0.00:	Initial commit
*	v
*
*/

#ifndef _JSPKT_h
#define _JSPKT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class JSPktClass
{
 protected:


 public:
	 int16_t DrvJSX;
	 int16_t DrvJSY;
	 int16_t PTJSX;
	 int16_t PTJSY;
	 int16_t VIn;
	 uint16_t ButtonStates;


	 JSPktClass();		// Default constructor
};

extern JSPktClass JSPkt;

#endif

