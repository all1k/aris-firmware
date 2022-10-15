#include "ph_sensor.hpp"

namespace aris {

AnalogPhSensor::AnalogPhSensor(std::uint8_t pin, float offset) 
	: offset_{offset}
{
	pin_ = pin;
}

bool AnalogPhSensor::init(void) {
	voltage_ = 0.0f;
	data_ = 0.0f;
	pinMode(pin_, INPUT);
	return true;
}

bool AnalogPhSensor::update(void) {
	voltage_ = getVoltage();
	data_ = ((voltage_ * 14.0f) / VREF) + offset_;

	if ((data_ > 14.0f) || (data_ < 0.0f)) {
		return false;
	}
	else {
		return true;
	}
}

}
