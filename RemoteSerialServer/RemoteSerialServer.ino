/*
 Name:		RemoteSerialServer.ino
 Created:	4/10/2020 1:23:16 PM
 Author:	Mitchell Baldwin

 Test program for Arduino-based serial server; the same functionality implemented here will be used for
the main (INO) programs implementing the MRSMCC, MRSRC, etc.

*/

//#include "MRSMessageTypes.h"
//#include "SerialClient.h"
#include "ArduinoControllerBase.h"

void setup()
{
	ClientConnection.SetPacketHandler(&OnSerialClientMessage);
	ClientConnection.Begin(115200);

	ArduinoControllerBase.Init();

}

void loop()
{
	ClientConnection.Update();
	delay(10);
}

void OnSerialClientMessage(const uint8_t* buffer, size_t size)
{
	uint8_t* commandPayload;

	// Call method in SerialClient class to get the command info:
	uint8_t command = ClientConnection.UnPackCommandMessage(buffer, size);
	commandPayload = ClientConnection.GetInPacketPayload();
	
	// Execute received command through the remote MRS communications controller:
	//MRSRemoteComController.ExecuteCommand(command);
	ArduinoControllerBase.ExecuteCommand(command, commandPayload);

}

