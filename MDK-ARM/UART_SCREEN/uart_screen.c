#include "uart_screen.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

char screenTxBuffer[256];
char screenRxBuffer[256];

HAL_StatusTypeDef Screen_Init(void)
{
	HAL_StatusTypeDef status;
	
	status = HAL_UARTEx_ReceiveToIdle_IT(&SCREEN_UART, (uint8_t *)screenRxBuffer, 255);
	
	return status;
}

HAL_StatusTypeDef Screen_Send_Command(const char *format, ...)
{
	va_list args;
    va_start(args, format);
	
	HAL_StatusTypeDef status;
	
	memset(screenTxBuffer, 0, 256);
	vsprintf(screenTxBuffer, format, args);
	
	uint8_t strLen = strlen(screenTxBuffer);
	
	screenTxBuffer[strLen] = 0xFF;
	screenTxBuffer[strLen + 1] = 0xFF;
	screenTxBuffer[strLen + 2] = 0xFF;
	
	status = HAL_UART_Transmit_IT(&SCREEN_UART, (uint8_t *)screenTxBuffer, strLen + 3);
	
	va_end(args);
	
	return status;
}

void Screen_Decode(char *data, uint16_t len)
{
	UNUSED(data);
	UNUSED(len);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == SCREEN_UART.Instance)
	{
		Screen_Decode(screenRxBuffer, Size);
		HAL_UARTEx_ReceiveToIdle_IT(&SCREEN_UART, (uint8_t *)screenRxBuffer, 255);
	}
}
