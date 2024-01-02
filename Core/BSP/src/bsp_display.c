#include "bsp_display.h"
#include "bsp.h"

DISP_T disp_t;


int8_t (*display_works_hours_value)(void);
int8_t (*display_works_minutes_value)(void);

int8_t (*display_timer_hours_value)(void);
int8_t (*display_timer_minutes_value)(void);

static int8_t display_works_hours_default_fun(void);
static int8_t display_works_minutes_default_fun(void);

static void Display_Works_Time_Handler(void);
static void Display_Timer_Time_Handler(void);
static void Timer_Times_Counter_Display(void);

static void Works_Time_Continue(void);


/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void Disp_Init(void)
{

    disp_t.timer_timing_define_flag = works_time;
	Display_Works_Hours_Handler(display_works_hours_default_fun);
    Display_Works_Minutes_Handler(display_works_minutes_default_fun);


  

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
			disp_t.disp_works_minutes_time++;
          
            if(disp_t.disp_works_minutes_time > 59){
				disp_t.disp_works_minutes_time=0;
				disp_t.disp_works_hours_time ++;
			    
				if(disp_t.disp_works_hours_time >23){
					disp_t.disp_works_hours_time=0;

				}

			}
	   }
            
         
	
	lcd_t.number5_low=(disp_t.disp_works_hours_time ) /10;
	lcd_t.number5_high =(disp_t.disp_works_hours_time) /10;

	lcd_t.number6_low = (disp_t.disp_works_hours_time) %10;;
	lcd_t.number6_high = (disp_t.disp_works_hours_time ) %10;

	lcd_t.number7_low = (disp_t.disp_works_minutes_time )/10;
	lcd_t.number7_high = (disp_t.disp_works_minutes_time )/10;

	lcd_t.number8_low = (disp_t.disp_works_minutes_time )%10;
	lcd_t.number8_high = (disp_t.disp_works_minutes_time )%10;

	
}
/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
static void Display_Timer_Time_Handler(void)
{

     switch(disp_t.timer_timing_define_flag){

       case timing_success:

	    if( ctl_t.gTimer_ctl_timer_time> 59){ //

		 	 ctl_t.gTimer_ctl_timer_time  =0;
			 ctl_t.gSet_timer_minutes--;
			 pro_t.gTimer_pro_disp_timer=40; //at once be changed display current numbers.
			 
		     if(ctl_t.gSet_timer_minutes < 0){
			 	ctl_t.gSet_timer_minutes =59;
				ctl_t.gSet_timer_hours --;
			 
				if(ctl_t.gSet_timer_hours <0 ){
					ctl_t.gSet_timer_minutes=0;

					pro_t.long_key_flag =0;
					pro_t.gKey_command_tag = power_off_fan_pro;
					pro_t.gPower_On = power_off;   
					SendData_PowerOnOff(0);
					Power_Off_Fun();
					LCD_Backlight_Off();
				

				}
		     }
	   	}

		 lcd_t.number5_low=(ctl_t.gSet_timer_hours  ) /10;
		 lcd_t.number5_high =(ctl_t.gSet_timer_hours ) /10;
		 
		 lcd_t.number6_low = (ctl_t.gSet_timer_hours ) %10;;
		 lcd_t.number6_high = (ctl_t.gSet_timer_hours) %10;
		 //minutes 
		 lcd_t.number7_low = ( ctl_t.gSet_timer_minutes)/10;
		 lcd_t.number7_high = (ctl_t.gSet_timer_minutes)/10;
		 
		 lcd_t.number8_low = ( ctl_t.gSet_timer_minutes)%10;
		 lcd_t.number8_high = ( ctl_t.gSet_timer_minutes )%10;
		    
	   break;

	   case works_time:


	  if(disp_t.gTimer_disp_timer_timing  > 59){ //
        
  		 disp_t.gTimer_disp_timer_timing  =0;
		 disp_t.disp_works_minutes_time--;
	    if( disp_t.disp_works_minutes_time < 0){
			
			disp_t.disp_works_hours_time -- ;
			disp_t.disp_works_minutes_time =59;

			if( disp_t.disp_works_hours_time < 0 ){

			disp_t.disp_works_hours_time =0;
			disp_t.disp_works_minutes_time =0;
			//run_t.display_set_timer_timing=beijing_time;
			disp_t.timer_timing_define_flag = works_time;
	
			ctl_t.gAi_flag = 1;//
			SendData_Set_Command(MODE_AI_NO_BUZZER);

				
		}
	    }

	  }

            
	    lcd_t.number5_low=(disp_t.disp_works_hours_time  ) /10;
		lcd_t.number5_high =(disp_t.disp_works_hours_time ) /10;

		lcd_t.number6_low = (disp_t.disp_works_hours_time  ) %10;;
		lcd_t.number6_high = (disp_t.disp_works_hours_time  ) %10;

		lcd_t.number7_low = ( disp_t.disp_works_minutes_time )/10;
		lcd_t.number7_high = ( disp_t.disp_works_minutes_time)/10;

		lcd_t.number8_low = (disp_t.disp_works_minutes_time)%10;
		lcd_t.number8_high = ( disp_t.disp_works_minutes_time )%10;

	

	 break;

	  }

}
/*************************************************************
 * 
 * Function Name:void DisplaySMG_LED(void)
 * Function :
 * 
*************************************************************/
void Display_Power_On_Works_Time(void)
{
     static uint8_t m,n,p,q;
    if(pro_t.gPower_On==power_on){

		

	    m = (disp_t.disp_works_hours_time/10) ;
		n=	(disp_t.disp_works_hours_time%10); 
		p = (disp_t.disp_works_minutes_time/10);
		q=  (disp_t.disp_works_minutes_time%10);

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

		// DisplayPanel_Ref_Handler();
		

   }

		   
}

/************************************************************************
	*
	*Function Name:void Display_Works_Or_Timer_times_Handler(void)
	*Funcion:
	*Iinput Ref:NO
	*Return Ref:NO
	*
************************************************************************/  
void Display_Works_Or_Timer_times_Handler(void)
{

  static uint8_t disp_ai_mode;
   disp_ai_mode = ai_state();

   switch(disp_ai_mode){ //disp_t.timer_timing_define_flag
         
    case works_time:
        Display_Works_Time_Handler();
	    Timer_Times_Counter_Display();
	   

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
			disp_t.disp_works_minutes_time++;
          
            if(disp_t.disp_works_minutes_time > 59){
				disp_t.disp_works_minutes_time=0;
				disp_t.disp_works_hours_time ++;
			    
				if(disp_t.disp_works_hours_time >23){
					disp_t.disp_works_hours_time=0;

				}

			}
	}
  }
}


/*************************************************************************
	*
	*Functin Name:void Setup_Timer_Times_Donot_Display(void)
	*
	*
	*
	*
*************************************************************************/       
static void Timer_Times_Counter_Display(void)
{

    if(disp_t.timer_timing_define_flag == timing_success){

	if(ctl_t.gTimer_ctl_timer_time  > 59){ //
        
  		 ctl_t.gTimer_ctl_timer_time  =0;
		 ctl_t.gSet_timer_minutes -- ;//disp_t.disp_timer_time_minutes--;
	    if( ctl_t.gSet_timer_minutes  < 0){
		   
		     ctl_t.gSet_timer_hours --;
			 ctl_t.gSet_timer_minutes =59;//disp_t.disp_timer_time_minutes =59;
           
			if(ctl_t.gSet_timer_hours < 0){//if( disp_t.disp_timer_time_hours < 0 ){

	            pro_t.gKey_command_tag = power_off_fan_pro;
				pro_t.gPower_On = power_off;   
				SendData_PowerOnOff(0);
				Power_Off_Fun();
				LCD_Backlight_Off();
				
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

void Display_Voice_Set_Temp_Value(void)
{
    if( ctl_t.gSet_temperature_value < 20){
	     ctl_t.gSet_temperature_value=20;
	}
	
	if( ctl_t.gSet_temperature_value > 40) ctl_t.gSet_temperature_value= 20;



   // decade_temp =   ctl_t.gSet_temperature_value / 10 ;
	//unit_temp =   ctl_t.gSet_temperature_value % 10; //
    
	lcd_t.number1_low= ctl_t.gSet_temperature_value / 10 ;
	lcd_t.number1_high = ctl_t.gSet_temperature_value / 10 ;

	lcd_t.number2_low =  ctl_t.gSet_temperature_value % 10; //
	lcd_t.number2_high =  ctl_t.gSet_temperature_value % 10; //
	
	lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led" timer timing
    pro_t.temperature_set_flag=1;  //set temperature value flag

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


