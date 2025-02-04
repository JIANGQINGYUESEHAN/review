#include "Drive_ADC_DMA.h"

void Driver_ADC1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    /* 1.2 gpio的时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* 2. gpio工作模式: PC0 PC2 模拟输入  CNF=00 MODE=00 */
    GPIOC->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    GPIOC->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);

    ADC1->CR1 &= ~ADC_CR1_SCAN;  // 关闭扫描模式
    ADC1->CR2 &= ~ADC_CR2_CONT;  // 连续转换
    ADC1->CR2 &= ~ADC_CR2_ALIGN; // 数据右对齐
    ADC1->CR2 |= ADC_CR2_DMA;    // 使用DMA模式

    ADC1->SQR1 &= ~ADC_SQR1_L_3;
    ADC1->SQR1 &= ~ADC_SQR1_L_2;
    ADC1->SQR1 &= ~ADC_SQR1_L_1;
    ADC1->SQR1 |= ADC_SQR1_L_0; // 两个转换

    ADC1->SMPR1 &= ~ADC_SMPR1_SMP10_0; // 通道10的转换
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_1;
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP10_2;

    ADC1->SMPR1 &= ~ADC_SMPR1_SMP12_0; // 通道12的转换
    ADC1->SMPR1 |= ADC_SMPR1_SMP12_1;
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP12_2;
    ADC1->SQR3 &= ~ADC_SQR3_SQ1;
    ADC1->SQR3 &= ~ADC_SQR3_SQ2;

    ADC1->SQR3 |= (10 << 0);
    ADC1->SQR3 |= (12 << 5);
    ADC1->CR2 |= ADC_CR2_EXTSEL;
    ADC1->CR2 &= ~ADC_CR2_EXTTRIG; /* 禁用规则组的外部转换 */
}

void Driver_ADC1_DMA_Init(void) {
    /* 1. 开启DMA时钟 */
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    /* 2. 设置传输方向 从外设读0 从内存读1*/
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;
    /* 3. 数据宽度 16位=01 */
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_PSIZE_0;

    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_MSIZE_0;

    /* 4. 外设和内存的地址是否增 外设不增  内存要增*/
    DMA1_Channel1->CCR &= ~DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;

    /* 5. 开启循环模式 */
    DMA1_Channel1->CCR |= DMA_CCR1_CIRC;

    /* 6. 给ADC1开启DMA模式 */;
    ADC1->CR2 |= ADC_CR2_DMA;
}

void Driver_ADC1_DMA_Start(uint32_t desAddr, uint8_t len) {
    /* 0. DMA 配置 */
    DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
    DMA1_Channel1->CMAR = desAddr;
    DMA1_Channel1->CNDTR = len;
    DMA1_Channel1->CCR |= DMA_CCR1_EN; /* 使能通道 */

    /* 1. 上电: 把ADC从休眠模式唤醒 */
    ADC1->CR2 |= ADC_CR2_ADON;

    /* 2. 执行校准 */
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL)
        ;

    /* 3. ADON = 1, 开始转换 0>1 从休眠模式唤醒 1->1 开始 */
    ADC1->CR2 |= ADC_CR2_ADON;

    /* 4. 使用软件开始转换规则通道 */;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* 5. 等待首次转换完成 */
    while ((ADC1->SR & ADC_SR_EOC) == 0)
        ;
}