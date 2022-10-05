#ifndef SEN0161_H
#define SEN0161_H

#include <Arduino.h>
#include <Sensor.h>

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
