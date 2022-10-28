#ifndef _ARIS_DATA_ACQUISITION_
#define _ARIS_DATA_ACQUISITION_

#include <Arduino.h>
#include <memory>
#include <map>

#include <sensor.hpp>

namespace aris {

class DataAcquisitionTask {
	private:
		std::shared_ptr<SensorInterface> sensor_;
		std::uint64_t timestamp_;
		float frequency_;
		bool active_;

	public:
		DataAcquisitionTask(
				std::shared_ptr<SensorInterface> sensor,
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
				std::shared_ptr<SensorInterface> ptr,
				float frequency,
				bool start);
};

}

#endif
