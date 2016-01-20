#include "Bluetooth.hpp"
#include <Arduino.h>

static const int STATE_PIN = 2;
static const int LED_PIN = 13;

#ifndef HAVE_HWSERIAL1
#error "Must use a board with Serial1"
#endif

Bluetooth::Bluetooth() :
	mState(LOW)
{
}

void Bluetooth::init() {
	pinMode(STATE_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
}

void Bluetooth::update() {
	int newState = digitalRead(STATE_PIN);
	if (mState != newState) {
		mState = newState;
		digitalWrite(LED_PIN, mState);
	}
}

bool Bluetooth::connected() const {
	return mState;
}
