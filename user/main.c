#include "headfile.h"

int main(void)
{
	int a = 1;
	motor_init();       //�����ʼ��
    encoder_init();     //��������ʼ��
//    motorA_duty(20000);    
//    motorB_duty(19840); 
    uart_init(UART_1,115200,0x00);
    //����ʽ���о�����λ��ʽPOSITION_PID
    pid_init(&motorA, POSITION_PID, 20, 170, 5);
    pid_init(&motorB, POSITION_PID, 20, 170, 5);
    pid_init(&angle, POSITION_PID, 2, 200, 0.5);

    //motor_target_set(10, 10);
    OLED_Init();
	OLED_Clear();
	
    gray_init();
    
    //�Ƕȴ�����
    
    I2C_Init();
	JY901S_Init();

    //tim_interrupt_ms_init(TIM_4,10,0);
    
	
	//��ʼ�����ģʽio
//	gpio_init(GPIO_B,Pin_5,ID);
//	
//	if(gpio_get(GPIO_B,Pin_5) == 1)//1�ϵ� ��ѭ�����ж�
//	{
//		tim_interrupt_ms_init(TIM_3,10,0);
//	}
//	else
//	{
//		gpio_init(GPIO_B,Pin_6,OUT_PP);     //�������ģʽ
//		gpio_set(GPIO_B,Pin_6,1);
//		tim_interrupt_ms_init(TIM_4,10,0);
//	}

	
 	while (1)
	{	
		delay_ms(100);
		//JY901S_GetData();
		OLED_ShowChar(1,1,'y');
		OLED_ShowChar(1,2,'a');
		OLED_ShowChar(1,3,'w');
		OLED_ShowChar(1,4,'=');
		OLED_ShowFloat(2,1,yaw_gyro,3,2);
        // �����ǽǶ�
        yaw_gyro = JY901S_Read(JY901_REG_YAW) / 32768.0 * 180.0;
		//printf("key:%d\r\n",JY901S_Read(JY901_REG_YAW));
		printf("yaw:%f\r\n",yaw_gyro);
//		OLED_ShowChar(1,1,'z');
//		OLED_ShowChar(1,2,'=');
//		//OLED_ShowNum(1,3,(int)motorA.now,5);
//		OLED_ShowFloat(1,3,yaw_gyro,3,3);
	} 

}

