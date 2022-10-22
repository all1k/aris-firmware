#ifndef _ARIS_SENSOR_MANAGER_HPP_
#define _ARIS_SENSOR_MANAGER_HPP_

#include <Arduino.h>

namespace aris {

class SensorManager {
	private:
		std::map<std::string, std::shared_ptr<Sensor>> sensors_;

	public:
		bool run(float frequency);
		bool spawn(const std::string& name, const std::shared_ptr<Sensor>& ptr);
		float getData(const std::string& name);
}

}
