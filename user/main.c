#include "headfile.h"

int main(void)
{
    motor_init();       //�����ʼ��
    encoder_init();     //��������ʼ��
//    motorA_duty(20000);    
//    motorB_duty(19840); 
    uart_init(UART_1,115200,0x00);
    //����ʽ���о�����λ��ʽPOSITION_PID
    pid_init(&motorA, DELTA_PID, 10, 12, 5);
    pid_init(&motorB, DELTA_PID, 10, 12, 5);
    pid_init(&angle, POSITION_PID, 2, 0, 1);

    //motor_target_set(10, 10);
    OLED_Init();
    OLED_Clear();
	
    gray_init();
    
<<<<<<< Updated upstream
   gpio_init(GPIO_B,Pin_6,OUT_PP);  //������IO����
    gpio_set(GPIO_B,Pin_6,1);
=======
//    gpio_init(GPIO_B,Pin_6,OUT_PP);  //������IO����
//    gpio_set(GPIO_B,Pin_6,1);
>>>>>>> Stashed changes
    gpio_init(GPIO_B,Pin_5,ID);
    //�Ƕȴ�����  
     I2C_Init();
	JY901S_Init();
    
    tim_interrupt_ms_init(TIM_3,150,0);  
<<<<<<< Updated upstream
    tim_interrupt_ms_init(TIM_2,15,1);   //���ȼ�����TIM3
=======
    tim_interrupt_ms_init(TIM_4,15,1);   //���ȼ�����TIM3
>>>>>>> Stashed changes
     	
    while (1)
	{	JY901S_GetData();
		delay_ms(10);
       // printf("%f\r\n",motorA.now);
    }
}
