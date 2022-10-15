#define UINITY_INCLUDE_FLOAT

#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <do_sensor.hpp>

aris::Sensor<float>* sensor;

void setUp(void) {
	pinMode(DO_SENSOR_PIN, OUTPUT);
	digitalWrite(DO_SENSOR_PIN, LOW);
	delay(500);
	sensor = new aris::DissolvedOxygenSensor(DO_SENSOR_PIN);
	sensor->init();
	delay(500);
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
