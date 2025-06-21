#include "motor.h"

#define MOTOR_AIN1_PIN Pin_6	//PA6
#define MOTOR_AIN2_PIN Pin_7	//PA7
#define MOTOR_BIN1_PIN Pin_0	//PB0
#define MOTOR_BIN2_PIN Pin_1	//PB1

uint8_t motorA_dir = 1; // 1为正转 0为反转
uint8_t motorB_dir = 1;

int Encoder_count1 = 0;
int Encoder_count2 = 0;

int speed_now;
void motor_init()   //初始化motorIO
{
	pwm_init(TIM_2,TIM2_CH1,1000);   //电机1
	gpio_init(GPIO_A,Pin_6,OUT_PP);
	gpio_init(GPIO_A,Pin_7,OUT_PP);
	
	pwm_init(TIM_2,TIM2_CH2,1000);   //电机2

	gpio_init(GPIO_B,Pin_0,OUT_PP);
	gpio_init(GPIO_B,Pin_1,OUT_PP);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		控制转速
// @param	  duty	  pwm占比，max50000
// @return		void  
//-------------------------------------------------------------------------------------------------------------------
void motorA_duty(int duty)   //MOTOR_LEFT
{ 
	pwm_update(TIM_2,TIM2_CH1,duty);  
	gpio_set(GPIO_A,Pin_6,motorA_dir);
	gpio_set(GPIO_A,Pin_7,!motorA_dir);
}

void motorB_duty(int duty)   //MOTOR_RIGHT
{
	pwm_update(TIM_2,TIM2_CH2,duty);  
	gpio_set(GPIO_B,Pin_0,motorB_dir);
	gpio_set(GPIO_B,Pin_1,!motorB_dir);
}

// 编码器IO初始化
void encoder_init()
{
	exti_init(EXTI_PA2,FALLING,0);  //E1A
	gpio_init(GPIO_A,Pin_3,IU);		//E1B
	
	exti_init(EXTI_PA4,FALLING,0);
	gpio_init(GPIO_A,Pin_5,IU);
}
