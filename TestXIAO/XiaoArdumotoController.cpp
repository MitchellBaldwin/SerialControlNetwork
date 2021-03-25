/*	ArdumotorControllerClass - Implementation of ArduinoControllerBase
*
*	Implement MRS Master Communications Controller (MRSMCC) based on Seeeduino XIAO
*	Uses COBS encoding (PacketSerial library, implemented in SerialClient class)
* Uses Sparkfun Qwiic Micro OLED Breakout as a local display
*
*	Mitchell Baldwin copyright 2021
*
*/

#include "XiaoArdumotoController.h"

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

void XiaoArdumotoController::Init(PacketSerial::PacketHandlerFunction OnSerialClientMessage)
{
	ArduinoControllerBase::Init(SerialClient::HardwareSerial1, OnSerialClientMessage);
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

bool XiaoArdumotoController::TestDisplay()
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

void XiaoArdumotoController::TestMotors()
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

void XiaoArdumotoController::Update()
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

void XiaoArdumotoController::ExecuteCommand(uint8_t)
{
	
}

void XiaoArdumotoController::ExecuteCommand(uint8_t command, uint8_t *commandPayload) //: EcecuteCommand(command, commandPayload)
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

void XiaoArdumotoController::SetupArdumotoBoard()
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

void XiaoArdumotoController::StopMotor(byte motor)
{
	SetMotor(motor, 0, 0);
}

void XiaoArdumotoController::StopBothMotors()
{
	SetMotor(LeftMotor, 0, 0);
	SetMotor(RightMotor, 0, 0);
}

void XiaoArdumotoController::Stop()
{
	StopBothMotors();
}

void XiaoArdumotoController::SetMotor(byte motor, byte dir, byte speed)
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

void XiaoArdumotoController::SetBothMotors(byte dir, byte speed)
{
	digitalWrite(LMDirPin, dir);
	analogWrite(LMPWMPin, speed);
	digitalWrite(RMDirPin, dir);
	analogWrite(RMPWMPin, speed);
}

void XiaoArdumotoController::DriveForward(byte speed)
{
	SetBothMotors(FORWARD, speed);
}

void XiaoArdumotoController::DriveBackward(byte speed)
{
	SetBothMotors(REVERSE, speed);
}

void XiaoArdumotoController::PivotLeft(byte speed)
{
	SetMotor(LeftMotor, REVERSE, speed);
	SetMotor(RightMotor, FORWARD, speed);
}

void XiaoArdumotoController::PivotRight(byte speed)
{
	SetMotor(LeftMotor, FORWARD, speed);
	SetMotor(RightMotor, REVERSE, speed);
}
