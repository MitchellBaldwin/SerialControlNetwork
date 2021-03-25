#include "InheretedSerialClient.h"


InheretedSerialClient::InheretedSerialClient()
{
	newCommandReceived = false;
	commandReceived = 0x00;

	PacketSerial::begin(115200);

	//PacketSerial::setPacketHandler(&OnUSBPacket);
}

InheretedSerialClient::InheretedSerialClient(unsigned long speed)
{
	newCommandReceived = false;
	commandReceived = 0x00;

	PacketSerial::begin(speed);
}


InheretedSerialClient::~InheretedSerialClient()
{
}
