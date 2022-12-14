#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock; // burada system core clock ayarlamas?n?n yap?ld??? de?i?keni ?a??r?yoruz.

uint32_t  systemClock;

void RCC_Config(void){

	RCC->CR &= ~(1<<0); // HSI OFF
	RCC->CR |= 1 << 16; // HSE ON
	while(!(RCC->CR & 1<<17)); // WAIT HSE ACTIVE
	RCC->CR |= 1 << 19; // CLOCK SECURITY ON
	// PLL ayarlamalar?n?n yap?lmas? ile u?ra??yoruz.
//	RCC->PLLCFGR &= ~(1<<0); // PLLM0 0 div : 4
//	RCC->PLLCFGR &= ~(1<<1); // PLLM1 0 div : 4
//	RCC->PLLCFGR |= ~(1<<2); // PLLM2 1 div : 4
//	RCC->PLLCFGR &= ~(1<<3); // PLLM3 0 div : 4
//	RCC->PLLCFGR &= ~(1<<4); // PLLM4 0 div : 4
//	RCC->PLLCFGR &= ~(1<<5); // PLLM5 0 div : 4
	// daha kolay bir yol ile pll_m de?erini ayarlama
	//RCC->PLLCFGR &= ~(31<<1); // ilk 5 biti 1 yap sonra tersini al?p s?f?rlama
	// bit k?s?mlar?n? teker teker s?f?rlamaktansa b?t?n 32 bitlik k?sm? s?f?rlama i?lemi yap?larak devam edilir
	RCC->PLLCFGR = 0x00000000; // buradaki 8 adet s?f?r 32 bit'i temsil eder ??nk? her basamak 4 bitlik alan? temsil ediyor
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

int main(void)
{
//	systemClock = SystemCoreClock;
//	RCC_DeInit(); // HSIEN PLL OFF
//	SystemCoreClockUpdate(); // 16 000 000
//	systemClock = SystemCoreClock;

	RCC_Config();
	SystemCoreClockUpdate();
	systemClock = SystemCoreClock;

  while (1)
  {

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
