/*
 * adc.h
 *
 *  Created on: 18 авг. 2017 г.
 *      Author: kvaoar
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm8s.h"

#define ADC_PORT  GPIOC
#define ADC_CS    GPIO_PIN_4


uint16_t adc_get();

#endif /* INC_ADC_H_ */
