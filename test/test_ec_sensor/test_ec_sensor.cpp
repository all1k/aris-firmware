#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <ec_sensor.hpp>
#include <vector>
#include <numeric>
#include <string>

aris::Sensor<float>* sensor;

void setUp(void) {
	sensor = new aris::ConductivitySensor(CONDUCTIVITY_SENSOR_PIN);
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

void test_conductivity_reading(void) {
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
		delay(500);
	}
	TEST_ASSERT_FLOAT_WITHIN(90.0f, 55.0f, getAverage(data_array));
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_conductivity_reading);
	UNITY_END();
}

void loop() {}
