#include "turbidity_sensor.hpp"

namespace aris {

TurbiditySensor::TurbiditySensor(std::uint8_t pin) {
	pin_ = pin;
	this->init();
}

bool TurbiditySensor::init(void) {
	voltage_ = 0.0f;
	data_ = 0.0f;
	pinMode(pin_, INPUT);
	return true;
}

bool TurbiditySensor::update(void) {
	this->readAdc();
	this->readVoltage();
	float shifted_voltage = (voltage_ * turbidity_vref_) / vref_;
	std::array<float, 3> coeficients = {-1120.4f, 5742.3f, -4352.9f};
	data_ = 0.0f;
	for (std::uint8_t i = 0; i < coeficients.size(); ++i) {
		data_ += coeficients.at(i) * std::pow(shifted_voltage, i);
	}
	if (data_ < 0.0f) {
		data_ = 0.50f;
		return false;
	}
	else {
		return true;
	}
}

void TurbiditySensor::calibrate(void) {
	;;
}

}
