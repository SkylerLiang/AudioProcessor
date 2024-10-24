#include "TLV320AIC.h"

void Codec_Hard_Reset(Codec_t *pCodec)
{
	HAL_GPIO_WritePin(pCodec->nrstPort, pCodec->nrstPin, GPIO_PIN_RESET);
	HAL_Delay(50);
	
	HAL_GPIO_WritePin(pCodec->nrstPort, pCodec->nrstPin, GPIO_PIN_RESET);
	HAL_Delay(50);
}

HAL_StatusTypeDef Codec_Write_Register(Codec_t *pCodec, uint8_t regAddr, uint8_t data)
{
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(pCodec->i2cHandle, TLV320AIC_I2C_ADDR << 1, regAddr, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xFF);
	return status;
}

HAL_StatusTypeDef Codec_Read_Register(Codec_t *pCodec, uint8_t regaddr, uint8_t *data)
{
	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(pCodec->i2cHandle, TLV320AIC_I2C_ADDR << 1, regaddr, I2C_MEMADD_SIZE_8BIT, data, 1, 0xFF);
	return status;
}

HAL_StatusTypeDef Codec_Init(Codec_t *pCodec, I2C_HandleTypeDef *pI2C, I2S_HandleTypeDef *pI2S, GPIO_TypeDef *pGpioPort, uint16_t gpioPin)
{
	HAL_StatusTypeDef status;
	
	pCodec->i2cHandle = pI2C;
	pCodec->i2sHandle = pI2S;
	pCodec->nrstPort = pGpioPort;
	pCodec->nrstPin = gpioPin;
	
	Codec_Hard_Reset(pCodec);
	
	// Software reset
	status = Codec_Write_Register(pCodec, 0x01, 0x01);
	HAL_Delay(50);
	
	/* MCLK = 48 MHz, fsref = 48 kHz */
	/* P = 4, R = 1, J = 8, D = 1920 */
	/* K = J.D */
	/* fsref = (MCLK * K * R) / (2048 * P) */
	status = Codec_Write_Register(pCodec, 0x03, 0x84); // Enable PLL, Q = 16 (doesn't matter), P = 4
	
	status = Codec_Write_Register(pCodec, 0x04, 0x08); // 
	
	return status;
}
