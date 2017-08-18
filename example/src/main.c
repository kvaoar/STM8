#include "stm8s.h"
#include "stm8s_gpio.h"
#include "display.h"
#include "adc.h"

#define SPI_PORT  GPIOC
#define CS_LED    GPIO_PIN_3
#define CS_ADC    GPIO_PIN_4
#define SPI_CLK   GPIO_PIN_5
#define SPI_MOSI  GPIO_PIN_6
#define SPI_MISO  GPIO_PIN_7


s32 cc =0;
s16 delay = 0;



void delay1(int del)
{
while(del)
{
	del--;
	nop();
}
}

void spi_config(){


	GPIO_DeInit(SPI_PORT);
	GPIO_Init(SPI_PORT, CS_ADC|CS_LED, GPIO_MODE_OUT_PP_HIGH_SLOW);


   CLK_DeInit();
   CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
   CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU

   SPI_DeInit();
   SPI_Init
   (
     SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_8, SPI_MODE_MASTER, //16/8 = 2mhz clk freq
     SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE,
     SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x00
   );

   SPI_Cmd(ENABLE);

}


int main( void )
{
uint16_t val = 0;
spi_config();


delay1(50000);
display_init();

  while(1)            
  {
	  delay1(900000);

	  val = adc_get();
	  ftoc(val);
  }
}






