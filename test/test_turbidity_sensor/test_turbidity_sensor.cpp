#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <turbidity_sensor.hpp>
#include <vector>
#include <numeric>
#include <string>

arislib::Sensor<float>* sensor;

void setUp(void) {
	sensor = new arislib::TurbiditySensor(TURBIDITY_SENSOR_PIN);
	if (!sensor->init()) {
		TEST_FAIL_MESSAGE("Failed to initialize object");
	}
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

void test_voltage_reading(void) {
	float voltage = sensor->getVoltage();
	if (voltage < 0.0f) {
		TEST_FAIL_MESSAGE("-1.0 Voltage returned");
	}
	TEST_ASSERT_FLOAT_WITHIN(1.0f, 3.3f, voltage);
}

void test_data_reading(void) {
	std::uint64_t timestamp = millis();
	std::uint64_t test_interval = 60000;
	std::uint16_t adc_value;
	std::vector<float> data_array, voltage_array;
	float data, voltage;
	TEST_MESSAGE("Sampling data");
	while((millis() - timestamp) < test_interval) {
		adc_value = sensor->getAdcValue();
		voltage = (sensor->getVoltage()*4.5f)/3.3f;
		voltage_array.push_back(voltage);
		data = sensor->getData();
		data_array.push_back(data);
		std::string message_string;
		message_string.append("D=");
		message_string.append(std::to_string(data));
		message_string.append("  V=");
		message_string.append(std::to_string(voltage));
		message_string.append("  A=");
		message_string.append(std::to_string(adc_value));
		TEST_MESSAGE(message_string.c_str());
		delay(500);
	}
	TEST_ASSERT_FLOAT_WITHIN(16.0f, 16.0f, getAverage(data_array));
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_voltage_reading);
	RUN_TEST(test_data_reading);
	UNITY_END();
}

void loop() {}
