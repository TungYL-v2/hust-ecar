#include "headfile.h"

/*
PA0 -> MOTOR_PWMA
PA1 -> MOTOR_PWMB

PA2 -> OUTPUT_E1A
PA3 -> OUTPUT_E1B

PA6 -> MOTOR_AIN1
PA7 -> MOTOR_AIN2

PB0 -> MOTOR_BIN1
PB1 -> MOTOR_BIN2
*/


int main(void)
{
	OLED_Init();
	motor_init();
	motorA_duty(20000);	//LEFT SPEED (MAX:50000)
	motorB_duty(19840); //RIGHT

	while (1)
	{

	
	} 
}
