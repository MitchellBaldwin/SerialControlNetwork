/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include <PacketSerial.h>
#include "ArdumotoController.h"

ArdumotoController R5MRSMCC;

bool FirstTime = true;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
	SerialUSB.begin(115200);
	SerialUSB.println("\r\nConnected...");

	Serial1.begin(115200);
	R5MRSMCC.Init(&OnSerialClientMessage);

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

