#ifndef TURBIDITY_SENSOR_HPP
#define TURBIDITY_SENSOR_HPP

#include <Arduino.h>
#include <sensor.hpp>

namespace aris {

class TurbiditySensor : public Sensor<float> {
	public:
		TurbiditySensor(std::uint8_t pin);
		bool init(void);
		bool update(void);
};

}

#endif
