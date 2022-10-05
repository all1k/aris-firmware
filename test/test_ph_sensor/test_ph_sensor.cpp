#define SENSOR_PIN				A0
#define SENSOR_OFFSET			0.0f
#define UINITY_INCLUDE_FLOAT

#include <Arduino.h>
#include <unity.h>
#include <SEN0161.h>

void setUp(void) {
	pinMode(SENSOR_PIN, OUTPUT);
	digitalWrite(SENSOR_PIN, LOW);
	delay(1000);
}

void tearDown(void) {}

void test_voltage_reading(void) {
	arislib::AnalogPhSensor sensor(SENSOR_PIN, SENSOR_OFFSET);
	float voltage = sensor.getVoltage();
	TEST_ASSERT_FLOAT_WITHIN(1.0f, 0.0f, voltage);
	sensor.~Sensor();
}

void test_data_reading(void) {
	arislib::AnalogPhSensor sensor(SENSOR_PIN, SENSOR_OFFSET);
	float data = sensor.getData();
	TEST_ASSERT_FLOAT_WITHIN(1.0f, 0.0f, data);
	sensor.~Sensor();
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_voltage_reading);
	RUN_TEST(test_data_reading);
	UNITY_END();
}

void loop() {
}
