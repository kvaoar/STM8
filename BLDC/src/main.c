#include "stm8s.h"
#include "stm8s_gpio.h"


//pc6
#define AH_PORT GPIOC
#define AH_PIN GPIO_PIN_6

//pc4
#define BH_PORT GPIOC
#define BH_PIN GPIO_PIN_4

//pb4
#define CH_PORT GPIOB
#define CH_PIN GPIO_PIN_4

//pc5
#define AL_PORT GPIOC
#define AL_PIN GPIO_PIN_5

//pc3
#define BL_PORT GPIOC
#define BL_PIN GPIO_PIN_3

//pb5
#define CL_PORT GPIOB
#define CL_PIN GPIO_PIN_5


//pd4
#define H1_PORT GPIOD
#define H1_PIN GPIO_PIN_4

//pd5
#define H2_PORT GPIOD
#define H2_PIN GPIO_PIN_5

//pd6
#define H3_PORT GPIOD
#define H3_PIN GPIO_PIN_6

//pa3
#define BTN_PORT GPIOA
#define BTN_PIN GPIO_PIN_3


void delay1(int del)
{
while(del)
{
	del--;
	nop();
}
}

typedef enum{ HI = 1, LO = 0, Z = 2 } phaze;
typedef struct {
uint8_t h1;
uint8_t h2;
uint8_t h3;
phaze A;
phaze B;
phaze C;

} BLDC;

BLDC arr[6] = {
		{1,0,1,Z ,HI,LO},
		{1,0,0,LO,HI,Z },
		{1,1,0,LO,Z ,HI},
		{0,1,0,Z ,LO,HI},
		{0,1,1,HI,LO,Z },
		{0,0,1,HI,Z ,LO}
};

void PhSwitch(uint8_t ph_name, phaze ph_state){

}
int main( void )
{
uint16_t val = 0;

GPIO_Init(AH_PORT,AH_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
GPIO_Init(AL_PORT,AL_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
GPIO_Init(BH_PORT,BH_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
GPIO_Init(BL_PORT,BL_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
GPIO_Init(CH_PORT,CH_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
GPIO_Init(CL_PORT,CL_PIN,GPIO_MODE_OUT_PP_LOW_FAST);


GPIO_Init(H1_PORT,H1_PIN,GPIO_MODE_IN_PU_NO_IT);
GPIO_Init(H2_PORT,H2_PIN,GPIO_MODE_IN_PU_NO_IT);
GPIO_Init(H3_PORT,H3_PIN,GPIO_MODE_IN_PU_NO_IT);

GPIO_Init(BTN_PORT,BTN_PIN,GPIO_MODE_IN_PU_NO_IT);

  while(1)            
  {

	  if(GPIO_ReadInputPin(BTN_PORT,BTN_PIN)==RESET)
	  {
	  GPIO_WriteReverse(AH_PORT,AH_PIN);
	delay1(100000);
	  }
  }
}






