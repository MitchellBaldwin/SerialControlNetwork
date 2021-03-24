/*
 Name:		TestXIAO.ino
 Created:	03/01/2021 11:51:58 AM
 Author:	Mitchell Baldwin

 Test program for Rover 5 chassis using Seeed Studio XIAO and PacketSerial server

*/

#define XIAO

#include <PacketSerial.h>
#include "XiaoArdumotoController.h"

XiaoArdumotoController R5MRSMCC;

bool FirstTime = true;

void setup() {
	
	// Use USB serial connection for debugger:
	SerialUSB.begin(115200);
	// Wait for USB serial port (for ATmega32u4 or other board / chips with a dedicated USB serial port:
	while (!SerialUSB);	
	SerialUSB.println("\r\nConnected...");
	
	// Initialize the Master Communications Controller (MCC), or in this test case, the Drive System MCU 
	//(DSMCU) subsystem in the form of a Seeeduino Xiao, Ardumoto motor controller shield and SF uOLED
	// This subsystem uses the Xiao hardware UART for COBS (PacketSerial) serial communication with the host:
	R5MRSMCC.Init(&OnSerialClientMessage);
	digitalWrite(LED_BUILTIN, HIGH);	// For the Xiao, pulling port HIGH turns built-in LED OFF

	// Debug / development trace code:
	R5MRSMCC.ScanI2CBus();
	// End of debug / development trace code block
}

void loop() 
{
	// Debug / development trace code:
	if (FirstTime)
	{
		SerialUSB.println("Entered loop");
		FirstTime = false;
	}
	// End of debug / development trace code block

	R5MRSMCC.Update();
	delay(10);
	
}

void OnSerialClientMessage(const uint8_t* buffer, size_t size)
{
	R5MRSMCC.ProcessMessages(buffer, size);
}

