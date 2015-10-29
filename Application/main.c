#include "common_head.h"
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Console_Task.h"
#include "serial.h"
#include "System_Task.h"
#include "Display_Task.h"

const char *version = "v0.0.1";


static void hal_init(void);
static void print_version(const char *version);

uint32 gSysClock;

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
	  
}

void vApplicationMallocFailedHook(void)
{
	   
}


int main(void)
{
	hal_init();
	print_version(version);
  xTaskCreate(console_task,(const signed char *)"Console", (configMINIMAL_STACK_SIZE*2), NULL, 2, NULL);
	xTaskCreate(system_task,(const signed char *)"System", (configMINIMAL_STACK_SIZE*2), NULL, 9, NULL);
	xTaskCreate(display_task,(const signed char *)"display", (configMINIMAL_STACK_SIZE*2), NULL, 8, NULL);
	// Start the scheduler
	vTaskStartScheduler();
	return 0;
}

static void hal_init(void)
{
	 gSysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN |SYSCTL_USE_PLL |SYSCTL_CFG_VCO_480), 120000000); 
	 bsp_gpio_init();
	 bsp_uart_init();
	
}


static void print_version(const char *version)
{
	s_printf("\r\n***************************************************\r\n");
	s_printf("*      NAD C358\r\n");
	s_printf("*      version:%s\r\n",version);
	s_printf("*      Created: %s %s \r\n", __DATE__, __TIME__);
	s_printf("***************************************************\r\n");
}


