#ifndef _ARIS_SENSOR_HPP_
#define _ARIS_SENSOR_HPP_

#include <conf.h>

#include <Arduino.h>
#include <memory>
#include <cstdint>
#include <cmath>

namespace aris {

	protected:
		std::uint8_t pin_;
		std::uint16_t adc_value_;
		float voltage_;
		float data_;
		static std::uint16_t adc_res_;
		static float vref_;

		Sensor(void);
	
	public:
		virtual bool init(void) = 0;
		virtual bool update(void) = 0;

		static void setAdcResolution(std::uint16_t res);
		static void setVoltageReference(float ref);

		std::uint16_t getAdcValue(void);
		float getVoltage(void);
		float getData(void) override;
};

}

#endif
