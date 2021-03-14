/*	ArduinoControllerBaseClass - Base class for implementing commands on the local embedded system received
*	from a remote controller system through a UART serial communication link (e.g., TTL UART, RS232,
*	USB Serial, Bluetooth Virtual Serial Port (SPP), etc.)
*
*	Base class for MRS Master Communications Controller (MRSMCC) and other embedded software modules
*	that rely on UART serial communication links
*
*	Mitchell Baldwin copyright 2020
*
*	v 0.00:	Initial command set
*	v
*
*/

#ifndef _ARDUINOCONTROLLERBASE_h
#define _ARDUINOCONTROLLERBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SerialClient.h"

class ArduinoControllerBase
{
private:
	void EchoCommandMessage(uint8_t, uint8_t*);

protected:
	virtual void ExecuteCommand(uint8_t);
	virtual void ExecuteCommand(uint8_t, uint8_t*);
	void GetStatusReport();
	void SendTextMessage(String);
	bool TestLocalDisplay();
	void ToggleLED();

 public:
	ArduinoControllerBase();
	void Init(PacketSerial::PacketHandlerFunction);
	void ProcessMessages(const uint8_t*, size_t);
	void Update();

};

#endif

