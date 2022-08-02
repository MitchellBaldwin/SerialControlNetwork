// Trellis.h

#ifndef _TRELLIS_h
#define _TRELLIS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/***************************************************
   The Adafruit Trellis parts of this example show reading buttons and
   setting/clearing buttons in a loop
   "momentary" mode has the LED light up only when a button is pressed
   "latching" mode lets you turn the LED on/off when pressed

   Up to 8 matrices can be used but this example will show 4 or 1
  ****************************************************/

#include <Adafruit_Trellis.h>

#define MOMENTARY 0
#define LATCHING 1
  // set the mode here
#define MODE LATCHING 

Adafruit_Trellis matrix0 = Adafruit_Trellis();
// uncomment the below to add 3 more matrices
/*
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();
// you can add another 4, up to 8
*/

// Just one
Adafruit_TrellisSet trellis = Adafruit_TrellisSet(&matrix0);
// or use the below to select 4, up to 8 can be passed in
//Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

// set to however many you're working with here, up to 8
#define NUMTRELLIS 1

#define numKeys (NUMTRELLIS * 16)

// Connect Trellis Vin to 5V and Ground to ground.
// Connect the INT wire to pin #A2 (can change later!)
#define TRELLISINTPIN A2
// Connect I2C SDA pin to your Arduino SDA line
// Connect I2C SCL pin to your Arduino SCL line
// All Trellises share the SDA, SCL and INT pin! 
// Even 8 tiles use only 3 wires max

void InitTrellis(void);
void ReadAndUpdateControls(void);

#endif

