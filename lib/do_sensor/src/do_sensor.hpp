#ifndef DISSOLVED_OXYGEN_SENSOR_HPP
#define DISSOLVED_OXYGEN_SENSOR_HPP

#include <Arduino.h>
#include <sensor.hpp>
#include <memory>

namespace aris {

const uint16_t g_do_table[41] =
{
	14460, 14220, 13820, 13090, 12740, 12420, 12110, 11810,
	11530, 11260, 11010, 10770, 10530, 10300, 10080, 9860 ,
	9660 , 9460 , 9270 , 9080 , 8900 , 8730 , 8570 , 8410 ,
	8250 , 8110 , 7960 , 7820 , 7690 , 7560 , 7430 , 7300 ,
	7180 , 7070 , 6950 , 6840 , 6730 , 6630 , 6530 , 6410 ,
};

class DissolvedOxygenSensor : public Sensor<float> {
	private:
		std::uint16_t sat_voltage_;
		std::uint16_t cal_voltage_;
		std::uint16_t cal_temp_;

		std::shared_ptr<Sensor> temp_sensor_;

	public:
		DissolvedOxygenSensor(std::uint8_t pin);
		bool init(void);
		bool update(void);
		bool attachTemperatureSensor(std::shared_ptr<Sensor<float>>& ptr);
		void setCalibrationVoltage(std::uint16_t voltage);
		void setCalibrationTemperature(std::uint16_t temperature);
};

}

#endif
