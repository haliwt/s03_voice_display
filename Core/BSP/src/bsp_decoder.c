#include "bsp_decoder.h"
#include "bsp.h"

DECODER_T decoder_t;

static void Receive_MainBoard_Data_Handler(uint8_t cmd);


/**********************************************************************************************************
**
*Function Name:static void notifyStatusToHost(uint8_t lightNum,uint8_t filterNum,uint8_t unionNum)
*Function : 
*Input Ref:lightNum--LED ,filterNum -filter number, unionNum - smart menu number
*Return Ref:NO
*
*********************************************************************************************************/
void Decode_Function(void)
{
   
   Receive_MainBoard_Data_Handler(pro_t.single_data);
    
}

/**********************************************************************************************************
	**
	*Function Name:void Receive_MainBoard_Data_Handler(uint8_t cmd)
	*Function : mainboard of command 
	*Input Ref:
	*Return Ref:NO
	*
*********************************************************************************************************/
void Receive_MainBoard_Data_Handler(uint8_t cmd)
{
    static uint8_t temperature_decade, temperature_unit;
	static uint8_t hum1,hum2,temp1,temp2; 
	
    switch(cmd){


	 case WIFI_CMD://5
	 	 Receive_Wifi_Cmd(decoder_t.d_cmd[0]);
	 break;

	 
	 case WIFI_REAL_TEMP: //4//set temperature value
	       if(power_state() ==1){
		   	   
            temperature_decade= temperature_value() /10 ;
            temperature_unit = temperature_value() %10;

            lcd_t.number1_high = temperature_decade;
            lcd_t.number1_low = temperature_decade;


            lcd_t.number2_high =  temperature_unit;
            lcd_t.number2_low = temperature_unit;

	      }

	 break;

	 case PANEL_DATA://1
	   
        if(power_state() ==1){
        hum1 =  humidity_value()/10 ;  //Humidity 
        hum2 =  humidity_value()%10;
        
        temp1 = humidity_value()/10 ;  // temperature
        temp2 = humidity_value()%10;
       
         //temperature 
		 lcd_t.number1_high = temp1;
		 lcd_t.number1_low = temp1;

		  lcd_t.number2_high = temp2;
		 lcd_t.number2_low = temp2;

		 //humidity
		 
		 lcd_t.number3_high = hum1;
		 lcd_t.number3_low = hum1;
		 
		 lcd_t.number4_high = hum2;
		 lcd_t.number4_low = hum2;

		 DisplayPanel_Ref_Handler();
        }

      break;

       case WIFI_BEIJING_TIME: //7//run_t.wifi_connect_success_flag
         if(power_state() ==1){
           if(run_t.timer_timing_define_flag==timing_not_definition ){
		   	
			 lcd_t.number5_low=beijing_hours_time()/10;
	         lcd_t.number5_high =beijing_hours_time() /10;
        
			 lcd_t.number6_low = beijing_hours_time() %10;
			 lcd_t.number6_high = beijing_hours_time() %10;
	        


			lcd_t.number7_low = beijing_minutes_time()/10;
			lcd_t.number7_high = beijing_minutes_time()/10;
            
			lcd_t.number8_low = beijing_minutes_time()%10;
			lcd_t.number8_high = beijing_minutes_time()%10;
            
	        DisplayPanel_Ref_Handler();

			lcd_t.display_beijing_time_flag = 1;
	      }
         }
		    
        
 
      break;

      case WIFI_SET_TIMING://10
        
        if(run_t.dispTime_hours !=0){
           
             lcd_t.number5_low=(run_t.dispTime_hours ) /10;
	         lcd_t.number5_high =(run_t.dispTime_hours) /10;
         
			 lcd_t.number6_low = (run_t.dispTime_hours ) %10;;
			 lcd_t.number6_high = (run_t.dispTime_hours ) %10;
	    


			lcd_t.number7_low = run_t.dispTime_minutes ;
			lcd_t.number7_high = run_t.dispTime_minutes ;

			lcd_t.number8_low = run_t.dispTime_minutes ;
			lcd_t.number8_high = run_t.dispTime_minutes;
            
        }

      break;

	  case WIFI_SET_TEMPERATURE://11

	  		if(power_state() ==1){

			run_t.panel_key_setup_timer_flag=1;

		  
			  run_t.wifi_set_temperature_value_flag =1;

			  run_t.wifi_set_temperature = run_t.wifi_set_oneself_temperature;

		      temperature_decade=  run_t.wifi_set_temperature /10 ;
			  temperature_unit =  run_t.wifi_set_temperature %10;
		      // HAL_Delay(5);
	         lcd_t.number1_high = temperature_decade;
			 lcd_t.number1_low = temperature_decade;

			 
		    lcd_t.number2_high =  temperature_unit;
			lcd_t.number2_low = temperature_unit;

			
			run_t.gTimer_numbers_one_two_blink=0;
	      }


	  break;



      default:
        
      break;

	}


}
/**********************************************************************
*
*Functin Name: void Receive_ManiBoard_Cmd(uint8_t cmd)
*Function :  wifi recieve data
*Input Ref:  receive wifi send order
*Return Ref: NO
*
**********************************************************************/
void Receive_Wifi_Cmd(uint8_t cmd)
{
	switch(cmd){


		   case WIFI_POWER_ON: //turn on 
		 	
           
              run_t.wifi_send_buzzer_sound = WIFI_POWER_ON_ITEM;
	         
		      run_t.wifi_connect_success_flag =1;
			  run_t.gPower_On = 1;
			  
				run_t.gModel =1;
				run_t.display_set_timer_timing=beijing_time ;
				run_t.gKey_command_tag = POWER_ON_ITEM;
                run_t.key_add_dec_spec_flag=1;
			  cmd=0xff;

	         break;

			 case WIFI_POWER_OFF: //turn off 
                
			   run_t.wifi_connect_success_flag =1;
			   run_t.wifi_send_buzzer_sound = WIFI_POWER_OFF_ITEM;
				
			   run_t.gKey_command_tag=POWER_OFF_ITEM;
               run_t.key_add_dec_spec_flag=1;
				
              cmd=0xff;

			 break;

			case WIFI_MODE_1: //AI Model
                if(run_t.gPower_On==1){
			
				
					run_t.display_set_timer_timing = beijing_time;
					run_t.gModel=1;


		    	}
			break;

			 case WIFI_MODE_2: //Timer Model
                 if(run_t.gPower_On==1){
				

					
						run_t.display_set_timer_timing = timer_time;
						run_t.gModel=2;


			 	   
                 }
             break;

			 case WIFI_KILL_ON: //kill turn on plasma
			  if(run_t.gPower_On==1){
                    run_t.gPlasma = 1;
			        run_t.gFan_RunContinue =0;
                 // HAL_Delay(200);
                } 
			 break;

			 case WIFI_KILL_OFF: //kill turn off
                if(run_t.gPower_On==1){
			 	  run_t.gPlasma =0;
				  
		          run_t.gFan_RunContinue =0;
                   // HAL_Delay(200);
                }
			 break;

			 case WIFI_PTC_ON://dry turn on
                if(run_t.gPower_On==1){
			        run_t.gDry =1;
                    run_t.gFan_RunContinue =0;
                   // HAL_Delay(200);
                 
                }
			 break;

			 case WIFI_PTC_OFF: //dry turn off
               
			 	if(run_t.gPower_On==1){
					run_t.gDry=0;
                 
		            run_t.gFan_RunContinue =0;
                    //HAL_Delay(200);
			 	}

			 break;

			 case WIFI_SONIC_ON:  //drive bug
		
				 if(run_t.gPower_On==1){		   
				  run_t.gUltransonic =1; //turn on 
			
				 run_t.gFan_RunContinue =0;
                
			    }

			 break;

			 case WIFI_SONIC_OFF: //drive bug turn off
			 	if(run_t.gPower_On==1){
				    run_t.gUltransonic=0;
					run_t.gFan_RunContinue =0;
                   
			   }
			 break;


			 case PTC_ERROR:
			 	 run_t.gTimer_ptc_fan_warning=0;
			 	  run_t.gDry=0;
				  run_t.ptc_too_hot_flag =1;
			      run_t.ptc_warning =1;

			 break;

			 case FAN_ERROR:
			 	 run_t.gTimer_ptc_fan_warning=31;
			 	 run_t.ptc_too_hot_flag =1;
			 	 run_t.disp_wind_speed_grade=0;
	
				 run_t.fan_warning =1;
			 break;


			 case FAN_REMOVE_ERROR:
			 	 run_t.disp_wind_speed_grade=100;
				 if( run_t.ptc_warning ==0)run_t.ptc_too_hot_flag =0;
				 run_t.fan_warning =0;

			 break;
				default :
                  cmd =0;
			 break;

			 
        }
   
}

/****************************************************************
 * 
 * Function Name:
 * Function :function of pointer 
 * 
 * 
****************************************************************/
void Single_Add_RunCmd(void(*addHandler)(void))
{
    single_add_fun = addHandler;   

}

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void))
{
	single_buzzer_fun = buzzerHandler;

}
void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat))
{
    sendAi_usart_fun = sendaiHandler;

}


