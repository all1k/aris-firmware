#include "ec_sensor.hpp"

namespace aris {

ConductivitySensor::ConductivitySensor(std::uint8_t pin) {
	pin_ = pin;
}

bool ConductivitySensor::init(void) {
	voltage_ = 0.0f;
	data_ = 0.0f;
	data_raw_ = 0.0f;
	pinMode(pin_, INPUT);
	return true;
}

bool ConductivitySensor::update(void) {
	voltage_ = getVoltage() * std::pow(10, 3); // Use mV instead of V
	data_raw_ = 1000 * voltage_ / ECRES / ECREF * kvalue_ * 10.0f;
	data_ = data_raw_ / (1.0f + 0.0185 * (temp_sensor->getData() - 25.0f));
	return true;
}

void ConductivitySensor::attachTempSensor(std::shared_ptr<Sensor<float>>& ptr) {
	temp_sensor_ = ptr;
	if (temp_sensor_ != ptr) {
		return false;
	}
	else {
		return true;
	}
}

}
