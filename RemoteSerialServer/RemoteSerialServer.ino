/*
 Name:		RemoteSerialServer.ino
 Created:	4/10/2020 1:23:16 PM
 Author:	Mitchell Baldwin

 Test program for Arduino-based serial server; the same functionality implemented here will be used for
the main (INO) programs implementing the MRSMCC, MRSRC, etc.

*/

#include "ArdumotoController.h"
//#include "ArduinoControllerBase.h"

//ArduinoControllerBaseClass ArduinoControllerBase;
ArdumotoControllerClass ArdumotoController;


void setup()
{
	//ArduinoControllerBase.Init(&OnSerialClientMessage);
	ArdumotoController.Init(&OnSerialClientMessage);
	ArdumotoController.TestMotors();
}

void loop()
{
	//ArduinoControllerBase.Update();
	ArdumotoController.Update();
	delay(10);
}

void OnSerialClientMessage(const uint8_t* buffer, size_t size)
{
	//ArduinoControllerBase.ProcessMessages(buffer, size);
	ArdumotoController.ProcessMessages(buffer, size);
}

