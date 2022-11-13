#ifndef _ARIS_TEMPERATURE_SENSOR_HPP_
#define _ARIS_TEMPERATURE_SENSOR_HPP_

#include <Arduino.h>
#include <OneWire.h>
#include <memory>
#include <sensor.hpp>

namespace aris {

class TemperatureSensor : public Sensor {
	private:
		std::unique_ptr<OneWire> wire_;

	public:
		TemperatureSensor(std::uint8_t pin);
		bool init(void) override;
		bool update(void) override;
		void calibrate(void) override;

		void readAdc(void) = delete;
		void readVoltage(void) = delete;
		std::uint16_t getAdcValue(void) const = delete;
		float getVoltage(void) const = delete;
};


}

#endif
