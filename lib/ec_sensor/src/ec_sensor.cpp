#include "ec_sensor.hpp"

namespace aris {

ConductivitySensor::ConductivitySensor
	(std::uint8_t pin, std::shared_ptr<Sensor<float>>& ptr)
{
	pin_ = pin;
	if (!attach(ptr)) {
		;;
	}
}

bool ConductivitySensor::init(void) {
	voltage_ = 0.0f;
	data_ = 0.0f;
	data_raw_ = 0.0f;
	kvalue_ = 1.254f;
	pinMode(pin_, INPUT);
	return true;
}

bool ConductivitySensor::update(void) {
	voltage_ = getVoltage() * std::pow(10, 3); // Use mV instead of V
	data_raw_ = 1000 * voltage_ / ECRES / ECREF * kvalue_ * 10.0f;
	data_ = data_raw_ / (1.0f + 0.0185 * (temp_sensor_->getData() - 25.0f));
	return true;
}

bool ConductivitySensor::attach(const std::shared_ptr<Sensor<float>>& ptr) {
	temp_sensor_ = ptr;
	if (temp_sensor_ != ptr) {
		return false;
	}
	else {
		return true;
	}
}

}
