#include <conf.h>

#include <Arduino.h>
#include <TinyGSM.h>

#include <memory>
#include <vector>
#include <string>

#include <sensor.hpp>
#include <temperature_sensor.hpp>
#include <turbidity_sensor.hpp>
#include <ph_sensor.hpp>
#include <ec_sensor.hpp>
#include <do_sensor.hpp>

#include <data_acquisition.hpp>

using SensorPointer = std::shared_ptr<aris::Sensor>;
using SensorInterface = std::shared_ptr<aris::SensorInterface>;
using SensorPointerVector = std::vector<SensorPointer>;
using SensorInterfaceVector = std::vector<SensorInterface>;

using aris::TemperatureSensor;
using aris::TurbiditySensor;
using aris::AnalogPhSensor;
using aris::ConductivitySensor;
using aris::DissolvedOxygenSensor;

aris::DataAcquisitionManager acquisition_manager;

SensorPointerVector sensor_pointers;
SensorInterfaceVector sensor_interfaces;

template<class Type>
SensorPointer createSensorInstance(std::uint8_t pin) {
	SensorPointer ptr = std::make_shared<Type>(pin);
	return ptr;
}

void setup() {
	Serial.begin(115200);

	sensor_pointers.push_back(createSensorInstance<TemperatureSensor>(DS18B20_PIN));
	sensor_pointers.push_back(createSensorInstance<TurbiditySensor>(SEN0189_PIN));
	sensor_pointers.push_back(createSensorInstance<AnalogPhSensor>(SEN0161_PIN));
	sensor_pointers.push_back(createSensorInstance<ConductivitySensor>(DFR0300_PIN));
	sensor_pointers.push_back(createSensorInstance<DissolvedOxygenSensor>(SEN0237_PIN));

	(*sensor_pointers.at(SEN0161_ID)).setOffset(SEN0161_OFFSET);

	sensor_pointers.at(DFR0300_ID)->attach(sensor_pointers.at(DS18B20_ID));
	sensor_pointers.at(SEN0237_ID)->attach(sensor_pointers.at(DS18B20_ID));

	acquisition_manager.spawn(DS18B20_ID, sensor_pointers[DS18B20_ID], 2.00f, true);
	acquisition_manager.spawn(SEN0189_ID, sensor_pointers[SEN0189_ID], 20.0f, true);
	acquisition_manager.spawn(SEN0161_ID, sensor_pointers[SEN0161_ID], 50.0f, true);
	acquisition_manager.spawn(DFR0300_ID, sensor_pointers[DFR0300_ID], 1.00f, true);
	acquisition_manager.spawn(SEN0237_ID, sensor_pointers[SEN0237_ID], 40.0f, true);

	for (std::size_t i = 0; i < sensor_pointers.size(); i++) {
		sensor_interfaces.push_back(sensor_pointers.at(i));
	}
}

void loop() {
	acquisition_manager.asyncRun();

	std::string log_msg;

	for (auto const& it : sensor_interfaces) {
		log_msg.append(std::to_string(it->getData()));
		log_msg.append("\t");
	}

	Serial.println(log_msg.c_str());
}
