/*
*	Name:		JSBoardESP32.ino
*	Created:	8/4/2022 12:39:13 PM
*	Mitchell Baldwin copyright 2022
*
*	v 0.00:	Initial commit
*	v
*
*/
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
#else
#define _PP(a)
#define _PL(a)
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

uint32_t lastMillis;

void setup() 
{
	pinMode(BlueLEDPin, OUTPUT);
	pinMode(GreenLEDPin, OUTPUT);
	pinMode(BuiltinLEDPin, OUTPUT);

#if defined(_DEBUG_) || defined(_TEST_)
	Serial.begin(115200);
	while (!Serial);
	_PL(F("\nJS Board ESP32"));
#endif

	// Normal operation; blink LED at 0.5 Hz:
	int16_t BuiltinLEDOnTime = 1000;
	JSBLocalDisplay.Init(LocalDisplayI2CAddress);
	if (!JSBLocalDisplay.Test())
	{
		// Local display initialization failed; blink LED at 2 Hz:
		BuiltinLEDOnTime = 250;
	}
	taskToggleBuiltinLED.setInterval(BuiltinLEDOnTime);
	//JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);

	TrellisKeypad.Init();
	TrellisKeypad.Test();

	lastMillis = millis();

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
	JSPkt.DrvJSX = (analogRead(DrvJSXPin) - 2048) / 4;
	JSPkt.DrvJSY = (analogRead(DrvJSYPin) - 2048) / 4;
	JSPkt.PTJSX = (analogRead(PTJSXPin) - 2048) / 4;
	JSPkt.PTJSY = (analogRead(PTJSYPin) - 2048) / 4;

	JSPkt.DFR4x4KPRaw = analogRead(DFR4x4KPPin);

	if (TrellisKeypad.KeyPressed())
	{
		switch (TrellisKeypad.GetLastKeyPressed())
		{
		case 0:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::Clear);
			break;
		case 1:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::SYSPage);
			break;
		case 2:
			JSBLocalDisplay.Control(JSBLocalDisplayClass::POWPage);
			break;
		default:
			break;
		}
	}

	JSBLocalDisplay.Update();

}
