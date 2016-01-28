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

float mapfloat(float x, float min1, float max1, float min2, float max2) {
	return (x - min1) / (max1 - min1) * (max2 - min2) + min2;
}
