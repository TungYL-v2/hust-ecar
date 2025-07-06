#include "stm32f10x.h" // Device header
#include "headfile.h"


uint8_t mode;

// ����Ϊ��ʱ���жϷ�����
void TIM2_IRQHandler(void)
{
	if (TIM2->SR & 1)
	{
		// �˴���д�жϴ���
		task_mode[mode]();
		TIM2->SR &= ~1;
	}
}

void TIM3_IRQHandler(void)
{

	if (TIM3->SR & 1) // ����������ȡ�Ƕȡ��ڰ�ת������
	{
		// �˴���д�жϴ���
		//       delay_ms(50);
		// ��ȡ����
		//        JY901S_GetData();
		OLED_ShowChar(1, 1, 'y');
		OLED_ShowChar(1, 2, 'a');
		OLED_ShowChar(1, 3, 'w');
		OLED_ShowChar(1, 4, '=');
		//	   OLED_ShowFloat(2,1,fabs(yaw_gyro - yaw_o - 185),3,2);
		OLED_ShowFloat(2, 1, yaw_o, 3, 2);
		OLED_ShowFloat(2, 8, yaw_gyro, 3, 2);
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

		if (((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8) && (if_black == 0)) || ((D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8) && (if_black == 1)))
		{ // ��������λ��ת��ʱ���������죬transformation��1
			transformation = transformation + 1;
			gpio_set(GPIO_B, Pin_6, 0);
			//	delay_ms(50);
			gpio_set(GPIO_B, Pin_6, 1);
		}

		if (!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8) // ��⴦�ڰ�ɫ����or��ɫ����
			if_black = 1;
		else
			if_black = 0;

		TIM3->SR &= ~1;
	}
}

void TIM4_IRQHandler(void)
{
	if (TIM4->SR & 1)
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

// ����Ϊ�����жϷ�����
void USART1_IRQHandler(void)
{
	if (USART1->SR & 0x20)
	{
		// �˴���д�жϴ���

		USART1->SR &= ~0x20; // �����־λ
	}
}

void USART2_IRQHandler(void)
{
	if (USART2->SR & 0x20)
	{
		// �˴���д�жϴ���

		USART2->SR &= ~0x20; // �����־λ
	}
}

void USART3_IRQHandler(void)
{
	if (USART3->SR & 0x20)
	{
		// �˴���д�жϴ���

		USART3->SR &= ~0x20; // �����־λ
	}
}

// ����Ϊ�ⲿ�жϷ�����
void EXTI0_IRQHandler(void) // PA0/PB0/PC0
{
	if (EXTI->PR & (1 << 0))
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 0; // �����־λ
	}
}

void EXTI1_IRQHandler(void) // PA1/PB1/PC1
{
	if (EXTI->PR & (1 << 1))
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 1; // �����־λ
	}
}
void EXTI2_IRQHandler(void) // PA2/PB2/PC2
{
	if (EXTI->PR & (1 << 2))
	{
		// �˴���д�жϴ���
		if (gpio_get(GPIO_A, Pin_3))
			Encoder_count1--;
		else
			Encoder_count1++;

		EXTI->PR = 1 << 2; // �����־λ
	}
}
void EXTI3_IRQHandler(void) // PA3/PB3/PC3
{
	if (EXTI->PR & (1 << 3))
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 3; // �����־λ
	}
}

void EXTI4_IRQHandler(void) // PA4/PB4/PC4
{
	if (EXTI->PR & (1 << 4))
	{
		// �˴���д�жϴ���
		if (gpio_get(GPIO_A, Pin_5))
			Encoder_count2++;
		else
			Encoder_count2--;
		EXTI->PR = 1 << 4; // �����־λ
	}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & (1 << 5)) // EXTI5  PA5/PB5/PC5
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 5; // �����־λ
	}

	if (EXTI->PR & (1 << 6)) // EXTI6  PA6/PB6/PC6
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 6; // �����־λ
	}

	if (EXTI->PR & (1 << 7)) // EXTI7  PA7/PB7/PC7
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 7; // �����־λ
	}

	if (EXTI->PR & (1 << 8)) // EXTI8
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 8; // �����־λ
	}

	if (EXTI->PR & (1 << 9)) // EXTI9
	{
		// �˴���д�жϴ���

		EXTI->PR = 1 << 9; // �����־λ
	}
}
