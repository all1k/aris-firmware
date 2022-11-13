#ifndef _ARIS_PH_SENSOR_HPP_
#define _ARIS_PH_SENSOR_HPP_

#include <Arduino.h>
#include <sensor.hpp>

namespace aris {

class AnalogPhSensor : public Sensor {
	public:
		AnalogPhSensor(std::uint8_t pin);
		bool init(void) override;
		bool update(void) override;
		void calibrate(void) override;
};

}

#endif
