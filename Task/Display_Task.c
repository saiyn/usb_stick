#include "common_head.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Display_Task.h"
#include "OSAL_Console.h"
#include "System_Task.h"
#include "Lcd_driver.h"

#include "osal_timers.h"

#define LCD_LINE_LEN 16

//#define SYS_ARCH_TIMEOUT 0xffffffffUL

xQueueHandle gDisQueue;

menu_t *gMenuHead;

menu_t *cur_menu;

menu_t *last_menu;




static void dis_print(uint8 line, char *fmt, ...)
{
	 uint8 j;
	 char buf[LCD_LINE_LEN + 1] = {0};
   va_list ap;

   va_start(ap, fmt);
   vsprintf(buf, fmt, ap);
   va_end(ap);

   lcd_write_cmd(line);
   bsp_delay_us(47);
   for(j = 0; j < LCD_LINE_LEN; j++){
		 if(buf[j] == '<'){
			 lcd_write_data(0);
		 }else if(buf[j] == '>'){
			 lcd_write_data(6);
		 }else if(buf[j] == '@'){
			 lcd_write_data(4);
		 }else if(buf[j] == 0){
			 lcd_write_data(' ');
		 }else if(buf[j] == '^'){
			 lcd_write_data(7);
		 }else{
			 lcd_write_data(buf[j]);
		 }
		 
		 bsp_delay_us(47);
	 }
   
}

uint32_t display_task_msg_fetch(xQueueHandle xQueue, void * const pvBuffer, portTickType timeout)
{
	portTickType starttime;
	
	/* Get the starting time. */
  starttime = xTaskGetTickCount();
	
	/* See if there is a timeout. */
  if(timeout != 0) {
    /* Receive a message from the queue. */
    if(xQueueReceive(xQueue, pvBuffer, timeout / portTICK_RATE_MS) == pdPASS) {
      /* Return the amount of time it took for the message to be received. */
      return (xTaskGetTickCount() - starttime) * portTICK_RATE_MS;
    } else {
      /* No message arrived in the allotted time. */
      return SYS_ARCH_TIMEOUT;
    }
  } else {
    /* Try to receive a message until one arrives. */
    while(xQueueReceive(xQueue, pvBuffer, portMAX_DELAY) != pdPASS);

    /* Return the amount of time it took for the message to be received. */
    return (xTaskGetTickCount() - starttime) * portTICK_RATE_MS;
  }
	
}


void display_msg_handler(dis_msg_t *msg)
{
	switch(msg->id){
		
		default:
			break;
	}
	
}

void display_task(void *parameter)
{
	 dis_msg_t msg;
   uint32_t time_needed;
	 struct sys_timeo *tmptimeout;
	 sys_timeout_handler handler;
	 void *arg;
	
	 SYS_TRACE(DIS_TASK_DEBUG, ("display_task:display task running\r\n"));
	
	 osal_timeout_init();
	
	 gDisQueue = xQueueCreate(20, sizeof(dis_msg_t));
	 OSAL_ASSERT(gDisQueue != NULL);

	while(1){
	
	again:
		if(!gnext_timeout){
			time_needed = display_task_msg_fetch(gDisQueue, &msg, 0);
			
			display_msg_handler(&msg);
		}else{
			if(gnext_timeout->time > 0){
        time_needed = display_task_msg_fetch(gDisQueue, &msg, gnext_timeout->time);
			}else{
				time_needed = SYS_ARCH_TIMEOUT;
			}
			
			/* If time == SYS_ARCH_TIMEOUT, a timeout occured before a message
         could be fetched. We should now call the timeout handler and
         deallocate the memory allocated for the timeout. */
			if(time_needed == SYS_ARCH_TIMEOUT){
				tmptimeout = gnext_timeout;
				gnext_timeout = tmptimeout->next;
				handler = tmptimeout->h;
				arg = tmptimeout->arg;
				
				vPortFree(tmptimeout);
				
				if(handler != NULL){
					handler(arg);
				}
				
				goto again;
				
			}else{
				/* If time != SYS_ARCH_TIMEOUT, a message was received before the timeout
         occured. The time variable is set to the number of
         milliseconds we waited for the message. */
				
				if (time_needed < gnext_timeout->time) {
					gnext_timeout->time -= time_needed;
				} else {
					gnext_timeout->time = 0;
				}
				
				display_msg_handler(&msg);
			}
			
		}
		
	}
	
}

void dis_send_msg(dis_msg_type_t type, menu_id_t id)
{
	 dis_msg_t msg;

   msg.msg = type;
   msg.id = id;	
	 
	 xQueueSend(gDisQueue, &msg, portMAX_DELAY);
}

void dis_send_msg_isr(dis_msg_type_t type, menu_id_t id)
{
	 dis_msg_t msg;

   msg.msg = type;
	 msg.id = id;
	
	 xQueueSendToFrontFromISR(gDisQueue, &msg, NULL);
}













