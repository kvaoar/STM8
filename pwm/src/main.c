/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/**
  * @brief  Configure TIM2 peripheral in PWM mode
  * @param  None
  * @retval None
  */

void TIM2_Config(void)
{
  
  uint16_t AFRval=FLASH_ReadOptionByte(0x4803);
if(!(AFRval&0x0001))
{
FLASH_ProgramOptionByte(0x4803, (uint8_t)(AFRval&0x0001));
}

  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 80-1);
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,25, TIM2_OCPOLARITY_LOW);
  TIM2_OC1PreloadConfig(ENABLE);
  TIM2_ARRPreloadConfig(ENABLE);
  //TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
  TIM2_Cmd(ENABLE);
}

void TIMER4_Configuration(void)
{
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_32, 0xFA );
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);
}


uint8_t SPI_txtr(uint8_t tx){
  /* Wait until end of transmit */
  while (SPI_GetFlagStatus(SPI_FLAG_TXE)== RESET){};
  /* Write one byte in the SPI Transmit Data Register */
  SPI_SendData(tx);
  /* Wait the byte is entirely received by SPI */
  while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET){};
  /* Store the received byte in the RxBuffer2 */
  return SPI_ReceiveData();
}

void main(void)
{
  GPIO_Init(DISPLAY_NSS_PORT, DISPLAY_NSS_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(ADC_NSS_PORT, ADC_NSS_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

 // TIM2_Config(); 
 // TIMER4_Configuration();
  
 /// enableInterrupts();

  /* SPI configuration */
  SPI_DeInit();
  /* Initialize SPI in Slave mode  */
  SPI_Init(SPI_FIRSTBIT_LSB, SPI_BAUDRATEPRESCALER_2, SPI_MODE_SLAVE, SPI_CLOCKPOLARITY_LOW,
           SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT,(uint8_t)0x07);

  while (1)
  {
    
  }
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
