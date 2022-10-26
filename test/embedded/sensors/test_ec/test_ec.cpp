#include <Arduino.h>
#include <unity.h>
#include <sensor.hpp>
#include <ec_sensor.hpp>
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
	sensor = new aris::ConductivitySensor(CONDUCTIVITY_SENSOR_PIN, temp_sensor);
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
		std::string msg;
		msg.append("Conductivity = ");
		msg.append(std::to_string(data));
		msg.append(" ms/cm");
		TEST_MESSAGE(msg.c_str());
		TEST_FAIL_MESSAGE("Data below lower threshold");
	}
	else if (data > upper_tresh) {
		std::string msg;
		msg.append("Conductivity = ");
		msg.append(std::to_string(data));
		msg.append(" ms/cm");
		TEST_MESSAGE(msg.c_str());
		TEST_FAIL_MESSAGE("Data above upper threshold");
	}
}

void test_voltage_reading(void) {
	float voltage = sensor->getVoltage();
	if (voltage < 0.0f) {
		TEST_FAIL_MESSAGE("Negative voltage returned");
	}
	TEST_ASSERT_FLOAT_WITHIN(3.3f, 1.65f, voltage);
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
		/* checkDataValidity(data, 100.0f, 10.0f); */
		delay(10);
	}
	float voltage = sensor->getVoltage();
	std::string vmsg;
	vmsg.append("Voltage = ");
	vmsg.append(std::to_string(voltage));
	vmsg.append(" V");
	TEST_MESSAGE(vmsg.c_str());
	float data_average = getAverage(data_array);
	std::string msg;
	msg.append("Conductivity = ");
	msg.append(std::to_string(data_average));
	msg.append(" ms/cm");
	if ((data_average < 10.0f) && (data_average > 100.0f)) {
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
