#include "Drive_ADC.h"
void Drive_ADC1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // 时钟分频
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    /* 1.2 gpio的时钟 */
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /* 2. gpio工作模式: PC0 模拟输入  CNF=00 MODE=00 */
    GPIOC->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    /* ADC配置 */
    ADC1->CR1 &= ~ADC_CR1_SCAN;  // 关闭扫描模式
    ADC1->CR2 &= ~ADC_CR2_ALIGN; // 右对齐
    ADC1->CR2 |= ADC_CR2_CONT;   // 开启连续转换
    ADC1->SQR1 &= ~ADC_SQR1_L;   // 转换数量

    ADC1->CR2 |=
        ADC_CR2_EXTSEL; // 规则通道组转换的外部事件,SWSTART软件启动：111

    // 转换通道
    /* 采样时间 */
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_0);
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_1;

    ADC1->SQR3 &= ~ADC_SQR3_SQ1; // 置0
    ADC1->SQR3 |= (10 << 0);

    ADC1->CR2 |= ADC_CR2_EXTTRIG; /* 开启规则组的外部转换 */
}
void Drive_ADC1_StartConvert(void) {
    // 先置0
    ADC1->CR2 |= ADC_CR2_ADON;
    // 在进行开启校准
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL)
        ; // 校准完成

    /* 4. 使用软件开始转换规则通道 */;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* 5. 等待首次转换完成 */
    while ((ADC1->SR & ADC_SR_EOC) == 0)
        ;
}
double Drive_ADC1_ReadV(void) { return ADC1->DR * 3.3 / 4095; }