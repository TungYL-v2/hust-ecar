#include "task.h"

int straight = 0;
int if_stop;
int transformation = 0;
int if_black = 0;

StateHandler task_mode[] = {task_1, task_2, task_3, task_4};

void task_1(void)
{
    if ((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)) // 在黑线
			{
				gpio_set(GPIO_A, Pin_6, 1);
				gpio_set(GPIO_A, Pin_7, 1);
				gpio_set(GPIO_B, Pin_0, 1);
				gpio_set(GPIO_B, Pin_1, 1);
			}
			else
			{
				motorA_duty(26260);
				motorB_duty(26453);
			}
}

void task_2(void)
{
    if (transformation <= 3) // 黑白转换次数<4（未回到出发点）
			{
				if ((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)) // 在黑线上循迹
				{
					straight = 0;
					pid_control();
				}

				else if ((D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8) && (((fabs(yaw_gyro - yaw_o - 179) < 3)) || (fabs(yaw_o - yaw_gyro - 181) < 3))) // 直线pid  //
				{
					straight = 1;
					pid_control();
				}
				else if ((straight == 0) && (transformation == 2) && (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)) // 出弯时角度不正则调整
				{
					if (yaw_o > 340 && yaw_o < 360)
						pid_control_angle(yaw_o - 179);
					else
						pid_control_angle(yaw_o + 181);
				}
				else if (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)
				{
					pid_control();
				}
			}
			if (transformation > 3) // 经过四次黑白转换，即回到A点，停车
			{
				gpio_set(GPIO_A, Pin_6, 1);
				gpio_set(GPIO_A, Pin_7, 1);
				gpio_set(GPIO_B, Pin_0, 1);
				gpio_set(GPIO_B, Pin_1, 1);
			}
}

void task_3(void)
{
    if (transformation <= 3) // 黑白转换次数<4（未回到出发点）
			{
				if ((!D1 || !D2 || !D3 || !D4 || !D5 || !D6 || !D7 || !D8)) // 在黑线上循迹
				{
					straight = 0;
					pid_control();
				}

				else if ((D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8) && (transformation == 0) && (((fabs(yaw_o - yaw_gyro - 37) < 2)) || (fabs(yaw_gyro - yaw_o - 323) < 2))) // 直线pid  //
				{
					straight = 1;
					pid_control();
				}
				else if ((D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8) && (transformation == 2) && (((fabs(yaw_o - yaw_gyro - 142) < 2)) || (fabs(yaw_gyro - yaw_o - 218) < 2))) // 直线pid  //
				{
					straight = 1;
					pid_control();
				}
				else if ((straight == 0) && (transformation == 0) && (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)) // 出弯时角度不正则调整
				{
					if (yaw_o > 340 && yaw_o < 360)
						pid_control_angle(yaw_o - 37);
					else
						pid_control_angle(yaw_o + 323);
				}
				else if ((straight == 0) && (transformation == 2) && (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)) // 出弯时角度不正则调整
				{
					if (yaw_o > 340 && yaw_o < 360)
						pid_control_angle(yaw_o - 142);
					else
						pid_control_angle(yaw_o + 218);
				}
				else if (D1 && D2 && D3 && D4 && D5 && D6 && D7 && D8)
				{
					pid_control();
				}
			}
			if (transformation > 3) // 经过四次黑白转换，即回到A点，停车
			{
				gpio_set(GPIO_A, Pin_6, 1);
				gpio_set(GPIO_A, Pin_7, 1);
				gpio_set(GPIO_B, Pin_0, 1);
				gpio_set(GPIO_B, Pin_1, 1);
			}
}

void task_4(void)
{
	
}



