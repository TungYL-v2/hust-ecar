#include "stm32f10x.h"                  // Device header
#include "headfile.h"

int straight = 0;
int if_stop ;
float yaw,yaw_gyro;
int transformation = 0;
int if_black=0;

//����Ϊ��ʱ���жϷ�����
void TIM2_IRQHandler(void)
{    if(TIM2->SR&1)
    {
        //�˴���д�жϴ���
//        speed_now = Encoder_count;
//        Encoder_count = 0;
    if(transformation <=3 )    //�ڰ�ת������<4��δ�ص������㣩    
      {
        if((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8))  //�ں�����ѭ��
        {   
            straight = 0;
            pid_control();        
        }
        
        else if((D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)&&(transformation == 0) && (((fabs( yaw_o - yaw_gyro -39)<2)) ||(fabs(yaw_gyro- yaw_o - 321)<2)))//ֱ��pid  //
        {    
            straight = 1;
            pid_control();   
	   }
        else if((D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)&&(transformation == 2) && (((fabs( yaw_o - yaw_gyro -144)<2)) ||(fabs(yaw_gyro- yaw_o - 216)<2)))//ֱ��pid  //
        {    
            straight = 1;
            pid_control(); 		   
        }            
        else if((straight == 0)&&(transformation == 0)&&(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8))   //����ʱ�ǶȲ��������            
        {   
			if(yaw_o >340 && yaw_o <360)
			   pid_control_angle (yaw_o - 39);
			else
		       pid_control_angle(yaw_o + 321);
	   }
	   else if((straight == 0)&&(transformation == 2)&&(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8))   //����ʱ�ǶȲ��������            
        {   
			if(yaw_o >340 && yaw_o <360)
			   pid_control_angle (yaw_o - 144);
			else
		       pid_control_angle(yaw_o + 216);
	   }
        else if(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)
        {
            pid_control();
        }
//        else 
//        {    
//            motorA_duty(3000);
//            motorB_duty(3000);
//        }
      }
      if(transformation > 3)     //�����Ĵκڰ�ת�������ص�A�㣬ͣ��
      {
        gpio_set(GPIO_A,Pin_6,1);
        gpio_set(GPIO_A,Pin_7,1);
        gpio_set(GPIO_B,Pin_0,1);
        gpio_set(GPIO_B,Pin_1,1);
      }
        TIM2->SR &= ~1; 
    }  
}


void TIM3_IRQHandler(void)
{
    
    if(TIM3->SR&1)   //����������ȡ�Ƕȡ��ڰ�ת������
    {
        //�˴���д�жϴ���
//       delay_ms(50);
        // ��ȡ����
//        JY901S_GetData();
	   OLED_ShowChar(1,1,'y');
	   OLED_ShowChar(1,2,'a');
	   OLED_ShowChar(1,3,'w');
	   OLED_ShowChar(1,4,'=');
//	   OLED_ShowFloat(2,1,fabs(yaw_gyro - yaw_o - 185),3,2);
	   OLED_ShowFloat(2,1,yaw_o,3,2);
	   OLED_ShowFloat(2,8,yaw_gyro,3,2);
//	   OLED_ShowChar(4,1,'t');
//	   OLED_ShowChar(4,2,'=');
//	    
//	   OLED_ShowNum(4,3,transformation,1);
//	   OLED_ShowChar(4,5,'s');
//	   OLED_ShowChar(4,6,'=');
//	   OLED_ShowNum(4,7,straight,1);
//	   OLED_ShowChar(4,8,'i');
//	   OLED_ShowChar(4,9,'=');
//	   OLED_ShowNum(4,10,straight,1);
	    
        if(((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)&&(if_black == 0))||((D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)&&(if_black == 1)))
		{                                                 //��������λ��ת��ʱ���������죬transformation��1
			transformation = transformation +1;
			gpio_set(GPIO_B,Pin_6,0);
			delay_ms(20);
			gpio_set(GPIO_B,Pin_6,1);
		}
		
		if(!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)  //��⴦�ڰ�ɫ����or��ɫ����
			if_black = 1;
		else 
			if_black = 0;		 
        
        TIM3->SR &= ~1; 
    }
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR&1)
	{
//		//�˴���д�жϴ���
//		//��
//		printf("%f\r\n",motorA.now);
//		OLED_ShowChar(1,1,'a');
//		OLED_ShowChar(1,2,'=');
//		//OLED_ShowNum(1,3,(int)motorA.now,5);
//		OLED_ShowFloat(1,3,motorA.now,2,2);
//		if((a==1)&&(!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8))
//		{
//			a = 0;
//			gpio_set(GPIO_B,Pin_6,0);
//			delay_ms(500);
//			gpio_set(GPIO_B,Pin_6,1);
//		
//		}
//		TIM4->SR &= ~1; 
	}
}


//����Ϊ�����жϷ�����
void USART1_IRQHandler(void)
{
	if (USART1->SR&0x20)
	{
		//�˴���д�жϴ���

		USART1->SR &= ~0x20;   //�����־λ
	}
}


void USART2_IRQHandler(void)
{
	if (USART2->SR&0x20)
	{
		//�˴���д�жϴ���

		USART2->SR &= ~0x20;   //�����־λ
	}
}

void USART3_IRQHandler(void)
{
	if (USART3->SR&0x20)
	{
		//�˴���д�жϴ���

		USART3->SR &= ~0x20;   //�����־λ
	}
}


//����Ϊ�ⲿ�жϷ�����
void EXTI0_IRQHandler(void) // PA0/PB0/PC0
{
	if(EXTI->PR&(1<<0))
	{
		//�˴���д�жϴ���
		
		EXTI->PR = 1<<0; //�����־λ
	}
}

void EXTI1_IRQHandler(void) // PA1/PB1/PC1
{
	if(EXTI->PR&(1<<1))
	{
		//�˴���д�жϴ���
		
		EXTI->PR = 1<<1; //�����־λ
	}
}
void EXTI2_IRQHandler(void) // PA2/PB2/PC2
{
	if(EXTI->PR&(1<<2))
	{
		//�˴���д�жϴ���
		if(gpio_get(GPIO_A, Pin_3))
			Encoder_count1 --;
		else
			Encoder_count1 ++;
		
//		// ��ȡԭʼ����
//		LSM6DSV16X_GetData();
////		MPU6050_GetData();
//		HMC5883L_GetData();
//		
//		// �����ǽǶ�
//		roll_gyro += (float)gx / 16.4 * 0.005;
//		pitch_gyro += (float)gy / 16.4 * 0.005;
//		yaw_gyro += (float)gz / 16.4 * 0.005;
//		
//		// ���ٶȼƽǶ�
//		roll_acc = atan((float)ay/az) * 57.296;
//		pitch_acc = - atan((float)ax/az) * 57.296;	
//		yaw_acc = atan((float)ay/ax) * 57.296;
////		
////		// �����ƽǶ�
//		yaw_hmc = atan2((float)hmc_x, (float)hmc_y) * 57.296;
////		
////		// �������˲��ںϽǶ�
//		roll_Kalman = Kalman_Filter(&KF_Roll, roll_acc, (float)gx / 16.4);
//		pitch_Kalman = Kalman_Filter(&KF_Pitch, pitch_acc, (float)gy / 16.4);
//		yaw_Kalman = Kalman_Filter(&KF_Yaw, yaw_hmc, (float)gz / 16.4);
		
		EXTI->PR = 1<<2; //�����־λ
		
		
	}
}
void EXTI3_IRQHandler(void) // PA3/PB3/PC3
{
	if(EXTI->PR&(1<<3))
	{
		//�˴���д�жϴ���
		
		EXTI->PR = 1<<3; //�����־λ
	}
}

void EXTI4_IRQHandler(void) // PA4/PB4/PC4
{
	if(EXTI->PR&(1<<4))
	{
		//�˴���д�жϴ���
		if(gpio_get(GPIO_A, Pin_5))
			Encoder_count2 ++;
		else
			Encoder_count2 --;
		EXTI->PR = 1<<4; //�����־λ
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR&(1<<5))   //EXTI5  PA5/PB5/PC5
	{
		//�˴���д�жϴ���

		EXTI->PR = 1<<5; //�����־λ
	}
	
	if(EXTI->PR&(1<<6))   //EXTI6  PA6/PB6/PC6
	{
		//�˴���д�жϴ���
		
		EXTI->PR = 1<<6; //�����־λ
	}
	
	if(EXTI->PR&(1<<7))   //EXTI7  PA7/PB7/PC7
	{
		//�˴���д�жϴ���
		
		
		EXTI->PR = 1<<7; //�����־λ
	}
	
	if(EXTI->PR&(1<<8))   //EXTI8
	{
		//�˴���д�жϴ���
		
		EXTI->PR = 1<<8; //�����־λ
	}
	
	if(EXTI->PR&(1<<9))   //EXTI9
	{
		//�˴���д�жϴ���
		
		EXTI->PR = 1<<9; //�����־λ
	}
}
