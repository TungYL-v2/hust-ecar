#include "stm32f10x.h"                  // Device header
#include "headfile.h"

//����Ϊ��ʱ���жϷ�����
void TIM2_IRQHandler(void)
{
	if(TIM2->SR&1)
	{
		//�˴���д�жϴ���
		JY901S_GetData();
  
        // �����ǽǶ�
        yaw_gyro = yaw / 32786.0f * 180.0f;
		
		OLED_ShowChar(1,1,'a');
		OLED_ShowChar(1,2,'=');
		//OLED_ShowNum(1,3,(int)motorA.now,5);
		OLED_ShowFloat(1,3,motorA.now,2,2);
		TIM2->SR &= ~1; 
	}
}

static int straight = 0;
static int if_stop = 0;
float yaw,yaw_gyro;

void TIM3_IRQHandler(void)
{
    
    if(TIM3->SR&1)
    {
        //�˴���д�жϴ���
        
        // ��ȡ����
        JY901S_GetData();
  
        // �����ǽǶ�
        //yaw_gyro = yaw / 32786.0f * 180.0f;
        
		
		//OLEDshow
		
		OLED_ShowChar(1,1,'a');
		OLED_ShowChar(1,2,'=');
		OLED_ShowNum(1,3,(int)motorA.now,2);
		//OLED_ShowFloat(1,3,motorA.now,2,2);
		OLED_ShowChar(2,1,'b');
		OLED_ShowChar(2,2,'=');
		OLED_ShowNum(2,3,(int)motorB.now,2);
        
         if((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8))  //�ں�����ѭ��
        {   
            straight = 0;
            pid_control();        
        }
        else if((D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8) && ((fabs(yaw_gyro-(-148))<40)) && (if_stop ==0) )//ͣ��
        {    
            gpio_set(GPIO_A,Pin_6,1);
            gpio_set(GPIO_A,Pin_7,1);
            gpio_set(GPIO_B,Pin_0,1);
            gpio_set(GPIO_B,Pin_1,1);
            if_stop = 1 ;
               delay_ms (500);
                           
        }        
        else if((D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8) && ((fabs(yaw_gyro-(0))<5)||(fabs(yaw_gyro-(-148))<2)))//ֱ��pid
        {    
            straight = 1;
            pid_control();                                                    
        }            
        else if(straight == 0 && if_stop ==1)                
        {    
                pid_control_angle(-148);
            delay_ms (15);
        }
        else if(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)
          pid_control();
        TIM3->SR &= ~1; 
    }
}

int a;

void TIM4_IRQHandler(void)
{
	if(TIM4->SR&1)
	{
		//�˴���д�жϴ���
		//��
		printf("%f\r\n",motorA.now);
		OLED_ShowChar(1,1,'a');
		OLED_ShowChar(1,2,'=');
		//OLED_ShowNum(1,3,(int)motorA.now,5);
		OLED_ShowFloat(1,3,motorA.now,2,2);
		if((a==1)&&(!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8))
		{
			a = 0;
			gpio_set(GPIO_B,Pin_6,0);
			delay_ms(500);
			gpio_set(GPIO_B,Pin_6,1);
		
		}
		TIM4->SR &= ~1; 
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
