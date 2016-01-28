#include "UV.hpp"
#include "util.hpp"
#include <Arduino.h>

static const int UVOUT = A1;
static const int REF_3V3 = A2;

UV::UV() :
	value(0)
{
}

void UV::init() {
	pinMode(UVOUT, INPUT);
	pinMode(REF_3V3, INPUT);
}

void UV::update() {
	const int uvLevel = averageAnalogRead(UVOUT);
	const int refLevel = averageAnalogRead(REF_3V3);
	const float outputVoltage = 3.3 / refLevel * uvLevel;
	value = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); // Convert the voltage to a UV intensity level
	Serial.print(uvLevel);
	Serial.print(" ");
	Serial.println(refLevel);
}
