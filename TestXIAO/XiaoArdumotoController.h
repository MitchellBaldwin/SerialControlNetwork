// ArdumotoController.h

#ifndef _XIAOARDUMOTOCONTROLLER_h
#define _XIAOARDUMOTOCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SerialClient.h>
#include <ArduinoControllerBase.h>

#include <wire.h>
#include <SFE_MicroOLED.h>

// The SFE_MicroOLED library assumes a reset pin is necessary. 
// The Qwiic OLED has RST hard-wired, so pick an arbitrarty IO pin that is NOT BEING USED
#define PIN_RESET 9  

// The DC_JUMPER is the I2C Address Select jumper. 
// Set to 1 if the jumper is open (Default), or set to 0 if it's closed.
#define DC_JUMPER 1

class XiaoArdumotoController : public ArduinoControllerBase
{
	private:
		bool DisplayPresent = false;
		void SetupArdumotoBoard();
		void StopMotor(byte);
		void StopBothMotors();
		void Stop();
		void SetMotor(byte, byte, byte);
		void SetBothMotors(byte, byte);
		void DriveForward(byte);
		void DriveBackward(byte);
		void PivotLeft(byte);
		void PivotRight(byte);

	protected:
		MicroOLED oled = MicroOLED(PIN_RESET, DC_JUMPER);
		bool TestDisplay();
		void TestMotors();
		virtual void ExecuteCommand(uint8_t);
		virtual void ExecuteCommand(uint8_t, uint8_t*);

	public:
		void Init(PacketSerial::PacketHandlerFunction);
		void Update();
};

#endif

