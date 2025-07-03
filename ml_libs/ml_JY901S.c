// ml_JY901.c
#include "ml_JY901S.h"

void JY901S_Write(uint8_t reg, uint16_t dat)
{
    I2C_Start();
    I2C_SendByte(JYaddr);
    I2C_WaitAck();
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_SendByte(dat & 0xFF);
    I2C_WaitAck();
    I2C_SendByte(dat >> 8);
    I2C_WaitAck();
    I2C_Stop();
}


uint16_t JY901S_Read(uint8_t reg)
{
    uint8_t low,high;
    I2C_Start();
    I2C_SendByte(JYaddr << 1);     // 写地址
    I2C_WaitAck();
    I2C_SendByte(reg);                  // 起始寄存器地址
    I2C_WaitAck();
    
    I2C_Start();
    I2C_SendByte((JYaddr << 1) | 1); // 读地址
    I2C_WaitAck();
    
    low = I2C_ReceiveByte();     //低字节
    I2C_SendAck();

    high = I2C_ReceiveByte();      // 高字节
    I2C_NotSendAck();

    // // 连续读取数据
    // for(uint8_t i = 0; i < len; i++) {
    //     buf[i] = I2C_ReceiveByte();
    //     if(i == len - 1) {
    //         I2C_NotSendAck();           // 最后一个字节不发送ACK
    //     } else {
    //         I2C_SendAck();              // 发送ACK继续读取
    //     }
    // }
    
    I2C_Stop();

    return (high << 8) | low;
}

void JY901S_Init(void)
{
    delay_ms(50);
    //unlock reg
    JY901S_Write(JY901_REG_KEY, 0xb588);
    delay_ms(20);
    JY901S_Write(JY901_REG_RSW,RSW_ANGLE);
    JY901S_Write(JY901_REG_RRATE,RRATE_10HZ);
    JY901S_Write(JY901_REG_BANDWIDTH,BANDWIDTH_21HZ);

    JY901S_Write(JY901_REG_SAVE,SAVE_PARAM);

    delay_ms(100);

    // 验证设备ID
    uint8_t ver = JY901S_Read(JY901_REG_VERSION);
    if(!ver) {
        // 错误处理
        //while(1);
        printf("ever:%d\r\n",ver);
    }
	else
        printf("ver:%d",ver);
    

}

void JY901S_GetData(void)
{
    
    // 解析角度数据(小端模式)
    //int16_t roll  = (buf[1] << 8) | buf[0];  // X轴角度
    //int16_t pitch = (buf[3] << 8) | buf[2];  // Y轴角度
    yaw_gyro   = JY901S_Read(JY901_REG_YAW)/ 32768.0 * 180.0;  // Z轴角度

}



