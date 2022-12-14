#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config(void){

	RCC->CR &= ~(1<<0); // HSI OFF
	RCC->CR |= 1 << 16; // HSE ON
	while(!(RCC->CR & 1<<17)); // WAIT HSE ACTIVE
	RCC->CR |= 1 << 19; // CLOCK SECURITY ON
	RCC->PLLCFGR = 0x00000000; // sifirlama islemi
	RCC->PLLCFGR = (1<<22); // HSE SELECT
	RCC->PLLCFGR |= (4<<0); // PLLM 4
	RCC->PLLCFGR |= (168<<6); // PLLN 168

	// configuring PLLP 2
	RCC->PLLCFGR &= ~(1<<16);
	RCC->PLLCFGR &= ~(1<<17);

	RCC->CR |= (1<<24); // PLL ON

	while(!(RCC->CR & (1<<25))); // PLL READY

	// System clock is PLL
	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1);

	while(!(RCC->CFGR & (1<<1))); // IS SYSTEM CLOCK SET TO PLL

}

void GPIO_Config()
{

	// GPIOD port clock enable
	RCC->AHB1ENR |= (1<<3);

	// GPIOD pin 12 set mode output
	GPIOD->MODER |= (1<<24);
	GPIOD->MODER &= ~(1<<25);
	// GPIOD pin 13 set mode output
	GPIOD->MODER |= (1<<26);
	GPIOD->MODER &= ~(1<<27);
	// GPIOD pin 14 set mode output
	GPIOD->MODER |= (1<<28);
	GPIOD->MODER &= ~(1<<29);
	// GPIOD pin 15 set mode output
	GPIOD->MODER |= (1<<30);
	GPIOD->MODER &= ~(1<<31);

	// GPIOD pin set speed very high speed
	GPIOD->OSPEEDR |= 0xFF000000;
	}

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();
	GPIO_Config();
  while (1)
  {
	  GPIOD->ODR |= (1<<12); // pin 12 set
	  GPIOD->ODR |= (1<<13); // pin 13 set
	  GPIOD->ODR |= (1<<14); // pin 14 set
	  GPIOD->ODR |= (1<<15); // pin 15 set

	  for(int i=0 ; i<1680000 ; i++);

	  GPIOD->ODR &= ~(1<<12); // pin 12 set
	  GPIOD->ODR &= ~(1<<13); // pin 13 set
	  GPIOD->ODR &= ~(1<<14); // pin 14 set
	  GPIOD->ODR &= ~(1<<15); // pin 15 set

	  for(int i=0 ; i<1680000 ; i++);
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
