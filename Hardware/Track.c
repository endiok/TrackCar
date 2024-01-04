#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"
#include "LED.h"
#include "inv_mpu.h"
uint8_t PWMR,PWML;
//float Pitch,Roll,Yaw;
#define R 125
#define L 84

void Track_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;//分别对应IN1 IN2 IN3 IN4
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}
void Track(void)
{
	LED_Init();
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1
		&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1)//stop
	{
		PWML=0;
		PWMR=0;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
		LED1_ON();
		//MPU6050_DMP_Init();
		Delay_ms(1700);
		LED1_OFF();
		PWML=135;
		PWMR=135;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
		Delay_ms(100);
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0
		&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)//直走
	{
			PWML=134;
			PWMR=131;
			PWM_SetCompare3(PWML);
			PWM_SetCompare4(PWMR);
	}
	//---------------------------------------------------------------------------------------
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1
		&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)//IN2检测到黑线,向右拐
	{
		PWML=125;
		PWMR=83;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
//	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1)//IN2检测到黑线,向右拐
//	{
//		PWML=127;
//		PWMR=85;
//		PWM_SetCompare3(PWML);
//		PWM_SetCompare4(PWMR);
//	}
	//----------------------------------------------------------------------------------------
//		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1)//IN3检测到黑线,向左拐
//	{
//		PWML=85;
//		PWMR=127;
//		PWM_SetCompare3(PWML);
//		PWM_SetCompare4(PWMR);
//	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0
		&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)//IN3检测到黑线,向左拐
	{
		PWML=83;
		PWMR=125;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
//	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0
//		&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)//IN1检测到黑线 向右拐
//	{
//		PWML=130;
//		PWMR=87;
//		PWM_SetCompare3(PWML);
//		PWM_SetCompare4(PWMR);
//	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0
		&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1)//IN4检测到黑线 向左拐
	{
		PWML=L;
		PWMR=R;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}

	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1&&
		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)//IN1 IN2
	{
		PWML=L;
		PWMR=R;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&
		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)
	{
		PWML=L;
		PWMR=R;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1
		&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)//右三路黑
	{
		PWML=L;
		PWMR=R;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&
		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
	{
		PWML=L;
		PWMR=R;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&
		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)
	{
		PWML=L;
		PWMR=R;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==1&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&
		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)==0&&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)
	{
		PWML=L;
		PWMR=R;
		PWM_SetCompare3(PWML);
		PWM_SetCompare4(PWMR);
	}
}
