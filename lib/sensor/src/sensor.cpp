#include "sensor.hpp"

namespace aris {

std::uint16_t Sensor::adc_res_;
float Sensor::vref_;

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

bool Sensor::attach(std::shared_ptr<Sensor> const& ptr) {
	;;
}

void Sensor::readAdc(void) {
	adc_value_ = analogRead(pin_);
}

void Sensor::readVoltage(void) {
	float adc_ratio = static_cast<float>(adc_value_)/static_cast<float>(adc_res_);
	voltage_ = vref_ * adc_ratio;
}

void Sensor::setLabel(std::string label) {
	label_ = label;
}

void Sensor::setOffset(float offset) {
	offset_ = offset;
}

std::string Sensor::getLabel(void) const {
	return label_;
}

std::uint16_t Sensor::getAdcValue(void) const {
	return adc_value_;
}

float Sensor::getVoltage(void) const {
	return voltage_;
}

float Sensor::getData(void) const {
	return data_;
}

}
