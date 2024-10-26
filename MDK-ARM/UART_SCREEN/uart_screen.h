#ifndef __UART_SCREEN_H
#define __UART_SCREEN_H

#include "main.h"
#include "usart.h"

#define SCREEN_UART huart1

HAL_StatusTypeDef Screen_Init(void);
HAL_StatusTypeDef Screen_Send_Command(const char *format, ...);

#endif
