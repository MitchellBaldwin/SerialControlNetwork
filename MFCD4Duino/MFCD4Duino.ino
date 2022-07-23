/*
 Name:		MFCD4Duino.ino
 Created:	4/27/2020 4:46:23 PM
 Author:	mitch
*/

// Define LOG_MESSAGES to a serial port to send SPE errors messages to. Do not use the same Serial port as SPE
//#define LOG_MESSAGES Serial

#define RESETLINE     30

#define DisplaySerial Serial1

//#define CommSerial SoftSerial1

const word screenWidth = 240;
const word screenHeight = 320;

#include "Picaso_Serial_4DLib.h"
#include "Picaso_Const4D.h"

Picaso_Serial_4DLib Display(&DisplaySerial);

// Uncomment to use ESP8266:

//#define ESPRESET 17
//#include <SoftwareSerial.h>
//#define ESPserial SerialS
//SoftwareSerial SerialS(8, 9) ;
//// Uncomment next 2 lines to use ESP8266 with ESP8266 library from https://github.com/itead/ITEADLIB_Arduino_WeeESP8266
////#include "ESP8266.h"
////ESP8266 wifi(SerialS,19200);

// Routine to handle Serial errors
void mycallback(int ErrCode, unsigned char Errorbyte)
{
#ifdef LOG_MESSAGES
	const char *Error4DText[] = { "OK\0", "Timeout\0", "NAK\0", "Length\0", "Invalid\0" };
	LOG_MESSAGES.print(F("Serial 4D Library reports error "));
	LOG_MESSAGES.print(Error4DText[ErrCode]);
	if (ErrCode == Err4D_NAK)
	{
		LOG_MESSAGES.print(F(" returned data= "));
		LOG_MESSAGES.println(Errorbyte);
	}
	else
		LOG_MESSAGES.println(F(""));
	while (1); // you can return here, or you can loop
#else
	// Pin 13 has an LED connected on most Arduino boards. Just give it a name
#define led 13
	while (1)
	{
		digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
		delay(200);                // wait for a second
		digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
		delay(200);                // wait for a second
	}
#endif
}	// end of routine to handle Serial errors

void setup()
{
	// Ucomment to use the Serial link to the PC for debugging:

	//  Serial.begin(115200) ;        // serial to USB port
	// Note! The next statement will stop the sketch from running until the serial monitor is started
	//       If it is not present the monitor will be missing the initial writes
	//    while (!Serial) ;             // wait for serial to be established

	pinMode(RESETLINE, OUTPUT);       // Display reset pin
	digitalWrite(RESETLINE, 1);       // Reset Display, using shield
	delay(100);                       // wait for it to be recognised
	digitalWrite(RESETLINE, 0);       // Release Display Reset, using shield

	// Uncomment when using ESP8266:

	//  pinMode(ESPRESET, OUTPUT);        // ESP reset pin
	//  digitalWrite(ESPRESET, 1);        // Reset ESP
	//  delay(100);                       // wait for it t
	//  digitalWrite(ESPRESET, 0);        // Release ESP reset
	
	delay(3000);                     // give display time to startup

	// Now start display as Serial lines should have 'stabilised'
	DisplaySerial.begin(200000);     // Hardware serial to Display, same as SPE on display is set to
	Display.TimeLimit4D = 5000;      // 5 second timeout on all commands
	Display.Callback4D = mycallback;

	// Uncomment if using ESP8266:
	
	//  ESPserial.begin(115200) ;         // assume esp set to 115200 baud, it's default setting
										// what we need to do is attempt to flip it to 19200
										// the maximum baud rate at which software serial actually works
										// if we run a program without resetting the ESP it will already be 19200
										// and hence the next command will not be understood or executed
	//  ESPserial.println("AT+UART_CUR=19200,8,1,0,0\r\n") ;
	//  ESPserial.end() ;
	//  delay(10) ;                         // Necessary to allow for baud rate changes
	//  ESPserial.begin(19200) ;            // start again at a resonable baud rate
	
	Display.gfx_ScreenMode(PORTRAIT_R); // change manually if orientation change

	//Display.gfx_Rectangle(0, 0, 239, 319, BLUE);    // draw open rectangle, line can be patterned

	Display.txt_FontID(FONT1);

	//String title = "MAIN";
	char title[] = "MAIN";
	word titleWidth = 0;
	word titleX = 0;
	word titleY = 0;
	//unsigned titleLength = sizeof(title);
	for (unsigned i = 0; i < sizeof(title); ++i)
	{
		titleWidth += Display.charwidth(title[i]) + 1;	// Adding 1 for the gap (estimate)
	}
	titleWidth - +1;
	titleX = (screenWidth - titleWidth) / 2;
	Display.gfx_MoveTo(titleX, titleY);
	Display.print(title);

	//Display.txt_MoveCursor(0, 10);
	//Display.print("MAIN");

	Display.gfx_MoveTo(10, 20);
	Display.print("POWER g");
	Display.gfx_MoveTo(0, 100);
	Display.print(">");

	Display.gfx_MoveTo(10, 100);
	Display.print("COMMS");
	Display.txt_FGcolour(ALICEBLUE);
	Display.gfx_MoveTo(20, 110);
	Display.print("CommSerial");
	Display.gfx_MoveTo(20, 120);
	Display.print("NC");

	Display.txt_FGcolour(SPRINGGREEN);
	Display.gfx_MoveTo(10, 180);
	Display.print("CONTROL");
	Display.gfx_MoveTo(10, 260);
	Display.print("NAV");

	Display.txt_MoveCursor(38,10);
	Display.print("Scratchpad 1\n\rScratchpad 2");

	Display.gfx_Line(1, 19, 238, 19, YELLOWGREEN);
	Display.gfx_Line(1, 29, 238, 29, YELLOWGREEN);

} // end Setup

void loop()
{
	// put your main code here, to run repeatedly:
}

