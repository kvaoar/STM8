#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_uart1.h"






int main( void )
{
	   CLK_DeInit();
	   CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	   CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU

	   UART1_DeInit();
//	   UART1_IrDAConfig(UART1_IRDAMODE_NORMAL);
//	   UART1_IrDACmd(ENABLE);

	   UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
	                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

	   	  // UART1_IrDAConfig(UART1_IRDAMODE_NORMAL);
	   	   //UART1_IrDACmd(ENABLE);

  while(1)            
  {
UART1_SendData8(0xff);
while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
UART1_SendData8(0x00);
while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
  }
}






