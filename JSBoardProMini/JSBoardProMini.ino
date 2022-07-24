/*
 Name:		JSBoardProMini.ino
 Created:	7/23/2022 3:55:16 PM
 Author:	Mitchell Baldwin
*/
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_GFX.h>
#include <splash.h>
#include <Adafruit_SSD1306.h>
#include "Trellis.h"
#include "LEDControl.h"
#include <Tasks.h>
#include <Wire.h>

int DrvJSX, DrvJSY, PTJSX, PTJSY;

constexpr auto PPM5VENAPIN = 4;
constexpr auto DRVJSBTNPIN = 6;
constexpr auto PTJSBTNPIN = 5;

#define SCREEN_WIDTH 128	// OLED display width, in pixels
#define SCREEN_HEIGHT 64	// OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1	// Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void ReadTrellis(void)
{
	if (MODE == MOMENTARY) {
		// If a button was just pressed or released...
		if (trellis.readSwitches()) {
			// go through every button
			for (uint8_t i = 0; i < numKeys; i++) {
				// if it was pressed, turn it on
				if (trellis.justPressed(i)) {
					Serial.print("v"); Serial.println(i);
					trellis.setLED(i);
				}
				// if it was released, turn it off
				if (trellis.justReleased(i)) {
					Serial.print("^"); Serial.println(i);
					trellis.clrLED(i);
				}
			}
			// tell the trellis to set the LEDs we requested
			trellis.writeDisplay();
		}
	}

	if (MODE == LATCHING) {
		// If a button was just pressed or released...
		if (trellis.readSwitches()) {
			// go through every button
			for (uint8_t i = 0; i < numKeys; i++) {
				// if it was pressed...
				if (trellis.justPressed(i)) {
					Serial.print("v"); Serial.println(i);
					// Alternate the LED
					if (trellis.isLED(i))
						trellis.clrLED(i);
					else
						trellis.setLED(i);
				}
			}
			// tell the trellis to set the LEDs we requested
			trellis.writeDisplay();
		}
	}
}

void ReadJoysticks()
{
	DrvJSX = analogRead(A0);
	DrvJSY = analogRead(A1);
	PTJSX = analogRead(A6);
	PTJSY = analogRead(A7);

	if (!digitalRead(DRVJSBTNPIN))
	{
		trellis.setLED(0);
		trellis.writeDisplay();
	}

	// Serial.println(DrvJSX);
}

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	Tasks_Init();
	Tasks_Add((Task)BuiltinLEDToggle, 750, 0);
	Tasks_Add((Task)ReadTrellis, 30, 0);
	Tasks_Add((Task)ReadJoysticks, 100, 0);
	Tasks_Start();

	Serial.begin(115200);
	while (!Serial);
	Serial.println("JS Board");
	//Serial.println((uint64_t)sizeof(DrvJSX));

	// Initialize joystick buttons
	pinMode(DRVJSBTNPIN, INPUT);
	digitalWrite(DRVJSBTNPIN, HIGH);
	pinMode(PTJSBTNPIN, INPUT);
	digitalWrite(PTJSBTNPIN, HIGH);

	// Initialize Trellis INT pin; requires a pullup
	pinMode(TRELLISINTPIN, INPUT);
	digitalWrite(TRELLISINTPIN, HIGH);

	//begin() with the addresses of each panel in order
	//I find it easiest if the addresses are in order
	trellis.begin(0x70);  // only one
	//trellis.begin(0x70, 0x71, 0x72, 0x73);  // or four!

	// light up all the LEDs in order
	for (uint8_t i = 0; i < numKeys; i++) {
		trellis.setLED(i);
		trellis.writeDisplay();
		delay(50);
	}
	// then turn them off
	for (uint8_t i = 0; i < numKeys; i++) {
		trellis.clrLED(i);
		trellis.writeDisplay();
		delay(50);
	}

	//Wire.begin();
	
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
	{
		Serial.println(F("SSD1306 allocation failed"));
		for (;;); // Don't proceed, loop forever
	}
	// Show initial display buffer contents on the screen --
	// the library initializes this with an Adafruit splash screen.
	display.display();
	delay(2000); // Pause for 2 seconds
	
	display.clearDisplay();					// Clear the buffer
	display.setTextSize(1);					// Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE);	// Draw white text
	display.setCursor(0, 0);				// Start at top-left corner
	display.cp437(true);					// Use full 256 char 'Code Page 437' font

	// Not all the characters will fit on the display. This is normal.
	// Library will draw what it can and the rest will be clipped.
	for (int16_t i = 0; i < 256; i++) {
		if (i == '\n') display.write(' ');
		else          display.write(i);
	}
	display.display();
}
void loop()
{
  
}
