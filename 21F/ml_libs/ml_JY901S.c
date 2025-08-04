// ml_JY901.c
#include "ml_JY901S.h"

float yaw_o, yaw, yaw_gyro;
const float YAW_SCALE = 180.0f / 32768.0f;

void JY901S_Write(uint8_t reg, uint16_t dat)
{
    I2C_Start();
    I2C_SendByte(JYaddr << 1);
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
    if(I2C_WaitAck())
		goto ERROR;
    I2C_SendByte(reg);                  // 起始寄存器地址
    if(I2C_WaitAck())
		goto ERROR;
	
    I2C_Start();
    I2C_SendByte((JYaddr << 1) | 1); // 读地址
    if(I2C_WaitAck())
		goto ERROR;
    
    low = I2C_ReceiveByte(1);     //低字节

    high = I2C_ReceiveByte(0);      // 高字节
    I2C_NotSendAck();

    I2C_Stop();
	
	return (high << 8) | low;
	
	ERROR:
		I2C_Stop();
		return yaw_gyro;
    
}
float last_yaw, error;
void JY901S_Init(void)
{
//    delay_ms(50);
//    //unlock reg
//    JY901S_Write(JY901_REG_KEY, 0xb588);
//    delay_ms(20);
//    JY901S_Write(JY901_REG_RSW,RSW_ANGLE);
//    JY901S_Write(JY901_REG_RRATE,RRATE_10HZ);
//    JY901S_Write(JY901_REG_BANDWIDTH,BANDWIDTH_21HZ);

//    JY901S_Write(JY901_REG_SAVE,SAVE_PARAM);

    delay_ms(100);
	
    // 验证设备ID
//    uint8_t ver = JY901S_Read(JY901_REG_VERSION);
//    if(!ver) {
//        // 错误处理
//        //while(1);
//        printf("ever:%d\r\n",ver);
//    }
//	else
//        printf("ver:%d",ver);

	int otime = 0;
	while(otime < 10)
	{
		otime++;
		yaw_o = JY901S_Read(JY901_REG_YAW) * YAW_SCALE; 
		yaw_o = yaw_o + 180;
          yaw_o = yaw_o >= 360 ? yaw_o - 360 : yaw_o;
		delay_ms(100);
	}
     
	last_yaw = 180;
	yaw = 180;
}



void JY901S_GetData(void)
{
    
    last_yaw = yaw;
    yaw = JY901S_Read(JY901_REG_YAW) / 32768.0 * 180.0;
    error = fabs(yaw - last_yaw);
    if(error > 180.0f) error = 360.0f - error; // 处理跨360°情况
    if (error < 0.008)
        ;//yaw_gyro = last_yaw; // yaw_gyro不更新
    else
        yaw_gyro = yaw; // yaw_gyro更新
    
    yaw = yaw + 180;
    yaw_gyro = yaw >= 360 ? yaw - 360 : yaw;

    // yaw_gyro   = JY901S_Read(JY901_REG_YAW)/ 32768.0 * 180.0;  // Z轴角度

}



