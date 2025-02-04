
#include "Delay.h"
#include "Drive_ADC.h"
#include "Drive_ADC_DMA.h"
#include "Drive_BaseTick.h"
#include "Drive_DMA.h"
#include "Drive_DMATOUATR.h"
#include "Drive_GeneralTick.h"
#include "Drive_GeneralTickTest.h"
#include "Drive_KEY.h"
#include "Drive_MesureTick.h"
#include "Drive_SenierTick.h"
#include "Drive_USART.h"
#include "Drive_USART_Interrupt.h"
#include "Inf_E2PROM.h"
#include "led.h"
// int main() {
//     Driver_LED_Init();
//     uint8_t dir = 1;
//     int8_t i = -1;
//     uint32_t leds[] = {LED_1, LED_2, LED_3};
//     while (1) {
//         // 姝ｆ柟鍚?
//         if (dir == 1) {
//             Driver_LED_On(leds[i]); // 寮�鐏?
//             Delay_ms(500);
//             Driver_LED_Off(leds[i]); // 鍏抽棴褰撳墠鐨勭伅
//             i++;
//             if (i >= 2) {
//                 dir = 0;
//             }
//         } else {
//             Driver_LED_On(leds[i]); // 寮�鐏?
//             Delay_ms(500);
//             Driver_LED_Off(leds[i]);
//             i--; // 鍏抽棴褰撳墠鐨勭伅
//             if (i <= 0) {
//                 dir = 1;
//             }
//         }
//     }
// }

// int main() {
//     Drive_Key_Init();
//     while (1) {
//         /* code */
//     }
// }
// int main() {
//     Drive_USART_Interrupt_Init();
//     while (1) {
//         // uint8_t str[] = "hello,world";
//         // Drive_USART_Sendstr(str, strlen((char *)str));
//         // Delay_ms(500);
//         // uint8_t ch = Driver_USART1_ReceiveChar();
//         // Drive_USART_Sendchar(ch);
//         // Delay_ms(500);
//     }
// }

// int main() {
//     Drive_USART_Interrupt_Init();
//     Inf_W24C02_Init();
//     Inf_W24C02_WriteByte(0x01, 'a');
//     uint8_t data = Inf_W24C02_ReadByte(0x01);
//     printf("deBug1\r\n");
//     printf("%c\r\n", data);
//     printf("deBug2\r\n");
//     Inf_W24C02_WriteBytes(0x00, "123456", 6);
//     uint8_t buff[100] = {0};
//     Inf_W24C02_ReadBytes(0x00, buff, 6);
//     printf("%s\r\n", buff);
//     // 将buffer置空
//     memset(buff, 0, sizeof(buff));
//     Inf_W24C02_WriteBytes(0x00, "0123456789abcdefghijk", 21);
//     Inf_W24C02_ReadBytes(0x00, buff, 21);
//     printf("%s\r\n", buff);
//     while (1) {
//     }
// }

// int main() {
//     Driver_LED_Init();
//     Drive_USART_Interrupt_Init();
//     printf("开始测验");
//     Drive_BaseTick_Init();
//     while (1) {
//         /* code */
//     }
// }

// int main() {
//     Drive_USART_Interrupt_Init();
//     Driver_LED_Init();
//     printf("开始测验");
//     Drive_GeneralTick_Init();
//     Drive_GeneralTick_Start();
//     uint8_t dutyCycle = 0;
//     uint8_t dir = 0; // 变大
//     Drive_GeneralTick_AdjustDutyCycle(dutyCycle);
//     while (1) {
//         if (dir == 0) {
//             dutyCycle += 1;
//             if (dutyCycle >= 99) {
//                 dir = 1;
//             }
//         } else {
//             dutyCycle -= 1;
//             if (dutyCycle <= 1) {
//                 dir = 0;
//             }
//         }
//         Drive_GeneralTick_AdjustDutyCycle(dutyCycle);
//         Delay_ms(10);
//     }
// }

// double ta, f;
// int main() {
//     Drive_USART_Interrupt_Init();
//     Drive_GeneralTick_Init();
//     Drive_GeneralTickTestTest_Init();

//     Drive_GeneralTickTestTest_Start();
//     Drive_GeneralTick_Start();

//     while (1) {
//         ta = Driver_GeneralTickTestTest_GetPWMCycle();
//         f = Driver_GeneralTickTestTest_GetPWMFreq();

//         printf("t=%.4fms, f=%.4fHz\r\n", ta, f);

//         Delay_ms(1000);
//     }
// }
// double ta, f, dutyCycle;

// int main() {
//     Drive_USART_Interrupt_Init();
//     Drive_GeneralTick_Init();
//     Drive_GeneralTick_Start();
//     Drive_MesureTick_Init();
//     Drive_MesureTick_Start();
//     while (1) {
//         ta = Drive_MesureTick_GetDutyCycle();
//         f = Drive_MesureTick_GetPWMFreq();
//         dutyCycle = Drive_MesureTick_GetDutyCycle();
//         printf("t=%.4fms, f=%.4fHz,dutyCycle=%.2f%\r\n", ta, f,
//                dutyCycle * 100);
//         Delay_ms(1000);
//     }
// }

// int main() {
//     Drive_USART_Interrupt_Init();
//     printf("高级定时器实验开始...\r\n");
//     Drive_SenierTick_Init();
//     Drive_SenierTick_Start();
//     while (1) {
//     }
// }
// const uint8_t src[] = {10, 20, 30, 40};
// uint8_t des[4] = {0};
// extern uint8_t isTransmitFinished;
// int main() {
//     Drive_USART_Interrupt_Init();
//     Drive_DMA_Init();
//     printf("DMA实验: ROM->RAM...\r\n");
//     printf("src=%p, des=%p\r\n", src, des);
//     Drive_DMA_TransmitData((uint32_t)&src[0], (uint32_t)&des[0], 8);
//     while (isTransmitFinished == 0)
//         ;
//     printf("%d, %d, %d, %d\r\n", des[0], des[1], des[2], des[3]);
//     while (1) {
//     }
// }

// uint8_t src[] = {'a', 'b', 'c', 'd'};

// int main() {
//     Drive_USART_Interrupt_Init();
//     printf("DMA实验: RAM->USART...\r\n");

//     Drive_DMATOUART_Init();
//     Delay_ms(1000);
//     Drive_DMATOUART_TransmitData((uint32_t)&src[0],
//     (uint32_t)(&(USART1->DR)),
//                                  4);
//     while (1) {
//     }
// }

// int main() {
//     Drive_USART_Interrupt_Init();
//     printf("DMA实验: RAM->USART...\r\n");
//     Drive_ADC1_Init();
//     Drive_ADC1_StartConvert();
//     while (1) {
//         double v = Drive_ADC1_ReadV();
//         printf("v = %.2f\r\n", v);
//         Delay_s(1);
//     }
// }

uint16_t data[2] = {0};
int main() {
    Drive_USART_Interrupt_Init();
    printf("DMA实验: RAM->USART...\r\n");
    Driver_ADC1_DMA_Init();
    Driver_ADC1_DMA_Start((uint32_t)data, 2);
    while (1) {
        printf("滑动变阻器=%.2f, 电源电压=%.2f\r\n", data[0] * 3.3 / 4095,
               data[1] * 3.3 / 4095);

        Delay_s(1);
    }
}