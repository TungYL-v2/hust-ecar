#ifndef _ml_hc05_h_
#define _ml_hc05_h_

#include "stm32f10x.h"
#include "ml_gpio.h"
#include "ml_uart.h"
#include "stdio.h"

#define  BLERX_LEN_MAX  200

#define  BLUETOOTH_LINK      ( ( gpio_get( HC05_PORT, HC05_state_PIN ) & HC05_state_PIN ) ? 1 : 0 )

#define  CONNECT             1       //蓝牙连接成功
#define  DISCONNECT          0       //蓝牙连接断开

extern unsigned char BLERX_BUFF[BLERX_LEN_MAX];
extern unsigned char BLERX_FLAG;
extern unsigned char BLERX_LEN;

void Send_hc05_Data(char *dat);
void Receive_hc05_Data(void);
void Clear_BLERX_BUFF(void);
void hc05_send_String(unsigned char *str);
void hc05_Send_Bit(unsigned char ch);
unsigned char Get_Bluetooth_ConnectFlag(void);
void Bluetooth_Mode(void);
void hc05_Init(void);



#endif
