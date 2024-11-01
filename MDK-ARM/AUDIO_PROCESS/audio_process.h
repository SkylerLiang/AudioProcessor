#ifndef __AUDIO_PROCESS_H
#define __AUDIO_PROCESS_H

#include "main.h"
#include "arm_math.h"
#include "mic.h"
#include <math.h>

#define M_PI 3.1415926535f

extern int16_t audio_buffer[2][512];
extern int16_t audio_buffer_mixed[1024];

void Audio_Get_From_Mic(Mic_Pair_t *pMics, int16_t *bufferL, int16_t *bufferR, int16_t *bufferM);
float Audio_Calc_Distance(int16_t *audioL, int16_t *audioR);

#endif
