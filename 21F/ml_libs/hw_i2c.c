#include "hw_i2c.h"

// 私有函数声明
static void I2C_GPIO_Config(void);
static void I2C_Mode_Config(void);
static uint8_t I2C_WaitEvent(uint32_t event);
static uint8_t I2C_Start(void);
static void I2C_Stop(void);

void HW_I2C_Init(void) {
    I2C_GPIO_Config();
    I2C_Mode_Config();
}

static void I2C_GPIO_Config(void) {
    // 使用ml_gpio.h中的函数初始化GPIO
    gpio_init(HW_I2C_PORT, HW_I2C_SCL_PIN, AF_OD);  // 复用开漏
    gpio_init(HW_I2C_PORT, HW_I2C_SDA_PIN, AF_OD);  // 复用开漏
    
    // 开启I2C和GPIO时钟
    RCC->APB1ENR |= RCC_APB1Periph_I2C2;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

static void I2C_Mode_Config(void) {
    HW_I2C->CR1 &= ~I2C_CR1_PE;  // 禁用I2C
    
    // 配置I2C时序
    HW_I2C->CR2 = (SystemCoreClock / 1000000);  // 输入时钟(MHz)
    HW_I2C->CCR = (SystemCoreClock / (2 * HW_I2C_SPEED));  // 标准模式
    HW_I2C->TRISE = ((SystemCoreClock / 1000000) + 1);      // 最大上升时间
    
    // 使能ACK
    HW_I2C->CR1 |= I2C_CR1_ACK;
    // 使能I2C
    HW_I2C->CR1 |= I2C_CR1_PE;
}

static uint8_t I2C_WaitEvent(uint32_t event) {
    uint32_t timeout = I2C_TIMEOUT;
    while (!(HW_I2C->SR1 & event)) {
        if (--timeout == 0) return 0;
    }
    return 1;
}

static uint8_t I2C_Start(void) {
    HW_I2C->CR1 |= I2C_CR1_START;
    return I2C_WaitEvent(I2C_SR1_SB);
}

static void I2C_Stop(void) {
    HW_I2C->CR1 |= I2C_CR1_STOP;
    while (HW_I2C->CR1 & I2C_CR1_STOP);
}

uint8_t HW_I2C_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    if (!I2C_Start()) return 0;
    
    HW_I2C->DR = devAddr << 1;  // 写模式
    if (!I2C_WaitEvent(I2C_SR1_ADDR)) return 0;
    (void)HW_I2C->SR2;  // 清除ADDR标志
    
    HW_I2C->DR = regAddr;
    if (!I2C_WaitEvent(I2C_SR1_TXE)) return 0;
    
    HW_I2C->DR = data;
    if (!I2C_WaitEvent(I2C_SR1_TXE)) return 0;
    
    I2C_Stop();
    return 1;
}

uint8_t HW_I2C_ReadByte(uint8_t devAddr, uint8_t regAddr) {
    if (!I2C_Start()) return 0;
    
    // 先写寄存器地址
    HW_I2C->DR = devAddr << 1;  // 写模式
    if (!I2C_WaitEvent(I2C_SR1_ADDR)) return 0;
    (void)HW_I2C->SR2;
    
    HW_I2C->DR = regAddr;
    if (!I2C_WaitEvent(I2C_SR1_TXE)) return 0;
    
    // 重新启动读操作
    if (!I2C_Start()) return 0;
    
    HW_I2C->DR = (devAddr << 1) | 0x01;  // 读模式
    if (!I2C_WaitEvent(I2C_SR1_ADDR)) return 0;
    (void)HW_I2C->SR2;
    
    // 禁用ACK并准备停止
    HW_I2C->CR1 &= ~I2C_CR1_ACK;
    I2C_Stop();
    
    if (!I2C_WaitEvent(I2C_SR1_RXNE)) return 0;
    return HW_I2C->DR;
}

uint8_t HW_I2C_WriteBuffer(uint8_t devAddr, uint8_t regAddr, uint8_t *pBuffer, uint16_t len) {
    if (!I2C_Start()) return 0;
    
    HW_I2C->DR = devAddr << 1;
    if (!I2C_WaitEvent(I2C_SR1_ADDR)) return 0;
    (void)HW_I2C->SR2;
    
    HW_I2C->DR = regAddr;
    if (!I2C_WaitEvent(I2C_SR1_TXE)) return 0;
    
    while (len--) {
        HW_I2C->DR = *pBuffer++;
        if (!I2C_WaitEvent(I2C_SR1_TXE)) return 0;
    }
    
    I2C_Stop();
    return 1;
}

uint8_t HW_I2C_ReadBuffer(uint8_t devAddr, uint8_t regAddr, uint8_t *pBuffer, uint16_t len) {
    if (!I2C_Start()) return 0;
    
    // 先写寄存器地址
    HW_I2C->DR = devAddr << 1;
    if (!I2C_WaitEvent(I2C_SR1_ADDR)) return 0;
    (void)HW_I2C->SR2;
    
    HW_I2C->DR = regAddr;
    if (!I2C_WaitEvent(I2C_SR1_TXE)) return 0;
    
    // 重新启动读操作
    if (!I2C_Start()) return 0;
    
    HW_I2C->DR = (devAddr << 1) | 0x01;
    if (!I2C_WaitEvent(I2C_SR1_ADDR)) return 0;
    (void)HW_I2C->SR2;
    
    if (len > 1) {
        HW_I2C->CR1 |= I2C_CR1_ACK;
    } else {
        HW_I2C->CR1 &= ~I2C_CR1_ACK;
    }
    
    while (len--) {
        if (len == 1) HW_I2C->CR1 &= ~I2C_CR1_ACK;
        if (len == 0) I2C_Stop();
        
        if (!I2C_WaitEvent(I2C_SR1_RXNE)) return 0;
        *pBuffer++ = HW_I2C->DR;
    }
    
    return 1;
}
