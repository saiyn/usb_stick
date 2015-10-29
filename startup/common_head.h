#ifndef _COMMON_HEAD_H_
#define _COMMON_HEAD_H_

#include "stdlib.h"
#include "stdbool.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

typedef   unsigned int     uint32;
typedef   unsigned short   uint16;
typedef   unsigned char    uint8;

typedef   unsigned int     UINT32;
typedef   unsigned short   UINT16;
typedef   unsigned char    UINT8;

typedef   unsigned int     uint32_t;
typedef   int              int32_t;
typedef   unsigned short   uint16_t;
typedef   unsigned char    uint8_t;

typedef   unsigned int     size_t;

enum
{
	   OFF = 0,
	   ON
};

#ifndef NULL
#define NULL    ((void*)0)    
#endif

#include "sysctl.h"
#include "pin_map.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "ssi.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "hw_ssi.h"
#include "interrupt.h"
#include "tm4c1290nczad.h"



#include "sys_database.h"
#include "bsp.h"
#include "sys_config.h"



extern uint32 gSysClock;

extern void s_printf(char *fmt, ...);

#endif





