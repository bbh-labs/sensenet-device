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
	const int uvLevel = analogRead(UVOUT);
	delay(10);
	const int refLevel = analogRead(REF_3V3);
	delay(10);

	const float outputVoltage = 3.3 / refLevel * uvLevel;
	//Serial.print(uvLevel);
	//Serial.print(" ");
	//Serial.println(refLevel);
	value = mapfloat(outputVoltage, 0.0, 3.3, 0.0, 15.0); // Convert the voltage to a UV intensity level
}
