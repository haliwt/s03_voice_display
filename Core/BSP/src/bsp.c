#include "bsp.h"





PRO_T pro_t;



static void DispPocess_Command_Handler(uint8_t flag_key);


static void power_off_fan_run(void);

static void Ptc_Temperature_Compare_Value(void);



static void Wifi_Link_Fun(void);
static void Mode_Ai_Fun(void);

static void ADD_Key_Fun(void);

static void DEC_Key_Fun(void);




uint8_t relay_id_led ;
uint8_t fun_key_counter,display_keep_temp_value;
uint8_t  disp_keep_temp_value ;
uint8_t fan_runContinue;
uint8_t wifi_link_flag;
uint8_t  voice_enable_flag;


/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- 喂狗 */
    if(pro_t.gTimer_pro_feed_dog > 3){
	   pro_t.gTimer_pro_feed_dog=0;
	   Feed_Dog();

    }
		
	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */
	
    /* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();
	
	/* 例如 uIP 协议，可以插入uip轮询函数 */
	//TOUCH_CapScan();
	
   Voice_Decoder_Handler();
   if(pro_t.decodeFlag ==1){
	  pro_t.decodeFlag =0;
      Decode_Function();
                
   }

}

/*
*********************************************************************************************************
*	函 数 名: void Display_Process_Handler(void)
*	功能说明: App 层 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
*********************************************************************************************************
*/
void Display_Process_Handler(void)
{
  
	DispPocess_Command_Handler(pro_t.gKey_command_tag);
	//USART1_Cmd_Error_Handler();
	 if(v_t.voice_to_buzzer_flag ==1){
	  v_t.voice_to_buzzer_flag =0;
      SendData_Buzzer();
	}
	
	
}
/******************************************************************************
	*
	*Function Name:void DispPocess_Command_Handler(void)
	*Funcion: handle of tall process 
	*Input Ref:
	*Return Ref:
	*
******************************************************************************/
static void DispPocess_Command_Handler(uint8_t flag_key)
{
   //key input run function

   static uint8_t temp1,temp2;
  
  
   static uint16_t counter;

   switch(flag_key){

   case  run_update_data:
      
      
      switch(pro_t.run_process_step){


	 case 0:
		//if(pro_t.ack_power_on_sig ==1){

			pro_t.ack_power_on_sig=0; 
			Lcd_PowerOn_Fun();
			pro_t.run_process_step=1;
			Display_Power_On_Works_Time();


	 break;

	 case 1:  //display works time + "temperature value " + "humidity value"
	      
         pro_t.long_key_flag =0;
	      if(pro_t.gTimer_pro_ms > 20){ //200ms
			 pro_t.gTimer_pro_ms =0;

		     Display_Panel_Action_Handler();
			 
          }
		  
		

		  //display dht11 real temperature and humidity value
		if(pro_t.gTimer_pro_disp_timer > 3){ //37s 
		  	pro_t.gTimer_pro_disp_timer =0;
		    Display_Works_Or_Timer_times_Handler();

		  }

		  Ptc_Temperature_Compare_Value();
		  
	      if(wifi_link_flag ==1){
			  pro_t.run_process_step=4;
          }
		  else
            pro_t.run_process_step=2;
		 
	     
		

	 break;

	

	 case 2: //set timer times pro
    
	 if(pro_t.gTimer_pro_disp_ms > 3 && voice_enable_flag==0){ //40ms
			pro_t.gTimer_pro_disp_ms=0;
			DisplayPanel_Ref_Handler();
       }
	   

	   pro_t.run_process_step=3;


	 break;

	 case 3:
      
	  if(pro_t.set_timer_flag==1){ //
		  pro_t.set_timer_flag++;
             
	      SendData_Time_Data(disp_t.disp_set_timer_timing);
		  
      }

	  pro_t.run_process_step=1;
      break;

	 case 4:
	   if(wifi_state() ==1){
		
		  SendData_Set_Command(WIFI_CONNECT_SUCCESS);
		  wifi_link_flag =0;
        }
		else if(pro_t.ack_wifi_led ==0){
			
		   SendData_Set_Wifi(0x01);

		}
		else{
			wifi_link_flag =0;

        }

	 pro_t.run_process_step=2;

	 break;



	 break;
    }

	case power_off_fan_pro:
		power_off_fan_run();
		
	    

	break;

    default:
    break;
   	}
}

/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
void Power_On_Fun(void)
{
   
  
   ctl_t.gPtc_flag = 1;
   ctl_t.gAi_flag = works_time;
   ctl_t.gPlasma_flag = 1;
   ctl_t.gBug_flag =1;
   fan_runContinue= 2;
	
	ctl_t.gSet_temperature_value =0; //run_t.temperature_set_flag = 0; //WT.EDIT 2023.01.31
    ctl_t.gSet_timer_hours = 0; //run_t.setup_temperature_value=0; // //WT.EDIT 2023.01.31
    ctl_t.gFan_speed_value =100; //run_t.disp_wind_speed_grade =100;
	

     pro_t.temperature_set_flag = 0;

	  //timer timing
	 ctl_t.gSet_timer_hours =0;
	 ctl_t.gSet_timer_minutes =0;

      //display work time is begin form "0"
     disp_t.timer_timing_define_flag = works_time;
     disp_t.gTimer_disp_timer_timing=0; //works times  clear zero.
	 disp_t.disp_works_hours_time =0;
	 disp_t.disp_works_minutes_time=0;
    
	 
	 lcd_t.number5_low=(disp_t.disp_works_hours_time ) /10;
     lcd_t.number5_high =(disp_t.disp_works_hours_time) /10;

	 lcd_t.number6_low = (disp_t.disp_works_hours_time ) %10;;
	 lcd_t.number6_high = (disp_t.disp_works_hours_time ) %10;
     
     lcd_t.number7_low = (disp_t.disp_works_minutes_time )/10;
	 lcd_t.number7_high = (disp_t.disp_works_minutes_time )/10;

	 lcd_t.number8_low = (disp_t.disp_works_minutes_time )%10;
	 lcd_t.number8_high = (disp_t.disp_works_minutes_time )%10;


}
     


void Power_Off_Fun(void)
{
	 		 
     
	SendData_PowerOnOff(0);

	pro_t.temperature_set_flag = 0;

    pro_t.wifi_led_fast_blink_flag=0;
	pro_t.gTimer_mode_flag = 0;

    ctl_t.gSet_timer_hours =0;

	ctl_t.ptc_warning = 0;
	ctl_t.fan_warning=0;

	if(fan_runContinue==2){
		fan_runContinue=1;
		pro_t.gTimer_pro_fan =0;

	}

}
void power_off_fan_run(void)
{
	

	if(pro_t.ack_power_off_sig ==0){
        SendData_PowerOnOff(0);
	

	}

	Breath_Led();
	
	if(fan_runContinue == 1){
	if(pro_t.gTimer_pro_fan < 61){
		LED_MODEL_OFF();
		POWER_ON_LED();
		LCD_Display_Wind_Icon_Handler();
	}
	else {
	    fan_runContinue  =0;
		Lcd_PowerOff_Fun();

	}

	}

}

/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void Mode_Ai_Fun(void)
{
	
	if(pro_t.gPower_On ==power_on){
		 //SendData_Buzzer();
			 
	   if(ctl_t.ptc_warning ==0 && ctl_t.fan_warning ==0){

	          if(ai_state()==works_time){ //be chaned ai mode 
			   //isp_t.disp_timer_or_works_timing = timer_time;
				ctl_t.gAi_flag = timer_time;
				SendData_Set_Wifi(MODE_TIMER);
				
				   
				
	           }
			   else{
				 ctl_t.gAi_flag =works_time; //no_AI model
				  SendData_Set_Wifi(MODE_AI);
				 
					
				}
				
				
	  } 	
	}
		 
}
/************************************************************************
	*
	*Function Name: static void Mode_Long_Key_Fun(void) 
	*Function : set timer timing is enable 
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
void Mode_Long_Key_Fun(void)  //MODE_KEY_LONG_TIME_KEY://case model_long_key:
{
	  if(pro_t.gPower_On ==power_on){
	   if(ctl_t.fan_warning ==0 && ctl_t.ptc_warning ==0){
	  	
		   
		   ctl_t.gAi_flag =timer_time;

		   pro_t.gTimer_mode_flag=1; //set timer timing enable,
		 
		   pro_t.gTimer_key_timing=0; //按键退出的限制，4秒以内
		
           SendData_Set_Wifi(MODE_TIMER);
		   
		   
	  	 }
        }
}
/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void ADD_Key_Fun(void)
{
 
    uint8_t  temp_bit_1_hours,temp_bit_2_hours,temp_bit_2_minute,temp_bit_1_minute;

	 if(pro_t.gPower_On ==power_on){

		   if(ctl_t.ptc_warning ==0 && ctl_t.fan_warning ==0){

			SendData_Buzzer();
		
			switch(pro_t.gTimer_mode_flag){

			case set_temperature: //set temperature value add number
      
		
				 ctl_t.gSet_temperature_value ++;
	            if( ctl_t.gSet_temperature_value < 20){
				     ctl_t.gSet_temperature_value=20;
				}
				
				if( ctl_t.gSet_temperature_value > 40) ctl_t.gSet_temperature_value= 20;

			
            
			   // decade_temp =   ctl_t.gSet_temperature_value / 10 ;
				//unit_temp =   ctl_t.gSet_temperature_value % 10; //
                
				lcd_t.number1_low=ctl_t.gSet_temperature_value / 10 ;
				lcd_t.number1_high =ctl_t.gSet_temperature_value / 10 ;

				lcd_t.number2_low = ctl_t.gSet_temperature_value % 10; //
				lcd_t.number2_high = ctl_t.gSet_temperature_value % 10; //
				
				lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led" timer timing
                pro_t.temperature_set_flag=1;  //set temperature value flag
                DisplayPanel_Ref_Handler();
				
               break;

			   case set_timer_timing:
				    
					pro_t.gTimer_key_timing =0;
                    disp_t.set_timer_timing_value_chaned_flag++;
			   		if(disp_t.set_timer_timing_value_chaned_flag > 254 ) disp_t.set_timer_timing_value_chaned_flag=0;
					
					ctl_t.gSet_timer_hours ++ ;//disp_t.disp_timer_time_hours++ ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes + 60;
				    if(ctl_t.gSet_timer_hours  > 24){ //if(pro_t.dispTime_minutes > 59){

		                 ctl_t.gSet_timer_hours =0;//pro_t.dispTime_hours =0;
		                

					}
				
                    temp_bit_2_hours = ctl_t.gSet_timer_hours  /10 ;
					temp_bit_1_hours = ctl_t.gSet_timer_hours  %10;
                 
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

					DisplayPanel_Ref_Handler();
				break;
				}	
			}
        }
       //  DisplayPanel_Ref_Handler();
}
/************************************************************************
	*
	*Function Name: static void DEC_Key_Fun(void)
	*Function : KEY OF decrease
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void DEC_Key_Fun(void)
{

    uint8_t  decade_temp,unit_temp,temp_bit_1_hours,temp_bit_2_hours;
	uint8_t temp_bit_2_minute=0,temp_bit_1_minute=0;
	if(pro_t.gPower_On ==power_on){
	   	if(ctl_t.ptc_warning ==0 && ctl_t.fan_warning ==0){

			SendData_Buzzer();
	   	
	     switch(pro_t.gTimer_mode_flag){

		   case set_temperature:  //default tempearture value 
	    
			 ctl_t.gSet_temperature_value--;
			if( ctl_t.gSet_temperature_value<20)  ctl_t.gSet_temperature_value=40;
	        if( ctl_t.gSet_temperature_value >40) ctl_t.gSet_temperature_value=40;

	

	        decade_temp =   ctl_t.gSet_temperature_value / 10;
			unit_temp =   ctl_t.gSet_temperature_value % 10; //
      
			lcd_t.number1_low=decade_temp;
			lcd_t.number1_high =decade_temp;

			lcd_t.number2_low = unit_temp;
			lcd_t.number2_high = unit_temp;

			lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led"
			pro_t.temperature_set_flag=1;  //set temperature value flag
			DisplayPanel_Ref_Handler();
		    break;

			case set_timer_timing: //timer timing set "decrease -down"
	    
	
				pro_t.gTimer_key_timing =0;
                disp_t.set_timer_timing_value_chaned_flag--;
			    if(disp_t.set_timer_timing_value_chaned_flag==0)disp_t.set_timer_timing_value_chaned_flag=255;
				
				ctl_t.gSet_timer_hours --;//disp_t.disp_timer_time_hours -- ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes - 1;
				if(ctl_t.gSet_timer_hours  < 0){//if(pro_t.dispTime_minutes < 0){

				    ctl_t.gSet_timer_hours  =24;//pro_t.dispTime_hours --;
					
					
				}
				temp_bit_2_hours = ctl_t.gSet_timer_hours  /10 ;
				temp_bit_1_hours = ctl_t.gSet_timer_hours  %10;

				temp_bit_2_minute=0;
				temp_bit_1_minute=0;


				lcd_t.number5_low=temp_bit_2_hours;
				lcd_t.number5_high =temp_bit_2_hours;

				lcd_t.number6_low = temp_bit_1_hours;
				lcd_t.number6_high = temp_bit_1_hours;

				lcd_t.number7_low=temp_bit_2_minute;
				lcd_t.number7_high =temp_bit_2_minute;

				lcd_t.number8_low = temp_bit_1_minute;
				lcd_t.number8_high = temp_bit_1_minute;
				DisplayPanel_Ref_Handler();

             break;

	    	}
	   	  }
		}

  //    DisplayPanel_Ref_Handler();
     



}



/**********************************************************************************************************
    **
    *Function Name:static void Ptc_Temperature_Compare_Value(void)
    *Function : 
    *Input Ref:lightNum--LED ,filterNum -filter number, unionNum - smart menu number
    *Return Ref:NO
    *
*********************************************************************************************************/
static void Ptc_Temperature_Compare_Value(void)
{
      //set up temparature value 
      switch(ctl_t.gSet_temperature_value_flag){

      case 1:
	  	//send temp value to smart phone 
	  	if(ctl_t.set_temp_has_been_flag==1){
			ctl_t.set_temp_has_been_flag =0;
			SendData_Temp_Data(ctl_t.gSet_temperature_value);

		}
	    if(pro_t.gTimer_pro_temp_delay> 61 && ctl_t.ptc_warning==0){
               pro_t.gTimer_pro_temp_delay =0;
		 
		  
		  if(smartphone_set_temp_value() <= disp_dht11_temperature_value()|| disp_dht11_temperature_value() >40){//envirment temperature
	  
				ctl_t.gPtc_flag = 0 ;//run_t.gDry = 0;
			    SendData_Set_Command(DRY_OFF_NO_BUZZER);
                 

            }
			else if((smartphone_set_temp_value() -3) > disp_dht11_temperature_value()||  disp_dht11_temperature_value() <38){
	  
		         ctl_t.gPtc_flag = 1;//run_t.gDry = 1;
			     SendData_Set_Command(DRY_ON_NO_BUZZER);
                    
		         }
				 
	   }
       break;


       case 0:
           
           if(pro_t.gTimer_pro_temp_delay > 66  && ctl_t.ptc_warning==0 ){ //WT.EDIT 2023.07.27 over 40 degree shut of ptc off
                pro_t.gTimer_pro_temp_delay=0;

            if(smartphone_set_temp_value() >19 && smartphone_set_temp_value() < 41){
           
               if(disp_dht11_temperature_value() >40 || smartphone_set_temp_value() <= disp_dht11_temperature_value()){//envirment temperature
               
                 ctl_t.gPtc_flag = 0;
                 SendData_Set_Command(DRY_OFF_NO_BUZZER);
                
           
               }
               else if(disp_dht11_temperature_value() <38 || (smartphone_set_temp_value() -2) > disp_dht11_temperature_value() ){
               
                  ctl_t.gPtc_flag = 1;
                  SendData_Set_Command(DRY_ON_NO_BUZZER);

				  
                }
                          

            }
            else{
                 if(disp_dht11_temperature_value() >40){//envirment temperature
               
                 ctl_t.gPtc_flag  = 0;
                 SendData_Set_Command(DRY_OFF_NO_BUZZER);
                
           
               }
               else if(disp_dht11_temperature_value() <38){
               
                  ctl_t.gPtc_flag = 1;
                  SendData_Set_Command(DRY_ON_NO_BUZZER);
                 
                }
                          



            }
          }

        break;
        
     }

}


void Power_Key_Detected(void)
{
    static uint8_t power_flag;
	if(POWER_KEY_StateRead()==KEY_DOWN && pro_t.long_key_flag ==0){

	       power_flag = power_flag ^ 0x01;

	      if(power_flag ==1){
		  	 pro_t.gKey_command_tag = run_update_data;
			 pro_t.gPower_On = power_on;   
            pro_t.long_key_flag =0;
            pro_t.run_process_step=0;
			SendData_PowerOnOff(1);
		    Power_On_Fun();
			LCD_Backlight_On();
			//Key_Sound();


		  }
		  else{

	           pro_t.long_key_flag =0;
			   pro_t.gKey_command_tag = power_off_fan_pro;
			   pro_t.gPower_On = power_off;   
	           SendData_PowerOnOff(0);
	           Power_Off_Fun();
			   LCD_Backlight_Off();
		      // Key_Sound();
			   pro_t.run_process_step=0xff;
			  
			  
           }


	   }

	if(POWER_KEY_StateRead()==KEY_POWER_LONG_DOWN && pro_t.long_key_flag ==1){

        SendData_Set_Wifi(0x01);

	    //Key_Sound();
        pro_t.wifi_led_fast_blink_flag=1;
		//pro_t.long_key_flag =0;


	}


}


void Mode_Key_Detected(void)
{
	if(MODE_KEY_StateRead() == KEY_DOWN && pro_t.long_key_flag ==0){

		if(ai_state() == works_time ){
		  pro_t.long_key_flag =0;
		
		  ctl_t.gAi_flag = timer_time;
		  SendData_Set_Wifi(MODE_AI);
		  pro_t.gTimer_pro_disp_timer = 40; //at once be changed ai or no_ai timing.
		 //  Key_Sound();
		 
		
		 }
         else{
		  	 pro_t.long_key_flag =0;
			  ctl_t.gAi_flag = works_time;
			  SendData_Set_Wifi(MODE_TIMER);
			//  Key_Sound();
			 pro_t.gTimer_pro_disp_timer = 40;//at once be changed ai or no_ai timing.
          }



	} 

	if(MODE_KEY_StateRead()==KEY_MODE_LONG_DOWN && pro_t.long_key_flag ==1){

       Mode_Long_Key_Fun();


	}


}


void ADD_Key_Detected(void)
{
	if(ADD_KEY_StateRead()==KEY_DOWN){

		//Key_Sound();
		
		ADD_Key_Fun();
    }


}
void DEC_Key_Detected(void)
{
	 if(DEC_KEY_StateRead()==KEY_DOWN){

		 DEC_Key_Fun();
	 }

}



