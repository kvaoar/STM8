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

typedef struct {
	GPIO_TypeDef* PORT;
	GPIO_Pin_TypeDef PIN;
} OutChan;

typedef struct {
	OutChan Hi;
	OutChan Lo;
} OutPhaseChan;

OutPhaseChan PhaseBank[3] = {
		{{AH_PORT,AH_PIN},{AL_PORT,AL_PIN}},
		{{BH_PORT,BH_PIN},{BL_PORT,BL_PIN}},
		{{CH_PORT,CH_PIN},{CL_PORT,CL_PIN}}
};

typedef enum{ HI = 1, LO = 0, Z = 2 } phaze;
typedef struct {
uint8_t h[3];
phaze Ph[3];

} BLDC;

BLDC BLDC_states[6] = {
		{{1,0,1},{Z ,HI,LO}},
		{{1,0,0},{LO,HI,Z }},
		{{1,1,0},{LO,Z ,HI}},
		{{0,1,0},{Z ,LO,HI}},
		{{0,1,1},{HI,LO,Z }},
		{{0,0,1},{HI,Z ,LO}}
};

void PhUpd(uint8_t ph_name, phaze ph_state){
if(ph_name >2) return;

if(ph_state == HI){
	GPIO_WriteLow(PhaseBank[ph_name].Lo.PORT,PhaseBank[ph_name].Lo.PIN);
	GPIO_WriteHigh(PhaseBank[ph_name].Hi.PORT,PhaseBank[ph_name].Hi.PIN);
	return;
}
if(ph_state == Z){
	GPIO_WriteLow(PhaseBank[ph_name].Hi.PORT,PhaseBank[ph_name].Hi.PIN);
	GPIO_WriteLow(PhaseBank[ph_name].Lo.PORT,PhaseBank[ph_name].Lo.PIN);
	return;
}
if(ph_state == LO){
	GPIO_WriteLow(PhaseBank[ph_name].Hi.PORT,PhaseBank[ph_name].Hi.PIN);
	GPIO_WriteHigh(PhaseBank[ph_name].Lo.PORT,PhaseBank[ph_name].Lo.PIN);
	return;
}
}

void BLDC_Upd(uint8_t step){
	int i = 0;
	if(step > 5) return;
	for(i = 0; i <3; i++) PhUpd(i,BLDC_states[step].Ph[i]);
}

uint8_t BLDC_GetStep(){
	int i = 0;

	uint8_t read_h[3] = {0,0,0};
	if(GPIO_ReadInputPin(H1_PORT,H1_PIN) == SET) read_h[0] = 1 ; else read_h[0] = 0 ;
	if(GPIO_ReadInputPin(H1_PORT,H2_PIN) == SET) read_h[1] = 1 ; else read_h[1] = 0 ;
	if(GPIO_ReadInputPin(H1_PORT,H3_PIN) == SET) read_h[2] = 1 ; else read_h[2] = 0 ;


	for(i = 0; i <6; i++){
		if((BLDC_states[i].h[0] == read_h[0])&&(BLDC_states[i].h[1] == read_h[1])&&(BLDC_states[i].h[2] == read_h[2]))
			return i;
	}

	return 0xFF;

}

int main( void )
{
uint8_t step = 0;

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

	//  if(GPIO_ReadInputPin(BTN_PORT,BTN_PIN)==RESET)
	  {
		  BLDC_Upd(step);
		  step++;
		  if(step> 5) step = 0;
		  delay1(100000);
	  }
  }
}






