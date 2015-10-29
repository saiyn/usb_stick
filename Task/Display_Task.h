#ifndef _DISPALY_TASK_H_
#define _DISPALY_TASK_H_

typedef enum{
	DIS_WELCOME=0,
	DIS_UPDATE,
	DIS_JUMP,
	DIS_MSG_NUM
}dis_msg_type_t;


typedef struct{
	dis_msg_type_t msg;
	menu_id_t id;
}dis_msg_t;




void display_menu_list_create(menu_t **head);

void dis_send_msg(dis_msg_type_t type, menu_id_t id);

void display_task(void *parameter);

void dis_send_msg_isr(dis_msg_type_t type, menu_id_t id);

void display_menu_jump(menu_id_t to);

void cancle_welcome_timeout(sys_state_t *sys);

#endif


