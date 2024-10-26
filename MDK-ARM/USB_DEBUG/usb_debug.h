#ifndef __USB_DEBUG_H
#define __USB_DEBUG_H

#include "main.h"
#include "usbd_cdc_if.h"

#define USB_BUFFER_SIZE 256

uint8_t USB_Send_Command(const char *format, ...);
void USB_Decode(uint8_t *data, uint16_t len);

#endif
