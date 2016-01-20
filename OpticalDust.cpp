#include "OpticalDust.hpp"
#include <Arduino.h>

static const int MEASURE_PIN = A4;
static const int LED_PIN = 4;
static const int SAMPLING_TIME = 280;
static const int DELTA_TIME = 40;
static const int SLEEP_TIME = 9680;

OpticalDust::OpticalDust() :
	value(0),
	mVoMeasured(0),
	mCalcVoltage(0)
{
}

void OpticalDust::init() {
	pinMode(LED_PIN,OUTPUT);
}

void OpticalDust::update() {
	digitalWrite(LED_PIN, LOW); // power on the LED
	delayMicroseconds(SAMPLING_TIME);

	mVoMeasured = analogRead(MEASURE_PIN); // read the dust value

	delayMicroseconds(DELTA_TIME);
	digitalWrite(LED_PIN, HIGH); // turn the LED off
	delayMicroseconds(SLEEP_TIME);

	// 0 - 3.3V mapped to 0 - 1023 integer values
	// recover voltage
	mCalcVoltage = mVoMeasured * (3.3 / 1024);

	// linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
	// Chris Nafis (c) 2012
	value = 0.17 * mCalcVoltage - 0.1;
}
