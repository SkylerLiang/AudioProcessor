#include "mic.h"

Mic_Pair_t mics[2];

void Mic_Init(Mic_Pair_t *pMics, I2S_HandleTypeDef *i2s, uint32_t sampleRate, uint8_t sampleDepth)
{
	pMics->i2sHandle = i2s;
	pMics->sampleRate = sampleRate;
	pMics->sampleDepth = sampleDepth;
//	SCB_InvalidateDCache_by_Addr((uint32_t *)pMics->rawRecvBuffer, sizeof(raw_data_type_t) * RAW_RECV_BUFFER_LEN);
}

HAL_StatusTypeDef Mic_Sample_Start(Mic_Pair_t *pMics)
{
	HAL_StatusTypeDef status;
	
	uint16_t i2sRecvLen;
	if (sizeof(raw_data_type_t) == 2)
	{
		i2sRecvLen = (uint16_t)RAW_RECV_BUFFER_LEN;
	}
	else if (sizeof(raw_data_type_t) == 4)
	{
		i2sRecvLen = (uint16_t)(RAW_RECV_BUFFER_LEN * 2);
	}
	
	__HAL_I2S_ENABLE(pMics->i2sHandle);
	status = HAL_I2S_Receive_DMA(pMics->i2sHandle, (uint16_t *)pMics->rawRecvBuffer, RAW_RECV_BUFFER_LEN);
	
	return status;
}

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	UNUSED(hi2s);
}


void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
//	HAL_I2S_Receive_DMA(hi2s, (uint16_t *)mics[0].rawRecvBuffer, RAW_RECV_BUFFER_LEN * 2);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
	UNUSED(hi2s);
}
