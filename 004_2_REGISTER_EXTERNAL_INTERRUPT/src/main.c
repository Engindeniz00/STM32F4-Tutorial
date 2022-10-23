#include "stm32f4xx.h"
#include "stm32f4_discovery.h"



void delay(uint32_t time)
{
	while(time--);
}

void CLK_Config()
{
	RCC->CR |= 0x00030000; // HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000)); // is HSEONRDY?
	RCC->CR |= 0x00080000; // Clock Security System enable
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

void GPIO_Config()
{
	// ilk olarak clock hatlarýný enable etmemiz gerekmektedir
	RCC->AHB1ENR = 0x00000009; // gpio a and d port clock bus enabled
	GPIOD->MODER = 0x55000000; // gpio d port pin 12 13 14 15 leri output moduna aldýk
	GPIOD->OTYPER = 0x00000000; // gpio d port push pull reset state
	GPIOD->OSPEEDR = 0xFF000000; // gpio d port pin speed at very high
	GPIOD->PUPDR = 0x00000000; // push pull -> no pull push

}

void EXTI_Config()
{
	RCC->APB2ENR = 0x00004000; // syscfg enabled (external interrupt)
	SYSCFG->EXTICR[0] = 0X00000000; // syscfg external interrupt configuration for PA[x] pin
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);

	NVIC_SetPriority(EXTI0_IRQn,0); // most significant interrupt
	NVIC_SetPriority(EXTI1_IRQn,1); // most significant interrupt
	NVIC_SetPriority(EXTI2_IRQn,2); // most significant interrupt

	// interrupt olarak mý yoksa event olarak mý kullanýlýp kullanýlmayacaðýný belirlemek için
	// mask ya da unmask ayarlamalarýný yapýyoruz.

	EXTI->IMR = 0x00000007; // interrupt line 0..2 is not masked yani pa0..2 interrupt için aktif
	EXTI->RTSR = 0x00000007; // rising edge trigger setted


	}

void EXTI0_IRQHandler()
{
	// interrupt yapýldý mý yapýlmadý mý burada anlaþýlmasý lazým
	if(EXTI->PR & 0x00000001)
	{
		GPIOD->ODR = 0x00001000; // pin 12 led turned on
		delay(33600000);
		EXTI->PR = 0x00000001; // interrupt bit cleared external interrupt flag off
	}
}

void EXTI1_IRQHandler()
{
	// interrupt yapýldý mý yapýlmadý mý burada anlaþýlmasý lazým
	if(EXTI->PR & 0x00000002)
	{
		GPIOD->ODR = 0x00002000; // pin 12 led turned on
		delay(33600000);
		EXTI->PR = 0x00000002; // interrupt bit cleared external interrupt flag off
	}
}

void EXTI2_IRQHandler()
{
	// interrupt yapýldý mý yapýlmadý mý burada anlaþýlmasý lazým
	if(EXTI->PR & 0x00000004)
	{
		GPIOD->ODR = 0x00004000; // pin 12 led turned on
		delay(33600000);
		EXTI->PR = 0x00000004; // interrupt bit cleared external interrupt flag off
		/*
		 * data sheet üzerinde flag bayraðýnýn indirilebilmesi tekrardan 1 olarak
		 * programlanmasý gerektiði yazýyor.
		 *
		 * */
	}
}

int main(void)
{
	CLK_Config();
	GPIO_Config();
	EXTI_Config();
  while (1)
  {
	  GPIOD->ODR = 0x0000F000; // all pin 12..15 are active led on.
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
