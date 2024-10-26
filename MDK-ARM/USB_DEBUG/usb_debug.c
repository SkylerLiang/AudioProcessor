#include "usb_debug.h"
#include <stdarg.h>

char usbTxBuffer[256];
char usbRxBuffer[256];

/**
  * @retval 0 if all operations are OK
  */
uint8_t USB_Send_Command(const char *format, ...)
{
	va_list args;
    va_start(args, format);
	
	uint8_t status;
	
	memset(usbTxBuffer, 0, 256);
	vsprintf(usbTxBuffer, format, args);
	
	uint8_t strLen = strlen(usbTxBuffer);
	
	status = CDC_Transmit_FS((uint8_t *)usbTxBuffer, strLen);
	
	va_end(args);
	
	return status;
}
void USB_Decode(uint8_t *data, uint16_t len)
{
	memcpy(usbRxBuffer, data, len);
	
	// process...
}
