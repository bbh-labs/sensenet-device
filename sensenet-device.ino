#include <DHT.h>

//#define ATMODE
//#define DEBUG

// Temperature & Humidity
#define DHTPIN 3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
static float humidity;
static float celcius;
static float celciusIndex;
static float fahrenheit;
static float fahrenheitIndex;

// Carbon Monoxide
#define CO_PIN A2
static int co; // Analog sensor data

// UV
#define UVOUT A0
#define REF_3V3 A1
static float uvIntensity;

// Level
#define LEVEL_PIN 6

// Bluetooth
#define STATE_PIN 2
#define KEY_PIN 8
#define LED_PIN 13

static int state = LOW;

void setup() {
	#ifdef DEBUG
	Serial.begin(9600);
	#endif
	
	pinMode(STATE_PIN, INPUT);
	pinMode(KEY_PIN, OUTPUT);
	digitalWrite(KEY_PIN, HIGH);

	// Temperature & Humidity
	dht.begin();

	// Carbon Monoxide
	pinMode(CO_PIN, INPUT);

	// UV
	pinMode(UVOUT, INPUT);
	pinMode(REF_3V3, INPUT);

	// Level
	pinMode(LEVEL_PIN, OUTPUT);
	analogWrite(LEVEL_PIN, 142);

	// Bluetooth
	#ifdef ATMODE
	Serial1.begin(38400);
	delay(1000);
	Serial1.write("AT+ROLE\r\n");
	#else
	Serial1.begin(9600);
	#endif
	
	// LED
	pinMode(LED_PIN, OUTPUT);
}

void loop() {
	#ifdef ATMODE
	if (Serial1.available()) {
		Serial.write(Serial1.read());
	}
	#else
	doTemperatureAndHumidity();
	doCarbonMonoxide();
	doUV();

	int newState = digitalRead(STATE_PIN);
	if (state != newState) {
		state = newState;
		#ifdef DEBUG
		if (state == LOW) {
			Serial.println("Bluetooth disconnected");
		} else {
			Serial.println("Bluetooth connected");
		}
		#endif
		digitalWrite(LED_PIN, state);
	}
	if (state == HIGH) {
		char buf[384] = { 0 };
		sprintf(buf, "{\"humidity\":%d,\"celcius\":%d,\"fahrenheit\":%d,\"celciusIndex\":%d,\"fahrenheitIndex\":%d,\"CO\":%d,\"UV\":%d}\r\n", (int) humidity, (int) celcius, (int) fahrenheit, (int) celciusIndex, (int) fahrenheitIndex, co, (int) uvIntensity);
		Serial1.write(buf);
		Serial1.flush();
	}
	delay(1000);
	#endif
}

void doTemperatureAndHumidity() {
	humidity = dht.readHumidity();
	celcius = dht.readTemperature();
	fahrenheit = dht.readTemperature(true);
	if (isnan(humidity) || isnan(celcius) || isnan(fahrenheit)) {
		#ifdef DEBUG
		Serial.println("Failed to read from DHT sensor!");
		#endif
		return;
	}

	// Compute heat index in Celsius (isFahreheit = false)
	celciusIndex = dht.computeHeatIndex(celcius, humidity, false);

	// Compute heat index in Fahrenheit (the default)
	fahrenheitIndex = dht.computeHeatIndex(fahrenheit, humidity);

	#ifdef DEBUG
	Serial.print("Humidity: ");
	Serial.print(humidity);
	Serial.print(" %\t");
	Serial.print("Temperature: ");
	Serial.print(celcius);
	Serial.print(" *C ");
	Serial.print(fahrenheit);
	Serial.print(" *F\t");
	Serial.print("Heat index: ");
	Serial.print(celciusIndex);
	Serial.print(" *C ");
	Serial.print(fahrenheitIndex);
	Serial.println(" *F");
	#endif
}

void doCarbonMonoxide() {
	co = analogRead(CO_PIN);
	#ifdef DEBUG
	Serial.print("Carbon Monoxide: ");
	Serial.println(co);
	#endif
}

void doUV() {
	int uvLevel = averageAnalogRead(UVOUT);
	int refLevel = averageAnalogRead(REF_3V3);
	float outputVoltage = 3.3 / refLevel * uvLevel;
	uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); // Convert the voltage to a UV intensity level

	#ifdef DEBUG
	Serial.print("UV: ");
	Serial.println(uvIntensity);
	#endif
}

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
