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
    uint8_t dat = I2C_ReceiveByte();
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
        while(1);
    }
    
    LSM6DSV16X_Write(LSM6DSV16X_CTRL1_XL, 0x6C);  // 加速度计416Hz, ±4g
    LSM6DSV16X_Write(LSM6DSV16X_CTRL2_G, 0x6C);   // 陀螺仪416Hz, ±2000dps
    
    // 2. 关键中断配置寄存器
    LSM6DSV16X_Write(LSM6DSV16X_CTRL3_C, 0x44);   // BDU=1, PP_OD=0 (推挽输出)
    LSM6DSV16X_Write(LSM6DSV16X_INT1_CTRL, 0x03); // 使能加速度+陀螺仪DRDY
    
    // 3. 必须配置的辅助寄存器

	LSM6DSV16X_Write(0x5A, 0x08);  // 设置INT1驱动强度为strong
    LSM6DSV16X_Write(0x0E, 0x00);    // INT1引脚无上拉
    //LSM6DSV16X_Write(0x5A, 0x01);    // 中断脉冲宽度=1个ODR周期
    LSM6DSV16X_Write(0x5B, 0x00);    // 中断信号无延迟
    

}

void LSM6DSV16X_GetData()
{
	// 在LSM6DSV16X_GetData()开头添加状态检查
	uint8_t status = LSM6DSV16X_Read(0x1E); // STATUS_REG
	if(!(status & 0x02)) { 
		printf("Gyro data not ready! STATUS=0x%02X\r\n", status);
		return; // 数据未就绪时直接返回
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
}
