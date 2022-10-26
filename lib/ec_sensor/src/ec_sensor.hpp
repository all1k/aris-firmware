#ifndef CONDUCTIVITY_SENSOR_HPP
#define CONDUCTIVITY_SENSOR_HPP

#define ECRES (7500.0f/0.66f)
#define ECREF 20.0f

#include <memory>
#include <Arduino.h>
#include <sensor.hpp>

namespace aris {

class ConductivitySensor : public Sensor<float> {
	private:
		std::shared_ptr<Sensor<float>> temp_sensor_;
		float data_raw_, kvalue_;

	public:
		ConductivitySensor(std::uint8_t pin, std::shared_ptr<Sensor<float>>& ptr);
		bool init(void);
		bool update(void);
		bool attach(const std::shared_ptr<Sensor<float>>& ptr);
};


}

#endif
