#include "util.hpp"
#include <Arduino.h>

int averageAnalogRead(int pin) {
	uint8_t numberOfReadings = 8;
	unsigned int runningValue = 0;

	for (int x = 0; x < numberOfReadings; x++) {
		runningValue += analogRead(pin);
	}
	runningValue /= numberOfReadings;

	return runningValue;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
