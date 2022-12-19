#ifndef _ARIS_SENSOR_HPP_
#define _ARIS_SENSOR_HPP_

#include <Arduino.h>
#include <conf.h>

#include <cmath>
#include <cstdint>
#include <memory>

namespace aris {

class SensorInterface {
	public:
		virtual bool        update(void)         = 0;
		virtual float       getData(void) const  = 0;
		virtual std::string getLabel(void) const = 0;
};

class Sensor : virtual public SensorInterface {
	protected:
		std::string          label_;
		std::uint8_t         pin_;
		std::uint16_t        adc_value_;
		float                voltage_;
		float                data_;
		float                offset_;
		static std::uint16_t adc_res_;
		static float         vref_;

		Sensor(void);

	public:
		static void setAdcResolution(std::uint16_t res);
		static void setVoltageReference(float ref);

		virtual bool init(void)      = 0;
		virtual bool update(void)    = 0;
		virtual void calibrate(void) = 0;
		virtual bool attach(std::shared_ptr<Sensor> const& ptr);

		void readAdc(void);
		void readVoltage(void);

		void setLabel(std::string label);
		void setOffset(float offset);

		std::string   getLabel(void) const;
		std::uint16_t getAdcValue(void) const;
		float         getVoltage(void) const;
		float         getData(void) const override;
};

}  // namespace aris

#endif
