#include "motor.h"

uint8_t motorA_dir = 1; // 1为正转 0为反转
uint8_t motorB_dir = 1; // 1为正转 0为反转

int Encoder_count1 = 0;
int Encoder_count2 = 0;

int speed_now;
void motor_init()   //电机初始化
{
	pwm_init(TIM_2,TIM2_CH1,1000);   //电机1
	gpio_init(GPIO_A,Pin_6,OUT_PP);
	gpio_init(GPIO_A,Pin_7,OUT_PP);
	
	pwm_init(TIM_2,TIM2_CH2,1000);   //电机2
	gpio_init(GPIO_B,Pin_0,OUT_PP);
	gpio_init(GPIO_B,Pin_1,OUT_PP);
}
 
void motorA_duty(int duty)   //电机1占空比
{ 
	pwm_update(TIM_2,TIM2_CH1,duty);  
	gpio_set(GPIO_A,Pin_6,motorA_dir);
	gpio_set(GPIO_A,Pin_7,!motorA_dir);
}

void motorB_duty(int duty)   //电机2占空比
{
	pwm_update(TIM_2,TIM2_CH2,duty);  
	gpio_set(GPIO_B,Pin_0,motorB_dir);
	gpio_set(GPIO_B,Pin_1,!motorB_dir);
}


void encoder_init()
{
	exti_init(EXTI_PA2,FALLING,0);
	gpio_init(GPIO_A,Pin_3,IU);
	
	exti_init(EXTI_PA4,FALLING,0);
	gpio_init(GPIO_A,Pin_5,IU);
}
