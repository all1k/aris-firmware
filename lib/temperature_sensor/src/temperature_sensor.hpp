#ifndef _ARIS_TEMPERATURE_SENSOR_HPP_
#define _ARIS_TEMPERATURE_SENSOR_HPP_

#include <memory>
#include <Arduino.h>
#include <OneWire.h>
#include <sensor.hpp>

namespace aris {

class TemperatureSensor : public Sensor {
	private:
		std::unique_ptr<OneWire> wire_;

	public:
		TemperatureSensor(std::uint8_t pin);
		bool init(void) override;
		bool update(void) override;

		std::uint16_t getAdcValue(void) = delete;
		float getVoltage(void) = delete;
};


}

#endif
