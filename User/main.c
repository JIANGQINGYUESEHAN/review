
#include "Delay.h"
#include "Drive_KEY.h"
#include "Drive_USART.h"
#include "Drive_USART_Interrupt.h"
#include "Inf_E2PROM.h"
#include "led.h"

#include "stm32f10x.h"
// int main() {
//     Driver_LED_Init();
//     uint8_t dir = 1;
//     int8_t i = -1;
//     uint32_t leds[] = {LED_1, LED_2, LED_3};
//     while (1) {
//         // 正方�?
//         if (dir == 1) {
//             Driver_LED_On(leds[i]); // 开�?
//             Delay_ms(500);
//             Driver_LED_Off(leds[i]); // 关闭当前的灯
//             i++;
//             if (i >= 2) {
//                 dir = 0;
//             }
//         } else {
//             Driver_LED_On(leds[i]); // 开�?
//             Delay_ms(500);
//             Driver_LED_Off(leds[i]);
//             i--; // 关闭当前的灯
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

int main() {

    Drive_USART_Interrupt_Init();
    Inf_W24C02_Init();

    Inf_W24C02_WriteByte(0x01, 'a');
    uint8_t data = Inf_W24C02_ReadByte(0x01);
    printf("deBug1\r\n");
    printf("%c\r\n", data);
    printf("deBug2\r\n");

    Inf_W24C02_WriteBytes(0x00, "123456", 6);

    uint8_t buff[100] = {0};
    Inf_W24C02_ReadBytes(0x00, buff, 6);
    printf("%s\r\n", buff);
    // ��buffer�ÿ�
    memset(buff, 0, sizeof(buff));
    Inf_W24C02_WriteBytes(0x00, "0123456789abcdefghijk", 21);
    Inf_W24C02_ReadBytes(0x00, buff, 21);
    printf("%s\r\n", buff);
    while (1) {
    }
}
