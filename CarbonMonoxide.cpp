#include "CarbonMonoxide.hpp"
#include <Arduino.h>

static const int CO_PIN = A2;
static const int LEVEL_PIN = 6;

CarbonMonoxide::CarbonMonoxide() :
	value(0)
{
}

void CarbonMonoxide::init() {
	// Carbon Monoxide
	pinMode(CO_PIN, INPUT);
	pinMode(LEVEL_PIN, OUTPUT);
	analogWrite(LEVEL_PIN, 142);
}

void CarbonMonoxide::update() {
	value = analogRead(CO_PIN);
}
