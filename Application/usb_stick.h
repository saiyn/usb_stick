#ifndef _USB_STICK_H_
#define _USB_STICK_H_


typedef enum{
	USB_HOST_READY = 0,
	USB_STICK_READY,
	USB_INTERFACE_CONFIG,
}umsg_type;


typedef struct{
	umsg_type msg;
}usb_msg_t;


void usb_stick_task(void *para);



void usb_send_msg(umsg_type type);

uint32_t
SimpleFsReadMediaSector(uint32_t ui32Sector, uint8_t *pui8Buf);













#endif




