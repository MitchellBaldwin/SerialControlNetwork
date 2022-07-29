// 
// 
// 

#include "JSBLocalDisplay.h"

void JSBLocalDisplayClass::DrawSYSPage()
{
	currentPage = SYS;
	if (lastPage != SYS)
	{
		// Clear display and redraw page format:
		display.clearDisplay();
		display.setCursor(0, 0);
		display.cp437();
		display.setTextSize(1);
		display.write("SYS");

		lastPage = currentPage;
	}
	// Draw dynamic elements:

	display.display();
}

void JSBLocalDisplayClass::DrawPOWPage()
{
	currentPage = POW;
	if (lastPage != POW)
	{
		// Clear display and redraw page format:
		display.clearDisplay();

		lastPage = POW;
	}
	// Draw dynamic elements:

	display.display();
}

void JSBLocalDisplayClass::DrawNONEPage()
{
	currentPage = NONE;
	if (lastPage != NONE)
	{
		display.clearDisplay();
		display.display();
		lastPage = NONE;
	}
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

	currentPage = SYS;
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
	
	//switch (currentPage)
	//{
	//	case SYS:
	//	{
	//		DrawSYSPage();
	//	}
	//	case POW:
	//	{
	//		DrawPOWPage();
	//	}
	//	default:
	//	{
	//		DrawSYSPage();
	//	}
	//}
}

void JSBLocalDisplayClass::Control(uint8_t command)
{
	switch (command)
	{
		case Clear:
			display.clearDisplay();
			display.display();
			break;
		case Refresh:
			lastPage = NONE;		// Will not refresh if currentPage == NONE...
			Update();
			break;
		default:
			return;
	}
}


JSBLocalDisplayClass JSBLocalDisplay;