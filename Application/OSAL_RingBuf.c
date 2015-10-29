#include "common_head.h"
#include "OSAL_RingBuf.h"


extern ring_buffer_t console;

ring_buffer_t *ring_list[] ={
	&console,
};

#define RING_BUF_COUNT (sizeof(ring_list)/sizeof(ring_list[0]))

void ring_buffer_init(void)
{
	 uint8 index;
	
	 for(index = 0; index < RING_BUF_COUNT; index++)
	{
		   ring_list[index]->pread = ring_list[index]->buffer;
		   ring_list[index]->pwrite = ring_list[index]->buffer;
		   memset(ring_list[index]->buffer, 0, sizeof(ring_list[index]->buffer));
	}

}

void ring_buffer_write(ringbuf_device_t index, uint8 ch)
{
	  ring_buffer_t *p;
	
	  OSAL_ASSERT(index < DEVICE_NUM);
	
	  p = ring_list[index];
	
	  if(p->bytes_in_buffer == RING_BUF_SIZE) return;
	
	  *p->pwrite++ = ch;
	
	  if(p->pwrite - p->buffer >= RING_BUF_SIZE)
		{
			  p->pwrite = p->buffer;    
		}
		
		p->bytes_in_buffer++;
}


uint8 ring_buffer_read(ringbuf_device_t index)
{  
	  uint8 byte = 0;
	  ring_buffer_t *p;
	
	  OSAL_ASSERT(index < DEVICE_NUM);
	
	  p = ring_list[index];
	
	  byte = * p->pread++;
	
	  if( p->pread -  p->buffer >= RING_BUF_SIZE)
		{
			     p->pread =  p->buffer;
		}
		
		p->bytes_in_buffer--;
		
		return byte;
}

bool Is_ring_buffer_empty(ringbuf_device_t index)
{
	  ring_buffer_t *p;
	
	  OSAL_ASSERT(index < DEVICE_NUM);
	
	  p = ring_list[index];
	
	 if( p->bytes_in_buffer > 0) return false;
	 else return true;
}

size_t ring_buffer_len(ringbuf_device_t index)
{
	  ring_buffer_t *p;
	  OSAL_ASSERT(index < DEVICE_NUM);
	
	  p = ring_list[index];
	
	  return  (p->bytes_in_buffer);
}









