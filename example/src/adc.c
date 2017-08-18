/*
 * adc.c
 *
 *  Created on: 18 авг. 2017 г.
 *      Author: kvaoar
 */
#include "adc.h"


uint16_t recieveData() {

unsigned short delay = 0;
uint8_t res[3];
uint16_t val = 0;
uint16_t tmp = 0;
int i = 0;

GPIO_WriteLow(ADC_PORT, ADC_CS);

for(i = 0; i < 3; i++){
		SPI_SendData(0);
		while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
		while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
		res[i] = SPI_ReceiveData();
		};

GPIO_WriteHigh(ADC_PORT, ADC_CS);

tmp = res[0];
val |= (tmp>>2);
tmp = res[1];
val |= (tmp<<6);
tmp = res[2];
val |= (tmp<<14);
return val;

}

uint16_t adc_get(){
uint16_t adccode = recieveData();



return adccode/10;
}
