#ifndef _HW_I2C_H
#define _HW_I2C_H

#include "headfile.h"

// 硬件I2C配置（使用I2C2）
#define HW_I2C               I2C2
#define HW_I2C_PORT          GPIO_B
#define HW_I2C_SCL_PIN       Pin_10
#define HW_I2C_SDA_PIN       Pin_11
#define HW_I2C_SPEED         100000  // 100kHz标准模式

// 超时设置
#define I2C_TIMEOUT          1000

void HW_I2C_Init(void);
uint8_t HW_I2C_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint8_t HW_I2C_ReadByte(uint8_t devAddr, uint8_t regAddr);
uint8_t HW_I2C_WriteBuffer(uint8_t devAddr, uint8_t regAddr, uint8_t *pBuffer, uint16_t len);
uint8_t HW_I2C_ReadBuffer(uint8_t devAddr, uint8_t regAddr, uint8_t *pBuffer, uint16_t len);

#endif
