/*
 Name:		RemoteSerialServer.ino
 Created:	4/10/2020 1:23:16 PM
 Author:	Mitchell Baldwin
*/

#include "SerialClient.h"

// The constructor may be called automatically when PCHostSerialConnection is declared?
// -> Yes, the constructor is called here and the constructor calls the 'begin' base method
//in PacketSerial
SerialClient PCHostSerialConnection;

const uint8_t BUILTINLED = 13;

void setup()
{
	// The constructor may be called automatically when PCHostSerialConnection is declared?
	//PCHostSerialConnection.begin(115200);

	pinMode(BUILTINLED, OUTPUT);

	PCHostSerialConnection.SetPacketHandler(&OnSerialClientMessage);
	PCHostSerialConnection.Begin(115200);

}

void loop()
{
	PCHostSerialConnection.Update();
	delay(100);
}

void OnSerialClientMessage(const uint8_t* buffer, size_t size)
{
	// Call method in SerialClient class to get the command info
	uint8_t command = PCHostSerialConnection.UnPackCommandMessage(buffer, size);

	// May no longer be necessary to use the newCommandReceived flag:
	PCHostSerialConnection.newCommandReceived = false;

	switch (command)
	{
	case 0xF8:
		ToggleLED();
		break;

	default:
		break;
	}

	
}

void ToggleLED()
{
	// DEBUG: Toggle system LED to verify receipt of 0xF0 command message
	if (digitalRead(BUILTINLED))
	{
		digitalWrite(BUILTINLED, 0);
	}
	else
	{
		digitalWrite(BUILTINLED, 1);
	}
}
