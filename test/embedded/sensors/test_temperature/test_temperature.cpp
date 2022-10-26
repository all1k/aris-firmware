#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <temperature_sensor.hpp>
#include <vector>
#include <numeric>
#include <string>

aris::Sensor<float>* sensor;

void setUp(void) {
	sensor = new aris::TemperatureSensor(TEMPERATURE_SENSOR_PIN);
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

template<typename Type>
void checkDataValidity(Type data, Type upper_tresh, Type low_tresh) {
	if (data < low_tresh) {
		TEST_FAIL_MESSAGE("Data below lower threshold");
	}
	else if (data > upper_tresh) {
		TEST_FAIL_MESSAGE("Data above upper threshold");
	}
}

void test_data_reading(void) {
	std::uint64_t timestamp = millis();
	std::uint64_t test_interval = TEST_READING_INTERVAL;
	std::vector<float> data_array;
	float data;
	TEST_MESSAGE("Aquiring data ... ");
	while((millis() - timestamp) < test_interval) {
		data = sensor->getData();
		data_array.push_back(data);
		checkDataValidity(data, 125.0f, -55.0f);
		delay(10);
	}
	float data_average = getAverage(data_array);
	std::string msg;
	msg.append("Temperature = ");
	msg.append(std::to_string(data_average));
	msg.append(" Celcius");
	if ((data_average < 23.0f) && (data_average > 36.0f)) {
		TEST_FAIL_MESSAGE(msg.c_str());
	}
	else {
		TEST_PASS_MESSAGE(msg.c_str());
	}
}

void setup() {
	UNITY_BEGIN();
	RUN_TEST(test_data_reading);
	UNITY_END();
}

void loop() {
	;;
}
