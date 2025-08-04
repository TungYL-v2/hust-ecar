#include "task.h"

//volatile uint8_t straight = 0;
//volatile uint8_t if_stop;
//volatile uint8_t transformation = 0;
//volatile uint8_t if_black = 0;
//volatile uint8_t task2_flag = 0;

//StateHandler task_mode[] = {task_1, task_2};

void detmdc_init(void)
{
	gpio_init(GPIO_B,Pin_7,ID);
}

uint8_t det_medicine(void)
{
	if (gpio_get(GPIO_B,Pin_7) == 1)
		return 0;
	else 
		return 1;		
}


//void task_1(void)
//{
//    if ((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)) // 在黑线
//			{
//				car_stop();
//			}
//			else
//			{
//				motorA_duty(20260);
//				motorB_duty(20453);
//			}
//}

//void task_2(void)
//{
//	if(task2_flag == 0)
//	{
//		pid_control_line(250,250);
//		if( !D3 || !D4 || !D5 || !D6 )
//		{
//			task2_flag = 1;
//			car_stop();
//		}
//	}
//	if(task2_flag == 1)
//	{
//		if(D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)
//		{
//			task2_flag = 2;
//			car_stop();
//		}
//		else
//		{
//				pid_control();
//		}
//	}
//	if(task2_flag==2)
//	{
//			if(yaw_gyro >150 && yaw_gyro <250)
//			{
//				pid_control_angle(181);
//			}
//			if(fabs(yaw_gyro-181)<3.5)
//			{
//				if(!D3 || !D4 || !D5 || !D6 )
//				{
//					car_stop();
//					task2_flag = 3;
//				}
//				else
//				{
//					pid_control_line(250,250);
//				}
//			}
//	}
//	if(task2_flag == 3)
//	{
//		pid_control();
//		if(  D2 && D3 && D4 && D5 && D6 && D7 )
//		{
//			task2_flag = 4;
//			car_stop();
//		}
//	}
//}
////    if (transformation <= 3) // 黑白转换次数<4（未回到出发点）
////			{
////				if ((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)) // 在黑线上循迹
////				{
////					straight = 0;
////					pid_control();
////				}

////				else if ((D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8) && (((fabs(yaw_gyro - yaw_o - 179) < 3)) || (fabs(yaw_o - yaw_gyro - 181) < 3))) // 直线pid  //
////				{
////					straight = 1;
////					pid_control_line(300,300);
////				}
////				else if ((straight == 0) && (transformation == 2) && (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)) // 出弯时角度不正则调整
////				{
////					if (yaw_o > 340 && yaw_o < 360)
////						pid_control_angle(yaw_o - 179);
////					else
////						pid_control_angle(yaw_o + 181);
////				}
////				else if (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)
////				{
////					pid_control_line(300,300);
////				}
////			}
////			if (transformation > 3) // 经过四次黑白转换，即回到A点，停车
////			{
////				car_stop();
////			}

//void task_3(void)
//{
//    if (transformation <= 3) // 黑白转换次数<4（未回到出发点）
//			{
//				if ((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)) // 在黑线上循迹
//				{
//					straight = 0;
//					pid_control();
//				}

//				else if ((D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8) && (transformation == 0) && (((fabs(yaw_o - yaw_gyro - 37) < 2)) || (fabs(yaw_gyro - yaw_o - 323) < 2))) // 直线pid  //
//				{
//					straight = 1;
//					pid_control();
//				}
//				else if ((D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8) && (transformation == 2) && (((fabs(yaw_o - yaw_gyro - 142) < 2)) || (fabs(yaw_gyro - yaw_o - 218) < 2))) // 直线pid  //
//				{
//					straight = 1;
//					pid_control();
//				}
//				else if ((straight == 0) && (transformation == 0) && (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)) // 出弯时角度不正则调整
//				{
//					if (yaw_o > 340 && yaw_o < 360)
//						pid_control_angle(yaw_o - 37);
//					else
//						pid_control_angle(yaw_o + 323);
//				}
//				else if ((straight == 0) && (transformation == 2) && (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)) // 出弯时角度不正则调整
//				{
//					if (yaw_o > 340 && yaw_o < 360)
//						pid_control_angle(yaw_o - 142);
//					else
//						pid_control_angle(yaw_o + 218);
//				}
//				else if (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)
//				{
//					pid_control();
//				}
//			}
//			if (transformation > 3) // 经过四次黑白转换，即回到A点，停车
//			{
//				gpio_set(GPIO_A, Pin_6, 1);
//				gpio_set(GPIO_A, Pin_7, 1);
//				gpio_set(GPIO_B, Pin_0, 1);
//				gpio_set(GPIO_B, Pin_1, 1);
//			}
//}

void sing(void)
{
	gpio_set(GPIO_B,Pin_6,0);
	delay_ms(20);
	gpio_set(GPIO_B,Pin_6,1);
}
void car_stop(void)
{
	gpio_set(GPIO_A,Pin_6,1);
	gpio_set(GPIO_A,Pin_7,1);
	gpio_set(GPIO_B,Pin_0,1);
	gpio_set(GPIO_B,Pin_1,1);
	motorA_duty(0);
	motorB_duty(0);
}

void low_speed(int time)
{
	for(int i=0;i<50;i++)
	{	
		for(int j=0;j<10;j++)
		{
			pid_control_line(i,i);
			delay_ms(3);
		}
	}
	for(int i=0;i<time;i++)				//这个i可调
	{
		pid_control_line(100,100);				
		delay_ms(5);
	}
}



void high_speed(int time)
{
	for(int i=0;i<50;i++)
	{	
		for(int j=0;j<10;j++)
		{
			pid_control_line(i,i);
			delay_us(1200);
		}
	}
	for(int i=0;i<=time;i++)				//这个i可调
	{
		pid_control_line(200,200);
		delay_ms(5);
	}
}

//volatile uint8_t flag = 0;//0是转角度 是直走 是灰度寻迹
//volatile uint8_t quan = 1;
//volatile uint8_t quan_max = 0;

//void text_3_4(void)
//{
//	yaw_o = 0;
//	while(quan<=quan_max)
//	{
//		motorA_duty(10000);
//		motorB_duty(0);
//		delay_ms(450);
//		motorA_duty(0);
//		while(flag == 0)//转头1
//		{	
//			JY901S_GetData();
//			delay_ms(10);
//			if((D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)&&yaw_gyro >300 && yaw_gyro <360)
//			{
//				pid_control_angle(319);
//			}
//			if(fabs(yaw_gyro-319)<3)
//			{
//				car_stop();
//				delay_ms(50);
//				flag = 1;
//				break;
//			}
//		}
//		
//		while(flag == 1)//走直线
//		{
//			high_speed(306);   
//			car_stop();
//			flag = 2;
//			break;
//		}
//		
//		while(flag == 2)//转头2
//		{
//			JY901S_GetData();
//			delay_ms(10);
//			if(yaw_gyro >300 && yaw_gyro <360)
//			{
//				pid_control_angle(359);
//			}
//			if(fabs(yaw_gyro-359.9)<2.5)
//			{
//				while(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)
//				{
//					for(int i=0;i<20;i++)
//					{	
//						for(int j=0;j<5;j++)
//						{
//							pid_control_line(i,i);
//							delay_us(1000);
//						}
//					}
//				}
//				sing();
//				car_stop();
//				delay_ms(50);
//				flag = 3;
//				break;
//			}
//		}
//		
//		while(flag == 3)//灰度
//		{
//			pid_control();
//			delay_ms(10);
//			if(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)
//			{
//				car_stop();
//				flag = 4;
//				sing();
//				break;
//			}
//		}
//		
//		while(flag == 4)//转头1
//		{
//			JY901S_GetData();
//			delay_ms(10);
//			if(yaw_gyro >150 && yaw_gyro <300)
//			{
//				pid_control_angle(230);
//			}
//			if(fabs(yaw_gyro-230)<3)
//			{
//				car_stop();
//				delay_ms(50);
//				flag = 5;
//				break;
//			}
//		}
//		
//		while(flag == 5)//走直线
//		{
//			high_speed(317);
//			car_stop();
//			flag = 6;
//			break;
//		}
//		
//		while(flag == 6)//转头2
//		{
//			JY901S_GetData();
//			delay_ms(10);
//			if(yaw_gyro >150 && yaw_gyro <250)
//			{
//				pid_control_angle(180);
//			}
//			if(fabs(yaw_gyro-180)<4)
//			{
//				while(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)
//				{
//					for(int i=0;i<20;i++)
//					{	
//						for(int j=0;j<10;j++)
//						{
//							pid_control_line(i,i);
//							delay_us(800);
//						}
//					}
//				}
//				sing();
//				car_stop();
//				delay_ms(50);
//				flag = 7;
//				break;
//			}
//		}
//		
//		while(flag == 7)//灰度
//		{
//			pid_control();
//			delay_ms(10);
//			if(D1&&D2&&D3&&D4&&D5&&D6&&D7&&D8)
//			{
//				car_stop();
//				flag = 0;
//				sing();
//				quan++;
//				break;
//			}
//		}
//	}
//}



