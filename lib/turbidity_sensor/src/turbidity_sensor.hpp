#ifndef _ARIS_TURBIDITY_SENSOR_HPP_
#define _ARIS_TURBIDITY_SENSOR_HPP_

#include <Arduino.h>
#include <sensor.hpp>

namespace aris {

class TurbiditySensor : public Sensor {

	public:
		TurbiditySensor(std::uint8_t pin);
		bool init(void);
		bool update(void);
};

}

#endif
