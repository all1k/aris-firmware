#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "configuration/conf.h"

#include <Arduino.h>
#include <cstdint>

namespace arislib {

template <typename Type>
class Sensor {
	protected:
		std::uint8_t pin_;
		float voltage_;
		Type data_;
	
	public:
		virtual bool init(void) = 0;
		virtual bool update(void) = 0;

		float getVoltage(void) {
			voltage_ = (static_cast<float>(analogRead(pin_)) * VREF) / ADC_RESOLUTION;
			return voltage_;
		}
		
		virtual Type getData(void) {
			if (!update()) {
				return -1.0f;
			}
			else {
				return data_;
			}
		}
};

}

#endif
