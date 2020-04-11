#pragma once
#include <PacketSerial.h>>

class InheretedSerialClient :
	public PacketSerial
{
public:
	// Constructors:
	InheretedSerialClient();
	InheretedSerialClient(unsigned long);

	// Deconstructors:
	~InheretedSerialClient();

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


};

