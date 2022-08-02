/*	JSBPktClass - Base class for maintaining dynamic measurements and user control states
*
*	Mitchell Baldwin copyright 2022
*
*/

#include "JSPkt.h"

JSPktClass::JSPktClass()
{
	DrvJSX = 512;
	DrvJSY = 512;
	PTJSX = 512;
	PTJSY = 512;
	ButtonStates = 0x00;
}

JSPktClass JSPkt;

