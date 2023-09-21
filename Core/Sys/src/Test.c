//
// Created by ubuntu on 2023/9/21.
//
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"

GPIO_InitTypeDef GPIO_InitStruct;

void TestSend() {
    while (1) {
        vTaskDelay(1000);
//        HAL_UART_Transmit_IT(&huart2, (uint8_t *)"Hello, USART!\r\n", 15);
    }
}

//PC4 PC5直接对联
void initGPIO() {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
//
//    GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0
//                          | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6
//                          | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
//                          | GPIO_PIN_11 | GPIO_PIN_12;
//    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

void testGPIOFunction() {
    initGPIO();
    while (1) {
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET); // 设置引脚为高电平
            vTaskDelay(1000);
            GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);
            printf("GPIO_PIN_4:%d GPIO_PIN_5:%d \r\n", GPIO_PIN_SET, state);
        }
        vTaskDelay(1000);
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET); // 设置引脚为高电平
            vTaskDelay(1000);
            GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);
            printf("GPIO_PIN_4:%d GPIO_PIN_5:%d \r\n", GPIO_PIN_RESET, state);
        }
    }
}

void startTestTask() {
    xTaskCreate(testGPIOFunction, "testGPIOFunction", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(TestSend, "TestSend", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}