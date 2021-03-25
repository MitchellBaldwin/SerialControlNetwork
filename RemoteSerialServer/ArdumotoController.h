// ArdumotoController.h

#ifndef _ARDUMOTOCONTROLLER_h
#define _XIAOARDUMOTOCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoControllerBase.h>

#include <wire.h>
#include <SFE_MicroOLED.h>

// The SFE_MicroOLED library assumes a reset pin is necessary. 
// The Qwiic OLED has RST hard-wired, so pick an arbitrarty IO pin that is NOT BEING USED
#define PIN_RESET 9  

// The DC_JUMPER is the I2C Address Select jumper. 
// Set to 1 if the jumper is open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1

class ArdumotoController : public ArduinoControllerBase
{
	private:
		void SetupArdumotoBoard();
		void StopMotor(byte);
		void StopBothMotors();
		void SetMotor(byte, byte, byte);
		bool DisplayPresent = false;

	protected:
		MicroOLED oled = MicroOLED(PIN_RESET, DC_JUMPER);
		bool TestMotors();
		bool TestDisplay();
		virtual void ExecuteCommand(uint8_t);
		virtual void ExecuteCommand(uint8_t, uint8_t*);

	public:
		void Init(PacketSerial::PacketHandlerFunction);
		void Update();
};

//extern ArdumotoControllerClass ArdumotoController;

#endif

