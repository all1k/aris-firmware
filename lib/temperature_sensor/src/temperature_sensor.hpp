#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include <memory>
#include <Arduino.h>
#include <OneWire.h>
#include <sensor.hpp>

namespace aris {

class TemperatureSensor : public Sensor<float> {
	private:
		std::unique_ptr<OneWire> wire_;

	public:
		TemperatureSensor(std::uint8_t pin);
		bool init(void);
		bool update(void);

		std::uint16_t getAdcValue(void) = delete;
		float getVoltage(void) = delete;
};


}

#endif
