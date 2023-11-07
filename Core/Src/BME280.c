/*
 * BME280.c
 *
 *  Created on: 6 de nov de 2023
 *      Author: Fellipe
 */

#include "BME280.h"

float bme280_temp(I2C_HandleTypeDef *hi2c, uint16_t devAdress){

	double var1,var2;
	float temperature;

	int32_t dig_sample,adc_T;
	int16_t dig_t2,dig_t3;
	uint16_t dig_t1;

	uint8_t temperature_data1[] = {0x88,0x89},
		  temperature_data2[] = {0x8A,0x8B},
		  temperature_data3[] = {0x8C,0x8D},

		  temperature_stored1[2],
		  temperature_stored2[2],
		  temperature_stored3[2],

		  sample_temperature_data[] = {0xFA},
		  temperature_stored_sample[3];

	HAL_I2C_Master_Transmit(hi2c,devAdress,sample_temperature_data,1,100);
	HAL_I2C_Master_Receive(hi2c,devAdress,&temperature_stored_sample,3,100);

	HAL_I2C_Master_Transmit(hi2c, devAdress, temperature_data1, 1, 100);
	HAL_I2C_Master_Receive(hi2c, devAdress, &temperature_stored1, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAdress, temperature_data2, 1, 100);
	HAL_I2C_Master_Receive(hi2c, devAdress, &temperature_stored2, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAdress, temperature_data3, 1, 100);
	HAL_I2C_Master_Receive(hi2c, devAdress, &temperature_stored3, 2, 100);


	dig_t1 = temperature_stored1[1];
	dig_t1 = (dig_t1 << 8) + temperature_stored1[0];

	dig_t2 = temperature_stored2[1];
	dig_t2 = (dig_t2 << 8) + temperature_stored2[0];

	dig_t3 = temperature_stored3[1];
	dig_t3 = (dig_t3 << 8) + temperature_stored3[0];


	dig_sample = temperature_stored_sample[0];
	dig_sample = (dig_sample << 12);
	dig_sample += (temperature_stored_sample[1] << 4);
	dig_sample += temperature_stored_sample[0];

	adc_T = dig_sample;

	var1  = (((double)adc_T)/16384.0 - ((double)dig_t1)/1024.0) * ((double)dig_t2);
	var2  = ((((double)adc_T)/131072.0 - ((double)dig_t1)/8192.0) * (((double)adc_T)/131072.0 - ((double) dig_t1)/8192.0)) * ((double)dig_t3);
	temperature = (var1 + var2) / 5120;

	return temperature;

}
