// ml_lsm6dsv16x.h
#ifndef _LSM6DSV16X_H
#define _LSM6DSV16X_H
#include "stdint.h"
#include "ml_i2c.h"
#include "math.h"

#define LSM6DSV16X_ADDR         0x6A << 1 // 默认I2C地址(SA0=0:0x6A << 1)
#define LSM6DSV16X_IF_CFG 		0x03 // 配置接口和中断引脚特性
#define LSM6DSV16X_WHO_AM_I     0x0F // 设备校验
#define LSM6DSV16X_CTRL1_XL     0x10 // 加速度计控制
#define LSM6DSV16X_CTRL2_G      0x11 // 陀螺仪控制
#define LSM6DSV16X_CTRL3_C      0x12 // 主控制
#define LSM6DSV16X_CTRL4_C		0x13 // 控制中断和DRDY行为
#define LSM6DSV16X_CTRL6_C      0x15
#define LSM6DSV16X_CTRL8_XL     0x17
#define LSM6DSV16X_OUTX_L_G     0x22 // 陀螺仪X低字节
#define LSM6DSV16X_OUTX_H_G     0x23 // 陀螺仪X高字节
#define LSM6DSV16X_OUTY_L_G     0x24 // 陀螺仪Y低字节
#define LSM6DSV16X_OUTY_H_G     0x25 // 陀螺仪Y高字节
#define LSM6DSV16X_OUTZ_L_G     0x26 // 陀螺仪Z低字节
#define LSM6DSV16X_OUTZ_H_G     0x27 // 陀螺仪Z高字节
#define LSM6DSV16X_OUTX_L_A     0x28 // 加速度计X低字节
#define LSM6DSV16X_OUTX_H_A     0x29 // 加速度计X高字节
#define LSM6DSV16X_OUTY_L_A     0x2A // 加速度计Y低字节
#define LSM6DSV16X_OUTY_H_A     0x2B // 加速度计Y高字节
#define LSM6DSV16X_OUTZ_L_A     0x2C // 加速度计Z低字节
#define LSM6DSV16X_OUTZ_H_A     0x2D // 加速度计Z高字节
#define LSM6DSV16X_OUT_TEMP_L   0x20 // 温度低字节
#define LSM6DSV16X_OUT_TEMP_H   0x21 // 温度高字节
#define LSM6DSV16X_TAP_CFG		0x56 // 
#define LSM6DSV16X_FIFO_CTRL1	0x07



#define LSM6DSV16X_COUNTER_BDR1   0x0B
#define LSM6DSV16X_COUNTER_BDR2   0x0C
#define LSM6DSV16X_INT1_CTRL      0x0D  // INT1引脚控制
#define LSM6DSV16X_INT2_CTRL      0x0E  // INT2引脚控制
#define LSM6DSV16X_MD1_CFG        0x5E  // 唤醒/数据就绪中断路由到INT1
#define LSM6DSV16X_MD2_CFG        0x5F  // 唤醒/数据就绪中断路由到INT2
#define LSM6DSV16X_STATUS_REG     0x1E  // 数据就绪状态寄存器

// 保持与原有MPU6050相同的全局变量定义
extern int16_t ax, ay, az, gx, gy, gz;
extern float roll_gyro, pitch_gyro, yaw_gyro;
extern float roll_acc, pitch_acc, yaw_acc;
extern float roll_Kalman, pitch_Kalman, yaw_Kalman;

void LSM6DSV16X_Write(uint8_t addr, uint8_t dat);
uint8_t LSM6DSV16X_Read(uint8_t addr);
void LSM6DSV16X_Init(void);
void LSM6DSV16X_GetData(void);

#endif
