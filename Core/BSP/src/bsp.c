#include "bsp.h"





PRO_T pro_t;


static void Process_Key_Handler(uint8_t keylabel);
static void DispPocess_Command_Handler(void);
static void Power_On_Fun(void);
static void Power_Off_Fun(void);
static void Wifi_Link_Fun(void);
static void Mode_Ai_Fun(void);

static void ADD_Key_Fun(void);

static void DEC_Key_Fun(void);
static void Mode_Long_Key_Fun(void);









uint8_t relay_id_led ;
uint8_t fun_key_counter,display_keep_temp_value;
uint8_t  disp_keep_temp_value ;
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
	


}
/*
*********************************************************************************************************
*	函 数 名: Key_Handler(uint8_t key_value)
*	功能说明: 中间层 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
*********************************************************************************************************
*/
void Key_Handler(uint8_t key_value)
{
  
       switch(key_value){

	   case power_off: //power off
	       pro_t.gKey_command_tag = power_off;
           SendData_PowerOnOff(0);
           Power_Off_Fun();
       key_value =0xff;
	   break;

		case power_on: //power on
       
            pro_t.gKey_command_tag = power_on;
			SendData_PowerOnOff(1);
		    Power_On_Fun();
            key_value =0xff;     
        break;

		case mode_ai:
		  pro_t.gKey_command_tag = mode_ai;
		  key_value =0xff;
		break;

		case mode_no_ai:
		  pro_t.gKey_command_tag = mode_no_ai;
		  key_value =0xff;
		break;

		case add_key:
			
		 key_value =0xff;
        break;

		case dec_key:
         key_value =0xff;
		break;

		default:
		break;

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
     if(pro_t.decodeFlag ==1){
		  pro_t.decodeFlag =0;
          Decode_Function();
                
     }
	
  // Process_Key_Handler(pro_t.gKey_command_tag);

	DispPocess_Command_Handler();
	USART1_Cmd_Error_Handler();
	

}

/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void Power_On_Fun(void)
{
  
  
    
     
}

static void Power_Off_Fun(void)
{
	  pro_t.wifi_receive_power_on_flag =0;
           Power_Off_Fun();
            if(pro_t.first_power_on_flag !=5){
               
            
            if(power_off_thefirst==0){
               power_off_thefirst++;
               
               pro_t.gFan_RunContinue = 0;
               
            }
            else if(pro_t.wifi_send_buzzer_sound != WIFI_POWER_OFF_ITEM){
       
                SendData_PowerOnOff(0);
      
               
            }
            if(power_off!=0){
                pro_t.gFan_RunContinue=1;
                pro_t.gTimer_first_power_on_counter=0;

             }
            pro_t.power_key_interrupt_counter=0;//WT.EDIT 2023.07.25
			pro_t.gPower_On = RUN_POWER_OFF;
          
			pro_t.temperature_set_flag = 0;
      
			pro_t.wifi_set_temperature_value_flag=0;
		    pro_t.gTimer_set_temp_times=0; //conflict with send temperatur value 
            pro_t.wifi_led_fast_blink_flag=0;
            pro_t.Timer_mode_flag = 0;
			pro_t.works_counter_time_value=0;
			pro_t.panel_key_setup_timer_flag=0;
            pro_t.setup_temperature_value=0;
		    pro_t.timer_time_hours =0;
			pro_t.timer_time_minutes =0;
			pro_t.timer_timing_define_flag = timing_not_definition;

			pro_t.ptc_too_hot_flag = 0;
			pro_t.ptc_warning = 0;
      
       
			
			pro_t.fan_warning=0;
            pro_t.gKey_command_tag = KEY_NULL;
            pro_t.key_add_dec_spec_flag=0;
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
static void Wifi_Link_Fun(void)
{
	if(pro_t.gPower_On ==1){
            send_times++;
           if(pro_t.fan_warning ==0 && pro_t.ptc_warning ==0){
            if(wifi_long_key!=send_times){
                wifi_long_key=send_times;
                
        	    SendData_Set_Wifi(0x01);
                HAL_Delay(1);
                pro_t.gTimer_set_temp_times=0; //conflict with send temperatur value 
                pro_t.gTimer_wifi_connect_counter=0;
                pro_t.gTimer_wifi_led_blink=0;
                 pro_t.wifi_connect_success_flag =0;
                pro_t.wifi_receive_led_fast_led_flag=0; //adjust if mainboard receive of connect wifi of signal
                pro_t.wifi_led_fast_blink_flag=1;
                pro_t.key_add_dec_spec_flag=0;
                
            }
            
            if(pro_t.wifi_receive_led_fast_led_flag==1){
              pro_t.gKey_command_tag = KEY_NULL;//WT.EDIT 2023.07.27
            }
            else{
               pro_t.gKey_command_tag =LINK_WIFI_ITEM;
               SendData_Set_Wifi(0x01);
               HAL_Delay(1);
             


            }
            }
           }
           else{

            pro_t.gKey_command_tag = KEY_NULL;
            pro_t.key_add_dec_spec_flag=0;
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
	
	if(pro_t.gPower_On ==1){
				//SendData_Buzzer();
			 
			   if(pro_t.ptc_warning ==0 && pro_t.fan_warning ==0){
			   if(pro_t.display_set_timer_timing == beijing_time){
			
				   //timer time + don't has ai item
				   pro_t.display_set_timer_timing = timer_time;
				   pro_t.gModel=2; //Timer time Model
				  SendData_Set_Wifi(MODE_TIMER);
				  HAL_Delay(10);
				   
				}
				else if(pro_t.display_set_timer_timing == timer_time){
					//beijing time + ai item
					pro_t.display_set_timer_timing = beijing_time;
				 
				   pro_t.gModel=1; //AI model
				  SendData_Set_Wifi(MODE_AI);
				  HAL_Delay(10);
					
				}
				
				
			  } 	
			 }
		  pro_t.gKey_command_tag = KEY_NULL;
		  pro_t.key_add_dec_spec_flag=0;
}
/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void Mode_Long_Key_Fun(void)  //MODE_KEY_LONG_TIME_KEY://case model_long_key:
{
	  if(pro_t.gPower_On ==1){
	   if(pro_t.fan_warning ==0 && pro_t.ptc_warning ==0){
	  	
		  
			pro_t.gModel=2;
		   pro_t.setup_timer_timing_item=1;//pro_t.gModel =2;
		   pro_t.display_set_timer_timing  =timer_time;
		   pro_t.gTimer_key_timing=0;
		
           display_model =1;
		   pro_t.Timer_mode_flag=1;
		   
		   
		   SendData_Set_Wifi(MODE_TIMER);
		   
		   
	  	 }
        }
		pro_t.gKey_command_tag = KEY_NULL;


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
	 if(pro_t.gPower_On ==1){

		   if(pro_t.ptc_warning ==0 && pro_t.fan_warning ==0){
		
			 SendData_Buzzer();
             HAL_Delay(20);
		

		    switch(pro_t.setup_timer_timing_item){

			case 0: //set temperature value add number
      
				pro_t.wifi_set_temperature_value_flag =0;
				pro_t.wifi_set_temperature ++;
	            if(pro_t.wifi_set_temperature < 20){
				    pro_t.wifi_set_temperature=20;
				}
				
				if(pro_t.wifi_set_temperature > 40)pro_t.wifi_set_temperature= 20;

				if(power_on_fisrt_flag ==0){
				     power_on_fisrt_flag ++;
			     	pro_t.wifi_set_temperature =40;


			      }
            
			    decade_temp =  pro_t.wifi_set_temperature / 10 ;
				unit_temp =  pro_t.wifi_set_temperature % 10; //
                
				lcd_t.number1_low=decade_temp;
				lcd_t.number1_high =decade_temp;

				lcd_t.number2_low = unit_temp;
				lcd_t.number2_high = unit_temp;

				pro_t.panel_key_setup_timer_flag = 1;
                
               pro_t.key_add_dec_spec_flag=0;
					
			
			   break;

			   case 1:
				    display_model++;
					pro_t.gTimer_key_timing =0;
                 
					pro_t.timer_time_hours++ ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes + 60;
				    if(pro_t.timer_time_hours > 24){ //if(pro_t.dispTime_minutes > 59){

		                 pro_t.timer_time_hours=0;//pro_t.dispTime_hours =0;
		                

					}
				
                  
					temp_bit_2_hours = pro_t.timer_time_hours /10 ;
					temp_bit_1_hours = pro_t.timer_time_hours %10;
                    HAL_Delay(20);
					pro_t.timer_time_minutes  =0;

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

				pro_t.key_add_dec_spec_flag=0;
				break;
				}	
			
		     }
            }
         

		 pro_t.gKey_command_tag = KEY_NULL;
          pro_t.key_add_dec_spec_flag=0;


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
	if(pro_t.gPower_On ==1){
	   	if(pro_t.ptc_warning ==0 && pro_t.fan_warning ==0){
	   	SendData_Buzzer();
        HAL_Delay(20);
	     switch(pro_t.setup_timer_timing_item){

		   case 0: 
	
	        pro_t.wifi_set_temperature_value_flag =0;
			pro_t.wifi_set_temperature--;
			if(pro_t.wifi_set_temperature<20) pro_t.wifi_set_temperature=40;
	        if(pro_t.wifi_set_temperature >40)pro_t.wifi_set_temperature=40;

			if(power_on_fisrt_flag ==0){
				power_on_fisrt_flag ++;
			  pro_t.wifi_set_temperature =40;


			}

	        decade_temp =  pro_t.wifi_set_temperature / 10;
			unit_temp =  pro_t.wifi_set_temperature % 10; //
         //    HAL_Delay(5);
			lcd_t.number1_low=decade_temp;
			lcd_t.number1_high =decade_temp;

			lcd_t.number2_low = unit_temp;
			lcd_t.number2_high = unit_temp;
			
			pro_t.panel_key_setup_timer_flag = 1;
	    	
            pro_t.key_add_dec_spec_flag=0;
		    break;

			case 1:
	    
			    display_model++;
				pro_t.gTimer_key_timing =0;
           
				pro_t.timer_time_hours -- ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes - 1;
				if(pro_t.timer_time_hours < 0){//if(pro_t.dispTime_minutes < 0){

				    pro_t.timer_time_hours =24;//pro_t.dispTime_hours --;
					
					
				}
				   // temp_bit_2_minute = pro_t.timer_time_hours /10 ;
					//temp_bit_1_minute = pro_t.timer_time_hours %10;
               
					temp_bit_2_hours = pro_t.timer_time_hours /10 ;
					temp_bit_1_hours = pro_t.timer_time_hours  %10;
                    HAL_Delay(20);
					pro_t.timer_time_minutes  =0;

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
                    pro_t.key_add_dec_spec_flag=0;

             break;

	    	}
	   	  }
		}

      pro_t.gKey_command_tag = KEY_NULL;
      pro_t.key_add_dec_spec_flag=0;



}

/******************************************************************************
	*
	*Function Name:void DispPocess_Command_Handler(void)
	*Funcion: handle of tall process 
	*Input Ref:
	*Return Ref:
	*
******************************************************************************/
static void DispPocess_Command_Handler(void)
{
   //key input run function

   static uint8_t temp1,temp2,key_set_temp_flag, link_wifi_success,power_off;
   static uint8_t power_on_fisrt_send_temperature_value, works_break_flag;

   switch(pro_t.gPower_On){

   case RUN_POWER_ON:
       power_off=0;
     
       //pro_t.first_power_on_flag=3;
     

	  if(pro_t.wifi_receive_power_on_flag==0){
     
	   	SendData_PowerOnOff(1);
    	HAL_Delay(1);
          
      }
        Lcd_PowerOn_Fun();
//        if(pro_t.fan_warning ==0 && pro_t.ptc_warning ==0){
//	        Timing_Handler();
//         }
//	    DisplayPanel_Ref_Handler();

	//send timer timing value to main board 
	  if(pro_t.first_power_on_flag==5){
          pro_t.first_power_on_flag++; 
	         Timing_Handler();
	         DisplayPanel_Ref_Handler();
             HAL_Delay(5);
          

      }
      if(pro_t.setup_timer_flag==1){
		   pro_t.setup_timer_flag++;
           
	       SendData_Time_Data(pro_t.dispTime_hours);
		    HAL_Delay(1);


	  }
        
		
       //Enable digital "1,2" -> blink LED
       //Enable digital "1,2" -> blink LED
	   if(pro_t.panel_key_setup_timer_flag==1){
           pro_t.panel_key_setup_timer_flag=0;
		   key_set_temp_flag =1;
		  pro_t.setup_temperature_value=1;
		   pro_t.gTimer_numbers_one_two_blink=0;
	     	  
	   }

	   //digital "1,2" ->display is dhtd11 real temperature value
	   if(pro_t.setup_temperature_value ==0 && key_set_temp_flag ==1 ){
	   	    key_set_temp_flag = 0;

	        temp1 = pro_t.gReal_humtemp[1]/10 %10;  // temperature
            temp2 = pro_t.gReal_humtemp[1]%10;

		    lcd_t.number1_low=temp1;
			lcd_t.number1_high =temp1;

			lcd_t.number2_low = temp2;
			lcd_t.number2_high = temp2;
		
			
		}
	   
	 Ptc_Temperature_Compare_Value();
	 
   
   //receive from mainboard data 
   //displayPannel set temperature vale to main board value 
    if(pro_t.gTimer_set_temp_times >9){ // set up temperature value [20,40]
	     pro_t.gTimer_set_temp_times=0;
		 if(pro_t.wifi_set_temperature==0)pro_t.wifi_set_temperature=20;
		 if(power_on_fisrt_send_temperature_value ==0){
		       power_on_fisrt_send_temperature_value++;
		     pro_t.wifi_set_temperature=40;


		 }
		  if(pro_t.wifi_set_temperature_value_flag != 1){
		  	  SendData_Temp_Data(pro_t.wifi_set_temperature);
               HAL_Delay(5);
	     }
    }


     if(pro_t.wifi_connect_success_flag ==1 && link_wifi_success==0 ){
            link_wifi_success++;
            pro_t.wifi_receive_led_fast_led_flag=0;
            SendData_Set_Command(WIFI_CONNECT_SUCCESS);

     }

     if(pro_t.gTimer_first_power_on_counter > 7 && pro_t.power_key_interrupt_counter==1){
        pro_t.gTimer_first_power_on_counter=0;
      
      if(pro_t.power_key_interrupt_counter==1)pro_t.power_key_interrupt_counter++;

     }

     break;

	 case RUN_POWER_OFF:
         pro_t.step_run_power_on_tag=0;
	     pro_t.step_run_power_on_tag =0;
         pro_t.wifi_receive_power_on_flag=0;

	    if(pro_t.wifi_receive_power_off_flag==0){
           
  
            SendData_PowerOnOff(0);
    		HAL_Delay(10);

         }

   	     Breath_Led();
         beijing_time_fun();
         if(pro_t.gFan_RunContinue == 1){
           if(pro_t.fan_off_60s < 61){
		      LED_MODEL_OFF();
			  POWER_ON_LED();
		      LCD_Display_Wind_Icon_Handler();
           	}
		   else {
               
               
               pro_t.gFan_RunContinue =0;
			   Lcd_PowerOff_Fun();

		   }

         }
        

    break;
   	}
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
      switch(run_t.temperature_set_flag ){

      case 1:
	    if(run_t.gTimer_temp_delay > 61 && run_t.ptc_warning==0){
               run_t.gTimer_temp_delay =0;
		 
		  
		  if(run_t.wifi_set_temperature <= run_t.gReal_humtemp[1] || run_t.gReal_humtemp[1] >40){//envirment temperature
	  
				run_t.gDry = 0;
			    SendData_Set_Command(DRY_OFF_NO_BUZZER);
                 HAL_Delay(5);

            }
			else if((run_t.wifi_set_temperature -3) > run_t.gReal_humtemp[1] ||  run_t.gReal_humtemp[1] <38){
	  
		         run_t.gDry = 1;
			     SendData_Set_Command(DRY_ON_NO_BUZZER);
                     HAL_Delay(1);
		         }
				 
	   }
       break;


       case 0:
           
           if(run_t.gTimer_detected_ptc_temp_value > 66  && run_t.ptc_warning==0 ){ //WT.EDIT 2023.07.27 over 40 degree shut of ptc off
                run_t.gTimer_detected_ptc_temp_value=0;

            if(run_t.wifi_set_temperature >19 && run_t.wifi_set_temperature < 41){
           
               if(run_t.gReal_humtemp[1] >40 || run_t.wifi_set_temperature <= run_t.gReal_humtemp[1]){//envirment temperature
               
                 run_t.gDry = 0;
                 SendData_Set_Command(DRY_OFF_NO_BUZZER);
                 HAL_Delay(5);
           
               }
               else if(run_t.gReal_humtemp[1] <38 || (run_t.wifi_set_temperature -2) > run_t.gReal_humtemp[1] ){
               
                  run_t.gDry = 1;
                  SendData_Set_Command(DRY_ON_NO_BUZZER);
                  HAL_Delay(1);
                }
                          

            }
            else{
                 if(run_t.gReal_humtemp[1] >40){//envirment temperature
               
                 run_t.gDry = 0;
                 SendData_Set_Command(DRY_OFF_NO_BUZZER);
                 HAL_Delay(5);
           
               }
               else if(run_t.gReal_humtemp[1] <38){
               
                  run_t.gDry = 1;
                  SendData_Set_Command(DRY_ON_NO_BUZZER);
                  HAL_Delay(1);
                }
                          



            }
          }

        break;
        
     }

}


