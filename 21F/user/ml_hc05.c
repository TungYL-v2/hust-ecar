/******************************************************************
 * 代码参考 嘉立创 
 https://wiki.lckfb.com/zh-hans/tmx-mspm0g3507/module/rf/hc05-bluetooth-module.html
******************************************************************/


#include "ml_hc05.h"

#define hc05_uart_INST UART_2_INST
#define hc05_IRQHandler UART_2_INST_IRQHandler                                                                                      
#define hc05_IRQN UART_2_INST_INT_IRQN                                      
#define hc05_RX_PORT GPIO_UART_2_RX_PORT                                               
#define hc05_TX_PORT GPIO_UART_2_TX_PORT                                                
#define hc05_RX_PIN GPIO_UART_2_RX_PIN                                        
#define hc05_TX_PIN GPIO_UART_2_TX_PIN                                         
// #define GPIO_UART_2_IOMUX_RX                                    
// #define GPIO_UART_2_IOMUX_TX                                     
// #define GPIO_UART_2_IOMUX_RX_FUNC                     
// #define GPIO_UART_2_IOMUX_TX_FUNC                     
// #define hc05_BAUD_RATE UART_2_BAUD_RATE                                               


unsigned char Bluetooth_ConnectFlag = 0; // 蓝牙连接状态 = 0没有手机连接   = 1有手机连接
unsigned char BLERX_BUFF[BLERX_LEN_MAX];
unsigned char BLERX_FLAG = 0;
unsigned char BLERX_LEN = 0;

// @brief       hc05初始化
// @return		void  
// Sample usage:	hc05_Init();     
void hc05_Init(void)
{
   uart_init(UART_3,9600,0);
}



//* 函 数 名 称：Bluetooth_Mode
//* 函 数 说 明：判断蓝牙模块的连接状态
//* 函 数 形 参：无
//* 函 数 返 回：无
//* 备       注：未连接时STATE低电平   连接成功时STATE高电平
void Bluetooth_Mode(void)
{
        static char flag = 0;
        //如果没有手机连接
        switch(BLUETOOTH_LINK)
        {
            case DISCONNECT:
                //连接状态为未连接
                Bluetooth_ConnectFlag = 0;
                //如果之前是连接状态
                if( flag == 1 )
                {
                        flag = 0;//修改状态
                }
                return;
            case CONNECT:
                Bluetooth_ConnectFlag = 1;
                                                //如果之前是断开状态
                if( flag == 0 )
                {
                        flag = 1;//修改状态
                }
        }
}

// /******************************************************************
//  * 函 数 名 称：Get_Bluetooth_ConnectFlag
//  * 函 数 说 明：获取手机连接状态
//  * 函 数 形 参：无
//  * 函 数 返 回：返回1=已连接                返回0=未连接
//  * 作       者：LC
//  * 备       注：使用该函数前，必须先调用 Bluetooth_Mode 函数
// ******************************************************************/
unsigned char Get_Bluetooth_ConnectFlag(void)
{
    return Bluetooth_ConnectFlag;
}

// /******************************************************************
//  * 函 数 名 称：hc05_Send_Bit
//  * 函 数 说 明：向蓝牙发送单个字符
//  * 函 数 形 参：ch=ASCII字符
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
void hc05_Send_Bit(unsigned char ch)
{
    //当串口1忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(hc05_uart_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(hc05_uart_INST, ch);
}

// /******************************************************************
//  * 函 数 名 称：BLE_send_String
//  * 函 数 说 明：向蓝牙发送字符串
//  * 函 数 形 参：str=发送的字符串
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
void hc05_send_String(unsigned char *str)
{
    while( str && *str ) // 地址为空或者值为空跳出
    {
        hc05_Send_Bit(*str++);
    }
}

// /******************************************************************
//  * 函 数 名 称：Clear_BLERX_BUFF
//  * 函 数 说 明：清除串口接收的数据
//  * 函 数 形 参：无
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
void Clear_BLERX_BUFF(void)
{
    BLERX_LEN = 0;
    BLERX_FLAG = 0;
}

// /******************************************************************
//  * 函 数 名 称：Receive_hc05_Data
//  * 函 数 说 明：接收蓝牙数据
//  * 函 数 形 参：无
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：无
// ******************************************************************/
void Receive_hc05_Data(void)
{
    if( BLERX_FLAG == 1 )//接收到蓝牙数据
    {
        /*接收数据后的操作*/
        /*即对BLERX_BUFF数组进行操作*/


        Clear_BLERX_BUFF();//清除接收缓存
    }
}

// /******************************************************************
//  * 函 数 名 称：Send_hc05_Data
//  * 函 数 说 明：向蓝牙模块发送数据
//  * 函 数 形 参：dat=要发送的字符串
//  * 函 数 返 回：无
//  * 作       者：LC
//  * 备       注：（如果手机连接了蓝牙，就是向手机发送数据）
// ******************************************************************/
void Send_hc05_Data(char *dat)
{
    //获取蓝牙状态
    Bluetooth_Mode();
    //如果手机已经连接
    if( Bluetooth_ConnectFlag == 1 )
    {
        //发送数据
        hc05_send_String((unsigned char*)dat);
    }
}



//void hc05_IRQHandler(void)
//{
//    switch (DL_UART_Main_getPendingInterrupt(hc05_uart_INST)) 
//    {
//        case DL_UART_MAIN_IIDX_RX:
//            if (BLERX_LEN < BLERX_LEN_MAX - 1) // 保留一个字符的空间用于'\0'
//            {
//                BLERX_BUFF[BLERX_LEN++] = DL_UART_Main_receiveData(hc05_uart_INST); // 接收数据
//            }
//            else
//            {
//                uint8_t temp = DL_UART_Main_receiveData(hc05_uart_INST); // 不保存数据
//            }

//            BLERX_BUFF[BLERX_LEN] = '\0';  // 确保字符串正确结束
//            BLERX_FLAG = 1;  // 设置接收完成标志位
//            

//            DL_UART_clearInterruptStatus(hc05_uart_INST, DL_UART_MAIN_IIDX_RX);
//            break;
//        default:
//            break;
//    }
//    
//}

