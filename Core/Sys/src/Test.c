//
// Created by ubuntu on 2023/9/21.
//
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "usart.h"

void TestSend() {
    while (1) {
        vTaskDelay(1000);
        HAL_UART_Transmit(&huart2, "1234\r\n", 6, 1000);
//        HAL_UART_Transmit_IT(&huart2, (uint8_t *)"Hello, USART!\r\n", 15);

    }
}

void startTestTask() {
    xTaskCreate(TestSend, "TestSend", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}