#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
short counter = 0;

void GPIO_Config()
{
	// A ve D portunun clock'u aktif edilmesi
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN ; //GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; // 0x03 yaz?labilirdi

	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // pushpull mode
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD,&GPIO_InitStruct);

	}

void delay(uint32_t time)
{
	while(time--);
	};

int main(void)
{
	GPIO_Config();
  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
	  {
		  while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));

		  /*
		   * Butona bas?ld???nda yakla??k olarak 100ms lik bir arc
		   * olu?umu g?zleniyor. E?er biz 100ms lik bir gecikme olu?turursak
		   * arc'tan gelen ve sistem ar?zaya neden olabilecek etkilerde kurtulmu? oluyoruz.
		   *
		   * */
		  delay(3360000); // 100ms lik delay

		  //GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

//		  for(int i = 210000; i<8400000 ; i+=1000000)
//		  {
//			  if(i<2000000 && i != 210000)
//			  {
//				  i -= 800000;
//			  }
//			  GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
//			  delay(i);
//			  GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
//			  delay(i);
//			  GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
//			  delay(i);
//			  GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
//			  delay(i);
//		  }

		  if(counter == 0)
		  {
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
		  }
		  else if (counter == 1)
		  {
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
		  }
		  else if (counter == 2)
		  {
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
		  }
		  else if (counter == 3)
		  {
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
		  }
		  else if(counter == 4)
		  {
			  for(int i = 210000; i<8400000 ; i+=1000000)
			  {
				  if(i<2000000 && i != 210000)
				  {
					  i -= 800000;
				  }
				  GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
				  delay(i);
				  GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
				  delay(i);
				  GPIO_ToggleBits(GPIOD,GPIO_Pin_14);
				  delay(i);
				  GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
				  delay(i);
			  }
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		  }

		  if(counter!=4)counter++;
		  else{counter = 0;}
	  }
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











