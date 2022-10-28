#include "sensor.hpp"

namespace aris {

Sensor::Sensor(void) {
	adc_res_ = 4096;
	vref_    = 3.3f;
}

void Sensor::setAdcResolution(std::uint16_t res) {
	adc_res_ = res;
}

void Sensor::setVoltageReference(float ref) {
	vref_ = ref;
}

std::uint16_t Sensor::getAdcValue(void) {
	adc_value_ = analogRead(pin_);
	return adc_value_;
}

float Sensor::getVoltage(void) {
	voltage_ = (static_cast<float>(getAdcValue())*vref_) / adc_res_;
	return voltage_;
}

float Sensor::getData(void) {
	if (!update()) {
		return -101.0f;
	}
	else {
		return data_;
	}
}

}
