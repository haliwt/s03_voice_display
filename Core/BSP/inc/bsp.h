#ifndef __BSP_H_
#define __BSP_H_
#include "main.h"

#include "iwdg.h"

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


/* ???????????? */
#if !defined (stm32G30_v1.0)
	#error "Please define the board model : V4.2"
#endif

/* ?? BSP ??? */
#define __STM32G030_BSP_VERSION		"1.0"


/* CPU???????? */
//#define CPU_IDLE()		bsp_Idle()

/* ???????? */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ?????? */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ?????? */

typedef enum{

   power_off,
   power_on,
   wifi_fun_on,
   set_timer_fun_on,
   mode_ai,
   mode_no_ai,
   add_key,
   dec_key
   

}key_state;

typedef enum{

    run_update_data =0x01,
	



}process_state;

typedef struct{


   uint8_t gKey_value;
   uint8_t gPower_On;
  
   uint8_t ack_wifi_led;
   uint8_t ack_power_on_sig;
   uint8_t ack_power_off_sig;

   uint8_t gKey_command_tag;

   uint8_t decodeFlag;
   //time
   uint8_t set_timer_flag;
   uint8_t Timer_mode_flag;
   uint8_t key_set_timer_flag;

   //temperature 
   uint8_t temperature_set_flag;
   uint8_t setup_temperature_value;
   //warning
    uint8_t ptc_warning;
    uint8_t fan_warning;
	//wifi
	uint8_t wifi_led_fast_blink_flag;

    uint8_t gTimer_pro_feed_dog;
	uint8_t gTimer_pro_temp ;
	uint8_t gTimer_pro_temp_delay ;



}PRO_T;


extern PRO_T pro_t;

void bsp_Idle(void);
void Key_Handler(uint8_t keyvalue);
void Display_Process_Handler(void);



#endif 



