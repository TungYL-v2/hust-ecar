#ifndef __ATM_MS901M_H
#define __ATM_MS901M_H

#include "sys.h"
#include "atk_ms601m_uart.h"

// 修改UART发送函数调用
void atk_ms601m_uart_send(uint8_t *dat, uint8_t len)
{
    USART_SendData(ATK_MS601M_UARTx, *dat);
    while(USART_GetFlagStatus(ATK_MS601M_UARTx, USART_FLAG_TXE) == RESET);
}

// 修改初始化部分
uint8_t atk_ms601m_init(uint32_t baudrate)
{
    // 初始化UART
    atk_ms601m_uart_init(baudrate);
    
    // ... 其余初始化代码不变 ...
}
