/*
*	Name:		JSBoardESP32.ino
*	Created:	8/4/2022 12:39:13 PM
*	Mitchell Baldwin copyright 2022
*
*	v 0.00:	Initial commit
*	v
*
*/
#include "JSBKeypad.h"
#include <I2CScanner.h>
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
constexpr auto ControlsUpdatePeriod = 100;

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

constexpr auto DFR4x4KPPin = 36;

constexpr auto LocalDisplayI2CAddress = 0x3C;
constexpr auto TrellisKeypadI2CAddress = 0x70;

I2CScanner i2CScanner;
uint8_t activeI2CAddresses[3];

uint8_t ScanI2CAddress(uint8_t address)
{
	Wire.beginTransmission(address);
	uint8_t error = Wire.endTransmission();
	return error;
}

void ScanI2CBus()
{
	//i2CScanner.Init();
	for (uint8_t i = i2CScanner.Low_Address; i <= i2CScanner.High_Address; ++i)
	{
		i2CScanner.Devices_Count = 0;
		if (!ScanI2CAddress(i))
		{
			activeI2CAddresses[i2CScanner.Devices_Count];
			i2CScanner.Devices_Count++;
			_PLH(i);
			if (i2CScanner.Devices_Count >= 3) exit;
		}
	}
}

//uint32_t lastMillis;

void setup() 
{
	pinMode(BlueLEDPin, OUTPUT);
	pinMode(GreenLEDPin, OUTPUT);
	pinMode(BuiltinLEDPin, OUTPUT);

#if defined(_DEBUG_) || defined(_TEST_)
	Serial.begin(115200);
	while (!Serial);
	_PL(F("\nJS Board ESP32 setup"));
#endif

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
		_PL("Trellis keypad initialized and OK");
	}
	else
	{
		BuiltinLEDOnTime = 250;
		_PL("Trellis keypad not responding");
	}

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
	//_PL(millis() - lastMillis);
}

void ReadAndUpdateControlsCallback()
{
	//JSPkt.DFR4x4KPRaw = analogRead(DFR4x4KPPin);
	JSPkt.DFR4x4KPRaw = analogRead(PTJSXPin);

	JSPkt.DrvJSX = (analogRead(DrvJSXPin) - 2048) / 4;
	JSPkt.DrvJSY = (analogRead(DrvJSYPin) - 2048) / 4;
	JSPkt.PTJSX = (JSPkt.DFR4x4KPRaw - 2048) / 4;
	JSPkt.PTJSY = (analogRead(PTJSYPin) - 2048) / 4;

	if (TrellisKeypad.KeyPressed())
	{
		switch (TrellisKeypad.GetLastKeyPressed())
		{
		case JSBKeypadClass::ClearKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::Clear);
			break;
		case JSBKeypadClass::SystemKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);
			break;
		case JSBKeypadClass::PowerKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::POWPage);
			break;
		case JSBKeypadClass::CommsKey:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::COMPage);
			break;

		case JSBKeypadClass::I2CKey:
			// Execute I2C bus scan
			ScanI2CBus();
			// Display I2C page on LocalDisplay

			break;

		default:
			break;
		}
	}

	JSBLocalDisplay.Update();

}
