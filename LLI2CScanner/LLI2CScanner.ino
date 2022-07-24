/*
 Name:		LLI2CScanner.ino
 Created:	7/23/2022 6:18:48 PM
 Author:	mitch
*/

#include "I2CScanner.h"

I2CScanner scanner;

const byte address;

void debug(byte address)
{
	Serial.print("Found at 0x");
	Serial.println(address, HEX);
}

void setup()
{
	Serial.begin(115200);
	while (!Serial) {};

	scanner.Init();
}

void loop()
{
	scanner.Execute(debug);
	delay(5000);
}