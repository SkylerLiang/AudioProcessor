#ifndef __MIC_H
#define __MIC_H

#include "main.h"
#include "i2s.h"

#define RAW_RECV_BUFFER_LEN 2048
#define SAMPLE_DEPTH 24
typedef uint32_t raw_data_type_t;

typedef struct
{
	I2S_HandleTypeDef *i2sHandle;
	raw_data_type_t rawRecvBuffer[RAW_RECV_BUFFER_LEN];
	raw_data_type_t *validDataPointer;
	uint8_t isDataValid;
	uint32_t sampleRate;
	uint8_t sampleDepth;
} Mic_Pair_t;

extern Mic_Pair_t mics[2];

void Mic_Init(Mic_Pair_t *pMics, I2S_HandleTypeDef *i2s, uint32_t sampleRate, uint8_t sampleDepth);
HAL_StatusTypeDef Mic_Sample_Start(Mic_Pair_t *pMics);

#endif
