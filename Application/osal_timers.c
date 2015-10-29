#include "common_head.h"
#include "osal_timers.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "System_Task.h"


struct sys_timeo *gnext_timeout;

void osal_timeout_init(void)
{
	sys_timeout(100, sys_poll_handler, NULL);
}


void sys_timeout(uint32_t msecs, sys_timeout_handler handler, void *arg)
{
	struct sys_timeo *timeout, *t;

  timeout = (struct sys_timeo *)pvPortMalloc(sizeof(struct sys_timeo));
  if (timeout == NULL) {
    SYS_TRACE(SYS_MEM_DEBUG, ("sys_timeout:No memory for sys_timeout\r\n"));
    return;
  }
  timeout->next = NULL;
  timeout->h = handler;
  timeout->arg = arg;
  timeout->time = msecs;


  if (gnext_timeout == NULL) {
    gnext_timeout = timeout;
    return;
  }

  if (gnext_timeout->time > msecs) {
    gnext_timeout->time -= msecs;
    timeout->next = gnext_timeout;
    gnext_timeout = timeout;
  } else {  
    for(t = gnext_timeout; t != NULL; t = t->next) {
      timeout->time -= t->time;
      if (t->next == NULL || t->next->time > timeout->time) {
        if (t->next != NULL) {
          t->next->time -= timeout->time;
        }
        timeout->next = t->next;
        t->next = timeout;
        break;
      }
    }
  }
	
	
}



void sys_untimeout(sys_timeout_handler handler, void *arg)
{
  struct sys_timeo *prev_t, *t;

  if (gnext_timeout == NULL) {
    return;
  }

  for (t = gnext_timeout, prev_t = NULL; t != NULL; prev_t = t, t = t->next) {
    if ((t->h == handler) && (t->arg == arg)) {
      /* We have a match */
      /* Unlink from previous in list */
      if (prev_t == NULL) {
        gnext_timeout = t->next;
      } else {
        prev_t->next = t->next;
      }
      /* If not the last one, add time of this one back to next */
      if (t->next != NULL) {
        t->next->time += t->time;
      }
      vPortFree(t);
      return;
    }
  }
  return;
}





















