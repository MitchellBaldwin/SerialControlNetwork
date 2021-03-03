/*	ArduinoControllerBaseClass - Base class for classes that handle receipt, unpacking and handling commands from remote controller
*
*	Base class for MRS Master Communications Controller (MRSMCC) and other embedded software modules
*	that rely on UART serial communication links
*
*	Mitchell Baldwin copyright 2020
*
*/

#include "ArduinoControllerBase.h"
#include "MRSCommandTypes.h"
#include "MRSMessageTypes.h"


ArduinoControllerBaseClass::ArduinoControllerBaseClass()
{
	
}

void ArduinoControllerBaseClass::Init(PacketSerial::PacketHandlerFunction OnSerialClientMessage)
{
	pinMode(LED_BUILTIN, OUTPUT);

	ClientConnection.SetPacketHandler(OnSerialClientMessage);
	ClientConnection.Begin(115200);

}

void ArduinoControllerBaseClass::Update()
{
	ClientConnection.Update();

}

void ArduinoControllerBaseClass::ProcessMessages(const uint8_t* buffer, size_t size)
{
	uint8_t* commandPayload;

	// Call method in SerialClient class to get the command info:
	uint8_t command = ClientConnection.UnPackCommandMessage(buffer, size);
	commandPayload = ClientConnection.GetInPacketPayload();

	// Execute received command through the remote MRS communications controller:
	//MRSRemoteComController.ExecuteCommand(command);
	ExecuteCommand(command, commandPayload);

}

void ArduinoControllerBaseClass::ExecuteCommand(uint8_t command)
{
	switch (command)
	{
	case MRSCommandTypes::ToggleBuiltInLED:
		ToggleLED();
		break;

	case MRSCommandTypes::TestPacketTransfer:
		ClientConnection.outPacket[0] = MRSMessageTypes::MRSStatusPacket;
		ClientConnection.SendPacket();
		break;

	default:
		break;
	}

}

void ArduinoControllerBaseClass::ExecuteCommand(uint8_t command, uint8_t *commandPayload)
{
	switch (command)
	{
	case MRSCommandTypes::ToggleBuiltInLED:
		ToggleLED();
		break;

	case MRSCommandTypes::TestPacketTransfer:
		// Test receipt of command packet payload data by returning it the client controller
		//as a status data packet:
		EchoCommandMessage(command, commandPayload);
		break;

	case MRSCommandTypes::GetTestTextMessage:
		// Return a text message to test caller's ability to interpret and display text messages:
		SendTextMessage("This is a test...");
		break;

	case MRSMessageTypes::MRSTextMessage:
	{
		// Display the incoming text message locally (and/or log it):
		String msg = String((char*)commandPayload);
		//LocalDisplay.WriteLine(msg);
	}
		break;

	case MRSCommandTypes::TestLocalDisplay:
		// Run demo / test of local display hardware:
		if (TestLocalDisplay())
		{
			SendTextMessage("Local display OK");
		}
		else
		{
			SendTextMessage("Local display FAIL");
		}
		break;

	default:
		break;
	}

}

void ArduinoControllerBaseClass::EchoCommandMessage(uint8_t command, uint8_t *commandPayload)
{
	ClientConnection.outPacket[0] = command;
	for (int i = 0; i < ClientConnection.PACKET_PAYLOAD_SIZE; ++i)
	{
		ClientConnection.outPacketPayload[i] = commandPayload[i];
	}
	//delay(100);
	ClientConnection.SendPacket();
}

void ArduinoControllerBaseClass::SendTextMessage(String msg) 
{
	ClientConnection.outPacket[0] = MRSMessageTypes::MRSTextMessage;
	for (int i = 0; i < ClientConnection.PACKET_PAYLOAD_SIZE; ++i) 
	{
		if (i < msg.length())
		{
			ClientConnection.outPacketPayload[i] = msg.c_str()[i];
		}
		else
		{
			ClientConnection.outPacketPayload[i] = 0x00;
		}
	}
	ClientConnection.SendPacket();
}

bool ArduinoControllerBaseClass::TestLocalDisplay()
{
	return true;
	//if (LocalDisplay.RunFont0Demo())
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

void ArduinoControllerBaseClass::GetStatusReport()
{
	ClientConnection.outPacket[0] = MRSMessageTypes::MRSStatusPacket;

}

void ArduinoControllerBaseClass::ToggleLED()
{
	// DEBUG: Toggle system LED to verify receipt of 0xF0 command message
	if (digitalRead(LED_BUILTIN))
	{
		digitalWrite(LED_BUILTIN, 0);
	}
	else
	{
		digitalWrite(LED_BUILTIN, 1);
	}
}

//ArduinoControllerBaseClass ArduinoControllerBase;

