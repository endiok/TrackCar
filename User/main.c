#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Track.h"
#include "PWM.h"
#include "Motor.h"
#include "inv_mpu.h"
uint8_t count;

int main(void)
{
	OLED_Init();
	Key_Init();
	Motor_Init();
	Track_Init();
//	MPU6050_DMP_Init();
//	OLED_ShowString(1,1,"Pitch:");
//	OLED_ShowString(2,1,"Roll:");
//	OLED_ShowString(3,1,"Yaw:");
	while (1)
	{
//		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);
//		OLED_ShowSignedNum(1,7,Pitch,3);
//		OLED_ShowSignedNum(2,7,Roll,3);
//		OLED_ShowSignedNum(3,7,Yaw,3);
		if(count==0)
		{
			count=1;
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			GPIO_ResetBits(GPIOA,GPIO_Pin_6);
			GPIO_SetBits(GPIOA,GPIO_Pin_7);
			PWML=138;
			PWMR=135;
			PWM_SetCompare3(PWML);
			PWM_SetCompare4(PWMR);
			Delay_ms(800);
		}
		Track();
		
	}
}
