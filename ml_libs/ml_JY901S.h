// ml_JY901S.h
#ifndef _JY901S_H
#define _JY901S_H
#include "stdint.h"
#include "ml_i2c.h"
#include "math.h"
//#include "wit_c_sdk.h"
extern int straight;
extern int if_stop;
extern int transformation;
extern int if_black;
extern uint8_t mode;


#define JYaddr      0x50

/* 系统配置寄存器 */
#define JY901_REG_SAVE          0x00  // 保存/重启/恢复出厂设置
#define JY901_REG_CALSW         0x01  // 校准模式
#define JY901_REG_RSW           0x02  // 输出内容控制
#define JY901_REG_RRATE         0x03  // 输出速率
#define JY901_REG_BAUD          0x04  // 串口波特率
#define JY901_REG_IICADDR       0x1A  // I2C设备地址
#define JY901_REG_LEDOFF        0x1B  // LED灯控制
#define JY901_REG_SLEEP         0x22  // 休眠控制
#define JY901_REG_ORIENT        0x23  // 安装方向
#define JY901_REG_AXIS6         0x24  // 算法选择
#define JY901_REG_POWONSEND     0x2D  // 指令启动控制
#define JY901_REG_KEY           0x69  // 解锁寄存器

/* 校准参数寄存器 */
#define JY901_REG_AXOFFSET      0x05  // 加速度X零偏
#define JY901_REG_AYOFFSET      0x06  // 加速度Y零偏
#define JY901_REG_AZOFFSET      0x07  // 加速度Z零偏
#define JY901_REG_GXOFFSET      0x08  // 角速度X零偏
#define JY901_REG_GYOFFSET      0x09  // 角速度Y零偏
#define JY901_REG_GZOFFSET      0x0A  // 角速度Z零偏
#define JY901_REG_HXOFFSET      0x0B  // 磁场X零偏
#define JY901_REG_HYOFFSET      0x0C  // 磁场Y零偏
#define JY901_REG_HZOFFSET      0x0D  // 磁场Z零偏
#define JY901_REG_MAGRANGX      0x1C  // 磁场X校准范围
#define JY901_REG_MAGRANGY      0x1D  // 磁场Y校准范围
#define JY901_REG_MAGRANGZ      0x1E  // 磁场Z校准范围

/* 传感器配置寄存器 */
#define JY901_REG_BANDWIDTH     0x1F  // 带宽设置
#define JY901_REG_GYRORANGE     0x20  // 陀螺仪量程
#define JY901_REG_ACCRANGE      0x21  // 加速度量程
#define JY901_REG_FILTK         0x25  // 动态滤波系数
#define JY901_REG_ACCFILT       0x2A  // 加速度滤波
#define JY901_REG_GYROCALITHR   0x61  // 陀螺仪静止阈值
#define JY901_REG_GYROCALTIME   0x63  // 陀螺仪自动校准时间

/* 时间寄存器 */
#define JY901_REG_YYMM          0x30  // 年月
#define JY901_REG_DDHH          0x31  // 日时
#define JY901_REG_MMSS          0x32  // 分秒
#define JY901_REG_MS            0x33  // 毫秒
#define JY901_REG_TIMEZONE      0x6B  // GPS时区

/* 传感器数据寄存器 */
#define JY901_REG_AX            0x34  // 加速度X
#define JY901_REG_AY            0x35  // 加速度Y
#define JY901_REG_AZ            0x36  // 加速度Z
#define JY901_REG_GX            0x37  // 角速度X
#define JY901_REG_GY            0x38  // 角速度Y
#define JY901_REG_GZ            0x39  // 角速度Z
#define JY901_REG_HX            0x3A  // 磁场X
#define JY901_REG_HY            0x3B  // 磁场Y
#define JY901_REG_HZ            0x3C  // 磁场Z
#define JY901_REG_ROLL          0x3D  // 横滚角
#define JY901_REG_PITCH         0x3E  // 俯仰角
#define JY901_REG_YAW           0x3F  // 航向角
#define JY901_REG_TEMP          0x40  // 温度
#define JY901_REG_WERROR        0x6A  // 陀螺仪变化值
#define JY901_REG_XREFROLL      0x79  // 横滚角零位参考值
#define JY901_REG_YREFPITCH     0x7A  // 俯仰角零位参考值

/* GPS相关寄存器 */
#define JY901_REG_GPSBAUD       0x26  // GPS波特率
#define JY901_REG_PRESSUREL     0x45  // 气压低16位
#define JY901_REG_PRESSUREH     0x46  // 气压高16位
#define JY901_REG_HEIGHTL       0x47  // 高度低16位
#define JY901_REG_HEIGHTH       0x48  // 高度高16位
#define JY901_REG_LONL          0x49  // 经度低16位
#define JY901_REG_LONH          0x4A  // 经度高16位
#define JY901_REG_LATL          0x4B  // 纬度低16位
#define JY901_REG_LATH          0x4C  // 纬度高16位
#define JY901_REG_GPSHEIGHT     0x4D  // GPS海拔
#define JY901_REG_GPSYAW        0x4E  // GPS航向角
#define JY901_REG_GPSVL         0x4F  // GPS地速低16位
#define JY901_REG_GPSVH         0x50  // GPS地速高16位
#define JY901_REG_SVNUM         0x55  // 卫星数
#define JY901_REG_PDOP          0x56  // 位置精度
#define JY901_REG_HDOP          0x57  // 水平精度
#define JY901_REG_VDOP          0x58  // 垂直精度

/* 四元数寄存器 */
#define JY901_REG_Q0            0x51  // 四元数0
#define JY901_REG_Q1            0x52  // 四元数1
#define JY901_REG_Q2            0x53  // 四元数2
#define JY901_REG_Q3            0x54  // 四元数3

/* 报警相关寄存器 */
#define JY901_REG_DELAYT        0x59  // 报警信号延时
#define JY901_REG_XMIN          0x5A  // X轴角度报警最小值
#define JY901_REG_XMAX          0x5B  // X轴角度报警最大值
#define JY901_REG_YMIN          0x5E  // Y轴角度报警最小值
#define JY901_REG_YMAX          0x5F  // Y轴角度报警最大值
#define JY901_REG_ALARMLEVEL    0x62  // 角度报警电平
#define JY901_REG_TRIGTIME      0x68  // 报警连续触发时间

/* 设备信息寄存器 */
#define JY901_REG_VERSION       0x2E  // 版本号
#define JY901_REG_BATVAL        0x5C  // 供电电压
#define JY901_REG_NUMBERID1     0x7F  // 设备编号1-2
#define JY901_REG_NUMBERID2     0x80  // 设备编号3-4
#define JY901_REG_NUMBERID3     0x81  // 设备编号5-6
#define JY901_REG_NUMBERID4     0x82  // 设备编号7-8
#define JY901_REG_NUMBERID5     0x83  // 设备编号9-10
#define JY901_REG_NUMBERID6     0x84  // 设备编号11-12

/* 引脚控制寄存器 */
#define JY901_REG_D0MODE        0x0E  // D0引脚模式
#define JY901_REG_D1MODE        0x0F  // D1引脚模式
#define JY901_REG_D2MODE        0x10  // D2引脚模式
#define JY901_REG_D3MODE        0x11  // D3引脚模式
#define JY901_REG_D0STATUS      0x41  // D0引脚状态
#define JY901_REG_D1STATUS      0x42  // D1引脚状态
#define JY901_REG_D2STATUS      0x43  // D2引脚状态
#define JY901_REG_D3STATUS      0x44  // D3引脚状态
#define JY901_REG_ALARMPIN      0x5D  // 报警引脚映射

/* KEY */
#define KEY_UNLOCK	0xB588

/* SAVE */
#define SAVE_PARAM	0x00
#define SAVE_SWRST	0xFF

/************RSW**************/
#define RSW_TIME 	0x01
#define RSW_ACC		0x02
#define RSW_GYRO	0x04
#define RSW_ANGLE	0x08
#define RSW_MAG		0x10
#define RSW_PORT	0x20
#define RSW_PRESS	0x40
#define RSW_GPS		0x80
#define RSW_V       0x100
#define RSW_Q       0x200
#define	RSW_GSA		0x400
#define RSW_MASK	0xfff

/**RRATE*****/
#define RRATE_NONE	0x0d
#define RRATE_02HZ	0x01
#define RRATE_05HZ	0x02
#define RRATE_1HZ 	0x03
#define RRATE_2HZ 	0x04
#define RRATE_5HZ 	0x05
#define RRATE_10HZ	0x06
#define RRATE_20HZ	0x07
#define RRATE_50HZ	0x08
#define RRATE_100HZ	0x09
#define RRATE_125HZ	0x0a	//only WT931
#define RRATE_200HZ	0x0b
#define RRATE_ONCE 	0x0c

/* BANDWIDTH */
#define BANDWIDTH_256HZ	0
#define BANDWIDTH_184HZ	1
#define BANDWIDTH_94HZ	2
#define BANDWIDTH_44HZ	3
#define BANDWIDTH_21HZ	4
#define BANDWIDTH_10HZ	5
#define BANDWIDTH_5HZ	6

#define DIO_MODE_AIN    0
#define DIO_MODE_DIN    1
#define DIO_MODE_DOH    2
#define DIO_MODE_DOL    3
#define DIO_MODE_DOPWM  4
#define DIO_MODE_GPS    5

extern float yaw;
extern float yaw_gyro,yaw_o;
extern const float YAW_SCALE;

void JY901S_Write(uint8_t reg, uint16_t dat);
uint16_t JY901S_Read(uint8_t reg);
void JY901S_Init(void);
void JY901S_GetData(void);


#endif
