#include "OpticalDust.hpp"
#include <Arduino.h>

const float OpticalDust::minValue = 0;
const float OpticalDust::maxValue = 8000;

static const int PIN = 8;
static const unsigned long SAMPLE_TIME_MS = 2000;

OpticalDust::OpticalDust() :
	value(0),
	mStartTime(0),
	mLowPulseOccupancy(0)
{
}

void OpticalDust::init() {
	pinMode(PIN, INPUT);
	mStartTime = millis();
}

void OpticalDust::update() {
	const unsigned long duration = pulseIn(PIN, LOW);
	mLowPulseOccupancy += duration;

	// if the sample time == 30s
	if ((millis() - mStartTime) >= SAMPLE_TIME_MS) {
		const float ratio = mLowPulseOccupancy / (SAMPLE_TIME_MS * 10.0);  // Integer percentage 0=&gt;100
		value = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62; // using spec sheet curve (pcs/0.01cf)
		mLowPulseOccupancy = 0;
		mStartTime = millis();
	}
}
