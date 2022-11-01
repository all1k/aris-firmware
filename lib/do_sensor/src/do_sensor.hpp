#ifndef _ARIS_DISSOLVED_OXYGEN_SENSOR_HPP_
#define _ARIS_DISSOLVED_OXYGEN_SENSOR_HPP_

#include <Arduino.h>
#include <sensor.hpp>
#include <memory>

namespace aris {

const std::size_t do_max_temperature = 41;

const std::array<std::uint16_t, do_max_temperature> g_do_table =
{
	14460, 14220, 13820, 13090, 12740, 12420, 12110, 11810,
	11530, 11260, 11010, 10770, 10530, 10300, 10080, 9860 ,
	9660 , 9460 , 9270 , 9080 , 8900 , 8730 , 8570 , 8410 ,
	8250 , 8110 , 7960 , 7820 , 7690 , 7560 , 7430 , 7300 ,
	7180 , 7070 , 6950 , 6840 , 6730 , 6630 , 6530 , 6410 ,
};

class DissolvedOxygenSensor : public Sensor {
	private:
		std::uint16_t sat_voltage_;
		std::uint16_t cal_voltage_;
		std::uint16_t cal_temp_;

		std::shared_ptr<Sensor> temp_sensor_;

	public:
		DissolvedOxygenSensor(std::uint8_t pin, std::shared_ptr<Sensor>& ptr);
		bool init(void) override;
		bool update(void) override;
		bool attach(const std::shared_ptr<Sensor>& ptr);
		void setCalibrationVoltage(std::uint16_t voltage);
		void setCalibrationTemperature(std::uint16_t temperature);
};

}

#endif
