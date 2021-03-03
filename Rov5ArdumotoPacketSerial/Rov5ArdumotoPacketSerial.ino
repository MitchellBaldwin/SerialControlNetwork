/*
 Name:		Rov5ArdumotoPacketSerial.ino
 Created:	2/28/2021 11:51:58 AM
 Author:	Mitchell Baldwin

 Test program for Rover 5 chassis using Arduino Pro controller and PacketSerial server 

*/

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
