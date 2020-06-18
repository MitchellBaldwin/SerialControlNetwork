/*	ArduinoControllerBaseClass - Class implementing commands from remote controller
*
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

class ArduinoControllerBaseClass
{
private:
	const uint8_t BUILTINLED = 13;
	
	void EchoCommandMessage(uint8_t, uint8_t*);
	void SendTextMessage(String);
	bool TestLocalDisplay();

protected:
	void GetStatusReport();

 public:
	ArduinoControllerBaseClass();
	void Init();
	void ExecuteCommand(uint8_t);
	void ExecuteCommand(uint8_t, uint8_t*);
	void ToggleLED();

};

extern ArduinoControllerBaseClass ArduinoControllerBase;

#endif

