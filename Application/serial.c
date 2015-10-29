#include "common_head.h"
#include <string.h>
#include "OSAL_Console.h"
#include "OSAL_RingBuf.h"
#include "serial.h"


ring_buffer_t console;


void bsp_uart_init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART0_BASE, gSysClock, 115200,(UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));

	//	Enable RX interrupt
	UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);

	// 	Enable UART0
	UARTEnable(UART0_BASE); 
}

void uart0_interrupt_handler(void)
{
	 uint32_t status;
	 int ch;
	
	 status = UARTIntStatus(UART0_BASE, true);
	 UARTIntClear(UART0_BASE, status);
	
	 if ((status & UART_INT_RX) || (status & UART_INT_RT)){
		   while(UARTCharsAvail(UART0_BASE)){
				 ch = UARTCharGetNonBlocking(UART0_BASE);
				 if(ch > 0){
					 ring_buffer_write(CONSOLE,(uint8)ch);
				 }
			 }
	 }
}


static void c_printf(uint8 ch)
{
	   while(UARTCharPutNonBlocking(UART0_BASE, ch) == false);
}


void serial_poll_handler(void)
{
	   size_t len;
	   uint8 ch;
	   static char buf[128] = {0};
     static  uint8 index = 0;
	
	   len = ring_buffer_len(CONSOLE);

	   if(len > 0){
			 while(len--){
				    ch = ring_buffer_read(CONSOLE);
				    if(ch == '\b'){
							  s_printf("\b \b");
							  if(index > 0){
							    buf[--index] = 0;
								}
							  continue;
						}
						if(ch == '\r' || ch == '\n'){
							if(index == 0){
								  s_printf("\r\nSaiyn->");
								  continue;
							}
							else{
							  buf[index] = 0;
							  osal_run_command(buf);
							  memset(buf, 0, sizeof(buf));
							  index = 0;
								continue;
							}
						}
						if(index > 127) index = 0;
						buf[index++] = ch;
						c_printf(ch);
			 }
		 }		
}


























