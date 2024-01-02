#include "bsp_decoder.h"
#include "bsp.h"

DECODER_T decoder_t;

static void Receive_Wifi_Cmd(uint8_t cmd);


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
   
   Receive_MainBoard_Data_Handler(decoder_t.single_data);
    
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
   
	static uint8_t hum1,hum2;
	
    switch(cmd){


	 case WIFI_CMD://5
	 	 Receive_Wifi_Cmd(decoder_t.d_cmd[0]);
	 break;

	 
//	 case WIFI_REAL_TEMP: //4//set temperature value
//	       if(power_on_off_state() ==power_on){
//		   	   
//     
//            lcd_t.number1_high = ctl_t.gSet_temperature_value/10 ;//temperature_decade;
//            lcd_t.number1_low = ctl_t.gSet_temperature_value /10 ;//temperature_decade;
//
//
//            lcd_t.number2_high =ctl_t.gSet_temperature_value %10;  //temperature_unit;
//            lcd_t.number2_low = ctl_t.gSet_temperature_value%10;//temperature_unit;
//			 lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led" timer timing
//              pro_t.temperature_set_flag=1;  //set temperature value flag
//	      }
//
//	 break;

	 case PANEL_DATA://1
	   
        if(power_on_off_state() ==power_on){
        hum1 =  humidity_value()/10 ;  //Humidity 
        hum2 =  humidity_value()%10;
        
        //temp1 = disp_dht11_temperature_value()/10 ;  // temperature
        //temp2 = disp_dht11_temperature_value()%10;
       
         //temperature 
		 lcd_t.number1_high = disp_t.disp_dht11_temp_value /10;
		 lcd_t.number1_low = disp_t.disp_dht11_temp_value /10;

		  lcd_t.number2_high = disp_t.disp_dht11_temp_value %10;//temp2;
		 lcd_t.number2_low = disp_t.disp_dht11_temp_value %10;//temp2;

		 //humidity
		 
		 lcd_t.number3_high = hum1;
		 lcd_t.number3_low = hum1;
		 
		 lcd_t.number4_high = hum2;
		 lcd_t.number4_low = hum2;
		DisplayPanel_Ref_Handler();
        }

      break;

       case WIFI_BEIJING_TIME: //7//run_t.wifi_connect_success_flag
         if(power_on_off_state() ==1){
           if(ai_state()==works_time){
		   	
			 lcd_t.number5_low=disp_t.disp_works_hours_time/10;
	         lcd_t.number5_high =disp_t.disp_works_hours_time /10;
        
			 lcd_t.number6_low = disp_t.disp_works_hours_time %10;
			 lcd_t.number6_high = disp_t.disp_works_hours_time %10;
	        


			lcd_t.number7_low = disp_t.disp_works_minutes_time/10;
			lcd_t.number7_high = disp_t.disp_works_minutes_time/10;
            
			lcd_t.number8_low = disp_t.disp_works_minutes_time%10;
			lcd_t.number8_high = disp_t.disp_works_minutes_time%10;
            
	        DisplayPanel_Ref_Handler();

		
	      }
         }
		    
        
 
      break;

      case PHONE_SET_TIMER_TIMING://wifi set timer_timing 

        
		lcd_t.number5_low=(ctl_t.gSet_timer_hours) /10;
		lcd_t.number5_high =(ctl_t.gSet_timer_hours ) /10;

		lcd_t.number6_low = (ctl_t.gSet_timer_hours ) %10;;
		lcd_t.number6_high = (ctl_t.gSet_timer_hours ) %10;



		lcd_t.number7_low = ctl_t.gSet_timer_minutes /10 ;
		lcd_t.number7_high = ctl_t.gSet_timer_minutes /10 ;

		lcd_t.number8_low = ctl_t.gSet_timer_minutes % 10;
		lcd_t.number8_high = ctl_t.gSet_timer_minutes %10;
            
       break;

	  case PHONE_SET_TEMPERATURE://11

		if(power_on_off_state()  ==1){

			//temperature_decade=  ctl_t.gSet_temperature_value /10 ;
			//temperature_unit =   ctl_t.gSet_temperature_value %10;
			// HAL_Delay(5);
			
			lcd_t.number1_high = ctl_t.gSet_temperature_value /10 ;
		    lcd_t.number1_low =ctl_t.gSet_temperature_value /10 ;
			
            lcd_t.number2_high =  ctl_t.gSet_temperature_value %10;//temperature_unit;
			lcd_t.number2_low = ctl_t.gSet_temperature_value %10;//temperature_unit;


			lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led" timer timing
             pro_t.temperature_set_flag=1;  //set temperature value flag
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
static void Receive_Wifi_Cmd(uint8_t cmd)
{
	switch(cmd){


		   case WIFI_POWER_ON: //turn on 
		 	
             // pro_t.gPower_On =power_on;
              //run_t.wifi_connect_success_flag =1;
              ctl_t.gWifi_flag =1;
		      pro_t.gKey_value = power_on;
			  
			  cmd=0xff;

	         break;

			 case WIFI_POWER_OFF: //turn off 

			   ctl_t.gWifi_flag =1;
		       pro_t.gKey_value = power_off;
             
				
              cmd=0xff;

			 break;

			case WIFI_MODE_1: //AI Model
                if(pro_t.gPower_On==power_on){
		
				ctl_t.gAi_flag =1;

				}
			break;

			 case WIFI_MODE_2: //Timer Model
                 if(pro_t.gPower_On==power_on){
				
		
				ctl_t.gAi_flag = 0;
			 }
             break;

			 case WIFI_KILL_ON: //kill turn on plasma
			  if(pro_t.gPower_On==power_on){
                    ctl_t.gPlasma_flag = 1;
			      
                } 
			 break;

			 case WIFI_KILL_OFF: //kill turn off
                if(pro_t.gPower_On==power_on){
			 	  ctl_t.gPlasma_flag = 0;
				  
		         
                }
			 break;

			 case WIFI_PTC_ON://dry turn on
                if(pro_t.gPower_On==power_on){
			        ctl_t.gPtc_flag =1;
                   
                   
                 
                }
			 break;

			 case WIFI_PTC_OFF: //dry turn off
               
			 	if(pro_t.gPower_On==power_on){
					   ctl_t.gPtc_flag =0;
			 	}

			 break;

			 case WIFI_SONIC_ON:  //drive bug
		
				 if(pro_t.gPower_On==power_on){		   
				   ctl_t.gBug_flag =1;
			    }

			 break;

			 case WIFI_SONIC_OFF: //drive bug turn off
			 	if(pro_t.gPower_On==power_on){
				    ctl_t.gBug_flag =0;
                   
			   }
			 break;


			 case PTC_ERROR:
			 	  ctl_t.ptc_warning =1;
			 	  ctl_t.gPtc_flag=0;//run_t.gDry=0;

			 break;

			 case FAN_ERROR:
			 	 ctl_t.fan_warning = 1;//run_t.gTimer_ptc_fan_warning=31;
			 	 ctl_t.gFan_speed_value = 0;
			 	
			 break;


			 
				default :
                  cmd =0;
			 break;

			 
        }
   
}


