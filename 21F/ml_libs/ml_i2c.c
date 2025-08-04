#include "ml_i2c.h"

#define SDA_Output(x)  gpio_set(I2C_GPIO, I2C_SDA_GPIO_Pin, x)
#define SCL_Output(x)  gpio_set(I2C_GPIO, I2C_SCL_GPIO_Pin, x)
#define SDA_Input() gpio_get(I2C_GPIO, I2C_SDA_GPIO_Pin)

void Delay(u32 count)//400KHzIIC
{
	unsigned int uiCnt = count*8;
	while (uiCnt --);
}

void I2C_Init()
{
	gpio_init(I2C_GPIO, I2C_SCL_GPIO_Pin, OUT_OD);
	gpio_init(I2C_GPIO, I2C_SDA_GPIO_Pin, OUT_OD);
	
	SDA_OUT();     
	IIC_SDA=1;	  	  
	IIC_SCL=1;
}

// 起始信号
void I2C_Start(void)
{
	SDA_OUT();    
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	
	Delay(5);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	
	Delay(5);
	IIC_SCL=0;
}

// 终止信号 
void I2C_Stop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	
		Delay(5);
	IIC_SCL=1; 
	IIC_SDA=1;
	
		Delay(5);							   	
}

// 主机发送一个字节
void I2C_SendByte(uint8_t txd)
{
	uint8_t t; 
		SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
			
		Delay(2);   
		IIC_SCL=1;
		Delay(5);
		IIC_SCL=0;	
		Delay(3);
    }	 
}

// 主机接收一个字节
uint8_t I2C_ReceiveByte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        
		Delay(5);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		
		Delay(5); 
    }					 
    if (ack)
        I2C_SendAck(); 
    else
        I2C_NotSendAck();
    return receive;
}

// 主机应答 
void I2C_SendAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
		Delay(5);
	IIC_SCL=1;
		Delay(5);
	IIC_SCL=0;
}

// 主机不应答 
void I2C_NotSendAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	
		Delay(5);
	IIC_SCL=1;
		Delay(5);
	IIC_SCL=0;
}

// 等待从机应答 
#define I2C_TIMEOUT 10  // 超时计数器值

uint8_t I2C_WaitAck(void)
{
	uint8_t ucErrTime=0; 
	SDA_IN();     
	IIC_SDA=1;
		Delay(5);	  
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			I2C_Stop();
			return 1;
		}
		Delay(5);
	}  
	IIC_SCL=1;
	Delay(5); 
	IIC_SCL=0;
	return 0;  
} 

int32_t IICreadBytes(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length)
{
    uint32_t count = 0;

    I2C_Start();
    I2C_SendByte(dev);	
    if(I2C_WaitAck() == 1)return 0;
    I2C_SendByte(reg);
    if(I2C_WaitAck() == 1)return 0;
    I2C_Start();
    I2C_SendByte(dev+1); 
    if(I2C_WaitAck() == 1)return 0;

    for(count=0; count<length; count++)
    {
        if(count!=length-1)data[count]=I2C_ReceiveByte(1);
        else  data[count]=I2C_ReceiveByte(0);	 
    }
    I2C_Stop();
    return 1;
}


int32_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length)
{
    uint32_t count = 0;
    I2C_Start();
    I2C_SendByte(dev);	   
    if(I2C_WaitAck() == 1)return 0;
    I2C_SendByte(reg);   
    if(I2C_WaitAck() == 1)return 0;
    for(count=0; count<length; count++)
    {
        I2C_SendByte(data[count]);
        if(I2C_WaitAck() == 1)return 0;
    }
    I2C_Stop();

    return 1; 
}

