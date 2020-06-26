/*	ArduinoControllerBaseClass - Class implementing commands from remote controller
*
*	Base class for MRS Master Communications Controller (MRSMCC) and other embedded software modules
*	that rely on UART serial communication links
*
*	Mitchell Baldwin copyright 2020
*
*/

#include "ArduinoControllerBase.h"
#include "MRSCommands.h"
#include "MRSMessageTypes.h"
//#include "SerialClient.h"
#include "LocalDisplay.h"

ArduinoControllerBaseClass::ArduinoControllerBaseClass()
{
	
}

void ArduinoControllerBaseClass::Init()
{
	pinMode(BUILTINLED, OUTPUT);

	LocalDisplay.init();

}

void ArduinoControllerBaseClass::ExecuteCommand(uint8_t command)
{
	switch (command)
	{
	case MRSCommands::ToggleBuiltInLED:
		ToggleLED();
		break;

	case MRSCommands::TestPacketTransfer:
		ClientConnection.outPacket[0] = MRSMessageTypes.MRSStatusPacket;
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
	case MRSCommands::ToggleBuiltInLED:
		ToggleLED();
		break;

	case MRSCommands::TestPacketTransfer:
		// Test receipt of command packet payload data by returning it the client controller
		//as a status data packet:
		EchoCommandMessage(command, commandPayload);
		break;

	case MRSCommands::GetTestTextMessage:
		// Return a text message to test caller's ability to interpret and display text messages:
		SendTextMessage("This is a test...");
		break;

	case MRSMessageTypesClass::MRSTextMessage:
	{
		// Display the incoming text message locally (and/or log it):
		String msg = String((char*)commandPayload);
		LocalDisplay.Print(msg);
	}
		break;

	case MRSCommands::TestLocalDisplay:
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
	ClientConnection.SendPacket();
}

void ArduinoControllerBaseClass::SendTextMessage(String msg) 
{
	ClientConnection.outPacket[0] = MRSMessageTypesClass::MRSTextMessage;
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
	if (LocalDisplay.RunFont0Demo())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ArduinoControllerBaseClass::GetStatusReport()
{
	ClientConnection.outPacket[0] = MRSMessageTypes.MRSStatusPacket;

}

void ArduinoControllerBaseClass::ToggleLED()
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

//ArduinoControllerBaseClass ArduinoControllerBase;

