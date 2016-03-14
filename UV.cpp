#include "UV.hpp"
#include "util.hpp"
#include <Arduino.h>

const float UV::minValue = 0;
const float UV::maxValue = 15;

static const int UVOUT = A1;

UV::UV() :
	value(0)
{
}

void UV::init() {
	pinMode(UVOUT, INPUT);
}

void UV::update() {
	int uvLevel = map(analogRead(UVOUT), 200, 1024, 0, 1024);
	delay(10);
	const int refLevel = 1024 * 3.3 / 5;
	delay(10);

	if (uvLevel < 0)
		uvLevel = 0;

	const float outputVoltage = 3.3 / refLevel * uvLevel;
	Serial.print(uvLevel);
	Serial.print(" ");
	Serial.println(refLevel);
	value = mapfloat(outputVoltage, 0.0, 3.3, minValue, maxValue); // Convert the voltage to a UV intensity level
}
