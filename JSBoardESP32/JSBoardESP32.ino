/*
*	Name:		JSBoardESP32.ino
*	Created:	8/4/2022 12:39:13 PM
*	Mitchell Baldwin copyright 2022
*
*	v 0.00:	Initial commit
*	v
*
*/
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

#define BUILTINLED_TOGGLE_PERIOD 500

// Scheduler
Scheduler mainScheduler;

void ToggleBuiltinLEDCallback();
Task taskToggleBuiltinLED(BUILTINLED_TOGGLE_PERIOD * TASK_MILLISECOND, -1, &ToggleBuiltinLEDCallback, &mainScheduler, true);

constexpr auto BuiltinLEDPin = 2;
constexpr auto BlueLEDPin = 27;

uint32_t lastMillis;

void setup() 
{
	pinMode(BlueLEDPin, OUTPUT);
	pinMode(BuiltinLEDPin, OUTPUT);

#if defined(_DEBUG_) || defined(_TEST_)
	Serial.begin(115200);
	while (!Serial);
	_PL(F("/nJS Board ESP32"));
#endif

	lastMillis = millis();
}

void loop() 
{
	mainScheduler.execute();

	digitalWrite(BlueLEDPin, HIGH);
	delay(1000);
	digitalWrite(BlueLEDPin, LOW);
	delay(1000);
}

void ToggleBuiltinLEDCallback()
{
	digitalWrite(BuiltinLEDPin, !digitalRead(BuiltinLEDPin));
	_PL(millis() - lastMillis);
}
