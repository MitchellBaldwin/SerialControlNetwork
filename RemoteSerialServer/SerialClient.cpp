#include "SerialClient.h"


SerialClient::SerialClient()
{
	newCommandReceived = false;
	commandReceived = 0x00;

	PacketSerial::begin(115200);

	//PacketSerial::setPacketHandler(&OnUSBPacket);
}

SerialClient::SerialClient(unsigned long speed)
{
	newCommandReceived = false;
	commandReceived = 0x00;

	PacketSerial::begin(speed);
}


SerialClient::~SerialClient()
{
}
