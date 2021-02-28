// ArdumotoController.h

#ifndef _ARDUMOTOCONTROLLER_h
#define _ARDUMOTOCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "ArduinoControllerBase.h"

class ArdumotoControllerClass : public ArduinoControllerBaseClass
{
	private:
		void SetupArdumotoBoard();
		void StopMotor(byte);
		void StopAllMotors();
		void SetMotor(byte, byte, byte);

	protected:
		virtual void ExecuteCommand(uint8_t);
		virtual void ExecuteCommand(uint8_t, uint8_t*);

	public:
		void init(PacketSerial::PacketHandlerFunction);
		void TestMotors();
};

//extern ArdumotoControllerClass ArdumotoController;

#endif

