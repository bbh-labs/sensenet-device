#include "UV.hpp"
#include "util.hpp"
#include <Arduino.h>

static const int UVOUT = A0;
static const int REF_3V3 = A1;

UV::UV() :
	value(0)
{
}

void UV::init() {
	pinMode(UVOUT, INPUT);
	pinMode(REF_3V3, INPUT);
}

void UV::update() {
	int uvLevel = averageAnalogRead(UVOUT);
	int refLevel = averageAnalogRead(REF_3V3);
	float outputVoltage = 3.3 / refLevel * uvLevel;
	value = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); // Convert the voltage to a UV intensity level
}
