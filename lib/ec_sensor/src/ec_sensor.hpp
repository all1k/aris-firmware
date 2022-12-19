#ifndef _ARIS_CONDUCTIVITY_SENSOR_HPP_
#define _ARIS_CONDUCTIVITY_SENSOR_HPP_

#include <Arduino.h>
#include <Preferences.h>

#include <memory>
#include <sensor.hpp>

namespace aris {

class ConductivitySensor : public Sensor {
	private:
		std::shared_ptr<Sensor> temp_sensor_;
		Preferences             preferences_;
		float                   kvalue_;
		static constexpr float  ec_res_ = 7500.0f / 0.66f;
		static constexpr float  ec_ref_ = 20.0f;

	public:
		ConductivitySensor(std::uint8_t pin);
		bool init(void) override;
		bool update(void) override;
		void calibrate(void) override;
		bool attach(std::shared_ptr<Sensor> const& ptr) override;
};

}  // namespace aris

#endif
