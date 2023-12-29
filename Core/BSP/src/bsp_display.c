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
				//disp_t.disp_timer_or_works_timing = timer_time;
			
				pro_t.gKey_value = power_off;
				Power_Off_Fun();
			}
			else{ //don't set timer timing to be changed "works time modes"
     
                  disp_t.disp_timer_time_hours =0;
                 disp_t.disp_timer_time_minutes =0;
			     //run_t.display_set_timer_timing=beijing_time;
			     disp_t.timer_timing_define_flag = works_time;
				 disp_t.disp_timer_or_works_timing = works_time;
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
    if(pro_t.gPower_On==power_on){

		

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
    switch(disp_t.disp_timer_or_works_timing){ //disp_t.timer_timing_define_flag
         
    case works_time:
        Display_Works_Time_Handler();
	   

	break;
    
    case timer_time:
		 
	  Display_Timer_Time_Handler();
			
	  Works_Time_Continue(); //still recoder "works time"


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
					 disp_t.disp_timer_or_works_timing = works_time;
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

    if(disp_t.timer_timing_define_flag == timing_success){

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
}

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

void Display_Voice_Set_Temp_Value(void)
{
    if(disp_t.disp_set_temp_value < 20){
	    disp_t.disp_set_temp_value=20;
	}
	
	if(disp_t.disp_set_temp_value > 40)disp_t.disp_set_temp_value= 20;



   // decade_temp =  disp_t.disp_set_temp_value / 10 ;
	//unit_temp =  disp_t.disp_set_temp_value % 10; //
    
	lcd_t.number1_low=disp_t.disp_set_temp_value / 10 ;
	lcd_t.number1_high =disp_t.disp_set_temp_value / 10 ;

	lcd_t.number2_low = disp_t.disp_set_temp_value % 10; //
	lcd_t.number2_high = disp_t.disp_set_temp_value % 10; //
	
	lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led" timer timing
    pro_t.temperature_set_flag=1;  //set temperature value flag

}

void Display_Voice_Set_Timer_Value(void)
{

   uint8_t temp_bit_1_hours,temp_bit_2_hours,temp_bit_1_minute,temp_bit_2_minute;
   
	
	if(ctl_t.fan_warning ==0 && ctl_t.ptc_warning ==0){
	

		   ctl_t.gAi_flag =0;
		   pro_t.setup_timer_timing_item=timer_time;
		 
		   pro_t.gTimer_key_timing=0; //按键退出的限制，4秒以内
		   pro_t.Timer_mode_flag=1; //set timer timing enable,
	
		   
		   
		   SendData_Set_Wifi(MODE_TIMER);             
		//disp_t.disp_timer_time_hours++ ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes + 60;
		if(disp_t.disp_timer_time_hours > 24){ //if(pro_t.dispTime_minutes > 59){

		disp_t.disp_timer_time_hours=0;//pro_t.dispTime_hours =0;


		}

		temp_bit_2_hours = disp_t.disp_timer_time_hours /10 ;
		temp_bit_1_hours = disp_t.disp_timer_time_hours %10;

		temp_bit_2_minute =0;
		temp_bit_1_minute =0;

		lcd_t.number5_low=temp_bit_2_hours;
		lcd_t.number5_high =temp_bit_2_hours;

		lcd_t.number6_low = temp_bit_1_hours;
		lcd_t.number6_high = temp_bit_1_hours;

		lcd_t.number7_low=temp_bit_2_minute;
		lcd_t.number7_high =temp_bit_2_minute;

		lcd_t.number8_low = temp_bit_1_minute;
		lcd_t.number8_high = temp_bit_1_minute;
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


