//
// Created by ubuntu on 2023/9/21.
//

#include <malloc.h>
#include "SerialConfig.h"
#include "main.h"
#include "uthash/utlist.h"

#define RX_BUFFER_SIZE 128
typedef struct UartHandler {
    UART_HandleTypeDef *_huart;
    DMA_HandleTypeDef *_DMAHandleTypeDef;
    UartPortDataHandler _uartPortDataHandler;
    struct UartHandler *next, *prev;
    uint8_t *_rxBuffer;
} UartHandler;

typedef struct UartSdioHandler {
    UART_HandleTypeDef *_huart;
    struct UartSdioHandler *next, *prev;
} UartSdioHandler;

UartHandler *uartHandlerHeader;
UartSdioHandler *uartSdioHandler;

////DMA_HandleTypeDef hdma_usart2_rx;
//DMA_HandleTypeDef hdma_usart2_tx;


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    UartHandler *elt;
    DL_FOREACH(uartHandlerHeader, elt) {
        if (huart == elt->_huart) {
//            HAL_UART_Transmit_DMA(&huart2, UART1_rxBuffer, Size);
            elt->_uartPortDataHandler(elt->_rxBuffer, Size);
            HAL_UARTEx_ReceiveToIdle_DMA(elt->_huart, elt->_rxBuffer, RX_BUFFER_SIZE);
            __HAL_DMA_DISABLE_IT(elt->_DMAHandleTypeDef, DMA_IT_HT);
        }
    }
}

void EnableUartDMA(UART_HandleTypeDef *huart, uint8_t *_rxBuffer, DMA_HandleTypeDef *dmaHandleTypeDef) {
    HAL_UARTEx_ReceiveToIdle_DMA(huart, _rxBuffer, RX_BUFFER_SIZE);
    __HAL_DMA_DISABLE_IT(dmaHandleTypeDef, DMA_IT_HT);
}

void AddDMAUartHandler(UART_HandleTypeDef *huart, DMA_HandleTypeDef *dmaHandleTypeDef,
                       UartPortDataHandler uartPortDataHandler) {
    UartHandler *uartHandler = malloc(sizeof(UartHandler));
    uartHandler->_huart = huart;
    uartHandler->_DMAHandleTypeDef = dmaHandleTypeDef;
    uartHandler->_uartPortDataHandler = uartPortDataHandler;
    uartHandler->_rxBuffer = malloc(RX_BUFFER_SIZE * sizeof(uint8_t));
    DL_APPEND(uartHandlerHeader, uartHandler);
    EnableUartDMA(huart, uartHandler->_rxBuffer, dmaHandleTypeDef);
}

int _write(int file, char *ptr, int len) {
    UartSdioHandler *elt;
    DL_FOREACH(uartSdioHandler, elt) {
        HAL_UART_Transmit_DMA(elt->_huart, (uint8_t *) ptr, len);
        return len;
    }
}

void AddUartSdio(UART_HandleTypeDef *uartHandleTypeDef) {
    UartSdioHandler *uartSdioHandler1 = malloc(sizeof(UartSdioHandler));
    uartSdioHandler1->_huart = uartHandleTypeDef;
    DL_APPEND(uartSdioHandler, uartSdioHandler1);
}