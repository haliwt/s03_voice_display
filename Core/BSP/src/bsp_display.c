#include "bsp_display.h"
#include "bsp.h"

DISP_T disp_t;


int8_t (*display_works_hours_value)(void);
int8_t (*display_works_minutes_value)(void);

int8_t (*display_timer_hours_value)(void);
int8_t (*display_timer_minutes_value)(void);

static int8_t display_works_hours_default_fun(void);
static int8_t display_works_minutes_default_fun(void);


static int8_t display_timer_hours_default_fun(void);
static int8_t display_timer_minutes_default_fun(void);

static void Display_Works_Time_Handler(void);
static void Display_Timer_Time_Handler(void);
static void Setup_Timer_Times_Donot_Display(void);
static void Works_Time_Continue(void);


/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void Disp_Init(void)
{
    Display_Works_Hours_Handler(display_works_hours_default_fun);
    Display_Works_Minutes_Handler(display_works_minutes_default_fun);

    Display_Timer_Hours_Handler(display_timer_hours_default_fun);
    Display_Timer_Minutes_Handler(display_timer_minutes_default_fun);

}
/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
static void Display_Works_Time_Handler(void)
{
	
	   if(disp_t.gTimer_disp_minutes_time >59){ //minute

			disp_t.gTimer_disp_minutes_time =0;
			disp_t.disp_minutes_time++;
          
            if(disp_t.disp_minutes_time > 59){
				disp_t.disp_minutes_time=0;
				disp_t.disp_hours_time ++;
			    
				if(disp_t.disp_hours_time >23){
					disp_t.disp_hours_time=0;

				}

			}
	   }
            
         
	Setup_Timer_Times_Donot_Display();
	lcd_t.number5_low=(disp_t.disp_hours_time ) /10;
	lcd_t.number5_high =(disp_t.disp_hours_time) /10;

	lcd_t.number6_low = (disp_t.disp_hours_time) %10;;
	lcd_t.number6_high = (disp_t.disp_hours_time ) %10;

	lcd_t.number7_low = (disp_t.disp_minutes_time )/10;
	lcd_t.number7_high = (disp_t.disp_minutes_time )/10;

	lcd_t.number8_low = (disp_t.disp_minutes_time )%10;
	lcd_t.number8_high = (disp_t.disp_minutes_time )%10;
}
/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
static void Display_Timer_Time_Handler(void)
{
	 if(disp_t.gTimer_disp_timer_timing  > 59){ //
        
  		 disp_t.gTimer_disp_timer_timing  =0;
		 disp_t.disp_timer_time_minutes--;
	    if( disp_t.disp_timer_time_minutes < 0){
		     disp_t.disp_timer_time_hours -- ;
			 disp_t.disp_timer_time_minutes =59;
           
			if( disp_t.disp_timer_time_hours < 0 ){


			  if(disp_t.timer_timing_define_flag == timing_success){
			    disp_t.disp_timer_time_minutes=0;
				disp_t.disp_timer_time_minutes=0;
				//run_t.wifi_send_buzzer_sound=0xff;
				pro_t.gKey_value = power_off;
				Power_Off_Fun();
			}
			else{ //don't set timer timing to be changed "works time modes"
     
                  disp_t.disp_timer_time_hours =0;
                 disp_t.disp_timer_time_minutes =0;
			     //run_t.display_set_timer_timing=beijing_time;
			     disp_t.timer_timing_define_flag = works_time;
                 ctl_t.gAi_flag = 1;//run_t.gModel=1;
				 SendData_Set_Command(MODE_AI_NO_BUZZER);
            }
	      }
                            
                
        }
    }
            
    lcd_t.number5_low=(disp_t.disp_timer_time_hours  ) /10;
	lcd_t.number5_high =(disp_t.disp_timer_time_hours ) /10;

	lcd_t.number6_low = (disp_t.disp_timer_time_hours  ) %10;;
	lcd_t.number6_high = (disp_t.disp_timer_time_hours  ) %10;

	lcd_t.number7_low = ( disp_t.disp_timer_time_minutes )/10;
	lcd_t.number7_high = ( disp_t.disp_timer_time_minutes)/10;

	lcd_t.number8_low = ( disp_t.disp_timer_time_minutes)%10;
	lcd_t.number8_high = ( disp_t.disp_timer_time_minutes )%10;

}
/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void Display_Temperature_Humidity_Value_Handler(void)
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
void Timing_Handler(void)
{
     switch(disp_t.timer_timing_define_flag){
         
     case works_time:
        Display_Works_Time_Handler();
	   

						 
    break;
    
    case timing_success:
	
		Display_Timer_Time_Handler();
		
	    Works_Time_Continue(); //still recoder "works time"
     
     break;

	case timer_time:
		 


	break;

	default:

	break;
		
    }
    DisplayPanel_Ref_Handler();
}
/***************************************************************
 * 
 * Function Name:
 * 
 *
 * 
 **************************************************************/
static void Works_Time_Continue(void)
{
  if(disp_t.timer_timing_define_flag == timing_success){
	 
	 if(disp_t.gTimer_disp_minutes_time >59){ //minute

			disp_t.gTimer_disp_minutes_time =0;
			disp_t.disp_minutes_time++;
          
            if(disp_t.disp_minutes_time > 59){
				disp_t.disp_minutes_time=0;
				disp_t.disp_hours_time ++;
			    
				if(disp_t.disp_hours_time >23){
					disp_t.disp_hours_time=0;

				}

			}
	}
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
void Setup_Timer_Times(void)
{
	if(disp_t.gTimer_disp_timer_timing> 59){ //
        
        disp_t.gTimer_disp_timer_timing=0;
		 disp_t.disp_timer_time_minutes --;
	    if(disp_t.disp_timer_time_minutes < 0){
		     disp_t.disp_timer_time_hours -- ;
			 disp_t.disp_timer_time_minutes =59;
           
			if(disp_t.disp_timer_time_hours < 0 ){

	           if(disp_t.timer_timing_define_flag == timing_success){
			    disp_t.disp_timer_time_hours=0;
				disp_t.disp_timer_time_minutes=0;
				
				Power_Off_Fun();
				}
                else{
     
                     disp_t.disp_timer_time_hours =0;
                     disp_t.disp_timer_time_minutes =0;
					 disp_t.timer_timing_define_flag = works_time;
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
static void Setup_Timer_Times_Donot_Display(void)
{
	if(disp_t.gTimer_disp_timer_timing  > 59){ //
        
  		 disp_t.gTimer_disp_timer_timing  =0;
		 disp_t.disp_timer_time_minutes--;
	    if( disp_t.disp_timer_time_minutes < 0){
		     disp_t.disp_timer_time_hours -- ;
			 disp_t.disp_timer_time_minutes =59;
           
			if( disp_t.disp_timer_time_hours < 0 ){

	           
			    disp_t.disp_timer_time_minutes=0;
				disp_t.disp_timer_time_minutes=0;
				//run_t.wifi_send_buzzer_sound=0xff;
				Power_Off_Fun();
			}
           
        }
    }
}
/***************************************************************
	 * 
	 * Function Name:
	 * Function:
	 * Input Ref:
	 * Return Ref:
	 * 
 **************************************************************/
#if 0
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
#endif 
/***************************************************************
	 * 
	 * Function Name:static uint8_t display_works_hours_default_fun(void)
	 * Function:display works hours 
	 * Input Ref:
	 * Return Ref: works of hours 
	 * 
 **************************************************************/
static int8_t display_works_hours_default_fun(void)
{
     static uint8_t disp_hours;

	if(disp_t.gTimer_disp_minutes_time > 59){
        disp_t.gTimer_disp_minutes_time= 0;
		disp_hours ++ ;

	}

	if(disp_hours > 24){
       disp_hours =0; 

	}

	return disp_hours;

}

/***************************************************************
	 * 
	 * Function Name:
	 * Function:
	 * Input Ref:
	 * Return Ref:
	 * 
 **************************************************************/
static int8_t display_works_minutes_default_fun(void)
{
     return disp_t.gTimer_disp_minutes_time;

}
/***************************************************************
	 * 
	 * Function Name:
	 * Function:
	 * Input Ref:
	 * Return Ref:
	 * 
 **************************************************************/
static int8_t display_timer_hours_default_fun(void)
{
     return  disp_t.disp_timer_time_hours;

}
/***************************************************************
	 * 
	 * Function Name:
	 * Function:
	 * Input Ref:
	 * Return Ref:
	 * 
 **************************************************************/
static int8_t display_timer_minutes_default_fun(void)
{

    if(disp_t.gTimer_disp_timer_timing > 59){
	    disp_t.gTimer_disp_timer_timing = 0;
        disp_t.disp_timer_time_minutes --;

		if(disp_t.disp_timer_time_minutes <0){
	    
        disp_t.disp_timer_time_hours --;
        if(disp_t.disp_timer_time_hours > -1){
		  
		    disp_t.disp_timer_time_minutes = 59;

              
	   }
	   }

	  if( disp_t.disp_timer_time_hours < 0){

          disp_t.disp_timer_time_hours= -1;
		  disp_t.disp_timer_time_minutes = 0;

	     

	  }

    }

	return disp_t.disp_timer_time_minutes;

	

}



/***************************************************************
	 * 
	 * Function Name:
	 * Function:
	 * Input Ref:
	 * Return Ref:
	 * 
 **************************************************************/

void Display_Works_Hours_Handler(int8_t(*disp_hours_handler)(void))
{
   display_works_hours_value = disp_hours_handler;
}
void Display_Works_Minutes_Handler(int8_t(*disp_minutes_handler)(void))
{
  display_works_minutes_value = disp_minutes_handler;
}

void Display_Timer_Hours_Handler(int8_t(*disp_timer_hours_handler)(void))
{
   display_timer_hours_value = disp_timer_hours_handler;

}
void Display_Timer_Minutes_Handler(int8_t(*disp_timer_minutes_handler)(void))
{
  display_timer_minutes_value = disp_timer_minutes_handler;
}


