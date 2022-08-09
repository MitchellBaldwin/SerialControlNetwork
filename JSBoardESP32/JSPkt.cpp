/*	JSBPktClass - Base class for maintaining dynamic measurements and user control states
*
*	Mitchell Baldwin copyright 2022
*
*/

#include "JSPkt.h"

JSPktClass::JSPktClass()
{
	DrvJSX = 2048;
	DrvJSY = 2048;
	PTJSX = 2048;
	PTJSY = 2048;
	DFR4x4KPRaw = 0x0000;
	ButtonStates = 0x0000;
}

JSPktClass JSPkt;

