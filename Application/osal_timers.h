#ifndef _OSAL_TIMERS_H_
#define _OSAL_TIMERS_H_

#define SYS_ARCH_TIMEOUT 0xffffffffUL

typedef void (* sys_timeout_handler)(void *arg);


struct sys_timeo {
  struct sys_timeo *next;
  uint32_t time;
  sys_timeout_handler h;
  void *arg;
};

extern struct sys_timeo *gnext_timeout;

void osal_timeout_init(void);

void sys_untimeout(sys_timeout_handler handler, void *arg);

void osal_timeout_init(void);

void sys_timeout(uint32_t msecs, sys_timeout_handler handler, void *arg);

#endif


