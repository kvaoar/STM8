/*
 * display.h
 *
 *  Created on: 18 авг. 2017 г.
 *      Author: kvaoar
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "stm8s.h"

#define DISPL_PORT  GPIOC
#define DISPL_CS    GPIO_PIN_3

typedef enum {
    REG_NO_OP         = 0x00 << 8,
    REG_DIGIT_0       = 0x01 << 8,
    REG_DIGIT_1       = 0x02 << 8,
    REG_DIGIT_2       = 0x03 << 8,
    REG_DIGIT_3       = 0x04 << 8,
    REG_DIGIT_4       = 0x05 << 8,
    REG_DIGIT_5       = 0x06 << 8,
    REG_DIGIT_6       = 0x07 << 8,
    REG_DIGIT_7       = 0x08 << 8,
    REG_DECODE_MODE   = 0x09 << 8,
    REG_INTENSITY     = 0x0A << 8,
    REG_SCAN_LIMIT    = 0x0B << 8,
    REG_SHUTDOWN      = 0x0C << 8,
    REG_DISPLAY_TEST  = 0x0F << 8,
}
MAX7219_REGISTERS;


unsigned short getSymbol(uint8_t number);
void sendData(signed short data);
void printError(void);
void max7219_setIntensivity(uint8_t intensivity);
void max7219_clean(void);
void ftoc( int in);

#endif /* INC_DISPLAY_H_ */
