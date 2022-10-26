#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <conf.h>

#include <Arduino.h>
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

		std::uint16_t getAdcValue(void);
		float getVoltage(void);
		bool isUpdated(void);

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
