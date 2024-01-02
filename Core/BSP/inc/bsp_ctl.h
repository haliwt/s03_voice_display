#ifndef __BSP_CTL_H_
#define __BSP_CTL_H_
#include "main.h"


typedef enum{

	 DRY_ON = 0x40,
	 DRY_OFF = 0x41,

	 DRY_ON_NO_BUZZER = 0x90,
	 DRY_OFF_NO_BUZZER = 0x91,

	 PLASMA_ON = 0x20,
	 PLASMA_OFF = 0x21,

   BUG_ON = 0x30,
   BUG_OFF = 0x31,

	 FAN_ON =0x10,
	 FAN_OFF = 0x11,

	 MODE_AI = 0x04,
	 MODE_TIMER = 0x14,
	 MODE_AI_NO_BUZZER= 0x44,

	 WIFI_CONNECT_FAIL=0x55,

	 WIFI_CONNECT_SUCCESS= 0xAA
}works_t;




typedef enum {
   
    WIFI_POWER_ON = 0x80,
    WIFI_POWER_OFF=0X81,
    WIFI_MODE_1=0X08,   //state ->normal works
    WIFI_MODE_2=0X18,   //state->sleeping works
    WIFI_KILL_ON=0x04,  //Anion(plasma)
    WIFI_KILL_OFF=0x14,
    WIFI_PTC_ON = 0x02, 
    WIFI_PTC_OFF = 0x12,
    WIFI_SONIC_ON = 0x01,       //ultrasonic
    WIFI_SONIC_OFF = 0x11,
    WIFI_WIND_SPEED_ITEM = 0x90,
    WIFI_TEMPERATURE = 0xA0,
    PTC_ERROR = 0xE0,
	FAN_ERROR = 0xE1,
	FAN_REMOVE_ERROR= 0xF1

}wifi_state_t;




typedef struct {

   uint8_t gPower_flag;
   uint8_t gPtc_flag;
   uint8_t gWifi_flag;
   uint8_t gAi_flag;
   uint8_t gPlasma_flag;
   uint8_t gBug_flag;
   uint8_t gSet_temp_value;

   uint8_t gFan_speed_value;
  
   uint8_t gReal_humidity_value;
   uint8_t gReal_tem_value;
  
   

   //warning
   uint8_t ptc_warning;
   uint8_t fan_warning;

   
   uint8_t gSet_temperature_value;
   uint8_t gSet_temperature_value_flag ;
   uint8_t gTimer_ctl_timer_time;
    //timer timing 
   int8_t gSet_timer_value;
   int8_t set_timer_minutes;
   
 
 

   
 }bsp_ctl;

 extern bsp_ctl ctl_t;




extern uint8_t (*wifi_state)(void);
extern uint8_t (*ptc_state)(void);
extern uint8_t (*ai_state)(void);
extern uint8_t (*fan_speed_state)(void);
extern uint8_t (*plasma_state)(void);
extern uint8_t (*bug_tate)(void);
extern uint8_t (*humidity_value)(void);
extern uint8_t (*temperature_value)(void);

extern uint8_t (*smartphone_set_timer_timing)(void);
extern uint8_t (*smartphone_set_temp_value)(void);







void bsp_ctlint(void);
void RunCommand_Handler(void);

void Wifi_Handler(uint8_t(*wifi_handler)(void));
void Ptc_Handler(uint8_t(*ptc_handler)(void));
void Ai_Handler(uint8_t(*ai_handler)(void));
void Fan_Handler(uint8_t(*fan_handler)(void));
void Plasma_Handler(uint8_t(*plasma_handler)(void));
void Bug_Handler(uint8_t(*bug_handler)(void));

void Humidity_Handler(uint8_t(*humi_handler)(void));
void Temp_Handler(uint8_t(*temp_handler)(void));

void Smartphone_Set_Timer_Handler(uint8_t(*set_timer_timing)(void));
void Smartphone_Set_Temp_Handler(uint8_t(*set_temp_value)(void));

void Display_Panel_Action_Handler(void);













#endif 



