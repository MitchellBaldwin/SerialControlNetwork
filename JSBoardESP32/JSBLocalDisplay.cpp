/*	JSBLocalDisplayClass - Base class for implementing paged graphical display interface for joystick,
*	keypad and other physical user controls used for remote control of mobile robot systems.
*
*	Mitchell Baldwin copyright 2022
*
*/

#include "JSBGlobals.h"
#include "JSBLocalDisplay.h"

void JSBLocalDisplayClass::DrawSYSPage()
{
	currentPage = SYS;

	if (lastPage != currentPage)
	{
		// Clear display and redraw static elements of the page format:
		display.clearDisplay();
		display.setCursor(0, 0);
		display.cp437();
		display.setTextSize(1);
		memcpy(buf, sysPageTitle, sizeof(sysPageTitle));
		display.write(buf);

		display.setCursor(0, 40);
		display.write("HWS:");
		display.setCursor(64, 40);
		display.write("SWS:");
		display.setCursor(0, 48);
		display.write("I2C:");

		display.setCursor(0, 56);
		memcpy(buf, sysPageMenu, sizeof(sysPageMenu));
		display.write(buf);

		lastPage = currentPage;
	}
	
	// Update dynamic displays:
	display.fillRect(0, 16, 128, 8, SSD1306_BLACK);
	snprintf(buf, 22, "U/D %+04d     F/R %+04d", JSPkt.PTJSY, JSPkt.DrvJSY);
	display.setCursor(0, 16);
	display.write(buf);
	display.fillRect(0, 24, 128, 8, 0x0000);
	snprintf(buf, 22, "L/R %+04d     L/R %+04d", JSPkt.PTJSX, JSPkt.DrvJSX);
	display.setCursor(0, 24);
	display.write(buf);

	display.fillRect(0, 32, 128, 8, SSD1306_BLACK);
	snprintf(buf, 22, "KP %05d", JSPkt.DFR4x4KPRaw);
	display.setCursor(0, 32);
	display.write(buf);

	display.display();
}

void JSBLocalDisplayClass::DrawPOWPage()
{
	currentPage = POW;
	if (lastPage != POW)
	{
		// Clear display and redraw static elements of the page format:
		display.clearDisplay();
		display.cp437();
		display.setTextSize(1);
		display.setCursor(0, 0);
		memcpy(buf, powPageTitle, sizeof(powPageTitle));
		display.write(buf);

		display.setCursor(0, 16);
		display.write("Vraw");
		display.setCursor(0, 24);
		display.write("5V Reg OFF/ENA");

		display.setCursor(0, 56);
		memcpy(buf, powPageMenu, sizeof(powPageMenu));
		display.write(buf);

		lastPage = currentPage;
	}
	// Draw dynamic elements:

	display.display();
}

void JSBLocalDisplayClass::DrawCOMPage()
{
}

void JSBLocalDisplayClass::DrawNONEPage()
{
	currentPage = NONE;
	display.clearDisplay();
	lastPage = NONE;
	display.display();
}

JSBLocalDisplayClass::JSBLocalDisplayClass()
{
	display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
}

void JSBLocalDisplayClass::Init(uint8_t address)
{
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin(SSD1306_SWITCHCAPVCC, address))
	{
		Serial.println(F("SSD1306 allocation failed"));
	}
	// I2C address is valid, so save it:
	I2CAddress = address;

	// Show initial display buffer contents on the screen --
	// the library initializes this with an Adafruit splash screen.
	display.display();
	delay(2000); // Pause for 2 seconds

	display.clearDisplay();					// Clear the buffer
	display.setTextSize(1);					// Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE);	// Draw white text
	display.setCursor(0, 0);				// Start at top-left corner
	display.cp437(true);					// Use full 256 char 'Code Page 437' font
	display.display();

	lastPage = NONE;
	currentPage = SYS;
}

bool JSBLocalDisplayClass::Test()
{
	Wire.beginTransmission(I2CAddress);
	bool error = Wire.endTransmission();
	if (error) return false;

	//// Check whether we can use WriteError as a means of detecting whether the display is connected and responsive
	//if (display.getWriteError() < 0)
	//{
	//	return false;
	//}
	
	display.clearDisplay();					// Clear the buffer
	display.setTextSize(1);					// Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE);	// Draw white text
	display.setCursor(0, 0);				// Start at top-left corner
	display.cp437(true);					// Use full 256 char 'Code Page 437' font

	// If all the characters will not fit on the display then the
	// library will draw what it can and the rest will be clipped.
	int16_t charCode = 0x30;				// ASCII '0'
	for (int16_t i = 0x00; i < 0x10; i++)
		for (int16_t j = 0x00; j < 0x0A; j++)
		{
			charCode = j + 0x30;
			if (charCode == '\n')	display.write(' ');
			else					display.write(charCode);
		}
	display.display();

	return true;
}

void JSBLocalDisplayClass::Update()
{
	switch (currentPage)
	{
		case SYS :
			DrawSYSPage();
			break;
		case POW :
			DrawPOWPage();
			break;
		default :
			DrawNONEPage();
	}
}

void JSBLocalDisplayClass::Control(uint8_t command)
{
	switch (command)
	{
		case Clear:
			DrawNONEPage();
			break;
		case Refresh:
			lastPage = NONE;		// Will not refresh if currentPage == NONE...
			display.clearDisplay();	// This might fix refreshing when currentPage == NONE
			Update();
			break;
		case SYSPage:
			DrawSYSPage();
			break;
		case POWPage:
			DrawPOWPage();
			break;
		case COMPage:
			DrawCOMPage();
			break;
		default:
			return;
	}
}

JSBLocalDisplayClass JSBLocalDisplay;