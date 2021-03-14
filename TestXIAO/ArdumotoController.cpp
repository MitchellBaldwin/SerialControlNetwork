/*	ArdumotorControllerClass - Implementation of ArduinoControllerBase
*
*	Implement MRS Master Communications Controller (MRSMCC) based on Seeeduino XIAO
*	Uses COBS encoding (PacketSerial library, implemented in SerialClient class)
* Uses Sparkfun Qwiic Micro OLED Breakout as a local display
*
*	Mitchell Baldwin copyright 2021
*
*/

#include "ArdumotoController.h"

#define FORWARD	0
#define REVERSE 1

constexpr auto LeftMotor = 0;
constexpr auto RightMotor = 1;

// TODO: Update pins used on Seeeduino XIAO
const byte LMDirPin = 12;
const byte LMPWMPin = 3;
const byte RMDirPin = 13;
const byte RMPWMPin = 11;

constexpr byte VMotorPin = A0;

void ArdumotoController::Init(PacketSerial::PacketHandlerFunction OnSerialClientMessage)
{
	ArduinoControllerBase::Init(OnSerialClientMessage);
	SetupArdumotoBoard();

	Wire.begin();	// Start I2C bus
	delay(100);	// Allow I2C bus time to initialize

	// Check for presence of SF uOLED display module and initialize if detected:
	Wire.beginTransmission(I2C_ADDRESS_SA0_1);
	if (Wire.endTransmission(0) == 0)
	{
		oled.begin();			// Initialize the OLED
		oled.clear(PAGE); // Clear the display's internal memory
		oled.display();	  // Display what's in the buffer (splashscreen)
		DisplayPresent = true;
	}

}

bool ArdumotoController::TestDisplay()
{
	Wire.beginTransmission(I2C_ADDRESS_SA0_1);
	if (Wire.endTransmission(0) == 0)
	{
		//uint8_t fontHeight = oled.getFontHeight();
		uint8_t screenWidth = oled.getLCDWidth();
		uint8_t screenHeight = oled.getLCDHeight();
		oled.setCursor(0, 9);
		oled.print("WxH: " + String(screenWidth) + "x" + String(screenHeight));
		oled.display();
		DisplayPresent = true;
	}
	else
	{
		DisplayPresent = false;
	}
	return DisplayPresent;
}

void ArdumotoController::TestMotors()
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
	delay(500);
}

void ArdumotoController::Update()
{
	// Read and display battery supply voltage
	uint16_t VBat5Raw = analogRead(VMotorPin);
	if (DisplayPresent)
	{
		oled.setCursor(0, 0);
		oled.print("VBat5: " + String(VBat5Raw));
		oled.display();
	}
	ArduinoControllerBase::Update();
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
			if (DisplayPresent)
			{
				String msg = String((char*)commandPayload);
				oled.setCursor(0, 30);
				oled.print(msg);
				oled.display();
				SendTextMessage("This is a test...");

				commandHandled = true;
			}

		}
		break;

		case MRSCommandTypes::TestLocalDisplay:
			// Run demo / test of local display hardware:
			if (TestDisplay())
			{
				SendTextMessage("Local display OK");
			}
			else
			{
				SendTextMessage("Local display FAIL");
			}
			ScanI2CBus();
			commandHandled = true;
			break;

		case MRSCommandTypes::TestMotors:
		{
			TestMotors();
			SendTextMessage("Motor test complete");
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

void ArdumotoController::Stop()
{
	StopBothMotors();
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

void ArdumotoController::SetBothMotors(byte dir, byte speed)
{
	digitalWrite(LMDirPin, dir);
	analogWrite(LMPWMPin, speed);
	digitalWrite(RMDirPin, dir);
	analogWrite(RMPWMPin, speed);
}

void ArdumotoController::DriveForward(byte speed)
{
	SetBothMotors(FORWARD, speed);
}

void ArdumotoController::DriveBackward(byte speed)
{
	SetBothMotors(REVERSE, speed);
}

void ArdumotoController::PivotLeft(byte speed)
{
	SetMotor(LeftMotor, REVERSE, speed);
	SetMotor(RightMotor, FORWARD, speed);
}

void ArdumotoController::PivotRight(byte speed)
{
	SetMotor(LeftMotor, FORWARD, speed);
	SetMotor(RightMotor, REVERSE, speed);
}
