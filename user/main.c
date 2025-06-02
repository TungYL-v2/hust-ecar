#include "headfile.h"

int main(void)
{
	OLED_Init();
	motor_init();
	motorA_duty(20000);
	motorB_duty(19840);

	while (1)
	{

	
	} 
}
