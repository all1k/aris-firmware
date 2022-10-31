#define TEMPERATURE_SENSOR_TEST

#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <temperature_sensor.hpp>
#include <vector>
#include <string>

#include "../../../test_utilities.h"

aris::Sensor* sensor;

void setUp(void) {
	sensor = new aris::TemperatureSensor(TEMPERATURE_SENSOR_PIN);
	if (!sensor->init()) {
		TEST_FAIL_MESSAGE("Failed to initialize object");
	}
}

void tearDown(void) {
	delete sensor;
}

void test_data_reading(void) {
	std::uint64_t timestamp = millis();
	std::vector<float> data_array;
	TEST_MESSAGE("Aquiring data ... ");
	while((millis() - timestamp) < TEST_READING_INTERVAL) {
		float data = sensor->getData();
		data_array.push_back(data);
		delay(10);
	}
	float data_average = aristest::getAverage(data_array);
	aristest::checkDataValidity(data_average, 36.0f, 26.0f);
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_data_reading);
	UNITY_END();
}

void loop() {
	;;
}
