#include "ec_sensor.hpp"

namespace aris {

ConductivitySensor::ConductivitySensor(std::uint8_t pin) {
	pin_ = pin;
	this->init();
}

bool ConductivitySensor::init(void) {
	voltage_ = 0.0f;
	data_ = 0.0f;
	preferences_.begin("ec-sensor", false);
	kvalue_ = preferences_.getFloat("kvalue", 1.254f);
	preferences_.end();
	pinMode(pin_, INPUT);
	return true;
}

bool ConductivitySensor::update(void) {
	this->readAdc();
	this->readVoltage();
	float voltage_mv = voltage_ * std::pow(10, 3);
	float data_raw_ = 1000.0f * voltage_mv / ec_res_ / ec_ref_ * kvalue_ * 10.0f;
	data_ = data_raw_ / (1.0f + 0.0185f * (temp_sensor_->getData() - 25.0f));
	return true;
}

void ConductivitySensor::calibrate(void) {
	float voltage_mv = voltage_ * std::pow(10, 3);
	float raw_ec_solution = 12.9f;
	raw_ec_solution *= 1.0f + 0.0185f * (temp_sensor_->getData()-25.0f);
	kvalue_ = ec_res_*ec_ref_*raw_ec_solution / std::pow(10, 3)/voltage_mv/10.0f;
	preferences_.begin("ec-sensor", false);
	preferences_.putFloat("kvalue", kvalue_);
	preferences_.end();
}

bool ConductivitySensor::attach(std::shared_ptr<Sensor> const& ptr) {
	temp_sensor_ = ptr;
	if (temp_sensor_ != ptr) {
		return false;
	}
	else {
		return true;
	}
}

}
