#ifndef __WAV_FILE_H
#define __WAV_FILE_H

#include "main.h"
#include "fatfs.h"
#include "sdmmc.h"

typedef struct
{
	FIL file;
	char fileName[32];
	uint16_t index;
	uint32_t dataSize;
} Wav_File_t;

typedef struct __attribute__((packed))
{
	uint32_t riff;				// "RIFF"
	uint32_t wholeSize;			// starts from the next data
	uint32_t wave;				// "WAVE"
	
	uint32_t fmt;				// "fmt "
	uint32_t fmtSize;			// 16 ends with bitsPerSample
	uint16_t encodeType; 		// 1 PCM
	uint16_t channelsNum;		// 2
	uint32_t sampleRate;		// 48,000
	uint32_t bytesPerSecond;	// 192,000	channelsNum * sampleRate * bitsPerSample / 8
	uint16_t bytesPerSample;	// 4		channelsNum * bitsPerSample / 8
	uint16_t bitsPerSample;		// 16
	
	uint32_t data;				// "data"
	uint32_t dataSize;			// 
} Wav_Head_t;

extern Wav_File_t wavFile;

FRESULT File_Init(void);
FRESULT File_Format(void);
FRESULT File_Wav_Create(Wav_File_t *wav, uint16_t index);
FRESULT File_Wav_Write_Data_And_Sync(Wav_File_t *wav, void *data, uint16_t len);
FRESULT File_Wav_Write_Head_And_Close(Wav_File_t *wav);

#endif
