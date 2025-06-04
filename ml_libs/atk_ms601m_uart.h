#ifndef __ATK_MS601M_UART_H
#define __ATK_MS601M_UART_H

#include "stm32f10x.h"

// UART3引脚定义（PB10-TX, PB11-RX）
#define ATK_MS601M_UARTx           USART3
#define ATK_MS601M_UART_IRQn       USART3_IRQn
#define ATK_MS601M_UART_CLK        RCC_APB1Periph_USART3
#define ATK_MS601M_GPIO_CLK        RCC_APB2Periph_GPIOB
#define ATK_MS601M_GPIO_PORT       GPIOB
#define ATK_MS601M_TX_PIN          GPIO_Pin_10
#define ATK_MS601M_RX_PIN          GPIO_Pin_11

// FIFO缓冲区大小
#define ATK_MS601M_UART_RX_FIFO_BUF_SIZE 128

void atk_ms601m_uart_init(uint32_t baudrate);
void atk_ms601m_uart_send(uint8_t *dat, uint16_t len);
uint16_t atk_ms601m_uart_rx_fifo_read(uint8_t *dat, uint16_t len);
void atk_ms601m_rx_fifo_flush(void);

#endif
