#ifndef __BSP_H_
#define __BSP_H_
#include "main.h"

#include "iwdg.h"
#include "tim.h"

#include "bsp_cmd_link.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_ctl.h"
#include "bsp_display.h"
#include "bsp_led.h"
#include "bsp_buzzer.h"
#include "bsp_lcd.h"
#include "bsp_display.h"
#include "bsp_voice.h"
#include "bsp_usart_fifo.h"
#include "bsp_wifi.h"
#include "bsp_decoder.h"
#include "bsp_key.h"
#include "bsp_delay.h"




/* ?? BSP ??? */
#define __STM32G030_BSP_VERSION		"1.0"


/* CPU???????? */
//#define CPU_IDLE()		bsp_Idle()

/* ???????? */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ?????? */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ?????? */

typedef enum{

  set_temperature,
  set_timer_timing
  
}key_state_en;

typedef enum{

   power_off,
   power_on,
   wifi_fun_on,
   set_timer_fun_on,
   mode_id,
   mode_ai,
   mode_no_ai,
   add_key,
   dec_key,
   power_id
   

}key_input_state;

typedef enum{

    run_update_data =0x01,
	power_off_fan_pro
	

}process_state;

typedef struct{

  //key
   uint8_t gKey_value;
   uint8_t gPower_On;
   uint8_t long_key_flag;
  
   uint8_t ack_wifi_led;
   uint8_t ack_power_on_sig;
   uint8_t ack_power_off_sig;

   uint8_t gKey_command_tag;

   uint8_t decodeFlag;
   //time
   uint8_t set_timer_flag;
   uint8_t gTimer_mode_flag;
   uint8_t key_set_timer_flag;

 

   //temperature 
   uint8_t temperature_set_flag;

   //warning
 
	//wifi
	uint8_t wifi_led_fast_blink_flag;

  uint8_t gTimer_pro_feed_dog;
	uint8_t gTimer_pro_temp ;
	uint8_t gTimer_pro_temp_delay ;
	uint8_t gTimer_wifi_connect_counter;
	uint8_t gTimer_key_timing;
	uint8_t gTimer_pro_disp;
	uint8_t gTimer_pro_fan;
	uint8_t gTimer_usart_error;
	uint8_t gTimer_pro_ms;
	uint8_t gTimer_pro_disp_timer ;
	uint8_t gTimer_pro_disp_ms;
	

}PRO_T;


extern PRO_T pro_t;

void bsp_Idle(void);
void Key_Handler(uint8_t keyvalue);
void Display_Process_Handler(void);

void Power_Off_Fun(void);

void Power_Key_Detected(void);
void Mode_Key_Detected(void);
void ADD_Key_Detected(void);
void DEC_Key_Detected(void);

void Mode_Long_Key_Fun(void);




#endif 



