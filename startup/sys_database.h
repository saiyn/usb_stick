#ifndef _SYS_DATABASE_H_
#define _SYS_DATABASE_H_


typedef enum{
	SYS_KEYBOARD_MEG=0,
	SYS_POWER_MSG,
	SYS_MSG_NUM
}sys_event_t;

typedef enum{
	SOFT_MDC_MSG = 0,
	SOFT_MSG_NUM
}Soft_task_event_t;

typedef struct{
	uint8 datawith;
	uint8 protocal;
	uint32 bitrate;
}spi_ctl_t;


typedef enum{
	HC595_NULL = 0,
	HC595_HP_MUTE,
	HC595_LINE_MUTE,
	HC595_PS_EN,
	HC595_PS1,
	HC595_PS2,
	HC595_PS4,
	HC595_PS5
}hc595_io_t;

typedef enum{
	KEY_ENTER = 0,
	KEY_SRC_PREV,
	KEY_SRC_NEXT,
	KEY_STANDBY,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_DOWN,
	KEY_UP,
	KEY_ENTER_LONG,
	KEY_SRC_PREV_LONG,
	KEY_SRC_NEXT_LONG,
	KEY_STANDBY_LONG,
	KEY_RIGHT_LONG,
	KEY_LEFT_LONG,
	KEY_DOWN_LONG,
	KEY_UP_LONG,
	KEY_VALUE_MAX
}key_value_t;

typedef enum{
	LED_OFF=0,
	LED_ORANGE,
	LED_RED,
	LED_BIUE
}led_state_t;

typedef enum{
	WELCOM_MENU = 0,
	FACTORY_SUB_SELECT_MENU,
	FACTOTY_SUB_CONFIRM_MENU,
	VOLUME_MENU,
	SOURCE_MENU,
	PRESET_MENU,
	BRIGHTLESS_MENU,
	INSTALL_MENU,
	IP_ADDRESS_MENU,
	SUB_MODEL_MENU,
	INPUT_GAIN_MENU,
	PHRASE_MENU,
	SUB_LOWPASS_MENU,
	SUB_HIGHPASS_MENU,
	LINEOUT_HIGHPASS_MENU,
	DELAY_ROUTER_MENU,
	DELAY_TIME_MENU,
	POWER_ON_METHOD_MENU,
	SENSE_THRESHOLD,
	SENSE_OFF_TIME,
	RESET_MENU,
	RESET_CONFIRM_MENU,
	MENU_NUM,
	DIS_OVER_TEMP,
	DIS_OVER_VOLTAGE_OR_SHORT,
	DIS_OVER_CLIP,
	DIS_OVER_DC_ERROR,
	DIS_OVER_CURRENT,
	DIS_OVER_15V
}menu_id_t;

typedef enum{
IR_VOL_UP =0,
IR_VOL_DOWN,
IR_ON,
IR_OFF,
IR_NORMAL,
IR_CINEMA,
IR_NIGHT,
IR_USER1,
IR_USER2,
IR_USER3,
IR_BACK,
IR_UP,
IR_LFET,
IR_CENTER,
IR_RIGHT,
IR_DOWN,
IR_MUTE,
IR_COMMOND_NUM
}ir_commond_t;

#define MENU_NODE  IP_ADDRESS_MENU


typedef enum{
	DETECT_AUDIO = 0,
	DETECT_TRIGGER,
	DETECT_AC_DET,
	DETECT_POWER_GOOD,
	DETECT_DC_ERROR,
	NUM_OF_DETECT
}detect_event_t;

extern const char *version;

typedef struct{
	size_t index;
	size_t min;
	size_t max;
}menu_context_t;

struct menu{
	menu_id_t id;
	menu_context_t *context;
	struct menu *next;
	struct menu *prev;
	struct menu *child;
	struct menu *parent;
};

typedef struct menu menu_t;

typedef enum{
	MANUAL=0,
	AUDIO,
	TRIGGER,
	IR_IP,
	POWER_ON_MAX
}power_on_t;

typedef enum{
	STATUS_STANDBY=0,
	STATUS_WORKING,
	STATUS_SHUTDOWN,
	STATUS_MAX
}sys_status_t;

typedef enum{
	SRC_COAX1=0,
	SRC_COAX2,
	SRC_OPT1,
	SRC_OPT2,
	SRC_CONSTANT_NUM
}src_t;

typedef enum{
	SENSE_3MV=0,
	SENSE_6MV,
	SENSE_9MV,
	SENSE_12MV,
	SENSE_15MV,
	SENSE_THRESHOLD_NUM
}sense_threshold_t;

typedef enum{
	SE_TIMEOUT_5=0,
	SE_TIMEOUT_10,
	SE_TIMEOUT_20,
	SE_TIMEOUT_30,
	SE_TIMEOUT_60,
	SE_TIMEOUT_NUM
}sense_timeout_t;

typedef struct{
  
	uint8 src_num;
	src_t src;
	uint32 a;
	uint32 b;
	uint32 c;

	
	uint32 sys_crc32;
	uint32 mdc_crc32;
	uint8 end_of_nv;
	

	sys_status_t status;
	

	
}sys_state_t;




#define SIZEOF_SYS_NV   ((uint8 *)&gSystem_t->end_of_nv - (uint8 *)&gSystem_t->src_num)


#endif


