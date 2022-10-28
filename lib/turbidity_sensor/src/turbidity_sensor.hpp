#ifndef _ARIS_TURBIDITY_SENSOR_HPP_
#define _ARIS_TURBIDITY_SENSOR_HPP_

#include <Arduino.h>
#include <sensor.hpp>

namespace aris {

class TurbiditySensor : public Sensor {
	private:
		const float turbidity_vref_ = 5.0f;

	public:
		TurbiditySensor(std::uint8_t pin);
		bool init(void) override;
		bool update(void) override;
};

}

#endif
