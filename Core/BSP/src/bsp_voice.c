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



static uint8_t v_hello_21h(void);

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

	
	Voice_Hello_Word_Handler(v_hello_21h);


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
/*
*********************************************************************************************************
*	函 数 名: static uint8_t v_hello_21h(void)
*	功能说明: 语音唤醒词
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************/
static uint8_t v_hello_21h(void)
{
	/*
	  协议：
		语音IC发送:
			A5 头文件
			FA 协议一
			00 协议二
			81 协议三
			00 协议四
			01 唤醒词 --功能码 “你好，小优”
			00 默认
			21 开机序列号
			FB 结束标志位
	*/
	
    if(v_t.voice_enable == 0){
	 
		    memcpy(v_t.RxBuf,v_rx_data,8);

		  if(v_t.RxBuf[4]==0x01 && v_t.RxBuf[6]==0x21){

	           v_t.voice_enable = 1;
			   SendData_Buzzer();
			 
		  }

		
    }
	else{
	 if(v_t.rx_voice_data_flag== 1){
	      if(v_t.RxBuf[4]==0x01 && v_t.RxBuf[6]==0x21){
		
			v_t.voice_enable = 1;
			SendData_Buzzer();
					
		}
	 }

	}
	return v_t.voice_enable ;
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
   

	if(voice_inputBuf[0]==0xA5){

	//voice_inputBuf[0]=0xff;

	key= voice_inputBuf[4] + voice_inputBuf[6];

	result = BinarySearch_Voice_Data(voice_sound_data,key);
	
	if(result ==0){
		v_t.voice_enable =1;
		 SendData_Buzzer();
	}
	else if(result >0 && result < 10){ //command 
	    if(v_t.voice_enable ==1)
		  voice_cmd_fun(result);
		

	}
	else if(result > 9 && result < 31){ //set temperature value 
		 if(v_t.voice_enable ==1)
            voice_set_temperature_value(result);
		

	}
	else if(result > 30 && result <55){ //set timer timing value 
		if(v_t.voice_enable ==1)
		voice_set_timer_timing_value(result);
		

	}

	voice_inputBuf[0]=0xff;
	}
	else{
		voice_inputBuf[0]=0xff;
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
	case voice_power_on:
        if(pro_t.gPower_On == power_on){


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

	break;
	case voice_power_off:
		if(pro_t.gPower_On == power_off){


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
		ctl_t.gSet_temperature_value = value;

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
      ctl_t.gSet_timer_hours= time /10;
	  ctl_t.gSet_timer_minutes = time %10;

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


