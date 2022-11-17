#include <conf.h>
#include <auth.h>

#include <Arduino.h>
#include <TinyGSM.h>
#include <WiFi.h>
#include <PubSubClient.h>

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

const std::string ssid = WIFI_SSID;
const std::string pass = WIFI_PASSWORD;
const std::string mqtt_server_ip = MQTT_BROKER_IP;

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);
unsigned long publish_timestamp = 0ul;
unsigned long publish_interval  = 100ul;

template<class Type>
SensorPointer createSensorInstance(std::uint8_t pin) {
	SensorPointer ptr = std::make_shared<Type>(pin);
	return ptr;
}

void setup_wifi() {
	delay(10);
	WiFi.begin(ssid.c_str(), pass.c_str());
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
	}
}

void callback(char* topic, byte* message, std::uint32_t length) {
	;;
}

void reconnectToMqttBroker() {
	while (!mqtt_client.connected()) {
		if (!mqtt_client.connect("ESP32Client")) {
			delay(5000);
		}
	}
}

void setup() {
	Serial.begin(115200);

	sensor_pointers.push_back(createSensorInstance<TemperatureSensor>(DS18B20_PIN));
	sensor_pointers.push_back(createSensorInstance<TurbiditySensor>(SEN0189_PIN));
	sensor_pointers.push_back(createSensorInstance<AnalogPhSensor>(SEN0161_PIN));
	sensor_pointers.push_back(createSensorInstance<ConductivitySensor>(DFR0300_PIN));
	sensor_pointers.push_back(createSensorInstance<DissolvedOxygenSensor>(SEN0237_PIN));

	sensor_pointers.at(DS18B20_ID)->setLabel("temperature");
	sensor_pointers.at(SEN0189_ID)->setLabel("turbidity");
	sensor_pointers.at(SEN0161_ID)->setLabel("ph");
	sensor_pointers.at(DFR0300_ID)->setLabel("conductivity");
	sensor_pointers.at(SEN0237_ID)->setLabel("do");

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

	setup_wifi();
	mqtt_client.setServer(mqtt_server_ip.c_str(), MQTT_BROKER_PORT);
	mqtt_client.setCallback(callback);
}

void loop() {
	if (!mqtt_client.connected()) {
		reconnectToMqttBroker();
	}

	mqtt_client.loop();
	acquisition_manager.asyncRun();

	if ((millis() - publish_timestamp) > publish_interval) {
		std::string log_msg;
		for (auto const& it : sensor_interfaces) {
			std::string topic_label = "esp32/";
			std::string msg;
			topic_label.append(it->getLabel());
			msg.append(std::to_string(it->getData()));
			mqtt_client.publish(topic_label.c_str(), msg.c_str());
			log_msg.append(std::to_string(it->getData()));
			log_msg.append("\t");
		}
		publish_timestamp = millis();
		Serial.println(log_msg.c_str());
	}
}
