#include "common_head.h"
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "OSAL_Console.h"
#include "serial.h"
#include "System_Task.h"
#include "EPRom_driver.h"
#include "OSAL_Utility.h"
#include "OSAL_RingBuf.h"
#include "lcd_driver.h"
#include "Display_Task.h"
#include "osal_timers.h"


xQueueHandle gSysQueue;

sys_state_t *gSystem_t;



const static char * const protect_name[]={
	"AUDIO",
	"TRIGGER",
	"OVER_TEMP",
	"OVER_VOLTAGE_AND_SHORT_CIRCIUT",
	"OVER_CLIP",
	"DC_ERROR",
	"OVER_CURRENT",
	"15V"
};

static void sys_database_save(sys_state_t *sys, uint8 type);
static int sys_audio_config_load(void);
static void sys_bled_flash(void *arg);
static void power_on_timeout(void *arg);




static void sys_msg_handler(sys_msg_t *msg)
{
  OSAL_ASSERT(msg != NULL);
	
	switch(msg->msg){
		
		
		default:
			break;
		
	}
}

static void sys_nv_set_default(sys_state_t *sys, uint8 type)
{
  if(0 == type){
		sys->src = SRC_COAX1;
		sys->src_num = SRC_CONSTANT_NUM;
	}else if(1 == type){
		
		
	}
 
	 sys_database_save(sys, type);

}





static void sys_runtime_parameter_init(sys_state_t *sys)
{
	 sys->src_num = SRC_CONSTANT_NUM;
}



void sys_database_init(void)
{
	int retval;
	uint32 crc = 0;
	uint8 *p = pvPortMalloc(sizeof(sys_state_t));
	OSAL_ASSERT(p != NULL);
	memset(p, 0, sizeof(sys_state_t));
	
  SYS_TRACE(NV_SYS_DEBUG, ("sys_database_init:will load %d bytes sys nv data from epprom\r\n", SIZEOF_SYS_NV));
	
	vPortEnterCritical();
	retval = eeprom_read(SYS_NV_ADDRESS, p, SIZEOF_SYS_NV);
	vPortExitCritical();
	OSAL_ASSERT(retval > 0);
	
	crc = calc_crc32(crc, p, SIZEOF_SYS_NV - 8);
	
	gSystem_t = (sys_state_t *)p;
	
	if(crc != gSystem_t->sys_crc32){
		SYS_TRACE(NV_SYS_DEBUG, ("sys_database_init:will set sys nv to default crc=%x, sys_crc=%x\r\n", crc, gSystem_t->sys_crc32));
		sys_nv_set_default(gSystem_t, 0);
	}else{
		SYS_TRACE(NV_SYS_DEBUG, ("sys_database_init:sys nv data load succuess, crc=%x\r\n", crc));
	}
	

	/*init sys runtime parameter*/
	sys_runtime_parameter_init(gSystem_t);
	
	//sys_audio_sense_thres_set(gSystem_t->sense_thres);

  //memcpy(&gSystem_last, gSystem_t, sizeof(sys_state_t));
}

static void sys_database_save(sys_state_t *sys, uint8 type)
{
	 uint32 crc = 0;
	 int retval;
	
	 if(type == 1){

	 }

	 crc = 0;
	 
	 crc = calc_crc32(crc, sys, SIZEOF_SYS_NV - 8);
	
   SYS_TRACE(NV_SYS_DEBUG, ("sys_database_save:will save sys crc=%x\r\n", crc));	
	  
	 sys->sys_crc32 = crc;
	
	 vPortEnterCritical();
	 retval = eeprom_write(SYS_NV_ADDRESS, (uint8 *)sys, SIZEOF_SYS_NV);
	 vPortExitCritical();
	 OSAL_ASSERT(retval > 0);
}


void sys_poll_handler(void *arg)
{
	
	
	sys_timeout(100, sys_poll_handler, NULL);
}


void system_task(void *parameter)
{
	sys_msg_t msg;
	gSysQueue = xQueueCreate(20, sizeof(sys_msg_t));
	
	OSAL_ASSERT(gSysQueue != NULL);
	
	sys_database_init();
	
	
	while(1){
		static uint8 is_first = 1;
		
		if(is_first){
	   	vTaskDelay(1000/portTICK_RATE_MS);
			is_first = 0;
		}else{
			vTaskDelay(5/portTICK_RATE_MS);
		}
		
		if(xQueueReceive(gSysQueue, &msg, 0)){
			sys_msg_handler(&msg);
		}
		
	}

}


void sys_send_msg_isr(sys_msg_type_t type, uint8 data)
{
	 sys_msg_t msg;

   msg.msg = type;
	 msg.data = data;
	
	 xQueueSendToFrontFromISR(gSysQueue, &msg, NULL);
}

void sys_send_msg(sys_msg_type_t type, uint8 data)
{
	 sys_msg_t msg;

   msg.msg = type;
	 msg.data = data;  
	
	 xQueueSend(gSysQueue, &msg, portMAX_DELAY);
}




static void sys_hw_power_on(void)
{
	AC_STANDBY(1);
	POWER_EN01(1);
	PS_EN(1);
	DC5V_EN(1);
	DC3V_EN(1);
	
	bsp_delay_ms(500);
}


static void sys_power_on_handler(sys_state_t *sys)
{
	sys_hw_power_on();
	
	lcd_init();
	
}

void timeout_test(void *arg)
{
	SYS_TRACE(TIMERS_DEBUG, ("timeout_test\r\n"));
	
	sys_timeout(500, timeout_test, NULL);
}


int power_on(struct cmd_tbl_s *cmdtp, int argc, char * const argv[])
{
	  
	sys_power_on_handler(gSystem_t);
	return 0;
}

OSAL_CMD(po, 1, power_on, "power on");



extern void display_init_menu(void);

int lcd_test(struct cmd_tbl_s *cmdtp, int argc, char * const argv[])
{
		
  display_init_menu();
	
	//SYS_TRACE("\r\n");
		
	return 0;
}

OSAL_CMD(lcd, 1, lcd_test, "lcd init test");


int timer_test(struct cmd_tbl_s *cmdtp, int argc, char * const argv[])
{
		
  sys_timeout(500, timeout_test, NULL);
	
//	SYS_TRACE("\r\nbegin timer_test\r\n");
		
	return 0;
}

OSAL_CMD(timer, 1, timer_test, "lcd init test");


int dis_task_msg(struct cmd_tbl_s *cmdtp, int argc, char * const argv[])
{
		
  dis_send_msg(0,0);
	
	return 0;
}

OSAL_CMD(dism, 1, dis_task_msg, "lcd init test");

struct ListNode{
	int val;
	struct ListNode *next;
};

typedef struct ListNode List_t;

static List_t *head = NULL;

static void sort_list_add(List_t **head, List_t *node)
{
	List_t *p = *head;
	
	if(p){
		while(p->next){
			p = p->next;
		}
		
		p->next = node;
		
	}else{
		*head = node;
	}
	
}

static void dump_list(List_t *head, const char *s)
{
	SYS_TRACE(SYS_DEBUG_ON,("%s:", s));
	while(head){
		SYS_TRACE(SYS_DEBUG_ON, ("%d->", head->val));
		head = head->next;
	}
	SYS_TRACE(SYS_DEBUG_ON, ("NULL\r\n"));
}

static List_t *merge_list(List_t *left, List_t *right)
{
	List_t head;
	List_t *p = &head;
	
	while(left && right){
		if(left->val <= right->val){
			p->next = left;
			left = left->next;
		}else{
			p->next = right;
			right = right->next;
		}
		
		p = p->next;
	}
	
	while(left){
		p->next = left;
		left = left->next;
		p = p->next;
	}
	
	while(right){
		p->next = right;
		right = right->next;
		p = p->next;
	}
	
	dump_list(head.next, "head.next");
	
	return head.next;
}

static List_t *do_list_sort(List_t *head)
{
	List_t *p1, *p2, *left = NULL, *right = NULL;
	
	dump_list(head, "head");
	
	if(head == NULL || head->next == NULL){
		return head;
	}
	
	p1 = head;
	p2 = head->next;
	
	while(p2 && p2->next){
		p1 = p1->next;
		p2 = p2->next->next;
	}
	
	p2 = p1->next;
	p1->next = NULL;
	
	SYS_TRACE(SYS_DEBUG_ON, ("do_list_sort left\r\n"));
	left = do_list_sort(head);
	dump_list(left, "left");
	SYS_TRACE(SYS_DEBUG_ON, ("do_list_sort right\r\n"));
	dump_list(p2, "p2");
	right = do_list_sort(p2);
	dump_list(right, "right");
	
	return merge_list(left, right);
}

int sort_list(struct cmd_tbl_s *cmdtp, int argc, char * const argv[])
{
	int temp[10] = {12,21,1,4,34,23,44,11,0,4};
	uint8 j;
  List_t *sorted = NULL;
  
  for(j = 0; j < 10; j++){
		List_t *p = (List_t *)pvPortMalloc(sizeof(List_t));
		if(p){
			p->val = temp[j];
			p->next = NULL;
		}
		
		sort_list_add(&head, p);
	}
  
	sorted = do_list_sort(head);
	
	dump_list(sorted, "sorted");
  
	
	return 0;
}

OSAL_CMD(sort, 1, sort_list, "leet code test");











