// 
// 
// 

#include "ArdumotoController.h"

#define FORWARD	0
#define REVERSE 1

//#define LEFT_MOTOR 0
//#define RIGHT_MOTOR	1

//const byte LEFT_MOTOR = 0;
//const byte RIGHT_MOTOR = 1;

constexpr auto LeftMotor = 0;
constexpr auto RightMotor = 1;

const byte LMDirPin = 12;
const byte LMPWMPin = 3;
const byte RMDirPin = 13;
const byte RMPWMPin = 11;

constexpr byte VMotorPin = A0;

void ArdumotoControllerClass::init(PacketSerial::PacketHandlerFunction OnSerialClientMessage)
{
	ArduinoControllerBaseClass::Init(OnSerialClientMessage);
	SetupArdumotoBoard();

}

void ArdumotoControllerClass::TestMotors()
{
	SetMotor(LeftMotor, FORWARD, 127);
	delay(2000);
	SetMotor(LeftMotor, 0, 0);
	delay(500);
	SetMotor(LeftMotor, HIGH, 127);
	delay(2000);
	SetMotor(LeftMotor, 0, 0);
	delay(500);
	SetMotor(RightMotor, FORWARD, 127);
	delay(2000);
	SetMotor(RightMotor, 0, 0);
	delay(500);
	SetMotor(RightMotor, REVERSE, 127);
	delay(2000);
	SetMotor(RightMotor, 0, 0);
	//delay(500);
}

void ArdumotoControllerClass::ExecuteCommand(uint8_t)
{
	
}

void ArdumotoControllerClass::ExecuteCommand(uint8_t command, uint8_t *commandPayload) //: EcecuteCommand(command, commandPayload)
{
	ArduinoControllerBaseClass::ExecuteCommand(command, commandPayload);
}

void ArdumotoControllerClass::SetupArdumotoBoard()
{
	pinMode(LMDirPin, OUTPUT);
	pinMode(LMPWMPin, OUTPUT);
	pinMode(RMDirPin, OUTPUT);
	pinMode(RMPWMPin, OUTPUT);

	digitalWrite(LMDirPin, LOW);
	digitalWrite(LMPWMPin, LOW);
	digitalWrite(RMDirPin, LOW);
	digitalWrite(RMPWMPin, LOW);

}

void ArdumotoControllerClass::StopMotor(byte motor)
{
	SetMotor(motor, 0, 0);
}

void ArdumotoControllerClass::StopAllMotors()
{
	SetMotor(LeftMotor, 0, 0);
	SetMotor(RightMotor, 0, 0);
}

void ArdumotoControllerClass::SetMotor(byte motor, byte dir, byte speed)
{
	switch (motor)
	{
	case LeftMotor:
	{
		digitalWrite(LMDirPin, dir);
		analogWrite(LMPWMPin, speed);
		break;
	}

	case RightMotor:
	{
		digitalWrite(RMDirPin, dir);
		analogWrite(RMPWMPin, speed);
		break;
	}

	default:
		break;

	}
}

//ArdumotoControllerClass ArdumotoController;

