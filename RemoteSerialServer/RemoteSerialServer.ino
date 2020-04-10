/*
 Name:		RemoteSerialServer.ino
 Created:	4/10/2020 1:23:16 PM
 Author:	Mitchell Baldwin
*/

#include "SerialClient.h"

// The constructor may be called automatically when PCHostSerialConnection is declared?
// -> Yes, the constructor is called here and the constructor calls the 'begin' base method
//in PacketSerial
SerialClient PCHostSerialConnection(115200);

const uint8_t BUILTINLED = 13;

void setup()
{
	// The constructor may be called automatically when PCHostSerialConnection is declared?
	//PCHostSerialConnection.begin(115200);

	pinMode(BUILTINLED, OUTPUT);

	PCHostSerialConnection.setPacketHandler(&OnUSBPacket);
	PCHostSerialConnection.begin(115200);

}

void loop()
{
	//ToggleLED();

	if (PCHostSerialConnection.newCommandReceived)
	{
		PCHostSerialConnection.newCommandReceived = false;
		switch (PCHostSerialConnection.commandReceived)
		{
			case 0xF8:
				ToggleLED();
				break;
		
			default:
				break;
		}
	}
	
	PCHostSerialConnection.update();
	delay(100);
}

void OnUSBPacket(const uint8_t* buffer, size_t size)
{
	PCHostSerialConnection.newCommandReceived = true;
	PCHostSerialConnection.commandReceived = buffer[0];

	for (int i = 0; i < PCHostSerialConnection.PACKET_SIZE; ++i)
	{
		PCHostSerialConnection.inBuffer[i] = buffer[i];
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
