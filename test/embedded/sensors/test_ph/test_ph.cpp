#define PH_SENSOR_TEST

#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <ph_sensor.hpp>
#include <vector>
#include <string>

#include "../../../test_utilities.h"

aris::Sensor* sensor;

void setUp(void) {
	sensor = new aris::AnalogPhSensor(PH_SENSOR_PIN, PH_SENSOR_OFFSET);
	if (!sensor->init()) {
		TEST_FAIL_MESSAGE("Failed to initialize object");
	}
}

void tearDown(void) {
	delete sensor;
}

void test_voltage_reading(void) {
	float voltage = sensor->getVoltage();
	if (voltage < 0.0f) {
		TEST_FAIL_MESSAGE("Negative voltage returned");
	}
	aristest::logValue(voltage, "Voltage", "Volt");
	TEST_ASSERT_FLOAT_WITHIN(3.3f, 1.65f, voltage);
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
	aristest::checkDataValidity(data_average, 8.0f, 6.0f);
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_voltage_reading);
	RUN_TEST(test_data_reading);
	UNITY_END();
}

void loop() {
	;;
}
