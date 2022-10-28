#include "data_acquisition.hpp"

namespace aris {

DataAcquisitionTask::DataAcquisitionTask(
		std::shared_ptr<SensorInterface> sensor,
		float frequency,
		bool start_active)
{
	sensor_ = sensor;
	timestamp_ = 0ul;
	frequency_ = frequency;
	active_ = start_active;
}

void DataAcquisitionTask::run(void) {
	if (!active_) {
		return void();
	}
	else {
		std::uint64_t time_period;
		time_period = std::uint64_t(std::lround(1000.0f/frequency_));
		if ((millis() - timestamp_) > time_period) {
			timestamp_ = millis();
			sensor_->update();
		}
	}
}

void DataAcquisitionTask::halt(bool active) {
	active_ = active;
}

void DataAquisitionManager::init(void) {
	;;
}

bool DataAquisitionManager::asyncRun(void) {
	for (const auto& it : tasks_) {
		auto& task_ptr = it.second;
		task_ptr->run();
	}
	return true;
}

bool DataAquisitionManager::spawn(
		const std::uint8_t& id,
		std::shared_ptr<SensorInterface> ptr,
		float frequency,
		bool start)
{
	std::shared_ptr<DataAcquisitionTask> new_task;
	new_task.reset(new DataAcquisitionTask(ptr, frequency, start));
	tasks_.insert(make_pair(id, new_task));
	return true;
}

}
