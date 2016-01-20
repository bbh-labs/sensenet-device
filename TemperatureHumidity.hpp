#ifndef TEMPERATURE_HUMIDITY_HPP
#define TEMPERATURE_HUMIDITY_HPP

#include <DHT.h>

class TemperatureHumidity {
public:
	float humidity;
	float celcius;
	float celciusIndex;
	float fahrenheit;
	float fahrenheitIndex;

	TemperatureHumidity();
	void init();
	void update();

private:
	DHT mDHT;
};

#endif
