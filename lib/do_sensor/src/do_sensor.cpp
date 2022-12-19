#include "do_sensor.hpp"

namespace aris {

DissolvedOxygenSensor::DissolvedOxygenSensor(std::uint8_t pin) {
	pin_ = pin;
	this->init();
}

bool DissolvedOxygenSensor::init(void) {
	voltage_ = 0.0f;
	data_    = 0.0f;
	preferences_.begin("do-sensor", false);
	cal_voltage_ = preferences_.getFloat("calvoltage", 1720);
	cal_temp_    = preferences_.getFloat("caltemp", 30);
	preferences_.end();
	pinMode(pin_, INPUT);
	return true;
}

bool DissolvedOxygenSensor::update(void) {
	if (temp_sensor_ == nullptr) {
		return false;
	}
	this->readAdc();
	this->readVoltage();
	std::uint16_t voltage_mv =
		static_cast<std::uint16_t>(voltage_ * std::pow(10, 3));
	std::uint16_t current_temp =
		static_cast<std::uint16_t>(temp_sensor_->getData());
	std::uint16_t sat_voltage =
		cal_voltage_ + 35 * current_temp - cal_temp_ * 35;
	data_ = (float)(voltage_mv * g_do_table.at(current_temp) / sat_voltage);
	data_ /= std::pow(10, 3);
	return true;
}

void DissolvedOxygenSensor::calibrate(void) {
	this->readAdc();
	this->readVoltage();
	cal_voltage_ = static_cast<std::uint16_t>(voltage_ * std::pow(10, 3));
	cal_temp_    = static_cast<std::uint16_t>(temp_sensor_->getData());
	preferences_.begin("do-sensor", false);
	preferences_.putFloat("calvoltage", cal_voltage_);
	preferences_.putFloat("caltemp", cal_temp_);
	preferences_.end();
}

bool DissolvedOxygenSensor::attach(std::shared_ptr<Sensor> const& ptr) {
	temp_sensor_ = ptr;
	if (temp_sensor_ == ptr) {
		return true;
	} else {
		return false;
	}
}

}  // namespace aris
