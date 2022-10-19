#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct; // gpio
EXTI_InitTypeDef EXTI_InitStruct; // interrupt
NVIC_InitTypeDef NVIC_InitStruct;


void delay(uint32_t time)
{
	while(time--);
}
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	// gpioA configurations
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

}

void EXTI_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	EXTI_InitStruct.EXTI_Line = EXTI_Line1|EXTI_Line2;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_InitStruct);

	/*
	 * iki buton kulland���m�z i�in �ncelik s�ralamalar�n� yapmam�z gerekiyor
	 * burada bir adet buton kullan�yoruz o halde prioritygroup1 kullanarak
	 * 1 bit i�in pre-emption priority i�in 3 tanesini subpriority i�in kullanmam�z gerekecek
	 * */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // e�er birden fazla interrupt kullan�yorsak bu fonskiyonu kullan�r�z

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	/*
	 *  �ncelik s�ralamas�nda d���k olan say� her zaman daha
	 *  �nceliklidir. O y�zden birinci butonun �nceli�ini 0 ikinci butonun
	 *  �nceli�ine 1 demeliyiz.
	 *  */
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVIC_InitStruct);
}


void EXTI1_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_All);
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		delay(1680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		delay(1680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_14);
		delay(1680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
		delay(1680000);


		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}


void EXTI2_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_All);
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
		delay(1680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_14);
		delay(1680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_13);
		delay(1680000);
		GPIO_SetBits(GPIOD,GPIO_Pin_12);
		delay(1680000);

		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}




int main(void)
{
	GPIO_Config();
	EXTI_Config();
  while (1)
  {
	  GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
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