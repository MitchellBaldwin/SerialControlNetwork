/*
*	Name:		JSBoardESP32.ino
*	Created:	8/4/2022 12:39:13 PM
*	Mitchell Baldwin copyright 2022
*
*	v 0.00:	Initial commit
*	v
*
*/
#include <SparkFun_Qwiic_Joystick_Arduino_Library.h>
#include "I2CBus.h"
#include "JSBKeypad.h"
#include "TrellisKeypad.h"
#include "JSBLocalDisplay.h"
#include <TaskSchedulerSleepMethods.h>
#include <TaskSchedulerDeclarations.h>
// #define _TASK_TIMECRITICAL		// Enable monitoring scheduling overruns
// #define _TASK_SLEEP_ON_IDLE_RUN	// Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
// #define _TASK_STATUS_REQUEST		// Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only
// #define _TASK_WDT_IDS			// Compile with support for wdt control points and task ids
// #define _TASK_LTS_POINTER		// Compile with support for local task storage pointer
// #define _TASK_PRIORITY			// Support for layered scheduling priority
// #define _TASK_MICRO_RES			// Support for microsecond resolution
// #define _TASK_STD_FUNCTION		// Support for std::function (ESP8266 and ESP32 ONLY)
// #define _TASK_DEBUG				// Make all methods and variables public for debug purposes
// #define _TASK_INLINE				// Make all methods "inline" - needed to support some multi-tab, multi-file implementations
// #define _TASK_TIMEOUT			// Support for overall task timeout
// #define _TASK_OO_CALLBACKS		// Support for dynamic callback method binding
#include <TaskScheduler.h>

// Select Debug and/or Test options here
#define _DEBUG_
//#define _TEST_

#ifdef _DEBUG_
#define _PP(a) Serial.print(a);
#define _PL(a) Serial.println(a);
#define _PLH(a) Serial.println(a, HEX);
#else
#define _PP(a)
#define _PL(a)
#define _PLH(a)
#endif

constexpr auto BuiltinLEDTogglePeriod = 500;
constexpr auto ControlsUpdatePeriod = 20;

// Scheduler
Scheduler mainScheduler;

void ToggleBuiltinLEDCallback();
Task taskToggleBuiltinLED(BuiltinLEDTogglePeriod * TASK_MILLISECOND, TASK_FOREVER, &ToggleBuiltinLEDCallback, &mainScheduler, false);

void ReadAndUpdateControlsCallback();
Task taskReadAndUpdateControls(ControlsUpdatePeriod *TASK_MILLISECOND, TASK_FOREVER, &ReadAndUpdateControlsCallback, &mainScheduler, false);

constexpr auto BuiltinLEDPin = 2;
constexpr auto BlueLEDPin = 26;
constexpr auto GreenLEDPin = 27;

constexpr auto DrvJSXPin = 32;
constexpr auto DrvJSYPin = 33;
constexpr auto PTJSXPin = 34;
constexpr auto PTJSYPin = 35;

constexpr auto VInPin = 36;

constexpr auto DrvJSI2CAddress = 0x21;
constexpr auto PTJSI2CAddress = 0x22;

constexpr auto LocalDisplayI2CAddress = 0x3C;
constexpr auto TrellisKeypadI2CAddress = 0x70;

//DEBUG - Test accuracy of the Task Scheduler:
//uint32_t lastMillis;

JOYSTICK DrvJoystick;
JOYSTICK PTJoystick;

void setup() 
{
	pinMode(BlueLEDPin, OUTPUT);
	pinMode(GreenLEDPin, OUTPUT);
	pinMode(BuiltinLEDPin, OUTPUT);

	pinMode(VInPin, INPUT);

#if defined(_DEBUG_) || defined(_TEST_)
	Serial.begin(115200);
	while (!Serial);
	_PL(F("\nJS Board ESP32 setup"));
#endif

	I2CBus.Init();
	I2CBus.Scan();

	// Normal operation; blink LED at 0.5 Hz:
	int16_t BuiltinLEDOnTime = 1000;
	JSBLocalDisplay.Init(LocalDisplayI2CAddress);
	if (JSBLocalDisplay.Test())
	{
		_PL("Local display initialized and OK");
	}
	else 
	{
		// Local display initialization failed; blink LED at 2 Hz:
		BuiltinLEDOnTime = 250;
		_PL("Local display not responding");
	}

	TrellisKeypad.Init(TrellisKeypadI2CAddress);
	if (TrellisKeypad.Test())
	{
		//TrellisKeypad.SetLEDToggleState(true);
		_PL("Trellis keypad initialized and OK");
	}
	else
	{
		// Trellis keypad initialization failed; blink LED at 1 Hz:
		BuiltinLEDOnTime = 500;
		_PL("Trellis keypad not responding");
	}

	DrvJoystick.begin(Wire, DrvJSI2CAddress);
	PTJoystick.begin(Wire, PTJSI2CAddress);
	
	//DEBUG - Test accuracy of the Task Scheduler:
	//lastMillis = millis();
	taskToggleBuiltinLED.setInterval(BuiltinLEDOnTime);

	taskToggleBuiltinLED.enable();
	taskReadAndUpdateControls.enable();

}

void loop() 
{
	mainScheduler.execute();
}

void ToggleBuiltinLEDCallback()
{
	digitalWrite(BuiltinLEDPin, !digitalRead(BuiltinLEDPin));
	//DEBUG - Test accuracy of the Task Scheduler:
	//_PL(millis() - lastMillis);
}

void ReadAndUpdateControlsCallback()
{
	if (JSPkt.currentAnalogChannel >= JSPktClass::LastChannel)
	{
		JSPkt.currentAnalogChannel = JSPktClass::DrvJSXChannel;
	}
	else
	{
		JSPkt.currentAnalogChannel = JSPktClass::analogChannels(JSPkt.currentAnalogChannel + 1);
	}
	
	switch (JSPkt.currentAnalogChannel)
	{
	case JSPktClass::DrvJSXChannel:
		JSPkt.DrvJSX = DrvJoystick.getHorizontal() - 512;
		break;
	case JSPktClass::DrvJSYChannel:
		JSPkt.DrvJSY = DrvJoystick.getVertical() - 512;
		break;
	case JSPktClass::PTJSXChannel:
		JSPkt.PTJSX = PTJoystick.getHorizontal() - 512;
		break;
	case JSPktClass::PTJSYChannel:
		JSPkt.PTJSY = PTJoystick.getVertical() - 512;
		break;
	case JSPktClass::VInChannel:
		JSPkt.VIn = analogRead(VInPin);
		break;
	case JSPktClass::AnalogKeypadChannel:
		break;

	default:
		break;
	}
	

	if (TrellisKeypad.KeyPressed())
	{
		switch (TrellisKeypad.GetLastKeyPressed())
		{
		case JSBKeypadClass::ClearKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::Clear);
			TrellisKeypad.ClearAllKeyLEDs();
			break;
		case JSBKeypadClass::SystemKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);
			TrellisKeypad.ClearAllKeyLEDs();
			TrellisKeypad.SetKeyLED(JSBKeypadClass::SystemKey);
			break;
		case JSBKeypadClass::PowerKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::POWPage);
			TrellisKeypad.ClearAllKeyLEDs();
			TrellisKeypad.SetKeyLED(JSBKeypadClass::PowerKey);
			break;
		case JSBKeypadClass::CommsKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::COMPage);
			TrellisKeypad.ClearAllKeyLEDs();
			TrellisKeypad.SetKeyLED(JSBKeypadClass::CommsKey);
			break;

		case JSBKeypadClass::I2CKey:
			// Execute I2C bus scan
			I2CBus.Scan();
			//// DEBUG Show I2C devices found in serial monitor
			//for (uint8_t i = 0x00; i < I2CBus.I2CDeviceCount; ++i)
			//{
			//	_PLH(I2CBus.ActiveI2CDeviceAddresses[i]);
			//}
			// Display I2C page on LocalDisplay
			JSBLocalDisplay.Control(JSBLocalDisplayClass::I2CPage);
			TrellisKeypad.ClearAllKeyLEDs();
			TrellisKeypad.SetKeyLED(JSBKeypadClass::I2CKey);
			break;

		default:
			break;
		}
	}

	JSBLocalDisplay.Update();

}
