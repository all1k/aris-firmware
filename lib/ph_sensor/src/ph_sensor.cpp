#include "ph_sensor.hpp"

namespace aris {

AnalogPhSensor::AnalogPhSensor(std::uint8_t pin) {
	pin_ = pin;
	this->init();
}

bool AnalogPhSensor::init(void) {
	voltage_ = 0.0f;
	data_    = 0.0f;
	pinMode(pin_, INPUT);
	return true;
}

bool AnalogPhSensor::update(void) {
	this->readAdc();
	this->readVoltage();
	data_ = ((voltage_ * 14.0f) / vref_) + offset_;
	if ((data_ > 14.0f) || (data_ < 0.0f)) {
		return false;
	} else {
		return true;
	}
}

void AnalogPhSensor::calibrate(void) {
	;
	;
}

}  // namespace aris
