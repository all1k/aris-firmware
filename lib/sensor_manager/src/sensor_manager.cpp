#include "sensor_manager.hpp"

namespace aris {

void SensorManager::init(void) : timestamp_(0) {
}

bool SensorManager::run(float frequency) {
	std::uint64_t time_period = 1000.0f / frequency;
	if ((millis() - timestamp_) > time_period) {
		time_stamp_ = millis();
		for (auto const& it : sensors_) {
			if (it->isUpdated()) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

bool SensorManager::spawn(const std::string& name, const std::shared_ptr<Sensor<float>>& ptr) {
	sensors_.insert(make_pair(name, ptr));
	return sensors_.contains(name);
}

float SensorManager:: getData(const std::string& name) {
	return sensors_[name]->getData();
}

}
