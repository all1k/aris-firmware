#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <conf.h>

#include <Arduino.h>
#include <memory>
#include <cstdint>
#include <cmath>

namespace aris {

template <typename Type>
class Sensor {
	protected:
		std::uint8_t pin_;
		std::uint16_t adc_value_;
		float voltage_;
		Type data_;
	
	public:
		virtual bool init(void) = 0;
		virtual bool update(void) = 0;

		std::uint16_t getAdcValue(void) {
			adc_value_ = analogRead(pin_);
			return adc_value_;
		}

		float getVoltage(void) {
			voltage_ = (static_cast<float>(getAdcValue()) * VREF) / ADC_RESOLUTION;
			return voltage_;
		}
		
		bool isUpdated(void) {
			if (!update()) {
				return false;
			}
			else {
				return true;
			}
		}

		virtual Type getData(void) {
			if (!isUpdated()) {
				return -101.0f;
			}
			else {
				return data_;
			}
		}
};

}

#endif
