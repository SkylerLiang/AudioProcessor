#include "mic.h"
#include "audio_process.h"

Mic_Pair_t mics[2];

void Mic_Init(Mic_Pair_t *pMics, I2S_HandleTypeDef *i2s, uint32_t sampleRate, uint8_t sampleDepth)
{
	pMics->i2sHandle = i2s;
	pMics->sampleRate = sampleRate;
	pMics->sampleDepth = sampleDepth;
	pMics->isDataValid = 0;
	pMics->validDataPointer = &pMics->rawRecvBuffer[0];
}

HAL_StatusTypeDef Mic_Sample_Start(Mic_Pair_t *pMics)
{
	HAL_StatusTypeDef status;
	
	uint16_t i2sRecvLen;
	if (sizeof(raw_data_type_t) == 2)
	{
		i2sRecvLen = (uint16_t)RAW_RECV_BUFFER_LEN / 2;
	}
	else if (sizeof(raw_data_type_t) == 4)
	{
		i2sRecvLen = (uint16_t)RAW_RECV_BUFFER_LEN;
	}
	
	__HAL_I2S_ENABLE(pMics->i2sHandle);
	status = HAL_I2S_Receive_DMA(pMics->i2sHandle, (uint16_t *)pMics->rawRecvBuffer, i2sRecvLen);
	
	return status;
}

void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	if (hi2s->Instance == hi2s1.Instance)
	{
		mics[0].validDataPointer = &mics[0].rawRecvBuffer[0];
		mics[0].isDataValid = 1;
	}
}


void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	if (hi2s->Instance == hi2s1.Instance)
	{
		mics[0].validDataPointer = &mics[0].rawRecvBuffer[RAW_RECV_BUFFER_LEN / 2];
		mics[0].isDataValid = 1;
	}
}
