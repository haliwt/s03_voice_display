#include "bsp_display.h"
#include "bsp.h"


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

	    m = (pro_t.dispTime_hours/10) ;
		n=	(pro_t.gTime_hours%10); 
		p = (pro_t.dispTime_minutes/10);
		q=  (pro_t.dispTime_minutes%10);

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
/*********************************************************************************
 * 
 * Function Name:static void Beijing_Time_Dispaly(void)
 * 
 * 
 * 
**********************************************************************************/
static void Beijing_Time_Display(void)
{

       #if 0
		run_t.Timer_mode_flag = 0;
	    if(run_t.gTimer_minute_Counter >59){ //minute

			run_t.gTimer_minute_Counter=0;
            run_t.dispTime_minutes ++;
           
            
			if(run_t.dispTime_minutes > 59){
				run_t.dispTime_minutes=0;
				run_t.dispTime_hours ++;
			    run_t.works_counter_time_value++; //works two hours ,after stop 10 minutes, than works 
				if(run_t.dispTime_hours >24){
					run_t.dispTime_hours=0;

					}

			}
	    	}
            
            if(run_t.gPower_On == RUN_POWER_ON) {
				Setup_Timer_Times_Donot_Display();
				lcd_t.number5_low=(run_t.dispTime_hours ) /10;
				lcd_t.number5_high =(run_t.dispTime_hours) /10;

				lcd_t.number6_low = (run_t.dispTime_hours ) %10;;
				lcd_t.number6_high = (run_t.dispTime_hours ) %10;

				lcd_t.number7_low = (run_t.dispTime_minutes )/10;
				lcd_t.number7_high = (run_t.dispTime_minutes )/10;

				lcd_t.number8_low = (run_t.dispTime_minutes )%10;
				lcd_t.number8_high = (run_t.dispTime_minutes )%10;
			}

		#endif 

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


      if(run_t.gTimer_timing > 59){ //
        
        run_t.gTimer_timing =0;
		 run_t.timer_time_minutes --;
	    if(run_t.timer_time_minutes < 0){
		     run_t.timer_time_hours -- ;
			 run_t.timer_time_minutes =59;
           
			if(run_t.timer_time_hours < 0 ){

	           if(run_t.timer_timing_define_flag == timing_success){
			    run_t.timer_time_hours=0;
				run_t.timer_time_minutes=0;
				run_t.wifi_send_buzzer_sound=0xff;
				Power_Off_Fun();
			

			    run_t.gFan_RunContinue=1;
				run_t.fan_off_60s = 0;
	           
	          
                
                }
                 else{
     
                     run_t.timer_time_hours =0;
                     run_t.timer_time_minutes =0;
				     run_t.display_set_timer_timing=beijing_time;
                     run_t.gModel=1;
					 SendData_Set_Command(MODE_AI_NO_BUZZER);
                 }
                            
                
                }
              }
            
		     }

	     
     
   
			lcd_t.number5_low=(run_t.timer_time_hours ) /10;
			lcd_t.number5_high =(run_t.timer_time_hours) /10;

			lcd_t.number6_low = (run_t.timer_time_hours ) %10;;
			lcd_t.number6_high = (run_t.timer_time_hours ) %10;

			lcd_t.number7_low = (run_t.timer_time_minutes )/10;
			lcd_t.number7_high = (run_t.timer_time_minutes)/10;

			lcd_t.number8_low = (run_t.timer_time_minutes)%10;
			lcd_t.number8_high = (run_t.timer_time_minutes )%10;
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
   if(run_t.gTimer_timing > 59){ //
        
        run_t.gTimer_timing =0;
		 run_t.timer_time_minutes --;
	    if(run_t.timer_time_minutes < 0){
		     run_t.timer_time_hours -- ;
			 run_t.timer_time_minutes =59;
           
			if(run_t.timer_time_hours < 0 ){

	           if(run_t.timer_timing_define_flag == timing_success){
			    run_t.timer_time_hours=0;
				run_t.timer_time_minutes=0;
				run_t.wifi_send_buzzer_sound=0xff;
				Power_Off_Fun();

			
				run_t.gPower_On =0 ;
			    run_t.gFan_RunContinue=1;
				run_t.fan_off_60s = 0;
	           
	          
                
                }
                 else{
     
                     run_t.timer_time_hours =0;
                     run_t.timer_time_minutes =0;
                 
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
  if(run_t.timer_timing_define_flag == timing_success){
	  if(run_t.gTimer_minute_Counter >59){ //minute
		
		run_t.gTimer_minute_Counter=0;
        run_t.dispTime_minutes ++;
       
          
		if(run_t.dispTime_minutes > 59){
			run_t.dispTime_minutes=0;
			run_t.dispTime_hours ++;
		    run_t.works_counter_time_value++;
		if(run_t.dispTime_hours >24){
			run_t.dispTime_hours=0;

		}

		}


	  }
  }
}



