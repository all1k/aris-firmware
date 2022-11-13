#include "temperature_sensor.hpp"

namespace aris {

TemperatureSensor::TemperatureSensor(std::uint8_t pin) {
	pin_ = pin;
	this->init();
}

bool TemperatureSensor::init(void) {
	data_ = 0.0f;
	wire_.reset(new OneWire(pin_));
	return true;
}

bool TemperatureSensor::update(void) {
	std::uint8_t data[12], addr[8];
	if (!wire_->search(addr)) {
		wire_->reset_search();
		return false;
	}
	if (OneWire::crc8(addr, 7) != addr[7]) {
		return false;
	}
	if ((addr[0]!=0x10) && (addr[0]!=0x28)) {
		return false;
	}

	wire_->reset();
	wire_->select(addr);
	wire_->write(0x44, 1);

	std::uint8_t present = wire_->reset();

	wire_->select(addr);
	wire_->write(0xBE);
	for (int i = 0; i < 9; i++) {
		data[i] = wire_->read();
	}

	wire_->reset_search();

	std::uint8_t high_byte = data[1];
	std::uint8_t low_byte = data[0];
	float temp_read = ((high_byte << 8) | low_byte);
	data_ = temp_read / 16;

	return true;
}

void TemperatureSensor::calibrate(void) {
	;;
}

}
