/*
 * display.c
 *
 *  Created on: 18 авг. 2017 г.
 *      Author: kvaoar
 */
#include "display.h"


int DIG[] = {1<<8, 2<<8, 3<<8, 4<<8};

char num[4];



unsigned short SYMBOLS[] = { 0x7E, 0x30, 0x6D, 0x79, 0x33,
  0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x00 };


uint16_t getSymbol(uint8_t number) {
  return SYMBOLS[number];
}



void sendData(signed short data) {

unsigned short delay = 0;

	GPIO_WriteLow(DISPL_PORT, DISPL_CS);
	                SPI_SendData(data>>8 & 0xff);
	                while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	                while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	                SPI_SendData(data & 0xff);
	                while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	         	    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	GPIO_WriteHigh(DISPL_PORT, DISPL_CS);

}


void printError(void)
{
  sendData(REG_SHUTDOWN | 0x01);
  sendData(REG_DECODE_MODE | 0x00);
  sendData(REG_SCAN_LIMIT | 0x03);
  sendData(REG_DIGIT_0 | 0x01); //-
  sendData(REG_DIGIT_1 | 0x4f); //e
  sendData(REG_DIGIT_3 | 0x05); //r
  sendData(REG_DIGIT_2 | 0x05); //r
}


void max7219_setIntensivity(uint8_t intensivity) {
  if (intensivity > 0x0F)
    return;
  sendData(REG_SHUTDOWN | 0x01);
  sendData(REG_DECODE_MODE | 0x00);
  sendData(REG_SCAN_LIMIT | 0x03);
  sendData(REG_INTENSITY | intensivity);
}

void max7219_clean() {
  sendData(REG_DIGIT_0 | 0x00);
  sendData(REG_DIGIT_1 | 0x00);
  sendData(REG_DIGIT_2 | 0x00);
  sendData(REG_DIGIT_3 | 0x00);
}


void ftoc( int in)
{

	     if(in>9999 || in < 1)
	     {
	    	 printError();

	     }

	    num[3] = in%10;
	    num[2] = (in/10)%10;
	    num[1] = (in/100)%10;
        num[0] = in/1000;


  sendData(REG_SHUTDOWN | 0x01);
  sendData(REG_DECODE_MODE | 0x00);
  sendData(REG_SCAN_LIMIT | 0x03);

     sendData(DIG[0] | getSymbol(num[0]) | (1<<7));
     sendData(DIG[1] | getSymbol(num[1]) );
     sendData(DIG[2] | getSymbol(num[2]) );
     sendData(DIG[3] | getSymbol(num[3]) );
}


