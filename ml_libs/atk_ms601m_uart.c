#include "atk_ms601m_uart.h"
#include "misc.h"

static struct {
    uint8_t buf[ATK_MS601M_UART_RX_FIFO_BUF_SIZE];
    uint16_t size;
    uint16_t reader;
    uint16_t writer;
} g_uart_rx_fifo;

void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(ATK_MS601M_UARTx, USART_IT_RXNE) != RESET)
    {
        uint8_t data = USART_ReceiveData(ATK_MS601M_UARTx);
        
        // 写入FIFO
        g_uart_rx_fifo.buf[g_uart_rx_fifo.writer] = data;
        g_uart_rx_fifo.writer = (g_uart_rx_fifo.writer + 1) % g_uart_rx_fifo.size;
        
        USART_ClearITPendingBit(ATK_MS601M_UARTx, USART_IT_RXNE);
    }
    
    if(USART_GetITStatus(ATK_MS601M_UARTx, USART_IT_ORE) != RESET)
    {
        USART_ClearITPendingBit(ATK_MS601M_UARTx, USART_IT_ORE);
        (void)USART_ReceiveData(ATK_MS601M_UARTx); // 读取DR清除错误
    }
}

void atk_ms601m_uart_init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 使能时钟
    RCC_APB2PeriphClockCmd(ATK_MS601M_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(ATK_MS601M_UART_CLK, ENABLE);
    
    // 配置TX引脚
    GPIO_InitStructure.GPIO_Pin = ATK_MS601M_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ATK_MS601M_GPIO_PORT, &GPIO_InitStructure);
    
    // 配置RX引脚
    GPIO_InitStructure.GPIO_Pin = ATK_MS601M_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(ATK_MS601M_GPIO_PORT, &GPIO_InitStructure);
    
    // 配置USART
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(ATK_MS601M_UARTx, &USART_InitStructure);
    
    // 配置中断
    NVIC_InitStructure.NVIC_IRQChannel = ATK_MS601M_UART_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    // 使能接收中断
    USART_ITConfig(ATK_MS601M_UARTx, USART_IT_RXNE, ENABLE);
    
    // 初始化FIFO
    g_uart_rx_fifo.size = ATK_MS601M_UART_RX_FIFO_BUF_SIZE;
    g_uart_rx_fifo.reader = 0;
    g_uart_rx_fifo.writer = 0;
    
    // 使能USART
    USART_Cmd(ATK_MS601M_UARTx, ENABLE);
}

void atk_ms601m_uart_send(uint8_t *dat, uint16_t len)
{
    while(len--)
    {
        USART_SendData(ATK_MS601M_UARTx, *dat++);
        while(USART_GetFlagStatus(ATK_MS601M_UARTx, USART_FLAG_TXE) == RESET);
    }
}

uint16_t atk_ms601m_uart_rx_fifo_read(uint8_t *dat, uint16_t len)
{
    uint16_t fifo_usage;
    uint16_t i;
    
    if(g_uart_rx_fifo.writer >= g_uart_rx_fifo.reader)
    {
        fifo_usage = g_uart_rx_fifo.writer - g_uart_rx_fifo.reader;
    }
    else
    {
        fifo_usage = g_uart_rx_fifo.size - g_uart_rx_fifo.reader + g_uart_rx_fifo.writer;
    }
    
    if(len > fifo_usage)
    {
        len = fifo_usage;
    }
    
    for(i=0; i<len; i++)
    {
        dat[i] = g_uart_rx_fifo.buf[g_uart_rx_fifo.reader];
        g_uart_rx_fifo.reader = (g_uart_rx_fifo.reader + 1) % g_uart_rx_fifo.size;
    }
    
    return len;
}

void atk_ms601m_rx_fifo_flush(void)
{
    g_uart_rx_fifo.writer = g_uart_rx_fifo.reader;
}
