/*
 * BME280.h
 *
 *  Created on: 6 de nov de 2023
 *      Author: Fellipe
 */

#ifndef INC_BME280_H_
#define INC_BME280_H_

#include "main.h"

float bme280_temp(I2C_HandleTypeDef *hi2c, uint16_t devAddress);
float bme280_press(I2C_HandleTypeDef *hi2c, uint16_t devAddress);

#endif /* INC_BME280_H_ */
