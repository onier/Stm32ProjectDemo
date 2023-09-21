//
// Created by ubuntu on 2023/9/21.
//

#ifndef STM32PROJECTDEMO_SERIALCONFIG_H
#define STM32PROJECTDEMO_SERIALCONFIG_H

#include "usart.h"

typedef int (*UartPortDataHandler)(const uint8_t *pData, uint16_t Size);

//UART DMA收发,初始化
void AddDMAUartHandler(UART_HandleTypeDef *huart, DMA_HandleTypeDef *dmaHandleTypeDef,
                       UartPortDataHandler uartPortDataHandler);

void AddUartSdio(UART_HandleTypeDef *uartHandleTypeDef);

#endif //STM32PROJECTDEMO_SERIALCONFIG_H
