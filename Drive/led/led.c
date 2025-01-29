#include "led.h"
void Driver_LED_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    /* mode:01  */
    GPIOA->CRL |= (GPIO_CRL_MODE0_0 | GPIO_CRL_MODE1_0);
    GPIOA->CRL &= ~(GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_1);
    GPIOA->CRH |= GPIO_CRH_MODE8_0;
    GPIOA->CRH &= ~GPIO_CRH_MODE8_1;
    /* cnf:00 */
    GPIOA->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0 | GPIO_CRL_CNF0_1 |
                    GPIO_CRL_CNF1_1);
    GPIOA->CRH &= ~(GPIO_CRH_CNF8_1 | GPIO_CRH_CNF8_0);
    uint32_t leds[] = {LED_1, LED_2, LED_3};
    Driver_LED_OffAll(leds, 3);
}

void Driver_LED_On(uint32_t led) { GPIOA->ODR &= ~led; }

void Driver_LED_Off(uint32_t led) { GPIOA->ODR |= led; }

void Driver_LED_Toggle(uint32_t led) {
    if ((GPIOA->ODR & led) == 0) {
        Driver_LED_Off(led);
    } else {
        Driver_LED_On(led);
    }
}

void Driver_LED_OnAll(uint32_t leds[], uint8_t size) {
    for (uint32_t i = 0; i < size; i++) {
        GPIOA->ODR &= ~leds[i];
    }
}

void Driver_LED_OffAll(uint32_t leds[], uint8_t size) {
    for (uint32_t i = 0; i < size; i++) {
        GPIOA->ODR |= leds[i];
    }
}