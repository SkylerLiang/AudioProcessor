#include "audio_process.h"

int16_t audio_buffer[2][1024];
int16_t audio_buffer_mixed[2048];

void Audio_Get_From_Mic(Mic_Pair_t *pMics, int16_t *bufferL, int16_t *bufferR, int16_t *bufferM)
{
	uint16_t L, R;
	for(uint16_t i = 0; i < 1024; i++)
	{
		int16_t sin = (int16_t)(20000 * arm_sin_f32(i * 6.28 / 64));
		if (sin > 15000)
			sin = 15000;
		else if(sin < -15000)
			sin = -15000;
		bufferM[i * 2] = sin;
		bufferM[i * 2 + 1] = sin;
//		uint32_t temp[2];
//		temp[0] = pMics->rawRecvBuffer[i * 2];
//		temp[1] = pMics->rawRecvBuffer[i * 2 + 1];
//		L = temp[0] >> 8;
//		R = temp[1] >> 8;
//		
//		memcpy(&bufferL[i], &L, 2);
//		memcpy(&bufferR[i], &R, 2);
//		memcpy(&bufferM[2 * i], &L, 4);
//		bufferL[i] = L;
//		bufferR[i] = R;
//		bufferM[i * 2] = L;
//		bufferM[i * 2 + 1] = R;
	}
}
