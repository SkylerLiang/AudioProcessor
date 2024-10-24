#ifndef __TLV320AIC_H
#define __TLV320AIC_H

#include "main.h"

#define TLV320AIC_I2C_ADDR 0x18

typedef struct
{
	I2C_HandleTypeDef *i2cHandle;
	I2S_HandleTypeDef *i2sHandle;
	GPIO_TypeDef *nrstPort;
	uint16_t nrstPin;
} Codec_t;

void Codec_Hard_Reset(Codec_t *pCodec);
HAL_StatusTypeDef Codec_Write_Register(Codec_t *pCodec, uint8_t regAddr, uint8_t data);
HAL_StatusTypeDef Codec_Read_Register(Codec_t *pCodec, uint8_t regaddr, uint8_t *data);
HAL_StatusTypeDef Codec_Init(Codec_t *pCodec, I2C_HandleTypeDef *pI2C, I2S_HandleTypeDef *pI2S, GPIO_TypeDef *pGpioPort, uint16_t gpioPin);

#endif
