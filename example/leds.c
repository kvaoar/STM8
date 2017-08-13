#include "stm8s.h"
#include "stm8s_gpio.h"


#define SPI_PORT  GPIOC
#define CS_LED    GPIO_PIN_3
#define CS_ADC    GPIO_PIN_4
#define SPI_CLK   GPIO_PIN_5
#define SPI_MOSI  GPIO_PIN_6
#define SPI_MISO  GPIO_PIN_7


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

int DIG[] = {1<<8, 2<<8, 3<<8, 4<<8};

char num[4];
s16 delay;
s32 cc =0;

unsigned short SYMBOLS[] = { 0x7E, 0x30, 0x6D, 0x79, 0x33,
  0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x00 };


unsigned short getSymbol(uint8_t number);
void sendData(signed short data);
void printError(void);
void max7219_setIntensivity(uint8_t intensivity);
void max7219_clean(void);
void ftoc( int in);


void delay1(int del)
{
while(del)
{
	del--;
	nop();
}
}




int main( void )
{



        	GPIO_DeInit(SPI_PORT);
        	GPIO_Init(SPI_PORT, CS_ADC|CS_LED, GPIO_MODE_OUT_PP_HIGH_SLOW);


	       CLK_DeInit();
	       CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	       CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU

	       SPI_DeInit();
	       SPI_Init
	       (
	         SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_8, SPI_MODE_MASTER, //2mhz clk freq
	         SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE,
	         SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00
	       );

	       SPI_Cmd(ENABLE);




delay1(50000);
max7219_clean();	```````````````````````````````````````````
max7219_setIntensivity(0x0f);

  while(1)            
  {
	  delay1(900000);
	  cc++;
	  ftoc(cc);
  }
}








uint16_t getSymbol(uint8_t number) {
  return SYMBOLS[number];
}



void sendData(signed short data) {

unsigned short delay = 0;

	GPIO_WriteLow(SPI_PORT, CS_LED);
	                SPI_SendData(data>>8 & 0xff);
	                while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	                while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	                SPI_SendData(data & 0xff);
	                while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	         	    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
	GPIO_WriteHigh(SPI_PORT, CS_LED);

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




