#include "Drive_FSMC.h"
void Drive_FSMC_GPIO_Init(void) {
    /* 1 配置 A0-A18 地址端口的输出模式 复用推挽输出CNF:10 50MHz速度 MODE:11*/
    /* =============MODE=============== */
    GPIOF->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 |
                   GPIO_CRL_MODE3 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5);

    GPIOF->CRH |=
        (GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15);

    GPIOG->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 |
                   GPIO_CRL_MODE3 | GPIO_CRL_MODE4 | GPIO_CRL_MODE5);

    GPIOD->CRH |= (GPIO_CRH_MODE11 | GPIO_CRH_MODE12 | GPIO_CRH_MODE13);

    /* =============CNF=============== */
    GPIOF->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 |
                   GPIO_CRL_CNF3_1 | GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
    GPIOF->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0 | GPIO_CRL_CNF2_0 |
                    GPIO_CRL_CNF3_0 | GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0);

    GPIOF->CRH |= (GPIO_CRH_CNF12_1 | GPIO_CRH_CNF13_1 | GPIO_CRH_CNF14_1 |
                   GPIO_CRH_CNF15_1);
    GPIOF->CRH &= ~(GPIO_CRH_CNF12_0 | GPIO_CRH_CNF13_0 | GPIO_CRH_CNF14_0 |
                    GPIO_CRH_CNF15_0);

    GPIOG->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 |
                   GPIO_CRL_CNF3_1 | GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
    GPIOG->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0 | GPIO_CRL_CNF2_0 |
                    GPIO_CRL_CNF3_0 | GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0);

    GPIOD->CRH |= (GPIO_CRH_CNF11_1 | GPIO_CRH_CNF12_1 | GPIO_CRH_CNF13_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF11_0 | GPIO_CRH_CNF12_0 | GPIO_CRH_CNF13_0);

    /*
        2 数据端口 复用推挽输出
            在实际应用中，即使数据线被配置为输出模式，FSMC控制器仍然能够管理数据线的方向，使其在需要时成为输入线。
            这种自动切换是由FSMC控制器硬件管理的，不需要软件干预。
            因此，即使GPIO配置为复用推挽输出，FSMC依然可以实现读取操作。
    */
    /* =============MODE=============== */
    GPIOD->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);
    GPIOD->CRH |= (GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE14 | GPIO_CRH_MODE15);

    GPIOE->CRL |= (GPIO_CRL_MODE7);
    GPIOE->CRH |=
        (GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11 |
         GPIO_CRH_MODE12 | GPIO_CRH_MODE13 | GPIO_CRH_MODE14 | GPIO_CRH_MODE15);

    /* =============CNF=============== */
    GPIOD->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0);

    GPIOD->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF14_1 | GPIO_CRH_CNF15_1);
    GPIOD->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0 | GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF14_0 | GPIO_CRH_CNF15_0);

    GPIOE->CRL |= (GPIO_CRL_CNF7_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF7_0);

    GPIOE->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1 |
                   GPIO_CRH_CNF11_1 | GPIO_CRH_CNF12_1 | GPIO_CRH_CNF13_1 |
                   GPIO_CRH_CNF14_1 | GPIO_CRH_CNF15_1);
    GPIOE->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0 | GPIO_CRH_CNF10_0 |
                    GPIO_CRH_CNF11_0 | GPIO_CRH_CNF12_0 | GPIO_CRH_CNF13_0 |
                    GPIO_CRH_CNF14_0 | GPIO_CRH_CNF15_0);

    /* 3 其他控制端口  复用推挽输出 */
    GPIOD->CRL |= (GPIO_CRL_MODE4 | GPIO_CRL_MODE5);
    GPIOD->CRL |= (GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1);
    GPIOD->CRL &= ~(GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0);

    GPIOE->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);
    GPIOE->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
    GPIOE->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0);

    GPIOG->CRH |= (GPIO_CRH_MODE10);
    GPIOG->CRH |= (GPIO_CRH_CNF10_1);
    GPIOG->CRH &= ~(GPIO_CRH_CNF10_0);
}

void Drive_FSMC_Init() {
    RCC->APB2ENR |= (RCC_APB2ENR_IOPGEN | RCC_APB2ENR_IOPDEN |
                     RCC_APB2ENR_IOPEEN | RCC_APB2ENR_IOPFEN);
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;
    Drive_FSMC_GPIO_Init();
    /* 寄存器配置 */
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MBKEN; // 存储器块使能位
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MTYP; // 存储器类型

    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MWID_1; // 16位
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MWID_0;

    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MUXEN; // 地址和数据复用: 不复用

    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_WREN; // 写使能位

    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_FACCEN; // 禁止闪存访问
    /* 3. fsmc的 时序 */
    FSMC_Bank1->BTCR[5] &=
        ~FSMC_BTR3_ADDHLD; // 地址建立时间 对同步读写来说,永远一个周期
    FSMC_Bank1->BTCR[5] &=
        ~FSMC_BTR3_ADDSET; // 地址保持时间 对同步读写来说永远一个周期
    FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_DATAST;
    FSMC_Bank1->BTCR[5] |=
        (71 << 8); // 数据保持时间 手册不能低于55ns 我们设置1us
}