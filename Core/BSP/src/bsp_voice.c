#include "bsp_voice.h"
#include "bsp.h"
#include <string.h>


#define HELLO     							0x01 
#define HELLO_CHECK         				0x21 

#define POWER_ON_DATA      					0x02
#define POWER_ON_DATA_CHECK        			0x22

#define POWER_OFF_DATA                      0x3
#define POWER_OFF_DATA_CHECK                0x23

#define LINK_NET_DATA                      0x4
#define LINK_NET_DATA_CHECK                0x24

#define OPEN_PTC_DATA                      0x5
#define OPEN_PTC_DATA_CHECK                0x25

#define CLOSE_PTC_DATA                      0x6
#define CLOSE_PTC_DATA_CHECK                0x26

#define OPEN_PLASMA_DATA                      0x7
#define OPEN_PLASMA_DATA_CHECK                0x27

#define CLOSE_PLASMA_DATA                      0x8
#define CLOSE_PLASMA_DATA_CHECK                0x28

#define OPEN_RAT_DATA                      0x9
#define OPEN_RAT_DATA_CHECK                0x29

#define CLOSE_RAT_DATA                      0x0A
#define CLOSE_RAT_DATA_CHECK                0x2A

//set temperature of voice command 


         

voice_sound_t v_t;

void (*rx_voice_data)(uint8_t data);
uint8_t (*hello_word_state)(void);

uint8_t key;
int8_t result = 0xff;
#if 0

static uint8_t const voice_ctl_value[9]={
	0x24,0x26,0x28,0x2a,0x2c,
	0x2e,0x30,0x32,0x34
	

};



static uint8_t const voice_temp_value[21]={
	0x36,0x38,0x3a,0x3c,0x3e,
	0x40,0x42,0x44,0x46,0x48,
	0x4a,0x4c,0x4e,0x50,0x52,
	0x54,0x56,0x58,0x5a,0x5c,
	0x5e

};

static uint8_t const voice_timer_array[24]={
	0x60,0x62,0x64,0x66,0x68,
	0x6a,0x6c,0x6e,0x70,0x72,
	0x74,0x76,0x78,0x7a,0x7c,
	0x7e,0x80,0x82,0x84,0x86,
	0x88,0x8a,0x8c,0x8e
	
};

#endif 

static uint8_t const voice_sound_data[55]={

	0x22,0x24,0x26,0x28,0x2a,
	0x2c,0x2e,0x30,0x32,0x34,
    0x36,0x38,0x3a,0x3c,0x3e,
	0x40,0x42,0x44,0x46,0x48,
	0x4a,0x4c,0x4e,0x50,0x52,
	0x54,0x56,0x58,0x5a,0x5c,
	0x5e,
    0x60,0x62,0x64,0x66,0x68,
	0x6a,0x6c,0x6e,0x70,0x72,
	0x74,0x76,0x78,0x7a,0x7c,
	0x7e,0x80,0x82,0x84,0x86,
	0x88,0x8a,0x8c,0x8e

};





static int8_t BinarySearch_Voice_Data(const uint8_t *pta,uint8_t key);

static void voice_cmd_fun(uint8_t cmd);
static void  voice_set_temperature_value(uint8_t value);
static void voice_set_timer_timing_value(uint8_t time);

uint8_t key;
int8_t result;


/***********************************************************
 *  *
    *Function Name: void voice_Init(void)
    *Function: 
    *Input Ref: NO
    *Return Ref:  NO
    * 
***********************************************************/
void Voice_Init(void)
{
     v_t.voice_bug_flag =1;
	 v_t.voice_plasma_flag =1;
	 v_t.voice_ptc_flag = 1;

	
	


}


/***********************************************************
 *  *
    *Function Name: void Rx_Voice_Data_Handler(void(*rx_voice_handler)(uint8_t data))
    *Function: 
    *Input Ref: function of pointer o
    *Return Ref:  NO
    * 
***********************************************************/
void Rx_Voice_Data_Handler(void(*rx_voice_handler)(uint8_t data))
{

   rx_voice_data = rx_voice_handler;

}

/***********************************************************
 *  *
    *Function Name: void Voice_Decoder_Handler(void);
    *Function: decoder to command 
    *Input Ref: NO
    *Return Ref:  NO
    * 
***********************************************************/
void Voice_Decoder_Handler(void)
{
   

if(v_t.rx_voice_data_enable ==1){

	v_t.rx_voice_data_enable =0;
	
	key= v_t.RxBuf[0] + v_t.RxBuf[1];

	result = BinarySearch_Voice_Data(voice_sound_data,key);
	
	if(result ==0){
		v_t.voice_sound_enable =1;
		v_t.voice_to_buzzer_flag =1;
		// SendData_Buzzer();
	    
	}

	
	if(v_t.voice_sound_enable ==1){
       if(result ==1){
	   	if(pro_t.gPower_On == power_on){
			
			v_t.voice_to_buzzer_flag =1;

            
        }
		else{
			
			pro_t.gKey_command_tag = run_update_data;
			pro_t.gPower_On = power_on;   
			pro_t.run_process_step=0;
			pro_t.long_key_flag =0;
			pro_t.run_process_step=0;
			SendData_PowerOnOff(1);
			Power_On_Fun();
			LCD_Backlight_On();
			
		}
		
		
	}

	}

    if(v_t.voice_sound_enable ==1 && pro_t.gPower_On == power_on){

	if(result >1 && result < 10){ //command 
	   
		  voice_cmd_fun(result);
		 
		

	}
	else if(result > 9 && result < 31){ //set temperature value 
		 
            voice_set_temperature_value(result);
			
		

	}
	else if(result > 30 && result <55){ //set timer timing value 
		
		voice_set_timer_timing_value(result);
		
		

	 }
    }

	
	}
	
    
	
}

/***********************************************************************************
 *  *
    *Function Name: static void voice_cmd_fun(uint8_t cmd)
    *Function: voice of command 
    *Input Ref: input command 
    *Return Ref:  NO
    * 
*************************************************************************************/
static void voice_cmd_fun(uint8_t cmd)
{
	
	switch(cmd){
//	case voice_power_on:
//        if(pro_t.gPower_On == power_on){
//
//
//        }
//		else{
//			
//			pro_t.gKey_command_tag = run_update_data;
//			pro_t.gPower_On = power_on;   
//			pro_t.run_process_step=0;
//			pro_t.long_key_flag =0;
//			pro_t.run_process_step=0;
//			SendData_PowerOnOff(1);
//			Power_On_Fun();
//			LCD_Backlight_On();
//		}
//
//	break;
	case voice_power_off:
		if(pro_t.gPower_On == power_off){
			v_t.voice_to_buzzer_flag =1;

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
	break;

	case voice_link_wifi:
		 SendData_Set_Wifi(0x01);

	    //Key_Sound();
        pro_t.wifi_led_fast_blink_flag=1;
	
	break;

	case voice_open_ptc:
		
		
	break;

	case voice_close_ptc:
	break;

	case voice_open_plasma:
	break;
   case voice_close_plasma:
	break;

	case voice_open_rat:
	break;
	case voice_close_rat:
	break;
	

	}
}


/***********************************************************************************
 *  *
    *Function Name: static void voice_ctl_fun(unit8_t data,uint8_t check_code)
    *Function: voice of command 
    *Input Ref: data:voice command , check_code : check code
    *Return Ref:  NO
    * 
*************************************************************************************/
static void  voice_set_temperature_value(uint8_t value)
{
		value = 10+value;
		v_t.voice_to_buzzer_flag =1;
		ctl_t.gSet_temperature_value = value;

		lcd_t.number1_low=ctl_t.gSet_temperature_value / 10 ;
		lcd_t.number1_high =ctl_t.gSet_temperature_value / 10 ;

		lcd_t.number2_low = ctl_t.gSet_temperature_value % 10; //
		lcd_t.number2_high = ctl_t.gSet_temperature_value % 10; //
		
		lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led" timer timing
        pro_t.temperature_set_flag=1;  //set temperature value flag
        DisplayPanel_Ref_Handler();

}
/***********************************************************
 *  *
    *Function Name: static void voice_set_timer_timing_value(uint8_t time)
    *Function: 
    *Input Ref: set timer timing time value 
    *Return Ref:  NO
    * 
***********************************************************/
static void voice_set_timer_timing_value(uint8_t time)
{

       uint8_t  temp_bit_1_hours,temp_bit_2_hours,temp_bit_2_minute,temp_bit_1_minute;
	  ctl_t.gSet_timer_hours = time - 30;
	  pro_t.gTimer_mode_flag= 1;//set_timer_timing;
	  ctl_t.gAi_flag =timer_time;
	  SendData_Set_Wifi(MODE_TIMER);
	  disp_t.set_timer_timing_value_chaned_flag++; //
	  
	  pro_t.gTimer_key_timing =0;
	  v_t.voice_to_buzzer_flag =1;
     
	  
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
		

}
/***********************************************************
 *  *
    *Function Name: static int8_t BinarySearch_Voice_Data(const uint8_t *pta,uint8_t key)
    *Function: from small to big sort
    *Input Ref: *pta is array ,look up key data
    *Return Ref:  NO
    * 
***********************************************************/
static int8_t BinarySearch_Voice_Data(const uint8_t *pta,uint8_t key)
{
   static uint8_t n;
   uint8_t left,right,mid;
   
   n = sizeof(voice_sound_data)/(sizeof(voice_sound_data[0]));
   
   left = 0;
   right = n-1;

   while(left<right || left == right){

      mid = (left + right )/2;

      if(pta[mid] == key){
         return mid;
	  }
	  else if(pta[mid]> key){

	      right = right -1; //在左边查找

	  }
	  else if(pta[mid] < key){

          left = mid +1 ;

	  }

   }

   return -1;

}
/**********************************************************************************
 *  *
    *Function Name: void Voice_Hello_Word_Handler(uint8_t(*hello_handler)(void))
    *Function: decoder to command 
    *Input Ref: NO
    *Return Ref:  NO
    * 
***********************************************************************************/
void Voice_Hello_Word_Handler(uint8_t(*hello_handler)(void))
{
   hello_word_state = hello_handler  ;

}


