/*	JSBLocalDisplayClass - Base class for implementing paged graphical display interface for joystick,
*	keypad and other physical user controls used for remote control of mobile robot systems.
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

#ifndef _JSBLOCALDISPLAY_h
#define _JSBLOCALDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "JSPkt.h"
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_GFX.h>
#include <splash.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128	// OLED display width, in pixels
#define SCREEN_HEIGHT 64	// OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1	// Reset pin # (or -1 if sharing Arduino reset pin)

const char sysPageTitle[] = "MRS RC CSS JSB System";
const char sysPageMenu[] = "<NONE    SYS     POW>";
const char powPageTitle[] = "MRS RC CSS JSB Power";
const char powPageMenu[] = "<SYS     POW     COM>";
const char comPageTitle[] = "MRS RC CSS JSB Comms";
const char comPageMenu[] = "<POW     COM     I2C>";
const char i2cPageTitle[] = "MRS RC CSS   JSB I2C";
const char i2cPageMenu[] = "<COM     I2C     nxt>";

class JSBLocalDisplayClass
{
 protected:
	 Adafruit_SSD1306 display;
	 uint8_t I2CAddress = 0x00;
	 char buf[32];

	 enum Pages
	 {
		 SYS,
		 POW,
		 COM,
		 I2C,

		 NONE
	 };
	 Pages currentPage = SYS;
	 Pages lastPage = NONE;		// Aid to determine when a complete page redraw is needed

	 void DrawSYSPage();
	 void DrawPOWPage();
	 void DrawCOMPage();
	 void DrawI2CPage();

	 void DrawNONEPage();

 public:
	 enum Commands
	 {
		 Clear,
		 Refresh,
		 SYSPage,
		 POWPage,
		 COMPage,
		 I2CPage,
		 Prev,
		 Next,

		 Last
	 };

	 JSBLocalDisplayClass();		// Default constructor
	 void Init(uint8_t address);
	 bool Test();
	 void Update();
	 void Control(uint8_t command);

};

extern JSBLocalDisplayClass JSBLocalDisplay;

#endif

