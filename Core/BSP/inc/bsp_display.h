#ifndef __BSP_DISPLAY_H_
#define __BSP_DISPLAY_H_

#include "main.h"

typedef enum TIMING_T{

   works_time=0x01,
   timer_time,
   timing_success ,
   
}timing_t;




typedef struct{

   //works timer timng normal 
   int8_t disp_timer_time_hours ;
   int8_t disp_timer_time_minutes;
   uint8_t disp_timer_time_seconds;

   //to wifi be set temperature value and set timer timing 
   uint8_t disp_set_temp_value;
   uint8_t disp_set_timer_timing;
   //display works times 
   uint8_t disp_hours_time;
   uint8_t disp_minutes_time;
   uint8_t disp_seconds_times;
   uint8_t timer_timing_define_flag;
   uint8_t disp_timer_or_works_timing;

   uint8_t gTimer_disp_seconds_time;
   uint8_t gTimer_disp_hours_time;
   uint8_t gTimer_disp_minutes_time;
   uint8_t gTimer_disp_timer_timing;
   



}DISP_T;

extern DISP_T disp_t;


extern int8_t (*display_works_hours_value)(void);
extern int8_t (*display_works_minutes_value)(void);

extern int8_t (*display_timer_hours_value)(void);
extern int8_t (*display_timer_minutes_value)(void);


void Disp_Init(void);


void Display_Temperature_Humidity_Value_Handler(void);

void Timing_Handler(void);



void Display_Works_Hours_Handler(int8_t(*disp_hours_handler)(void));
void Display_Works_Minutes_Handler(int8_t (*disp_minutes_handler)(void));

void Display_Timer_Hours_Handler(int8_t(*disp_timer_hours_handler)(void));
void Display_Timer_Minutes_Handler(int8_t(*disp_timer_minutes_handler)(void));


void Display_Voice_Set_Temp_Value(void);

void Display_Voice_Set_Timer_Value(void);













#endif 
