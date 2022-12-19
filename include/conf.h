#ifndef _ARIS_CONFIG_H_
#define _ARIS_CONFIG_H_

#define ADC_RESOLUTION 4096  // 12-bit analog to digital converter resolution
#define VREF           3.3f  // 3.3V voltage reference

#define TINY_GSM_MODEM_SIM800    // Set module type
#define TINY_GSM_USE_GPRS true   // Set SIM800 to use gprs
#define TINY_GSM_USE_WIFI false  // Disable SIM800 Wi-Fi

#define DS18B20_ID  0
#define DS18B20_PIN 5  // DS18B20 pin number

#define SEN0189_ID  1
#define SEN0189_PIN A3  // Turbidity sensor pin number

#define SEN0161_ID     2
#define SEN0161_PIN    A0   // pH sensor pin number
#define SEN0161_OFFSET 2.8  // pH value offset

#define DFR0300_ID  3
#define DFR0300_PIN A5  // Conductivity sensor pin number

#define SEN0237_ID  4
#define SEN0237_PIN A4  // DO sensor pin number

#endif
