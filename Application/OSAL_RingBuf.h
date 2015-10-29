#ifndef _OSAL_RINGBUF_H_
#define _OSAL_RINGBUF_H_


#define RING_BUF_SIZE  512


typedef struct
{
	   uint8  buffer[RING_BUF_SIZE];
	   size_t bytes_in_buffer;
	   uint8  *pread;
	   uint8  *pwrite;
}ring_buffer_t;


typedef  enum{
	CONSOLE =0,
	IR_FRONT,
	IR_BACK_IN,
	DEVICE_NUM
}ringbuf_device_t;



void ring_buffer_init(void);

void ring_buffer_write(ringbuf_device_t index, uint8 ch);

size_t ring_buffer_len(ringbuf_device_t index);


uint8 ring_buffer_read(ringbuf_device_t index);


#endif

