/*	TrellisKeypadClass - Base class for interfacing with the Adafruit Trellis 4x4 lighted keypad
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

#ifndef _TRELLISKEYPAD_h
#define _TRELLISKEYPAD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "JSBKeypad.h"
#include <Adafruit_Trellis.h>

// Connect Trellis Vin to 5V and Ground to ground
// Connect the INT wire to pin #A2 (can change later!):
#define TRELLISINTPIN 4		// GPIO4
// Connect I2C SDA pin to your Arduino SDA line
// Connect I2C SCL pin to your Arduino SCL line
// All Trellises share the SDA, SCL and INT pin! 
// Even 8 tiles use only 3 wires max

// Total number of keys:
#define numKeys 16

class TrellisKeypadClass: public JSBKeypadClass
{
protected:
	uint8_t I2CAddress = 0x00;
	uint8_t lastKeyPressed;


public:
	 
	Adafruit_Trellis Keypad;
	void Init(uint8_t address);
	bool Test();
	bool KeyPressed();
	KeyTypes GetLastKeyPressed();
};

extern TrellisKeypadClass TrellisKeypad;

#endif

