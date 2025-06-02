#include "motor.h"

#define MOTOR_AIN1_PIN Pin_6	//PA6
#define MOTOR_AIN2_PIN Pin_7	//PA7
#define MOTOR_BIN1_PIN Pin_0	//PB0
#define MOTOR_BIN2_PIN Pin_1	//PB1

uint8_t motorA_dir = 1; // 1Ϊ��ת 0Ϊ��ת
uint8_t motorB_dir = 1;

int Encoder_count1 = 0;
int Encoder_count2 = 0;

int speed_now;
void motor_init()   //��ʼ��motorIO
{
	pwm_init(TIM_2,TIM2_CH1,1000);   //���1
	gpio_init(GPIO_A,MOTOR_AIN1_PIN,OUT_PP);
	gpio_init(GPIO_A,MOTOR_AIN2_PIN,OUT_PP);
	
	pwm_init(TIM_2,TIM2_CH2,1000);   //���2

	gpio_init(GPIO_B,MOTOR_BIN1_PIN,OUT_PP);
	gpio_init(GPIO_B,MOTOR_BIN2_PIN,OUT_PP);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief		����ת��
// @param	  duty	  pwmռ�ȣ�max50000
// @return		void  
//-------------------------------------------------------------------------------------------------------------------
void motorA_duty(int duty)   //MOTOR_LEFT
{ 
	pwm_update(TIM_2,TIM2_CH1,duty);  
	gpio_set(GPIO_A,MOTOR_AIN1_PIN,motorA_dir);
	gpio_set(GPIO_A,MOTOR_AIN2_PIN,!motorA_dir);
}

void motorB_duty(int duty)   //MOTOR_RIGHT
{
	pwm_update(TIM_2,TIM2_CH2,duty);  
	gpio_set(GPIO_B,MOTOR_BIN1_PIN,motorB_dir);
	gpio_set(GPIO_B,MOTOR_BIN2_PIN,!motorB_dir);
}


void encoder_init()
{
	exti_init(EXTI_PA2,FALLING,0);
	gpio_init(GPIO_A,Pin_3,IU);
	
	exti_init(EXTI_PA4,FALLING,0);
	gpio_init(GPIO_A,Pin_5,IU);
}
