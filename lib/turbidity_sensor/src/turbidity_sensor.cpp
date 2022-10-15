#include "turbidity_sensor.hpp"

namespace aris {

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
	voltage_ = (getVoltage() * TURBIDITY_SENSOR_VREF) / VREF;
	float A[3] = {-1120.4f, 5742.3f, 4352.9f};
	data_ = ((A[0]*std::pow(voltage_, 2)) + (A[1]*voltage_)) - A[2];
	if (data_ < 0.0f) {
		return false;
	}
	else {
		return true;
	}
}

}
