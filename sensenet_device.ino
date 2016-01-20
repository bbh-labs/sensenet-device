static const char DEVICE_ID[] = "71GM9xi757";

//#define USE_BLUETOOTH

#include "Bluetooth.hpp"
#include "CarbonMonoxide.hpp"
#include "TemperatureHumidity.hpp"
#include "UV.hpp"
#include "OpticalDust.hpp"

Bluetooth bluetooth;
CarbonMonoxide carbonMonoxide;
TemperatureHumidity temperatureHumidity;
UV uv;
OpticalDust opticalDust;

void setup() {
	carbonMonoxide.init();
	temperatureHumidity.init();
	uv.init();
	opticalDust.init();

	#ifdef USE_BLUETOOTH
	Serial1.begin(9600);
	bluetooth.init();
	#else
	Serial.begin(9600);
	#endif
}

void loop() {
	carbonMonoxide.update();
	temperatureHumidity.update();
	uv.update();
	opticalDust.update();

	#ifdef USE_BLUETOOTH
	bluetooth.update();
	if (bluetooth.connected()) {
		Serial1.print("{");
		Serial1.print("\"deviceID\":\"");
		Serial1.print(DEVICE_ID);
		Serial1.print("\",\"temperature\":");
		Serial1.print(temperatureHumidity.celcius);
		Serial1.print(",\"humidity\":");
		Serial1.print(temperatureHumidity.humidity);
		Serial1.print(",\"carbonMonoxide\":");
		Serial1.print(carbonMonoxide.value);
		Serial1.print(",\"uv\":");
		Serial1.print(uv.value);
		Serial1.print(",\"particles\":");
		Serial1.print(opticalDust.value);
		Serial1.println("}");
	}
	#else
	Serial.print("{");
	Serial.print("\"deviceID\":\"");
	Serial.print(DEVICE_ID);
	Serial.print("\",\"temperature\":");
	Serial.print(temperatureHumidity.celcius);
	Serial.print(",\"humidity\":");
	Serial.print(temperatureHumidity.humidity);
	Serial.print(",\"carbonMonoxide\":");
	Serial.print(carbonMonoxide.value);
	Serial.print(",\"uv\":");
	Serial.print(uv.value);
	Serial.print(",\"particles\":");
	Serial.print(opticalDust.value);
	Serial.println("}");
	#endif

	delay(10000);
}
