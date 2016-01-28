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
	value = analogRead(CO_PIN);
}
