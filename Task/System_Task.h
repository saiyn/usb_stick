#ifndef _SYSTEM_TASK_H_
#define _SYSTEM_TASK_H_

typedef enum{
	KEYBOARD_MSG = 0,
	POWER_KEY_MSG,
	DATABASE_UPDATE_MSG,
	CODE_PASS_MSG,
}sys_msg_type_t;

typedef struct{
	sys_msg_type_t msg;
	uint8 data;
}sys_msg_t;

extern xQueueHandle gSysQueue;
extern sys_state_t *gSystem_t;



void sys_factory_reset(sys_state_t *sys);

void system_task(void *parameter);

void sys_database_init(void);


void sys_send_msg_isr(sys_msg_type_t type, uint8 data);

void sys_send_msg(sys_msg_type_t type, uint8 data);

void sys_update_timeout(uint32 *timeout);

void sys_check_timeout(void);

void sys_ip_set_to_default(sys_state_t *sys);

void sys_eq_state_control(sys_state_t *cur);

int sys_input_init(void);

void sys_poll_handler(void *arg);

void sys_power_off_handler(sys_state_t *sys);

void sys_lcd_bright_change(sys_state_t *cur);

void sys_database_update(void *arg);


void sys_audio_valid_handler(uint8 index);

void sys_audio_invalid_handler(uint8 index);

void sys_trigger_valid_handler(uint8 index);

void sys_trigger_invalid_handler(uint8 index);

void sys_input_select(src_t src);

void sys_input_gain_change(sys_state_t *sys);

void sys_master_vol_set(sys_state_t *sys);

void sys_audio_sense_thres_set(sense_threshold_t thrs);

void sys_sub_lowpass_set(sys_state_t *sys);

void dsp_subHpFreq_set(uint8 slope, uint16 freq, uint8 num, uint8 offset);

void sys_sub_highpass_set(sys_state_t *sys);

void sys_line_highpass_set(sys_state_t *sys);

void sys_line_highpass_set(sys_state_t *sys);

void sys_delay_time_set(sys_state_t *sys);

void sys_delay_switch_to(sys_state_t *sys);

void sys_phrase_set(sys_state_t *sys);

void sys_load_roomeq(sys_state_t *sys);

void sys_load_peq(sys_state_t *sys);

void sys_load_custeq(sys_state_t *sys);

void sys_eq_state_set(sys_state_t *sys);

void sys_peq_single_set(sys_state_t *sys, uint8 preset, uint8 index, uint32 a, uint32 b, uint32 g);

void sys_req_single_set(sys_state_t *sys, uint8 index, uint32 a, uint32 b, uint32 g);

void sys_sub_preset_load(sys_state_t *sys);

void sys_protect_valid_handler(uint8 index);

void sys_protect_invalid_handler(uint8 index);

void sys_database0_update_later(void *arg);

void sys_database1_update_later(void *arg);

void sys_database2_update_later(void *arg);

void sys_15v_valid_handler(uint8 index);

void sys_15v_invalid_handler(uint8 index);

void sys_ip_power_on_handler(sys_state_t *sys);

void sys_low_power_handler(void);

#endif


