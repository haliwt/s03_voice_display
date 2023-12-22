#include "bsp_display.h"
#include "bsp.h"

DISP_T disp_t;

/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void Display_Temperature_Humidity_Value(void)
{
     static uint8_t m,n,p,q;
    if(pro_t.gPower_On==1){

		
		panel_led_fun();

	    m = (disp_t.disp_hours_time/10) ;
		n=	(disp_t.disp_hours_time%10); 
		p = (disp_t.disp_minutes_time/10);
		q=  (disp_t.disp_minutes_time%10);

        //hours
		 lcd_t.number5_high = m;
		 lcd_t.number5_low = m;

		  lcd_t.number6_high = n;
		 lcd_t.number6_low = n;

		 //minutes 
		 lcd_t.number7_high = p;
		 lcd_t.number7_low = p;

		  lcd_t.number8_high = q;
		 lcd_t.number8_low = q;

		 DisplayPanel_Ref_Handler();
		

   }

		   
}

/************************************************************************
	*
	*Function Name:static void Setup_Timer_Times(void)
	*Funcion:
	*Iinput Ref:NO
	*Return Ref:NO
	*
************************************************************************/  
static void Timing_Handler(void)
{
     switch(run_t.display_set_timer_timing ){
         
     case beijing_time:
      // beijing_time_fun();
        Display_Works_Times_Value();

						 
    break;
    
    case timer_time:
	
		//Setup_Timer_Times();
		Display_Works_Times_Value();
		Works_Counter_Time();
	
     
     break;
		
    }
}

/*************************************************************************
	*
	*Functin Name:static void Setup_Timer_Times(void)
	*Function : set up timer timing function
	*
	*
	*
*************************************************************************/
static void Setup_Timer_Times(void)
{


      if(pro_t.gTimer_timing > 59){ //
        
        pro_t.gTimer_timing =0;
		 disp_t.disp_timer_time_minutes --;
	    if(disp_t.disp_timer_time_minutes < 0){
		     disp_t.disp_timer_time_hours -- ;
			 disp_t.disp_timer_time_minutes =59;
           
			if(disp_t.disp_timer_time_hours < 0 ){

	           if(disp_t.timer_timing_define_flag == timing_success){
			    disp_t.disp_timer_time_hours=0;
				disp_t.disp_timer_time_minutes=0;
				//run_t.wifi_send_buzzer_sound=0xff;
				Power_Off_Fun();
			

			    //run_t.gFan_RunContinue=1;
				//run_t.fan_off_60s = 0;
	           
	          
                
                }
                else{
     
                     disp_t.disp_timer_time_hours =0;
                     disp_t.disp_timer_time_minutes =0;
				     disp_t.display_set_timer_timing=beijing_time;
                     ctl_t.gAi_flag =1 ;//run_t.gModel=1;
					 SendData_Set_Command(MODE_AI_NO_BUZZER);
                 }
                            
                
                }
              }
            
		     }

	     
     
   
			lcd_t.number5_low=(disp_t.disp_timer_time_hours ) /10;
			lcd_t.number5_high =(disp_t.disp_timer_time_hours) /10;

			lcd_t.number6_low = (disp_t.disp_timer_time_hours ) %10;;
			lcd_t.number6_high = (disp_t.disp_timer_time_hours ) %10;

			lcd_t.number7_low = (disp_t.disp_timer_time_minutes )/10;
			lcd_t.number7_high = (disp_t.disp_timer_time_minutes)/10;

			lcd_t.number8_low = (disp_t.disp_timer_time_minutes)%10;
			lcd_t.number8_high = (disp_t.disp_timer_time_minutes )%10;
}
/*************************************************************************
	*
	*Functin Name:void Setup_Timer_Times_Donot_Display(void)
	*
	*
	*
	*
*************************************************************************/       
void Setup_Timer_Times_Donot_Display(void)
{
   if(pro_t.gTimer_timing > 59){ //
        
        pro_t.gTimer_timing =0;
		disp_t.disp_timer_time_minutes --;
	    if(disp_t.disp_timer_time_minutes < 0){
		     disp_t.disp_timer_time_hours -- ;
			 disp_t.disp_timer_time_minutes =59;
           
			if(disp_t.disp_timer_time_hours < 0 ){

	           if(disp_t.timer_timing_define_flag == timing_success){
			    disp_t.disp_timer_time_hours=0;
				disp_t.disp_timer_time_minutes=0;
				//pro_t.wifi_send_buzzer_sound=0xff;
				Power_Off_Fun();

			
				pro_t.gPower_On =0 ;
			    pro_t.gFan_RunContinue=1;
				pro_t.fan_off_60s = 0;
	           
	          
                
                }
                 else{
     
                     disp_t.disp_timer_time_hours =0;
                     disp_t.disp_timer_time_minutes =0;
                 
                 }
                            
                
                }
              }
            
		     }




}

/***************************************************************
 * 
 * Function Name:
 * 
 *
 * 
 **************************************************************/
static void Works_Counter_Time(void)
{
  if(disp_t.timer_timing_define_flag == timing_success){ //设置定时模式 is enable
	  if(disp_t.gTimer_minute_Counter >59){ //minute
		
		disp_t.gTimer_minute_Counter=0;
        disp_t.disp_minutes_time ++;
       
          
		if( disp_t.disp_minutes_time > 59){
			  disp_t.disp_minutes_time=0;
			disp_t.disp_hours_time ++;
		  
		if(disp_t.disp_hours_time >24){
			disp_t.disp_hours_time=0;

		}

		}


	  }
  }
}



