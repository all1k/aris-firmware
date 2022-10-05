#ifndef PH_SENSOR_HPP
#define PH_SENSOR_HPP

#include <Arduino.h>
#include <sensor.hpp>

namespace arislib {

class AnalogPhSensor : public Sensor<float> {
	private:
		float offset_;

	public:
		AnalogPhSensor(std::uint8_t pin, float offset);
		bool init(void);
		bool update(void);
};

}

#endif
