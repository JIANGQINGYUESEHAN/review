#include "Drive_FSMC.h"
void Drive_FSMC_GPIO_Init(void) {
    /* 1 ���� A0-A18 ��ַ�˿ڵ����ģʽ �����������CNF:10 50MHz�ٶ� MODE:11*/
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
        2 ���ݶ˿� �����������
            ��ʵ��Ӧ���У���ʹ�����߱�����Ϊ���ģʽ��FSMC��������Ȼ�ܹ����������ߵķ���ʹ������Ҫʱ��Ϊ�����ߡ�
            �����Զ��л�����FSMC������Ӳ������ģ�����Ҫ�����Ԥ��
            ��ˣ���ʹGPIO����Ϊ�������������FSMC��Ȼ����ʵ�ֶ�ȡ������
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

    /* 3 �������ƶ˿�  ����������� */
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
    /* �Ĵ������� */
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MBKEN; // �洢����ʹ��λ
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MTYP; // �洢������

    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MWID_1; // 16λ
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MWID_0;

    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MUXEN; // ��ַ�����ݸ���: ������

    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_WREN; // дʹ��λ

    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_FACCEN; // ��ֹ�������
    /* 3. fsmc�� ʱ�� */
    FSMC_Bank1->BTCR[5] &=
        ~FSMC_BTR3_ADDHLD; // ��ַ����ʱ�� ��ͬ����д��˵,��Զһ������
    FSMC_Bank1->BTCR[5] &=
        ~FSMC_BTR3_ADDSET; // ��ַ����ʱ�� ��ͬ����д��˵��Զһ������
    FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_DATAST;
    FSMC_Bank1->BTCR[5] |=
        (71 << 8); // ���ݱ���ʱ�� �ֲ᲻�ܵ���55ns ��������1us
}