/*	SerialClient - Class implementing serial RX and TX with COBS encoding
*	Wrapper for PacketSerial Arduino Library by Christopher Baker
*
*	Mitchell Baldwin copyright 2020
*
*	v 0.00:	Packet handling
*	v
*
*/

#pragma once
#include <PacketSerial.h>>

class SerialClient
{
public:
	// Constructors:
	SerialClient();

	// Destructors:
	~SerialClient();

	static const uint8_t COM_BUFFER_SIZE = 32;
	static const uint8_t ENCODED_PACKET_SIZE = COM_BUFFER_SIZE - 1;
	static const uint8_t PACKET_SIZE = ENCODED_PACKET_SIZE - 1;
	static const uint8_t PACKET_PAYLOAD_SIZE = PACKET_SIZE - 2;

	uint8_t inBuffer[COM_BUFFER_SIZE];
	uint8_t outBuffer[COM_BUFFER_SIZE];

	uint8_t inPacket[PACKET_SIZE];
	uint8_t outPacket[PACKET_SIZE];

	uint8_t inPacketPayload[PACKET_PAYLOAD_SIZE];
	uint8_t outPacketPayload[PACKET_PAYLOAD_SIZE];

	uint8_t commandReceived;

	PacketSerial SerialClientConnection;
	
	void Begin(unsigned long baudRate = 115200);
	void SetPacketHandler(PacketSerial::PacketHandlerFunction);
	void Update();
	void SendPacket();

	uint8_t UnPackCommandMessage(const uint8_t* buffer, size_t size);

	uint8_t* GetInPacketPayload();

};

extern SerialClient ClientConnection;

