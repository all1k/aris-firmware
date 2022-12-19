#ifndef _ARIS_DISSOLVED_OXYGEN_SENSOR_HPP_
#define _ARIS_DISSOLVED_OXYGEN_SENSOR_HPP_

#include <Arduino.h>
#include <Preferences.h>

#include <memory>
#include <sensor.hpp>

namespace aris {

const std::size_t do_max_temperature = 41;

const std::array<std::uint16_t, do_max_temperature> g_do_table = {
	0x387C, 0x378C, 0x35FC, 0x3322, 0x31C4, 0x3084, 0x2F4E, 0x2E22,
	0x2D0A, 0x2BFC, 0x2B02, 0x2A12, 0x2922, 0x283C, 0x2760, 0x2684,
	0x25BC, 0x24F4, 0x2436, 0x2378, 0x22C4, 0x221A, 0x217A, 0x20DA,
	0x203A, 0x1FAE, 0x1F18, 0x1E8C, 0x1E0A, 0x1D88, 0x1D06, 0x1C84,
	0x1C0C, 0x1B9E, 0x1B26, 0x1AB8, 0x1A4A, 0x19E6, 0x1982, 0x190A,
};

class DissolvedOxygenSensor : public Sensor {
	private:
		std::uint16_t cal_voltage_;
		std::uint16_t cal_temp_;

		std::shared_ptr<Sensor> temp_sensor_;
		Preferences             preferences_;

	public:
		DissolvedOxygenSensor(std::uint8_t pin);
		bool init(void) override;
		bool update(void) override;
		void calibrate(void) override;
		bool attach(std::shared_ptr<Sensor> const& ptr) override;
};

}  // namespace aris

#endif
