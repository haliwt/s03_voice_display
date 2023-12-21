#ifndef __BSP_DISPLAY_H_
#define __BSP_DISPLAY_H_

#include "main.h"



typedef struct{

   uint8_t disp_hours_time;
   uint8_t disp_minutes_time;
   uint8_t disp_seconds_times;
   uint8_t display_beijing_time_flag ;

   uint8_t gTimer_disp_seconds_time;
   uint8_t gTimer_disp_hours_time;
   uint8_t gTimer_disp_minutes_time;



}DISP_T;

extern DISP_T disp_t;















#endif 
