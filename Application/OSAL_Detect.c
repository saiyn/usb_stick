#include "common_head.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "OSAL_Detect.h"
#include "System_Task.h"


detect_control_t detectlist[NUM_OF_DETECT] =
{
{GPIO_ReadSinglePin, AUDIO_SENSE_PORT, AUDIO_SENSE_PIN, 1, DETECT_BEGIN, sys_audio_valid_handler, sys_audio_invalid_handler},
{GPIO_ReadSinglePin, TRIGGER_IN_PORT, TRIGGER_IN_PIN, 0, DETECT_BEGIN, sys_trigger_valid_handler, sys_trigger_invalid_handler},
{GPIO_ReadSinglePin, OVER_TEMP_PORT, OVER_TEMP_PIN, 1, DETECT_BEGIN, sys_protect_valid_handler, sys_protect_invalid_handler},
{GPIO_ReadSinglePin, OVER_VOLTAGE_OR_SHORT_PORT, OVER_VOLTAGE_OR_SHORT_PIN,1, DETECT_BEGIN, sys_protect_valid_handler, sys_protect_invalid_handler},
{GPIO_ReadSinglePin, OVER_CLIP_PORT, OVER_CLIP_PIN, 1, DETECT_BEGIN, sys_protect_valid_handler, sys_protect_invalid_handler},
{GPIO_ReadSinglePin, OVER_DC_ERROR_PORT, OVER_DC_ERROR_PIN, 1, DETECT_BEGIN, sys_protect_valid_handler, sys_protect_invalid_handler},
{GPIO_ReadSinglePin, OVER_CURRENT_PORT, OVER_CURRENT_PIN, 1, DETECT_BEGIN, sys_protect_valid_handler, sys_protect_invalid_handler},
{GPIO_ReadSinglePin, OVER_15V_PORT, OVER_15V_PIN, 1, DETECT_BEGIN, sys_15v_valid_handler, sys_15v_invalid_handler}
};

void update_detect_state(detect_event_t event)
{
	OSAL_ASSERT(event < NUM_OF_DETECT);
	
	detectlist[event].state = DETECT_BEGIN;
}

void update_all_protect_state(void)
{
	uint8 index;
	
	for(index = DETECT_OVER_TEMP; index < NUM_OF_DETECT; index++){
		detectlist[index].state = DETECT_BEGIN;
	}
}

void DetectGpioPoll(void)
{
	uint8 index;
	
	for(index = 0; index < NUM_OF_DETECT; index++){ 
		/*don't detect protection event before power on*/
		if(index > 1 && gSystem_t->status != STATUS_WORKING) return;
		switch(detectlist[index].state){
			case DETECT_BEGIN:
				if(detectlist[index].pstateread(detectlist[index].port, detectlist[index].pin) == detectlist[index].mode){
					 vTaskDelay(100/portTICK_RATE_MS);
				   if(detectlist[index].pstateread(detectlist[index].port, detectlist[index].pin) == detectlist[index].mode){
							if(detectlist[index].validstatecallback != NULL){
								detectlist[index].validstatecallback(index);
								detectlist[index].state = DETECT_VALID;
							}
					 }else{
						  if(detectlist[index].invalidstatecallback != NULL){
				        detectlist[index].invalidstatecallback(index);
			        }
								detectlist[index].state = DETECT_INVALID;
					 }
				 }else{
					  if(detectlist[index].invalidstatecallback != NULL){
				        detectlist[index].invalidstatecallback(index);
			        }
								detectlist[index].state = DETECT_INVALID;
				 }
				break;
				
			case DETECT_VALID:
				if(detectlist[index].pstateread(detectlist[index].port, detectlist[index].pin) != detectlist[index].mode){
					if(detectlist[index].invalidstatecallback != NULL){
				     detectlist[index].invalidstatecallback(index);
			     }
					 detectlist[index].state = DETECT_INVALID;
				}
				break;
				
			case DETECT_INVALID:
				if(detectlist[index].pstateread(detectlist[index].port, detectlist[index].pin) == detectlist[index].mode){
					vTaskDelay(100/portTICK_RATE_MS);
					if(detectlist[index].pstateread(detectlist[index].port, detectlist[index].pin) == detectlist[index].mode){
							if(detectlist[index].validstatecallback != NULL){
								detectlist[index].validstatecallback(index);
								detectlist[index].state = DETECT_VALID;
				   }
				 }
			 }
				break;
			
			default:
				break;
		}
}

}











