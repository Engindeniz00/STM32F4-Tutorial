#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t counter;

void RCC_Config()
{
	RCC->CR |= 0x00030000; // HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000)); // is HSEONRDY?
	RCC->CR |= 0x00080000; // Clock Security System enable
	RCC->CR |= 0x01000000; // PLL ON
	RCC->PLLCFGR |= 0x00400000; // PLL HSEON enable
	RCC->PLLCFGR |= 0x00000004; // PLL M = 4
	RCC->PLLCFGR |= 0x00005A00; // PLL N = 168
	RCC->PLLCFGR |= 0x00000000; // PLL P = 2
	RCC->CFGR |= 0x00000000; // AHB1 freq 168 MHz max
	RCC->CFGR |= 0x00001400; // APB1 freq 42 MHz max
	RCC->CFGR |= 0x00008000; // APB2 freq 84 MHz max
	RCC->CIR |= 0x00080000; // HSERDY flag clear
	RCC->CIR |= 0x00800000; // CSS flag clear
}

void TIM_Config()
{
	RCC->APB1ENR = 0x00000001; // Enabling tim2 clock port

	TIM2->CR1 |= 0 << 5; // center align mode edge align mode
	TIM2->CR1 |= 0 << 8; // set time division 1
	TIM2->SMCR |= 0 << 0; // slave mode disabled
 	TIM2->CR1 |= 0 << 4; // upcounting mode
	TIM2->CR1 |= 1 <<0; // counter enable
	TIM2->EGR |= 1<<0; // update generation enabled to make interrupt signals
	TIM2->PSC = 41999; // timer prescaler set to 41999
	TIM2->ARR = 1999; // arr set to 1999 to make counter frequency 1 second

}

int main(void)
{
	RCC_Config();
	TIM_Config();

  while (1)
  {
	  counter = TIM2->CNT;
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
