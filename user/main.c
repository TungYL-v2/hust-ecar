#include "headfile.h"

int main(void)
{
//	OLED_Init();
	motor_init();       //�����ʼ��
	encoder_init();     //��������ʼ��
	//motorA_duty(20000);    
	//motorB_duty(19840); 
     uart_init(UART_1,115200,0x00);
	//����ʽ���о�����λ��ʽPOSITION_PID
	pid_init(&motorA, POSITION_PID, 10, 10, 5);
	pid_init(&motorB, POSITION_PID, 10, 10, 5);
	motor_target_set(10, 10);
	tim_interrupt_ms_init(TIM_3,10,0);
 	while (1)
	{
		printf("speedA_now:%d,speedB_now:%d\r\n",(int)motorA.now,(int)motorB.now);
		//printf("speed_now:%d\r\n",(int)speed_now);
	} 
}


