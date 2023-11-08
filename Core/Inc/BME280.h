/*
 * BME280.h
 *
 *  Created on: 6 de nov de 2023
 *      Author: Wagner Nogueira
 */

#ifndef INC_BME280_H_
#define INC_BME280_H_

#include "main.h"

double bme280_temp(I2C_HandleTypeDef *hi2c, uint16_t devAddress);	//Temperature function declaration
double bme280_press(I2C_HandleTypeDef *hi2c, uint16_t devAddress);	// Pressure function declaration
double bme280_hum(I2C_HandleTypeDef *hi2c, uint16_t devAddress);	// Humidity function declaration

#endif /* INC_BME280_H_ */
