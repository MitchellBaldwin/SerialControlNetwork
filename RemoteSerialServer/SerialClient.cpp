#include "SerialClient.h"



SerialClient::SerialClient()
{
	newCommandReceived = false;
	commandReceived = 0x00;
}

SerialClient::~SerialClient()
{
	newCommandReceived = false;
	commandReceived = 0x00;
}

void SerialClient::Begin(unsigned long baudRate)
{
	SerialClientConnection.begin(baudRate);
}

void SerialClient::SetPacketHandler(PacketSerial::PacketHandlerFunction onPacketFunction)
{
	SerialClientConnection.setPacketHandler(onPacketFunction);
}

void SerialClient::Update()
{
	SerialClientConnection.update();
}

uint8_t SerialClient::UnPackCommandMessage(const uint8_t* buffer, size_t size)
{
	newCommandReceived = true;
	commandReceived = buffer[0];

	for (int i = 0; i < PACKET_SIZE; ++i)
	{
		inBuffer[i] = buffer[i];
	}


	return commandReceived;
}

