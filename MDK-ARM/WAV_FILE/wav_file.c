#include "wav_file.h"
#include <stdio.h>
#include <string.h>

Wav_File_t wavFile;
Wav_Head_t wavHead;

void Wav_Head_Init(void)
{
	wavHead.riff = 0x46464952;
	wavHead.wholeSize = 0;
	wavHead.wave = 0x45564157;
	
	wavHead.fmt = 0x20746d66;
	wavHead.fmtSize = 0x10;
	wavHead.encodeType = 0x01;
	wavHead.channelsNum = 0x02;
	wavHead.sampleRate = 16000;
	wavHead.bytesPerSecond = 64000;
	wavHead.bytesPerSample = 0x04;
	wavHead.bitsPerSample = 0x10;
	
	wavHead.data = 0x61746164;
	wavHead.dataSize = 0;
}

FRESULT File_Init(void)
{
	FRESULT res;
	Wav_Head_Init();
	res = f_mount(&SDFatFS, "0:", 1);
	return res;
}

FRESULT File_Format(void)
{
	FRESULT res;
	BYTE workBuffer[4096 * 2];
	res = f_mkfs("0:", FM_EXFAT, 0, workBuffer, 4096 * 2);
	return res;
}

FRESULT File_Wav_Create(Wav_File_t *wav, uint16_t index)
{
	FRESULT res;
	wav->index = index;
	wav->dataSize = 0;
	sprintf(wav->fileName, "%04d.wav", index);
	res = f_open(&wav->file, wav->fileName, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
	return res;
}

FRESULT File_Wav_Write_Data_And_Sync(Wav_File_t *wav, void *data, uint16_t len)
{
	FRESULT res;
	UINT bytesWritten;
	res = f_write(&wav->file, data, len, &bytesWritten);
	
	if (res != FR_OK)
	{
		return res;
	}
	
	wav->dataSize += bytesWritten;
	
	res = f_sync(&wav->file);
	return res;
}

FRESULT File_Wav_Write_Head_And_Close(Wav_File_t *wav)
{
	FRESULT res;
	UINT bytesWritten;
	wavHead.wholeSize = wav->dataSize + 36;
	wavHead.dataSize = wav->dataSize;
	
	res = f_lseek(&wav->file, 0);	// move pointer to the top
	if (res != FR_OK)
	{
		return res;
	}
	
	res = f_write(&wav->file, &wavHead, sizeof(wavHead), &bytesWritten);	// write head to file
	if (res != FR_OK)
	{
		return res;
	}
	
	res = f_close(&wav->file);
	return res;
}

