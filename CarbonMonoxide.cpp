#include "CarbonMonoxide.hpp"
#include <Arduino.h>

static const int CO_PIN = A0;

CarbonMonoxide::CarbonMonoxide() :
	value(0)
{
}

void CarbonMonoxide::init() {
	// Carbon Monoxide
	pinMode(CO_PIN, INPUT);
}

void CarbonMonoxide::update() {
	// Warm-up analogRead
	analogRead(CO_PIN);
	delay(10);

	// Actual reading
	value = analogRead(CO_PIN);
	delay(10);
}
