#include "common_head.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


#define GPIO_PORTD_CR_R     (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_LOCK_R   (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTF_CR_R     (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_LOCK_R   (*((volatile unsigned long *)0x40025520))

void bsp_gpio_init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOR);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOS);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOT);
	
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTD_LOCK_R = 0x4C4F434B;

	GPIO_PORTF_CR_R = 0x1;
	GPIO_PORTD_CR_R = (1<<7);
	
	/*eeprom releated gpio init*/
  GPIOPinTypeGPIOOutput(EPROM_SDA_PORT, EPROM_SDA_PIN);
	GPIOPinTypeGPIOOutput(EPROM_SCL_PORT, EPROM_SCL_PIN);
	
	
	 /*init lcd related gpio*/
	GPIOPinTypeGPIOOutput(LCD_RS_PORT, LCD_RS_PIN);
	GPIOPinTypeGPIOOutput(LCD_RW_PORT, LCD_RW_PIN);
	GPIOPinTypeGPIOOutput(LCD_EN_PORT, LCD_EN_PIN);
	GPIOPinTypeGPIOOutput(LCD_DB4_PORT, LCD_DB4_PIN);
	GPIOPinTypeGPIOOutput(LCD_DB5_PORT, LCD_DB5_PIN);
	GPIOPinTypeGPIOOutput(LCD_DB6_PORT, LCD_DB6_PIN);
  GPIOPinTypeGPIOOutput(LCD_DB7_PORT, LCD_DB7_PIN);
	GPIOPinTypeGPIOOutput(LCD_PWM_PORT, LCD_PWM_PIN);
	
	GPIO_PIN_SET(LCD_PWM_PORT, LCD_PWM_PIN, 1);
	
  	/*power management gpio*/
	GPIOPinTypeGPIOOutput(AC_STANDBY_PORT, AC_STANDBY_PIN);
	GPIOPinTypeGPIOOutput(DC5V_EN_PORT, DC5V_EN_PIN);
	GPIOPinTypeGPIOOutput(DC3V_EN_PORT, DC3V_EN_PIN);
	GPIOPinTypeGPIOOutput(PS_EN_PORT, PS_EN_PIN);
	//GPIO_PIN_SET(DC3V_EN_PORT, DC3V_EN_PIN, 1);
	GPIOPinTypeGPIOOutput(POWER_EN01_PORT, POWER_EN01_PIN);
	GPIOPinTypeGPIOInput(AC_DETECT_PORT, AC_DETECT_PIN);
	
}


void s_printf(char *fmt, ...)
{
	    va_list ap;
	    char buf[512] = {0};
      size_t len;
      size_t index = 0;

      va_start(ap, fmt);
	    vsprintf(buf, fmt, ap);
      va_end(ap);

      len = strlen(buf);
      while(index < len){
				while(UARTCharPutNonBlocking(UART0_BASE, buf[index]) == false);
				index++;
			}
}



void bsp_delay_us(uint32 time)
{
	SysCtlDelay(40 * time);
}


void bsp_delay_ms(uint32 time)
{
	 for(;time;time--)
		 bsp_delay_us(1000);
}


uint8 GPIO_ReadSinglePin(uint32 ulPort, uint8 ucPins)
{
	if ((HWREG(ulPort + (GPIO_O_DATA + (ucPins << 2)))) != 0)
		return 1;
	else
		return 0;
}

