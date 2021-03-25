/*	ArdumotorControllerClass - Implementation of ArduinoControllerBase
*
*	Base class for MRS Master Communications Controller (MRSMCC) and other embedded software modules
*	that rely on UART serial communication links
*
*	Mitchell Baldwin copyright 2021
*
*/

#include "ArdumotoController.h"

#define FORWARD	0
#define REVERSE 1

constexpr auto LeftMotor = 0;
constexpr auto RightMotor = 1;

const byte LMDirPin = 12;
const byte LMPWMPin = 3;
const byte RMDirPin = 13;
const byte RMPWMPin = 11;

constexpr byte VMotorPin = A0;

void ArdumotoController::Init(PacketSerial::PacketHandlerFunction OnSerialClientMessage)
{
	ArduinoControllerBase::Init(SerialClient::SerialOverUSB, OnSerialClientMessage);
	SetupArdumotoBoard();

	Wire.begin();
	delay(100);
	if (TestDisplay())
	{
		oled.begin();			// Initialize the OLED
		oled.clear(PAGE); // Clear the display's internal memory
		oled.display();		// Display what's in the buffer (splashscreen)
	}

}

bool ArdumotoController::TestMotors()
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
	return true;
}

bool ArdumotoController::TestDisplay()
{
	Wire.beginTransmission(I2C_ADDRESS_SA0_1);
	if (Wire.endTransmission(0) == 0)
	{
		uint8_t fontHeight = oled.getFontHeight();
		oled.setCursor(0, 10);
		oled.print("Font h: " + String(fontHeight));
		oled.display();
		DisplayPresent = true;
	}
	else
	{
		DisplayPresent = false;
	}
	return DisplayPresent;
}

void ArdumotoController::Update()
{
	ArduinoControllerBase::Update();

	// Read and display battery supply voltage
	uint16_t VBat5Raw = analogRead(VMotorPin);
	oled.setCursor(0, 0);
	oled.print("VBat5: " + String(VBat5Raw));
	oled.display();

}

void ArdumotoController::ExecuteCommand(uint8_t)
{
	
}

void ArdumotoController::ExecuteCommand(uint8_t command, uint8_t *commandPayload) //: EcecuteCommand(command, commandPayload)
{
	bool commandHandled = false;
	
	switch (command)
	{
		case MRSMessageTypes::MRSTextMessage:
		{
			// Display the incoming text message locally (and/or log it):
			String msg = String((char*)commandPayload);
			oled.setCursor(0, 30);
			oled.print(msg);
			oled.display();
			SendTextMessage("This is a test...");

			commandHandled = true;
		}
		break;

		case MRSCommandTypes::DSMCUSetMotors:
		{
			int16_t speed = (((int16_t)commandPayload[0x01]) << 8) + (int16_t)(commandPayload[0x00]);
			// This works, too:
			//byte raw[2] = { commandPayload[0x00], commandPayload[0x01] };
			//int16_t speed = *((int16_t*)raw);

			byte direction = FORWARD;
			if (speed < 0)
			{
				direction = REVERSE;
				speed = abs(speed);
			}
			SetMotor(LeftMotor, direction, speed);
			SetMotor(RightMotor, direction, speed);

			commandHandled = true;
		}
		break;

		case MRSCommandTypes::RunSystemDiagnostics:
		{
			// Run demo / test of local display hardware:
			if (TestDisplay())
			{
				ArduinoControllerBase::SendTextMessage("Local display OK");
			}
			else
			{
				ArduinoControllerBase::SendTextMessage("Local display FAIL");
			}

			// Run demo / test of local display hardware:
			if (TestMotors())
			{
				ArduinoControllerBase::SendTextMessage("Motor test complete");
			}
			else
			{
				ArduinoControllerBase::SendTextMessage("Motor test FAIL");
			}

			commandHandled = true;
		}
		break;

		case MRSCommandTypes::TestLocalDisplay:
			// Run demo / test of local display hardware:
			if (TestDisplay())
			{
				ArduinoControllerBase::SendTextMessage("Local display OK");
			}
			else
			{
				ArduinoControllerBase::SendTextMessage("Local display FAIL");
			}
			commandHandled = true;
			break;

		case MRSCommandTypes::TestMotors:
		{
			TestMotors();
			ArduinoControllerBase::SendTextMessage("Motor test complete");
			commandHandled = true;
		}

		default:
			break;
	}

	if (!commandHandled)
	{
		ArduinoControllerBase::ExecuteCommand(command, commandPayload);
	}
}

void ArdumotoController::SetupArdumotoBoard()
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

void ArdumotoController::StopMotor(byte motor)
{
	SetMotor(motor, 0, 0);
}

void ArdumotoController::StopBothMotors()
{
	SetMotor(LeftMotor, 0, 0);
	SetMotor(RightMotor, 0, 0);
}

void ArdumotoController::SetMotor(byte motor, byte dir, byte speed)
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
