/******************************************************************
 * ����ο� ������ 
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


unsigned char Bluetooth_ConnectFlag = 0; // ��������״̬ = 0û���ֻ�����   = 1���ֻ�����
unsigned char BLERX_BUFF[BLERX_LEN_MAX];
unsigned char BLERX_FLAG = 0;
unsigned char BLERX_LEN = 0;

// @brief       hc05��ʼ��
// @return		void  
// Sample usage:	hc05_Init();     
void hc05_Init(void)
{
   uart_init(UART_3,9600,0);
}



//* �� �� �� �ƣ�Bluetooth_Mode
//* �� �� ˵ �����ж�����ģ�������״̬
//* �� �� �� �Σ���
//* �� �� �� �أ���
//* ��       ע��δ����ʱSTATE�͵�ƽ   ���ӳɹ�ʱSTATE�ߵ�ƽ
void Bluetooth_Mode(void)
{
        static char flag = 0;
        //���û���ֻ�����
        switch(BLUETOOTH_LINK)
        {
            case DISCONNECT:
                //����״̬Ϊδ����
                Bluetooth_ConnectFlag = 0;
                //���֮ǰ������״̬
                if( flag == 1 )
                {
                        flag = 0;//�޸�״̬
                }
                return;
            case CONNECT:
                Bluetooth_ConnectFlag = 1;
                                                //���֮ǰ�ǶϿ�״̬
                if( flag == 0 )
                {
                        flag = 1;//�޸�״̬
                }
        }
}

// /******************************************************************
//  * �� �� �� �ƣ�Get_Bluetooth_ConnectFlag
//  * �� �� ˵ ������ȡ�ֻ�����״̬
//  * �� �� �� �Σ���
//  * �� �� �� �أ�����1=������                ����0=δ����
//  * ��       �ߣ�LC
//  * ��       ע��ʹ�øú���ǰ�������ȵ��� Bluetooth_Mode ����
// ******************************************************************/
unsigned char Get_Bluetooth_ConnectFlag(void)
{
    return Bluetooth_ConnectFlag;
}

// /******************************************************************
//  * �� �� �� �ƣ�hc05_Send_Bit
//  * �� �� ˵ �������������͵����ַ�
//  * �� �� �� �Σ�ch=ASCII�ַ�
//  * �� �� �� �أ���
//  * ��       �ߣ�LC
//  * ��       ע����
// ******************************************************************/
void hc05_Send_Bit(unsigned char ch)
{
    //������1æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
    while( DL_UART_isBusy(hc05_uart_INST) == true );
    //���͵����ַ�
    DL_UART_Main_transmitData(hc05_uart_INST, ch);
}

// /******************************************************************
//  * �� �� �� �ƣ�BLE_send_String
//  * �� �� ˵ ���������������ַ���
//  * �� �� �� �Σ�str=���͵��ַ���
//  * �� �� �� �أ���
//  * ��       �ߣ�LC
//  * ��       ע����
// ******************************************************************/
void hc05_send_String(unsigned char *str)
{
    while( str && *str ) // ��ַΪ�ջ���ֵΪ������
    {
        hc05_Send_Bit(*str++);
    }
}

// /******************************************************************
//  * �� �� �� �ƣ�Clear_BLERX_BUFF
//  * �� �� ˵ ����������ڽ��յ�����
//  * �� �� �� �Σ���
//  * �� �� �� �أ���
//  * ��       �ߣ�LC
//  * ��       ע����
// ******************************************************************/
void Clear_BLERX_BUFF(void)
{
    BLERX_LEN = 0;
    BLERX_FLAG = 0;
}

// /******************************************************************
//  * �� �� �� �ƣ�Receive_hc05_Data
//  * �� �� ˵ ����������������
//  * �� �� �� �Σ���
//  * �� �� �� �أ���
//  * ��       �ߣ�LC
//  * ��       ע����
// ******************************************************************/
void Receive_hc05_Data(void)
{
    if( BLERX_FLAG == 1 )//���յ���������
    {
        /*�������ݺ�Ĳ���*/
        /*����BLERX_BUFF������в���*/


        Clear_BLERX_BUFF();//������ջ���
    }
}

// /******************************************************************
//  * �� �� �� �ƣ�Send_hc05_Data
//  * �� �� ˵ ����������ģ�鷢������
//  * �� �� �� �Σ�dat=Ҫ���͵��ַ���
//  * �� �� �� �أ���
//  * ��       �ߣ�LC
//  * ��       ע��������ֻ��������������������ֻ��������ݣ�
// ******************************************************************/
void Send_hc05_Data(char *dat)
{
    //��ȡ����״̬
    Bluetooth_Mode();
    //����ֻ��Ѿ�����
    if( Bluetooth_ConnectFlag == 1 )
    {
        //��������
        hc05_send_String((unsigned char*)dat);
    }
}



//void hc05_IRQHandler(void)
//{
//    switch (DL_UART_Main_getPendingInterrupt(hc05_uart_INST)) 
//    {
//        case DL_UART_MAIN_IIDX_RX:
//            if (BLERX_LEN < BLERX_LEN_MAX - 1) // ����һ���ַ��Ŀռ�����'\0'
//            {
//                BLERX_BUFF[BLERX_LEN++] = DL_UART_Main_receiveData(hc05_uart_INST); // ��������
//            }
//            else
//            {
//                uint8_t temp = DL_UART_Main_receiveData(hc05_uart_INST); // ����������
//            }

//            BLERX_BUFF[BLERX_LEN] = '\0';  // ȷ���ַ�����ȷ����
//            BLERX_FLAG = 1;  // ���ý�����ɱ�־λ
//            

//            DL_UART_clearInterruptStatus(hc05_uart_INST, DL_UART_MAIN_IIDX_RX);
//            break;
//        default:
//            break;
//    }
//    
//}

