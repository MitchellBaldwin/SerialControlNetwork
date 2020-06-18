/*	LocalDisplayClass - Class implementing handlers for a local display
*
*
*	Mitchell Baldwin copyright 2020
*
*
*/

#include "LocalDisplay.h"

void LocalDisplayClass::init()
{
	//oled = MicroOLED(PIN_RESET, DC_JUMPER);
	
	Wire.begin();

	delay(100);
	oled.begin();    // Initialize the OLED
	oled.clear(ALL); // Clear the display's internal memory
	oled.display();  // Display what's in the buffer (splashscreen)


}

bool LocalDisplayClass::RunFont0Demo()
{
	// Demonstrate font 0. 5x8 font
	oled.clear(PAGE);     // Clear the screen
	oled.setFontType(0);  // Set font to type 0
	oled.setCursor(0, 0); // Set cursor to top-left
	// There are 255 possible characters in the font 0 type.
	// Lets run through all of them and print them out!
	for (int i = 0; i <= 255; i++)
	{
		// You can write byte values and they'll be mapped to
		// their ASCII equivalent character.
		oled.write(i);  // Write a byte out as a character
		oled.display(); // Draw on the screen
		delay(10);      // Wait 10ms
		// We can only display 60 font 0 characters at a time.
		// Every 60 characters, pause for a moment. Then clear
		// the page and start over.
		if ((i % 60 == 0) && (i != 0))
		{
			delay(500);           // Delay 500 ms
			oled.clear(PAGE);     // Clear the page
			oled.setCursor(0, 0); // Set cursor to top-left
		}
	}
	oled.clear(PAGE);
	oled.setFontType(0);
	oled.setCursor(0, 0); 
	oled.write(248);			// degree symbol
	oled.display();

	return true;
}

void LocalDisplayClass::Print(String msg)
{
	oled.println(msg);
	oled.display();
}


LocalDisplayClass LocalDisplay;

