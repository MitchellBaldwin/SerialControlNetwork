/*
 Name:		Rover5ArdProArdumoto.ino
 Created:	3/14/2021 2:51:23 PM
 Author:	mitch
*/
#include "ArdProArdumotoController.h"

ArdProArdumotoController R5MRSMCC;

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
