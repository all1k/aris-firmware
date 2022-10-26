#include "sensor.hpp"

namespace aris {

std::uint16_t Sensor::getAdcValue(void) {
	adc_value_ = analogRead(pin_);
	return adc_value_;
}

float Sensor::getVoltage(void) {
	voltage_ = (static_cast<float>(getAdcValue()) * VREF) / ADC_RESOLUTION;
	return voltage_;
}

bool Sensor::isUpdated(void) {
	if (!update()) {
		return false;
	}
	else {
		return true;
	}
}

}
