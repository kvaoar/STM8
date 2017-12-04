
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_spi.h"
#include "string.h"
#include "stdio.h"
#include "stm8s_uart1.h"

#define MAX_PORT GPIOD
#define MAX_CS GPIO_PIN_3


char buf[50];


void delay1(uint32_t del)
{
while(del)
{
	del--;
	nop();
}
}


uint16_t ReadMAX6675()
{
	    uint8_t highByte=0;
	    uint8_t lowByte=0;
	    uint16_t tp = 0;

	    GPIO_WriteLow(MAX_PORT, MAX_CS);

	    delay1(1);

	                                SPI_SendData(0x00);
	   	    		                while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	   	    		                highByte = SPI_ReceiveData();

	    		                SPI_SendData(0x00);
	    		                while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
	    		                lowByte = SPI_ReceiveData();



//	    		                SPI_SendData(0x00 );
//	    		                while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET);
//	    		         	    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
//	    		         	    lowByte = SPI_ReceiveData();
  delay1(1);



    GPIO_WriteHigh(MAX_PORT, MAX_CS);
	  //  delay1(400);

    tp =  (highByte +lowByte*256);

 //(tp & (!0x807))>>3


    return ((tp & (~0x807))>>3)/4;
}

int uart_write(const char *str) {
	char i;
	for(i = 0; i < strlen(str); i++) {
		while(!(UART1->SR & UART1_SR_TXE));
		UART1->DR = str[i];
	}
	return(i);
}


int main( void )
{
	unsigned long i = 0;

   CLK_DeInit();
   CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
   CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU


   GPIO_DeInit(MAX_PORT);
   GPIO_Init(MAX_PORT, MAX_CS, GPIO_MODE_OUT_PP_HIGH_FAST); //MAX6675 !CS

   SPI_DeInit();
   SPI_Init
   (
     SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_8, SPI_MODE_MASTER,
     SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE,
     SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00
   );

   SPI_Cmd(ENABLE);



   UART1_DeInit();
   UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                 UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

   UART1_Cmd(ENABLE);







  while(1)
  {

	  delay1(1000000);
	  sprintf(buf, "t= %d\r\n", ReadMAX6675());
	  uart_write(buf);
	 // ReadMAX6675();




	}
  }







