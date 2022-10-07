#include "turbidity_sensor.hpp"

namespace arislib {

TurbiditySensor::TurbiditySensor(std::uint8_t pin) {
	pin_ = pin;
}

bool TurbiditySensor::init(void) {
	voltage_ = 0.0f;
	data_ = 0.0f;
	pinMode(pin_, INPUT);
	return true;
}

bool TurbiditySensor::update(void) {
	voltage_ = getVoltage();
	data_ = (voltage_ * 14.0f) / VREF;

	if ((data_ > 14.0f) || (data_ < 0.0f)) {
		return false;
	}
	else {
		return true;
	}
}

}
