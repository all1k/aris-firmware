#ifndef _ARIS_SENSOR_MANAGER_HPP_
#define _ARIS_SENSOR_MANAGER_HPP_

#include <Arduino.h>
#include <memory>
#include <map>

#include <sensor.hpp>

namespace aris {

class DataAcquisitionTask {
	private:
		std::shared_ptr<Sensor<float>> sensor_;
		std::uint64_t timestamp_;
		float frequency_;
		bool active_;

	public:
		DataAcquisitionTask(
				std::shared_ptr<Sensor<float>> sensor,
				float frequency,
				bool start_active);

		void run(void);
		void halt(bool active);
};

class DataAquisitionManager {
	private:
		std::map<std::uint8_t, std::shared_ptr<DataAcquisitionTask>> tasks_;

	public:
		void init(void);
		bool asyncRun(void);

		bool spawn(
				const std::uint8_t& id,
				std::shared_ptr<Sensor<float>> ptr,
				float frequency,
				bool start);
};

}

#endif
