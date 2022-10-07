#ifndef ARIS_CONFIG_H
#define ARIS_CONFIG_H

/////////////////////////
// ESP32 CONFIGURATION //
/////////////////////////

#define ADC_RESOLUTION			4096	// 12-bit analog to digital converter resolution
#define VREF					3.3f	// 3.3V voltage reference

/////////////////////////////////
// SIM800 MODULE CONFIG MACROS //
/////////////////////////////////

#define TINY_GSM_MODEM_SIM800			// Set module type
#define TINY_GSM_USE_GPRS		true	// Set SIM800 to use gprs
#define TINY_GSM_USE_WIFI		false	// Disable SIM800 Wi-Fi

////////////////////////////
// ANALOG pH METER MACROS //
////////////////////////////

#define PH_SENSOR_PIN			A0		// pH sensor pin number
#define PH_SENSOR_OFFSET		0.00	// pH value offset

/////////////////////////////
// TURBIDITY SENSOR MACROS //
/////////////////////////////

#define TURBIDITY_SENSOR_PIN	A1		// Turbidity sensor pin number

////////////////////////////////////
// DISSOLVED OXYGEN SENSOR MACROS //
////////////////////////////////////

#define DO_SENSOR_PIN			A2		// DO sensor pin number
#define TWO_POINT_CALIBRATION	false	// Enable or disable two point calibration
#define SATURATED_DO_VOLTAGE	1.6f	// Calibratied saturated do voltage
#define CALIBRATION_TEMPERATURE	25.0f	// Temperature while calibration performed

#endif
