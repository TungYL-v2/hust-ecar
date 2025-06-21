#include "headfile.h"

int main(void)
{

	motor_init();       //电机初始化
	encoder_init();     //编码器初始化
	//motorA_duty(20000);    
	//motorB_duty(19840); 
    uart_init(UART_1,115200,0x00);
	//增量式不行就试试位置式POSITION_PID
	pid_init(&motorA, POSITION_PID, 10, 10, 5);
	pid_init(&motorB, POSITION_PID, 10, 10, 5);
	motor_target_set(10, 10);
	
	
	
	//角度传感器
	
	I2C_Init();
	LSM6DSV16X_Init();
//	MPU6050_Init();
	exti_init(EXTI_PB7,FALLING,0);
	
	
	
	
	tim_interrupt_ms_init(TIM_3,10,0);
 	while (1)
	{
//		printf("speedA_now:%d,speedB_now:%d\r\n",(int)motorA.now,(int)motorB.now);
		//printf("speed_now:%d\r\n",(int)speed_now);
		LSM6DSV16X_GetData();
				// 陀螺仪角度
		roll_gyro += (float)gx / 16.4 * 0.005;
		pitch_gyro += (float)gy / 16.4 * 0.005;
		yaw_gyro += (float)gz / 16.4 * 0.005;
		
		// 加速度计角度
		roll_acc = atan((float)ay/az) * 57.296;
		pitch_acc = - atan((float)ax/az) * 57.296;	
		yaw_acc = atan((float)ay/ax) * 57.296;
		roll_Kalman = Kalman_Filter(&KF_Roll, roll_acc, (float)gx / 16.4);
		pitch_Kalman = Kalman_Filter(&KF_Pitch, pitch_acc, (float)gy / 16.4);
		//printf("roll_gyro:%.2f,pitch_gyro:%.2f,yaw_gyro:%.2f,roll_acc:%.2f,pitch_acc:%.2f,yaw_acc:%.2f\r\n",roll_gyro,pitch_gyro,yaw_gyro,roll_acc,pitch_acc,yaw_acc);
		printf("roll_Kalman:%.2f\r\n",roll_Kalman);
		delay_ms(20);
		// 读取CTRL2_G寄存器值（应为0x6C）
		//uint8_t ctrl2g = LSM6DSV16X_Read(LSM6DSV16X_CTRL2_G); 
		//printf("CTRL2_G=0x%02X\n", ctrl2g); // 预期输出0x6C
		// 读取并打印关键寄存器
//		uint8_t ctrl2g = LSM6DSV16X_Read(0x11); // CTRL2_G
//		uint8_t ctrl3c = LSM6DSV16X_Read(0x12); // CTRL3_C
//		uint8_t ctrl7g = LSM6DSV16X_Read(0x16); // CTRL7_G
//		printf("CTRL2_G=0x%02X, CTRL3_C=0x%02X, CTRL7_G=0x%02X\r\n", ctrl2g, ctrl3c, ctrl7g);
		// 绕过状态寄存器直接读取Z轴原始值
//		uint8_t zl = LSM6DSV16X_Read(0x26); // OUTZ_L_G
//		uint8_t zh = LSM6DSV16X_Read(0x27); // OUTZ_H_G
//		int16_t gz_raw = (zh << 8) | zl;
//		printf("GZ_RAW=0x%04X (%d)\r\n", gz_raw, gz_raw);
		// 在初始化后读取关键寄存器验证
//		uint8_t int1_ctrl = LSM6DSV16X_Read(LSM6DSV16X_INT1_CTRL);
//		uint8_t ctrl3_c = LSM6DSV16X_Read(LSM6DSV16X_CTRL3_C);
//		printf("INT1_CTRL=0x%02X CTRL3_C=0x%02X\r\n", int1_ctrl, ctrl3_c);
		// 正确值应为：INT1_CTRL=0x03, CTRL3_C=0x44






	} 
}


