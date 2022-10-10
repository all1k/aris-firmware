#define UINITY_INCLUDE_FLOAT

#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <temperature_sensor.hpp>
#include <vector>
#include <numeric>
#include <string>

arislib::Sensor<float>* sensor;

void setUp(void) {
	delay(500);
	sensor = new arislib::TemperatureSensor(TEMPERATURE_SENSOR_PIN);
	if (!sensor->init()) {
		TEST_FAIL_MESSAGE("Failed to initialize object");
	}
	delay(500);
}

void tearDown(void) {
	delete sensor;
}

template<typename Type>
float getAverage(std::vector<Type> const& v) {
	if (v.empty()) {
		return 0;
	}
	else {
		return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
	}
}

void test_temperature_reading(void) {
	std::uint64_t timestamp = millis();
	std::uint64_t test_interval = 60000;
	std::vector<float> data_array;
	float data;
	TEST_MESSAGE("Sampling data");
	while((millis() - timestamp) < test_interval) {
		data = sensor->getData();
		data_array.push_back(data);
		std::string data_string = std::to_string(data);
		TEST_MESSAGE(data_string.c_str());
		if (data < -55.0f) {
			TEST_FAIL_MESSAGE("Data below lower threshold");
			break;
		}
		else if (data > 125.0f) {
			TEST_FAIL_MESSAGE("Data above upper threshold");
			break;
		}
		delay(500);
	}
	TEST_ASSERT_FLOAT_WITHIN(16.0f, 26.0f, getAverage(data_array));
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_temperature_reading);
	UNITY_END();
}

void loop() {}
