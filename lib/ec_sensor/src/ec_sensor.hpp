#ifndef _ARIS_CONDUCTIVITY_SENSOR_HPP_
#define _ARIS_CONDUCTIVITY_SENSOR_HPP_

#include <memory>
#include <Arduino.h>
#include <sensor.hpp>

namespace aris {

class ConductivitySensor : public Sensor {
	private:
		std::shared_ptr<Sensor> temp_sensor_;
		float data_raw_, kvalue_;
		const float ec_res_ = 7500.0f/0.66f;
		const float ec_ref_ = 20.0f;

	public:
		ConductivitySensor(std::uint8_t pin, std::shared_ptr<Sensor>& ptr);
		bool init(void) override;
		bool update(void) override;
		bool attach(const std::shared_ptr<Sensor>& ptr);
};


}

#endif
