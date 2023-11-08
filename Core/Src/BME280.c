/*
 * BME280.c
 *
 *  Created on: 6 de nov de 2023
 *      Author: Fellipe
 */

#include "BME280.h"

double t_fine;

float bme280_temp(I2C_HandleTypeDef *hi2c, uint16_t devAddress){

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

	HAL_I2C_Master_Transmit(hi2c,devAddress,sample_temperature_data,1,100);
	HAL_I2C_Master_Receive(hi2c,devAddress,&temperature_stored_sample,3,100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, temperature_data1, 1, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &temperature_stored1, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, temperature_data2, 1, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &temperature_stored2, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, temperature_data3, 1, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &temperature_stored3, 2, 100);


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
	t_fine = var1 + var2;
	temperature = (var1 + var2) / 5120;

	return temperature;

}


float bme280_press(I2C_HandleTypeDef *hi2c, uint16_t devAddress){

	HAL_Delay(500);
	double var1,var2,p;

	uint8_t pressure_adress1[] = {0x8E,0x8F},
			pressure_adress2[] = {0x90,0x91},
			pressure_adress3[] = {0x92,0x93},
			pressure_adress4[] = {0x94,0x95},
			pressure_adress5[] = {0x96,0x97},
			pressure_adress6[] = {0x98,0x99},
			pressure_adress7[] = {0x9A,0x9B},
			pressure_adress8[] = {0x9C,0x9D},
			pressure_adress9[] = {0x9E,0x9F},

			stored_pressure_address_read1[2],
			stored_pressure_address_read2[2],
			stored_pressure_address_read3[2],
			stored_pressure_address_read4[2],
			stored_pressure_address_read5[2],
			stored_pressure_address_read6[2],
			stored_pressure_address_read7[2],
			stored_pressure_address_read8[2],
			stored_pressure_address_read9[2],

			sample_measurement_values[] = {0xF7,0xF8,0xF9},
			stored_sample_measurement_values[8];


	uint16_t dig_p1;

	int16_t dig_p2,
			dig_p3,
			dig_p4,
			dig_p5,
			dig_p6,
			dig_p7,
			dig_p8,
			dig_p9;

	int64_t adc_P;

	HAL_I2C_Master_Transmit(hi2c, devAddress, sample_measurement_values, 1, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_sample_measurement_values, 8, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress1, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read1, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress2, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read2, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress3, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read3, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress4, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read4, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress5, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read5, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress6, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read6, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress7, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read7, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress8, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read8, 2, 100);

	HAL_I2C_Master_Transmit(hi2c, devAddress, pressure_adress9, 2, 100);
	HAL_I2C_Master_Receive(hi2c, devAddress, &stored_pressure_address_read9, 2, 100);

	adc_P = ((stored_sample_measurement_values[0] << 12) + (stored_sample_measurement_values[1] << 4) + stored_sample_measurement_values[2]);


	dig_p1 = stored_pressure_address_read1[1];
	dig_p1 = (dig_p1 << 8) + stored_pressure_address_read1[0];

	dig_p2 = stored_pressure_address_read2[1];
	dig_p2 = (dig_p2 << 8) + stored_pressure_address_read2[0];

	dig_p3 = stored_pressure_address_read3[1];
	dig_p3 = (dig_p3 << 8) + stored_pressure_address_read3[0];

	dig_p4 = stored_pressure_address_read4[1];
	dig_p4 = (dig_p4 << 8) + stored_pressure_address_read4[0];

	dig_p5 = stored_pressure_address_read5[1];
	dig_p5 = (dig_p5 << 8) + stored_pressure_address_read5[0];

	dig_p6 = stored_pressure_address_read6[1];
	dig_p6 = (dig_p6 << 8) + stored_pressure_address_read6[0];

	dig_p7 = stored_pressure_address_read7[1];
	dig_p7 = (dig_p7 << 8) + stored_pressure_address_read7[0];

	dig_p8 = stored_pressure_address_read8[1];
	dig_p8 = (dig_p8 << 8) + stored_pressure_address_read8[0];

	dig_p9 = stored_pressure_address_read9[1];
	dig_p9 = (dig_p9 << 8) + stored_pressure_address_read9[0];

	var1 = ((double)t_fine/2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_p6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_p5) * 2.0;
	var2 = (var2/4.0)+(((double)dig_p4) * 65536.0);
	var1 = (((double)dig_p3) * var1 * var1 / 524288.0 + ((double)dig_p2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_p1);
	p = 1048576.0 - (double)adc_P;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_p9) * p * p / 2147483648.0;
	var2 = p * ((double)dig_p8) / 32768.0;
	p = p + (var1 + var2 + ((double)dig_p7)) / 16.0;
	p /= 100; // return hPA
	return p;

}
