/*
 Name:		RemoteSerialServer.ino
 Created:	4/10/2020 1:23:16 PM
 Author:	Mitchell Baldwin

 Test program for Arduino-based serial server; the same functionality implemented here will be used for
the main (INO) programs implementing the MRSMCC, MRSRC, etc.

*/

#include <PacketSerial.h>
#include "ArdumotoController.h"

ArdumotoController R5MRSMCC;

void setup()
{
	R5MRSMCC.Init(&OnSerialClientMessage);
}

void loop()
{
	R5MRSMCC.Update();
	delay(10);
}

void OnSerialClientMessage(const uint8_t* buffer, size_t size)
{
	R5MRSMCC.ProcessMessages(buffer, size);
}

