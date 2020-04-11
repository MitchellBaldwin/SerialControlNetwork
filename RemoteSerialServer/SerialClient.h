#pragma once
#include <PacketSerial.h>>

class SerialClient
{
public:
	// Constructors:
	SerialClient();

	// Destructors:
	~SerialClient();

	static const uint8_t COM_BUFFER_SIZE = 16;
	static const uint8_t ENCODED_PACKET_SIZE = COM_BUFFER_SIZE - 1;
	static const uint8_t PACKET_SIZE = ENCODED_PACKET_SIZE - 1;
	static const uint8_t PACKET_PAYLOAD_SIZE = PACKET_SIZE - 1;

	uint8_t inBuffer[COM_BUFFER_SIZE];
	uint8_t outBuffer[COM_BUFFER_SIZE];

	uint8_t inPacket[PACKET_SIZE];
	uint8_t outPacket[PACKET_SIZE];

	bool newCommandReceived;
	uint8_t commandReceived;

	PacketSerial SerialClientConnection;
	
	void Begin(unsigned long baudRate = 115200);
	void SetPacketHandler(PacketSerial::PacketHandlerFunction);
	void Update();

	uint8_t UnPackCommandMessage(const uint8_t* buffer, size_t size);

};

