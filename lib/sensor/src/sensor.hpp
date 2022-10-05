#ifndef SENSOR_HPP
#define SENSOR_HPP

#ifndef CONFIG_HPP
#define ADC_RESOLUTION 4096
#define LOGIC_LEVEL 3.3f
#endif

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
			voltage_ = (static_cast<float>(analogRead(pin_)) * LOGIC_LEVEL) / ADC_RESOLUTION;
			return voltage_;
		}
		
		Type getData(void) {
			data_ = static_cast<Type>(getVoltage());
			return data_;
		}
};

}

#endif
