/*
 Name:		TestXIAO.ino
 Created:	03/01/2021 11:51:58 AM
 Author:	Mitchell Baldwin

 Test program for Rover 5 chassis using Seeed Studio XIAO and PacketSerial server

*/

#include <PacketSerial.h>
#include "ArdumotoController.h"

ArdumotoController R5MRSMCC;

bool FirstTime = true;

void setup() {
  // Should not be needed; handled in ArduinoControllerBase
  //pinMode(LED_BUILTIN, OUTPUT);	// Initialize digital pin 13 as an output.
	
	// Use USB serial connection for debugger:
	SerialUSB.begin(115200);	
	SerialUSB.println("\r\nConnected...");
	
	// Use hardware UART for COBS (PacketSerial) serial communication:
	Serial1.begin(115200);	
	R5MRSMCC.Init(&OnSerialClientMessage);

	R5MRSMCC.ScanI2CBus();

}

void loop() 
{
	if (FirstTime)
	{
		SerialUSB.println("Entered loop");
		digitalWrite(LED_BUILTIN, HIGH);	// Pulling port HIGH turns built-in LED OFF
		FirstTime = false;
	}
	
	R5MRSMCC.Update();
	delay(10);
	
 //// Standard built-in LED blink test:
 // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
 // delay(1000);              // wait for a second
 // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
 // delay(1000);              // wait for a second
}

void OnSerialClientMessage(const uint8_t* buffer, size_t size)
{
	R5MRSMCC.ProcessMessages(buffer, size);
}
