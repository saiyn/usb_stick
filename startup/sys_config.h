#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_


#define CONFIG_USE_CONSOLE
#define CONFIG_USE_CONSOLE

#define SYS_NV_ADDRESS  0x00
#define SYS_LOW_POWER_FLAG_ADDRESS 0x200
#define SYS_NV_ADDRESS_MDC  0x400

#define CONFIG_SYS_MAXARGS  16

#define EPPROM_IIC_ADDRESS 0xA0


#define SYS_DEBUG_ON 0x80U
#define SYS_DEBUG_OFF 0x00U

#define SYS_PLATFORM_DIAG(msg)  s_printf msg

#if 1
#define SYS_TRACE(debug, message) do{ \
	if((debug) & SYS_DEBUG_ON){ \
		SYS_PLATFORM_DIAG(message); \
	} \
}while(0)
#else
#define SYS_TRACE(debug, message)
#endif


#if 1
#define OSAL_ASSERT(x) \
if(!(x)){\
	SYS_TRACE(SYS_DEBUG_ON, ("(%s) has assert failed at %s.\n", #x, __FUNCTION__));\
  while(1);\
}
#else

#define OSAL_ASSERT(...)

#endif


#define NV_SYS_DEBUG    SYS_DEBUG_ON

#define TIMERS_DEBUG   SYS_DEBUG_ON

#define DIS_TASK_DEBUG   SYS_DEBUG_ON

#define CONSOLE_SYS_DEBUG  SYS_DEBUG_ON

#define LCD_DRIVER_DEBUG   SYS_DEBUG_ON

#define SYS_MEM_DEBUG      SYS_DEBUG_ON

#define IIC_DRIVER_DEBUG    SYS_DEBUG_ON


#endif


