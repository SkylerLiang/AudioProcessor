#ifndef __AUDIO_PROCESS_H
#define __AUDIO_PROCESS_H

#include "main.h"
#include "arm_math.h"
#include "mic.h"

extern int16_t audio_buffer[2][1024];
extern int16_t audio_buffer_mixed[2048];

void Audio_Get_From_Mic(Mic_Pair_t *pMics, int16_t *bufferL, int16_t *bufferR, int16_t *bufferM);

#endif
