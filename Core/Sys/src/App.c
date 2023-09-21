//
// Created by ubuntu on 2023/9/21.
//

#include <stdio.h>
#include "App.h"
#include "main.h"
#include "SerialConfig.h"
#include "FreeRTOS.h"
#include "task.h"

extern void startTestTask();

void EnableUart2Sdio() {
    AddUartSdio(&huart2);
    printf("uart2 has enable sdio \n");
}

void StartApp() {
    EnableUart2Sdio();
    startTestTask();
}