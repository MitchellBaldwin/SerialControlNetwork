/*	SerialClient - Class implementing serial RX and TX with COBS encoding 
*	Wrapper for PacketSerial Arduino Library by Christopher Baker
*
*	Mitchell Baldwin copyright 2020
*
*
*/

#include "SerialClient.h"

SerialClient::SerialClient()
{
	commandReceived = 0x00;
}

SerialClient::~SerialClient()
{
}

void SerialClient::Begin(unsigned long baudRate)
{
	Serial.begin(baudRate);
	SerialClientConnection.setStream(&Serial);
}

void SerialClient::SetPacketHandler(PacketSerial::PacketHandlerFunction onPacketFunction)
{
	SerialClientConnection.setPacketHandler(onPacketFunction);
}

void SerialClient::Update()
{
	SerialClientConnection.update();
}

void SerialClient::SendPacket()
{
	for (int i = 0; i < PACKET_PAYLOAD_SIZE; ++i)
	{
		outPacket[i+1] = outPacketPayload[i];
	}

	int checksum = 0;
	for (int i = 0; i < PACKET_SIZE - 1; ++i)
	{
		checksum += outPacket[i];
	}
	outPacket[PACKET_SIZE - 1] = checksum;

	SerialClientConnection.send(outPacket, PACKET_SIZE);
	
}

uint8_t SerialClient::UnPackCommandMessage(const uint8_t* buffer, size_t size)
{
	commandReceived = buffer[0];

	for (int i = 0; i < PACKET_SIZE; ++i)
	{
		inPacket[i] = buffer[i];
		if (i > 0)
		{
			inPacketPayload[i - 1] = inPacket[i];
		}
	}

	return commandReceived;
}

uint8_t * SerialClient::GetInPacketPayload()
{
	return inPacketPayload;
}

SerialClient ClientConnection;
