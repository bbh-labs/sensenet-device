#include "TemperatureHumidity.hpp"

static const int DHTPIN = 3;
static const int DHTTYPE = DHT22;

TemperatureHumidity::TemperatureHumidity() :
	mDHT(DHT(DHTPIN, DHTTYPE)),
	humidity(0),
	celcius(0),
	celciusIndex(0),
	fahrenheit(0),
	fahrenheitIndex(0)
{
}

void TemperatureHumidity::init() {
	mDHT.begin();
}

void TemperatureHumidity::update() {
	humidity = mDHT.readHumidity();
	celcius = mDHT.readTemperature();
	fahrenheit = mDHT.readTemperature(true);
	if (isnan(humidity) || isnan(celcius) || isnan(fahrenheit)) {
		return;
	}

	// Compute heat index in Celsius (isFahreheit = false)
	celciusIndex = mDHT.computeHeatIndex(celcius, humidity, false);

	// Compute heat index in Fahrenheit (the default)
	fahrenheitIndex = mDHT.computeHeatIndex(fahrenheit, humidity);
}
