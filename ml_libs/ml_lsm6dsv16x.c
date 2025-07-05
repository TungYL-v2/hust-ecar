// ml_lsm6dsv16x.c
#include "ml_lsm6dsv16x.h"

int16_t ax, ay, az, gx, gy, gz;
float roll_gyro, pitch_gyro, yaw_gyro;
float roll_acc, pitch_acc, yaw_acc;
float roll_Kalman, pitch_Kalman, yaw_Kalman;

void LSM6DSV16X_Write(uint8_t addr, uint8_t dat)
{
    I2C_Start();
    I2C_SendByte(LSM6DSV16X_ADDR);
    I2C_WaitAck();
    I2C_SendByte(addr);
    I2C_WaitAck();
    I2C_SendByte(dat);
    I2C_WaitAck();
    I2C_Stop();
}

uint8_t LSM6DSV16X_Read(uint8_t addr)
{
    I2C_Start();
    I2C_SendByte(LSM6DSV16X_ADDR);
    I2C_WaitAck();
    I2C_SendByte(addr);
    I2C_WaitAck();
    //I2C_Stop();
    
    I2C_Start();
    I2C_SendByte(LSM6DSV16X_ADDR | 0x01);
    I2C_WaitAck();
    uint8_t dat = I2C_ReceiveByte(0);
    I2C_NotSendAck();
    I2C_Stop();
    
    return dat;
}

void LSM6DSV16X_Init()
{
    // 验证设备ID
    uint8_t id = LSM6DSV16X_Read(LSM6DSV16X_WHO_AM_I);
    if(id != 0x70) {
        // 错误处理
        //while(1);
    }
    // 1. 加速度计配置：ODR=208Hz, ±2g, 高性能模式
    LSM6DSV16X_Write(LSM6DSV16X_CTRL1_XL, 0x4C);  // 01001100

    // 2. 陀螺仪配置：ODR=240Hz, 高性能模式
    LSM6DSV16X_Write(LSM6DSV16X_CTRL2_G, 0x07);   // 00000111

    // 3. 系统控制：启用BDU和地址自增
    //LSM6DSV16X_Write(LSM6DSV16X_CTRL3_C, 0x44);   // 01000100

    // 4. 陀螺仪量程设置：±2000dps
    LSM6DSV16X_Write(LSM6DSV16X_CTRL6_C, 0x04);   // 00001100

    // 5. 加速度计量程确认：±2g（默认值）
    LSM6DSV16X_Write(LSM6DSV16X_CTRL8_XL, 0x00);  // 00000000
  
	LSM6DSV16X_Write(LSM6DSV16X_CTRL4_C, 0x0a);   // 使能INT1的DRDY脉冲模式


	LSM6DSV16X_Write(LSM6DSV16X_IF_CFG, 0x78);    // INT1推挽输出/低电平有效
	LSM6DSV16X_Write(LSM6DSV16X_INT1_CTRL, 0x40); //陀螺仪
	LSM6DSV16X_Write(LSM6DSV16X_COUNTER_BDR1, 0x4a);
	LSM6DSV16X_Write(LSM6DSV16X_COUNTER_BDR2, 0xf4);
	
    LSM6DSV16X_Write(LSM6DSV16X_MD1_CFG, 0x00);
	LSM6DSV16X_Write(LSM6DSV16X_FIFO_CTRL1, 0x00);  // 关闭FIFO

}

void LSM6DSV16X_GetData()
{
	// 在LSM6DSV16X_GetData()开头添加状态检查
	uint8_t status = LSM6DSV16X_Read(0x1E); // STATUS_REG
	if(!(status & 0x02)) { 
		//printf("Gyro data not ready! STATUS=0x%02X\r\n", status);
		//return; // 数据未就绪时直接返回
}

    uint8_t data_h, data_l;
    
    // 读取加速度计数据 (连续读取可优化性能)
    data_h = LSM6DSV16X_Read(LSM6DSV16X_OUTX_H_A);
    data_l = LSM6DSV16X_Read(LSM6DSV16X_OUTX_L_A);
    ax = (data_h << 8) | data_l;
    
    data_h = LSM6DSV16X_Read(LSM6DSV16X_OUTY_H_A);
    data_l = LSM6DSV16X_Read(LSM6DSV16X_OUTY_L_A);
    ay = (data_h << 8) | data_l;
    
    data_h = LSM6DSV16X_Read(LSM6DSV16X_OUTZ_H_A);
    data_l = LSM6DSV16X_Read(LSM6DSV16X_OUTZ_L_A);
    az = (data_h << 8) | data_l;
    
    // 读取陀螺仪数据
    data_h = LSM6DSV16X_Read(LSM6DSV16X_OUTX_H_G);
    data_l = LSM6DSV16X_Read(LSM6DSV16X_OUTX_L_G);
    gx = (data_h << 8) | data_l;
    
    data_h = LSM6DSV16X_Read(LSM6DSV16X_OUTY_H_G);
    data_l = LSM6DSV16X_Read(LSM6DSV16X_OUTY_L_G);
    gy = (data_h << 8) | data_l;
    
    data_h = LSM6DSV16X_Read(LSM6DSV16X_OUTZ_H_G);
    data_l = LSM6DSV16X_Read(LSM6DSV16X_OUTZ_L_G);
    gz = (data_h << 8) | data_l;
	
	if(gz<=3 && gz>=-1)
		gz = 0;
}
