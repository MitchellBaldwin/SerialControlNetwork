// JSBLocalDisplay.h

#ifndef _JSBLOCALDISPLAY_h
#define _JSBLOCALDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
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

class JSBLocalDisplayClass
{
 protected:
	 Adafruit_SSD1306 display;

	 enum Pages
	 {
		 SYS,
		 POW,

		 NONE
	 };
	 Pages currentPage = SYS;
	 Pages lastPage = NONE;		// Aid to determine when a complete page redraw is needed

	 void DrawSYSPage();
	 void DrawPOWPage();

 public:
	 enum Commands
	 {
		 Clear,
		 Refresh,
		 Prev,
		 Next,

		 Last
	 };

	 JSBLocalDisplayClass();		// Default constructor
	 void Init(uint8_t address);
	 void Update();
	 void Control(uint8_t command);

};

extern JSBLocalDisplayClass JSBLocalDisplay;

#endif

