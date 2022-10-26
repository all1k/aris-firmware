#define UINITY_INCLUDE_FLOAT

#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <do_sensor.hpp>
#include <temperature_sensor.hpp>
#include <vector>
#include <numeric>
#include <string>

aris::Sensor<float>* sensor;
std::shared_ptr<aris::Sensor<float>> temp_sensor;

void setUp(void) {
	temp_sensor.reset(new aris::TemperatureSensor(TEMPERATURE_SENSOR_PIN));
	if (!temp_sensor->init()) {
		TEST_FAIL_MESSAGE("Failed to initialize object");
	}
	sensor = new aris::DissolvedOxygenSensor(DO_SENSOR_PIN, temp_sensor);
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
		TEST_FAIL_MESSAGE("-1.0 Voltage returned");
	}
	TEST_ASSERT_FLOAT_WITHIN(1.0f, 0.0f, voltage);
}

void test_data_reading(void) {
	float data = sensor->getData();
	if (data < 0.0f) {
		TEST_FAIL_MESSAGE("-1.0 Data returned");
	}
	TEST_ASSERT_FLOAT_WITHIN(1.0f, 0.0f, data);
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_voltage_reading);
	RUN_TEST(test_data_reading);
	UNITY_END();
}

void loop() {}
