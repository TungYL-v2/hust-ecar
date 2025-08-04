#include "headfile.h"


int main(void)
{
	motor_init();   // 电机初始化
	encoder_init(); // 编码器初始化
    
//	uart_init(UART_1, 115200, 0x00);
	uart_init(UART_2, 115200, 0x00);        //k230串口，UART_2  =  0x01,  // PA2 -> TX     PA3 -> RX
    
	// 增量式不行就试试位置式POSITION_PID
	pid_init(&motorA, DELTA_PID, 10, 12, 5);
	pid_init(&motorB, DELTA_PID, 10, 12, 5);
	pid_init(&angle, POSITION_PID, 2, 0, 1);
	
	gpio_init(GPIO_B,Pin_14,OUT_PP );	//红灯控制引脚（暂定）
	gpio_set(GPIO_B,Pin_14,0);
	
	gpio_init(GPIO_B,Pin_12,OUT_PP );	//绿灯控制引脚（暂定）
	gpio_set(GPIO_B,Pin_12,0);
	
    // motor_target_set(10, 10);
	OLED_Init();
	OLED_Clear();	
	
//	tim_interrupt_ms_init(TIM_2,10,0);

	gray_init();

    // 角度传感器
	I2C_Init();
	JY901S_Init();
	detmdc_init();

	volatile uint8_t direction = 0;
	volatile uint8_t direction_2 = 0;
//	volatile uint8_t situation = -1;
	situation = 66;
    volatile uint8_t count = 0;

	delay_ms(1000); 
	
//	motorA_duty(21000);
//	motorB_duty(0); 
//	delay_ms(900);
//	
//	while(1)
//	{
//		car_stop(); 
//	}
	
//                                                           起步时，轮子最前点与起点最后面的黑线垂直
	while(det_medicine() == 0)
	{
//		count ++;
//		uint8_t a = Get_TurnSignal(UART_2);
//		JY901S_GetData(); 
//		Get_TurnSignal(UART_2);
//		OLED_ShowChar(1, 1, 'l');
//		OLED_ShowNum(2,1,count,5);
//		printf("%c,%d\r\n",signal,count); 
//		printf("yaw:%0.2f\r\n",yaw_gyro);
//		printf("det:%d",det_medicine());
		delay_ms(200);
		direction = signal;
	}
    
	delay_ms(1000);
	
//	if(direction == 'l'||direction == 'r')
//		situation = 0;
//	else if(direction == 's')
//	{
//		situation = 11;
////		goto task_23;
//	}
	
//	while(1)
//		printf("%c\r\n",direction);
	switch(direction)
	{
		case 'l':
		case 'r':
		{
			situation = 0;
			for(int i=0;i<98;i++)		//发车
			{     
				pid_control(); 
				delay_ms(15);				
			}
			
//			if(situation == 1)		//灰度传感器遇到路口时，再往前开一点点，保证车子到达路口
//			{
//				delay_ms(180); 
//				car_stop(); 
//				situation = 2;
//			}
			if(situation == 0)
			{
				car_stop();
				situation = 2;
			}
			
			
			while(situation == 2)		//转头
			 {	
				JY901S_GetData(); 
				switch(direction)
				{
					case 'l':		
						if(fabs(yaw_gyro- 270)<5)
						{
							car_stop();
							situation = 3;
						}
						else
						{
							pid_control_angle(270);
							delay_ms(10);					
						}
						break;				
					case 'r':	
						if(fabs(yaw_gyro- 90)<5)
						{
							car_stop();
							situation = 3;
						}
						else
						{
							pid_control_angle(90);
							delay_ms(10);	
						}
						break;	
				}
			}
			
			if(situation == 3)		//到病房		
			 {
				for(int j=0;j<48;j++)
				{
					pid_control();
					delay_ms(20);
				}
				gpio_set(GPIO_B,Pin_14,1);
				car_stop();
				situation = 4;	   
			 }
			 
			while(det_medicine() == 1 )	//若药品没取出，则一直停车，拿出后即走出循环
			{
				car_stop(); 
				delay_ms(50); 
			}
			
			if(situation==4)
			{
				delay_ms(800); 
				situation = 5;
				gpio_set(GPIO_B,Pin_14,0);
			}
			
			while(situation == 5)
			{
				switch(direction)
				{
					case 'r':
					for(int i=0;i<45;i++)
					{
						pid_control_line(-520,-520);
						delay_ms(20);
					}
					break;
					case 'l':
					for(int i=0;i<45;i++)
					{
						pid_control_line(-520,-520);
						delay_ms(20);
					}
					break;
						
				}
				car_stop();
				situation = 8;
				
			}
			
			
//			while(situation == 5)		//转头
//			 {    
//				JY901S_GetData(); 
//				switch(direction)
//				{
//					case 'l':		
//						if(fabs(yaw_gyro- 90)<5)
//						{
//							car_stop();
//							situation = 6;
//						}
//						else
//						{
//							pid_control_angle(90);
//							delay_ms(10);	
//						}
//						break;				
//					case 'r':	
//						if(fabs(yaw_gyro- 270)<5)
//						{
//							car_stop();
//							situation = 6;
//						}
//						else
//						{
//							pid_control_angle(270);
//							delay_ms(10);	
//						}
//						break;	
//				}
//			}
//			 
//			while(situation == 6)		//到路口
//			{
//				if( D8 )
//				{
//					pid_control();
//					delay_ms(20);
//				}
//				else
//					situation = 7;
//			}
//			
//			if(situation == 7)		//灰度传感器遇到路口时，再往前开一点点，保证车子到达路口
//			{    
////				pid_control_line(500,500);
//				delay_ms(285); 
//				car_stop(); 
//				situation = 8;
//			}
			
			while(situation == 8)		//转头
			{	
				JY901S_GetData(); 
				if(fabs(yaw_gyro - 0)<3)
				{
					car_stop();
					situation = 9;
				}
				else
				{
					switch(direction)
					{
						case 'l':
							pid_control_angle(360);
							break;
						case 'r':
							pid_control_angle(0);
							break;				
					}
				}	
			}
			
			while(situation == 9)		//回到起点
			{
				for(int j=0;j<70;j++)
				{
					pid_control(); 
					delay_ms(15);
				}
				situation = 10;
				break;
			}
			
			while(situation == 10)
			{
				car_stop();
				gpio_set(GPIO_B,Pin_12,1);
			}
			break;
		}
				
		case 's':
		{
			
			situation = 11;
			while(situation == 11)	//开到中端入口前可以检测识别数字的地方
			{
				for(int j=0;j<185;j++)
				{
					pid_control(); 
					delay_ms(15);
				}
				car_stop();
				situation = 12;
				break;
			}
			
			if(situation == 12)
			{
				for(int i=0;i<16;i++)
				 {
					delay_ms(80);
					direction = signal;
				}
				if(direction == 'l'||direction == 'r')
					situation = 13;	
				else
					situation = 24;	//若为s，即没有目标数字，则situation=24，继续往前
			}
			
//			while(situation == 13)		//继续往前开，直到传感器到红线路口处
//			{     
//				if( D8 )
//				{	
//					pid_control(); 
//					delay_ms(20);
//				}
//				else 
//				{    
//					situation = 14;
//					break;
//				}
//			}
			for(int i=0;i<32;i++)		//继续往前开，直到传感器到红线路口处
			{     
					pid_control(); 
					delay_ms(20);
			}			
			
			if(situation == 13)		
			{
				car_stop(); 
				situation = 15;
			}
			
			while(situation == 15)		//转头
			 {	
				JY901S_GetData(); 
				switch(direction)
				{
					case 'l':		
						if(fabs(yaw_gyro- 270)<5)
						{
							car_stop();
							situation = 16;
						}
						else
							{
								pid_control_angle(270);
								delay_ms(10);
							}
						break;				
					case 'r':	
						if(fabs(yaw_gyro- 89)<3.5)
						{
							car_stop();
							situation = 16;
						}
						else
						{
							pid_control_angle(89);
							delay_ms(10);
						}
						break;	
				}
			}
			
			if(situation == 16)		//到病房		
			 {
				for(int j=0;j<50;j++)
				{
					pid_control();
					delay_ms(20);
				}
				car_stop();
				gpio_set(GPIO_B,Pin_14,1);
				situation = 17;	   
			 }
			 
			while(det_medicine() == 1 && situation<24)	//若药品没取出，则一直停车，拿出后即走出循环
			{
				car_stop();
				delay_ms(1000); 
			}
			
			if(situation == 17)
			{
				situation = 18;
				gpio_set(GPIO_B,Pin_14,0);
			}
			
			while(situation == 18)		//转头
			 {    
				JY901S_GetData(); 
				switch(direction)
				{
					case 'l':		
						if(fabs(yaw_gyro- 89)<5)
						{
							car_stop();
							situation = 19;
						}
						else
						{
							pid_control_angle(89);
							delay_ms(10);
						}
						break;				
					case 'r':	
						if(fabs(yaw_gyro- 269)<5)
						{
							car_stop();
							situation = 19;
						}
						else
						{
							pid_control_angle(269);
							delay_ms(10);
						}
						break;	
				}
			}
			 
			
			if(situation == 19)		//到路口
			{
				for(int i=0;i<35;i++)
				{
					pid_control();
					delay_ms(20);
					if(!D1 && !D2 && !D3 && !D4 && !D5 )
						break;
				}
					situation = 20;
			}
			
			if(situation == 20)		//灰度传感器遇到路口时，再往前开一点点，保证车子到达路口
			{    
//				pid_control_line(500,500);
				delay_ms(290); 
				car_stop(); 
				situation = 21;
			}
			
			while(situation == 21)		//转头
			{	
				JY901S_GetData(); 
				if(fabs(yaw_gyro - 0)<3)
				{
					car_stop();
					situation = 22;
				}
				else
				{
					switch(direction)
					{
						case 'l':
						{
							pid_control_angle(0);
							delay_ms(10);
							break;
						}
						case 'r':
						{
							pid_control_angle(360);
							delay_ms(10);
							break;
						}				
					}
				}	
			}
			
			while(situation == 22)		//回到起点
			{
				for(int j=0;j<195;j++)
				{
					pid_control(); 
					delay_ms(20);
				}
				situation = 23;
				break;
			}
			
			while(situation == 23)	//第二小题结束，进入停车循环
			{
				car_stop();
				gpio_set(GPIO_B,Pin_12,1);
			}
			
			if(situation == 24)	//中端分类第二项，开到远端前停下，接下来识别四个数字
			{	
				motorA_duty(17000);
				motorB_duty(17000);
				delay_ms (200);
				for(int j=0;j<77;j++)
				{
					pid_control(); 
					delay_ms(15);
				}
				car_stop();
				situation = 25;	
			}
			
			if(situation == 25)		//识别四个数字，判断左右方向
			{
				for(int i=0;i<16;i++)
				 {
					delay_ms(80);
					direction = signal;
				}
				situation = 26;
			}
			
			if(situation == 26)
			{
				motorA_duty(15000);
				motorB_duty(15000);
				delay_ms (180);
			}
			
//			while(situation == 26)		//继续往前开，直到传感器到红线路口处
//			{     
//				if( D1 )
//				{	
//					pid_control(); 
//					delay_ms(20);
//				}
//				else 
//				{    
//					situation = 27;
//					break;
//				}
//			}
			for(int i=0;i<24;i++)		//继续往前开，直到传感器到红线路口处
			{     
				pid_control(); 
				delay_ms(20);
			}
			
			if(situation == 26)		
			{    
				car_stop(); 
				situation = 28;
			}
			
			while(situation == 28)		//转头
			 {	
				JY901S_GetData(); 
				switch(direction)
				{
					case 'l':		
						if(fabs(yaw_gyro- 268)<3)
						{
							car_stop();
							situation = 29;
						}
						else
						{	
							pid_control_angle(268);
							delay_ms(10);
						}
						break;				
					case 'r':	
						if(fabs(yaw_gyro- 90)<5)
						{
							car_stop();
							situation = 29;
						}
						else
						{
							pid_control_angle(90);
							delay_ms(10);
						}
						break;	
				}
			}
			
			while(situation == 29)		//开到第二个路口前停下，接下来识别两个数字
			{
				for(int j=0;j<82;j++)
				{
					pid_control(); 
					delay_ms(15);
					OLED_ShowNum(1,1,situation,2) ;
				}
				car_stop();
				situation = 30;	
			}
			
			if(situation == 30)		//识别两个数字，判断左右方向
			{
				for(int i=0;i<16;i++)
				 {
					delay_ms(80);
					direction_2 = signal;		//注意不是direction
				}
				situation = 31;
			}
			
			if(situation == 31)
			{
				motorA_duty(15000);
				motorB_duty(15000);
				delay_ms (400);
			}
			
//			while(situation == 31)		//继续往前开，直到传感器到第二个红线路口处
//			{   OLED_ShowNum(1,1,situation,2) ;  
//				if( D1 && D8 )
//				{	
//					pid_control();
//					delay_ms(20);
//					if(!D1 && !D2 && !D3 && !D4 && !D5 )
//						break;
//				}
//				else 
//				{    
//					situation = 32;
//					break;
//				}
//			}
//			
//			if(situation == 32)		//灰度传感器遇到第二个路口时，再往前开一点点，保证车子到达路口
//			{
//				OLED_ShowNum(1,1,situation,2) ;
//				delay_ms(300); 
//				car_stop(); 
//				situation = 33;
//			}
			while(situation == 31)
			{
				switch(direction)
				{
					case 'l':
					for(int i=0;i<20;i++)
					{
						pid_control();
						delay_ms(20);
					}
					break;
					case 'r':
					for(int i=0;i<20;i++)
					{
						pid_control();
						delay_ms(20);
					}
					break;
				}
				car_stop();
				situation = 33;
			}
			
			
			while(situation == 33)		//转头,四种情况
			 {	
				 //OLED_ShowNum(1,1,situation,2) ;
				JY901S_GetData(); 
				switch(direction)
				{
					case 'l':		
						switch(direction_2)
						{
							case 'l':
								if(fabs(yaw_gyro- 360)<3)
								{
									car_stop();
									situation = 34;
								}
								else
								{
									pid_control_angle(360);	
									delay_ms(10);
								}									
								break;
							case 'r':
								if(fabs(yaw_gyro- 180)<4)
								{
									car_stop();
									situation = 34;
								}
								else
								{
									pid_control_angle(180);		
									delay_ms(10);
								}									
								break;								
						}
						break;				
					case 'r':	
						switch(direction_2)
						{
							case 'l':
								if(fabs(yaw_gyro- 180)<4)
								{
									car_stop();
									situation = 34;
								}
								else
									pid_control_angle(180);	
									delay_ms(10);
								break;
							case 'r':
								if(fabs(yaw_gyro- 0)<4)
								{
									car_stop();
									situation = 34;
								}
								else
									pid_control_angle(0);		
									delay_ms(10);
								break;								
						}		
						break;	
				}
			}
			
			if(situation == 34)		//到病房		
			 {
				switch(direction)
				{
					case 'r':
					for(int j=0;j<47;j++)
					{
						pid_control();
						delay_ms(20);
					}
					break;
					case 'l':
					for(int j=0;j<51;j++)
					{
						pid_control();
						delay_ms(20);
					}
					break;
				}
				gpio_set(GPIO_B,Pin_14,1);
				car_stop();
				situation = 35;
			}
			 
			while(det_medicine() == 1 )	//若药品没取出，则一直停车，拿出后即走出循环
			{
				car_stop();
				delay_ms(1000); 
			}
			
			if(situation == 35)
			{
				situation = 36;
				gpio_set(GPIO_B,Pin_14,0);
			}
			
			/*尝试倒车*/
			while(situation == 36)
			{
				switch(direction)
				{
					case 'r':
					for(int i=0;i<45;i++)
					{
						pid_control_line(-520,-520);
						delay_ms(20);
					}
					break;
					case 'l':
					for(int i=0;i<52;i++)
					{
						pid_control_line(-520,-520);
						delay_ms(20);
					}
					break;
						
				}
				car_stop();
				situation = 39;
				
			}
			
			
//			while(situation == 36)		//往回转头180度,四种情况
//			 {    
//				JY901S_GetData(); 
//				switch(direction)
//				{
//					case 'l':		
//						
//						switch(direction_2)
//						{
//							case 'l':
//								if(fabs(yaw_gyro- 175)<4)
//								{
//									car_stop();
//									situation = 37;
//								}
//								else
//									pid_control_angle(175);								
//								break;
//							case 'r':
//								if(fabs(yaw_gyro- 5)<4)			//这个角度比较抽象
//								{
//									car_stop();
//									situation = 37;
//								}
//								else
//									pid_control_angle(5);								
//								break;								
//						}
//						break;		
//						
//					case 'r':	
//						
//						switch(direction_2)
//						{
//							case 'l':
//								if(fabs(yaw_gyro- 355)<5)
//								{
//									car_stop();
//									situation = 37;
//								}
//								else
//									pid_control_angle(355);								
//								break;
//							case 'r':
//								if(fabs(yaw_gyro- 185)<5)
//								{
//									car_stop();
//									situation = 37;
//								}
//								else
//									pid_control_angle(185);								
//								break;								
//						}		
//						break;	
//				}
//			}
//			
////			while(situation == 37)		//回到第二个路口
////			{
////				if( D1 && D8 )
////				{
////					pid_control();
////					delay_ms(20);
////				}
////				else
////					situation = 38;
////			}
//			while(situation == 37)		//回到第二个路口
//			{
//				for(int j=0;j<39;j++)
//				{
//					pid_control();
//					delay_ms(20);
//				}
//				car_stop();
//				situation = 39;
//			}
			
//			if(situation == 38)		//灰度传感器遇到第二个路口时，再往前开一点点，保证车子到达路口
//			{    
//				pid_control_line(500,500);
//				delay_ms(300);			//重点调试这个delay的时间
//				car_stop(); 
//				situation = 39;
//			}
			
//			delay_ms(300); 
			
			while(situation == 39)
			{
				JY901S_GetData(); 
				switch(direction)
				{
					case 'l':		
						if(fabs(yaw_gyro- 94)<3.5)
						{
							car_stop();
							situation = 40;
							break;
						}
						else
						{
							pid_control_angle(94);
							delay_ms(10);
						}							
						break;				
					case 'r':	
						if(fabs(yaw_gyro- 270)<4)
						{
							car_stop();
							situation = 40;
							break;
						}
						else
						{
							pid_control_angle(270);
							delay_ms(10);
						}							
						break;	
				}
			}
			
//			delay_ms(300); 
//			if(situation == 40)
//			{
//				motorA_duty(22000);
//				motorB_duty(22000);
//				delay_ms (1000);
//			}
////			
//			while(situation == 40)		//回到第一个路口
//			{
//				if( (direction == 'l' && D8 )||(direction == 'r' && D1 ))
//				{
//					pid_control();
//					delay_ms(18);
//				}
//				else
//					situation = 41;
//			}
//			
//			if(situation == 41)		//灰度传感器遇到第一个路口时，再往前开一点点，保证车子到达路口
//			{    	
//				delay_ms(310); 
//				car_stop(); 
//				situation = 42;
//			}
			
			if(situation == 40)	//回到第一个路口
			{	
				motorA_duty(13000);
				motorB_duty(13000);
				delay_ms (180);
				for(int j=0;j<115;j++)
				{
					pid_control(); 
					delay_ms(15);
				}
				car_stop();
				situation = 42;	
			}
			
			while(situation == 42)		//转头
			{	
				JY901S_GetData(); 
				if(fabs(yaw_gyro - 0)<4)
				{
					car_stop();
					situation = 43;
				}
				else
				{
					switch(direction)
					{
						case 'l':
						{
							pid_control_angle(0);
							delay_ms(25);
						}
						case 'r':
						{
							pid_control_angle(360);
							delay_ms(4);	
						}							
					}
				}	
			}
//			if(situation == 42)		//转头
//			{	     
//					delay_ms(200); 				
//					switch(direction)
//					{
//						case 'l':
//						{
//							motorA_duty(21000);
//							motorB_duty(0); 
//							delay_ms(950);
//							situation = 43;
//							break;
//						}
//						case 'r':
//						{
//							motorA_duty(0);
//							motorB_duty(21000); 
//							delay_ms(900);
//							situation = 43;
//							break;
//						}							
//					}
//					
//			}
			
			while(situation == 43)		//回到起点
			{

				/*       */
				motorA_duty(10000);
				motorB_duty(10000);
				/*change*/
				
				
				for(int j=0;j<315;j++)
				{
					pid_control(); 
					delay_ms(15);
				}
				situation = 44;
				break;
			
			}
				
			while(situation == 44)	//第三小题结束，进入停车循环
			{
				car_stop();
				gpio_set(GPIO_B,Pin_12,1);
			}
			
			break;
		}
		
	
	}
}

