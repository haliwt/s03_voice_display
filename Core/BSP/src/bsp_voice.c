#include "bsp_voice.h"
#include "bsp.h"


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

#define SET_TEMP_20D                     0x0B
#define SET_TMEP_20D_CHECK               0x2B

#define SET_TEMP_21D                     0x0C
#define SET_TMEP_21D_CHECK               0x2C

#define SET_TEMP_22D                     0x0D
#define SET_TMEP_22D_CHECK               0x2D

#define SET_TEMP_23D                     0x0E
#define SET_TMEP_23D_CHECK               0x2E

#define SET_TEMP_24D                     0x0F
#define SET_TMEP_24D_CHECK               0x2F

#define SET_TEMP_25D                     0x10
#define SET_TMEP_25D_CHECK               0x30

#define SET_TEMP_26D                     0x11
#define SET_TMEP_26D_CHECK               0x31

#define SET_TEMP_27D                     0x12
#define SET_TMEP_27D_CHECK               0x32

#define SET_TEMP_28D                     0x13
#define SET_TMEP_28D_CHECK               0x33

#define SET_TEMP_29D                     0x14
#define SET_TMEP_29D_CHECK               0x34

#define SET_TEMP_30D                     0x15
#define SET_TMEP_30D_CHECK               0x35

#define SET_TEMP_31D                     0x16
#define SET_TMEP_31D_CHECK               0x36

#define SET_TEMP_32D                     0x17
#define SET_TMEP_32D_CHECK               0x37

#define SET_TEMP_33D                     0x18
#define SET_TMEP_33D_CHECK               0x38

#define SET_TEMP_34D                     0x19
#define SET_TMEP_34D_CHECK               0x39

#define SET_TEMP_35D                     0x1A
#define SET_TMEP_35D_CHECK               0x3A

#define SET_TEMP_36D                     0x1B
#define SET_TMEP_36D_CHECK               0x3B

#define SET_TEMP_37D                     0x1C
#define SET_TMEP_37D_CHECK               0x3C

#define SET_TEMP_38D                     0x1D
#define SET_TMEP_38D_CHECK               0x3D

#define SET_TEMP_39D                     0x1E
#define SET_TMEP_39D_CHECK               0x3E

#define SET_TEMP_40D                     0x1F
#define SET_TMEP_40D_CHECK               0x3F

//timer timing 

#define TIMER_ONE_HOURS                  0x20
#define TIMER_ONE_HOURS_CHECK            0x40

#define TIMER_TWO_HOURS                  0x21
#define TIMER_TWO_HOURS_CHECK            0x41

#define TIMER_THREE_HOURS                  0x22
#define TIMER_THREE_HOURS_CHECK            0x42

#define TIMER_FOUR_HOURS                  0x23
#define TIMER_FOUR_HOURS_CHECK            0x43

#define TIMER_FIVE_HOURS                  0x24
#define TIMER_FIVE_HOURS_CHECK            0x44

#define TIMER_SIX_HOURS                  0x25
#define TIMER_SIX_HOURS_CHECK            0x45

#define TIMER_SEVEN_HOURS                  0x26
#define TIMER_SEVEN_HOURS_CHECK            0x46

#define TIMER_EIGHT_HOURS                  0x27
#define TIMER_EIGHT_HOURS_CHECK            0x47

#define TIMER_NINE_HOURS                  0x28
#define TIMER_NINE_HOURS_CHECK            0x48

#define TIMER_TEN_HOURS                  0x29
#define TIMER_TEN_HOURS_CHECK            0x49

#define TIMER_ELEVEN_HOURS                  0x2A
#define TIMER_ELEVEN_HOURS_CHECK            0x4A

#define TIMER_TWELVE_HOURS                  0x2B
#define TIMER_TWELVE_HOURS_CHECK            0x4B

#define TIMER_THIRTEEN_HOURS                  0x2C
#define TIMER_THIRTEEN_HOURS_CHECK            0x4C

#define TIMER_FOURTEEN_HOURS                  0x2D
#define TIMER_FOURTEEN_HOURS_CHECK            0x4D

#define TIMER_FIFEEN_HOURS                  0x2E
#define TIMER_FIFTEEN_HOURS_CHECK            0x4E

#define TIMER_SIXTEEN_HOURS                  0x2F
#define TIMER_SIXTEEN_HOURS_CHECK            0x4F

#define TIMER_SEVENTEEN_HOURS                  0x30
#define TIMER_SEVENTEEN_HOURS_CHECK            0x50

#define TIMER_EIGHTEEN_HOURS                  0x31
#define TIMER_EIGHTEEN_HOURS_CHECK            0x51

#define TIMER_NINETEEN_HOURS                  0x32
#define TIMER_NINETEEN_HOURS_CHECK            0x52

#define TIMER_TWENTY_HOURS                  0x33
#define TIMER_TWENTY_HOURS_CHECK            0x53

#define TIMER_TWENTY_ONE_HOURS                  0x34
#define TIMER_TWENTY_ONE_HOURS_CHECK            0x54

#define TIMER_TWENTY_TWO_HOURS                  0x35
#define TIMER_TWENTY_TWO_HOURS_CHECK            0x55

#define TIMER_TWENTY_THREE_HOURS                  0x36
#define TIMER_TWENTY_THREE_HOURS_CHECK            0x56

#define TIMER_TWENTY_FOUR_HOURS                  0x37
#define TIMER_TWENTY_FOUR_HOURS_CHECK            0x57

         

voice_sound_t v_t;

void (*rx_voice_data)(uint8_t data);
uint8_t (*hello_word_state)(void);

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


static void rx_voice_data_default_fun(uint8_t data);
static uint8_t v_hello_21h(void);

static void voice_ctl_fun(uint8_t data,uint8_t check_code);

static void voice_power_on(uint8_t data ,uint8_t check_code);
static void voice_power_off(uint8_t data ,uint8_t check_code);

static void voice_link_net(uint8_t data ,uint8_t check_code);

static void voice_open_ptc(uint8_t data ,uint8_t check_code);
static void voice_close_ptc(uint8_t data ,uint8_t check_code);

static void voice_open_plasma(uint8_t data ,uint8_t check_code);
static void voice_close_plasma(uint8_t data ,uint8_t check_code);

static void voice_open_rat(uint8_t data ,uint8_t check_code);
static void voice_close_rat(uint8_t data ,uint8_t check_code);



static int8_t voice_set_temp_data(uint8_t data,uint8_t check_code);
static int8_t  voice_set_timer_data(uint8_t data,uint8_t chek_code);

static int8_t BinarySearch_Temp(const uint8_t *pta,uint8_t key,uint8_t n);
static int8_t BinarySearch_Timer(const uint8_t *pta,uint8_t key,uint8_t n);



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

	Rx_Voice_Data_Handler(rx_voice_data_default_fun);
	Voice_Hello_Word_Handler(v_hello_21h);


}
/***********************************************************
 *  *
    *Function Name: static uint8_t power_default_fun(void);
    *Function: call back interrupt of USAT2 
    *Input Ref: usart2 receive data form interrupt 
    *Return Ref:  NO
    * 
***********************************************************/
void rx_voice_data_default_fun(uint8_t data)
{
   
   if(data==0xA5){
      v_t.rx_data_enable =1;    
   }

  if(v_t.rx_data_enable){
     v_t.RxBuf[v_t.rxCounter] = data;
     v_t.rxCounter++;

   }
   else{
	   v_t.rxCounter=0;

   }
 
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
	if(v_t.rxCounter != 8)
	{
		v_t.rx_data_enable =0;			/* 数据值域错误 */
		return 0;
	}

    if(v_t.RxBuf[7] == 0xFB){
      v_t.rx_data_enable =0;

	  if(v_t.RxBuf[4]==0x01 && v_t.RxBuf[6]==0x21){

           v_t.voice_enable = 1;
		   Voice_Buzzer_Sound();
		   v_t.rxCounter=0;
	  }
	  else{
	  	  v_t.voice_enable = 0;
		  v_t.rxCounter=0;
	  }

	}
	else{
      v_t.rxCounter=0;
	  v_t.rx_data_enable =0;

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
    int8_t ret_temp_value,ret_timer_value;
    if(hello_word_state() ==1){
      
    if(v_t.rxCounter != 8){
		v_t.rx_data_enable =0;			/* 数据值域错误 */
		v_t.rxCounter =0;
		return;
	}

    if(v_t.RxBuf[7] == 0xFB){
      v_t.rx_data_enable =0;
      if(v_t.RxBuf[4] < 0x0B){
	  	 Voice_Buzzer_Sound();
		 voice_ctl_fun(v_t.RxBuf[4],v_t.RxBuf[6]);
	
	  } //voice set temperature value 
      else if(v_t.RxBuf[4] > 0x0A && (v_t.RxBuf[4] < 0x20)){
	  	
           ret_temp_value = voice_set_temp_data(v_t.RxBuf[4],v_t.RxBuf[6]);
		   if(ret_temp_value >= 0){

              Voice_Buzzer_Sound();
			  disp_t.disp_set_temp_value =(uint8_t)ret_temp_value;
			  Display_Voice_Set_Temp_Value();
		     
		   }
		   else{
		   	  
                Error_Sound();

		   }

	
	  } //voice set timer timing value 
	  else if(v_t.RxBuf[4] > 0x1F){

	     ret_timer_value = voice_set_timer_data(v_t.RxBuf[4],v_t.RxBuf[6]);
		 if(ret_temp_value > 0){

		    ctl_t.gSet_timer_value =(uint8_t)ret_temp_value;
			Mode_Long_Key_Fun();

              
		 }
		 else{
			 Error_Sound();


		 }
	  	
	 
	  }
	}
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
static void voice_ctl_fun(uint8_t data,uint8_t check_code)
{
		switch(data){

		case POWER_ON_DATA:
				voice_power_on(data,check_code);
		break;

		case POWER_OFF_DATA:
				voice_power_off(data,check_code);
		break;

		case LINK_NET_DATA:
			voice_link_net(data,check_code);

		break;

		case OPEN_PTC_DATA:
			voice_open_ptc(data,check_code);
		break;

		case CLOSE_PTC_DATA:
			voice_close_ptc(data,check_code);

		break;

		case OPEN_PLASMA_DATA:
			voice_open_plasma(data,check_code);

		break;

		case CLOSE_PLASMA_DATA:
			voice_close_plasma(data,check_code);

		break;

		case OPEN_RAT_DATA:
			voice_open_rat(data,check_code);

		break;

		case CLOSE_RAT_DATA:
			voice_close_rat(data,check_code);

		break;
	}


}
/***********************************************************
 *  *
    *Function Name: void Voice_Decoder_Handler(void);
    *Function: decoder to command 
    *Input Ref: NO
    *Return Ref:  NO
    * 
***********************************************************/
static void voice_power_on(uint8_t data ,uint8_t check_code)
{
	if(data==POWER_ON_DATA && check_code==POWER_ON_DATA_CHECK){

           pro_t.gKey_value = power_on;//pro_t.gPower_On = power_on;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}

}

static void voice_power_off(uint8_t data ,uint8_t check_code)
{
	if(data==POWER_OFF_DATA && check_code==POWER_OFF_DATA_CHECK){

           pro_t.gKey_value = power_off;//pro_t.gPower_On = power_off;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}
}

static void voice_link_net(uint8_t data ,uint8_t check_code)
{
	if(data==POWER_OFF_DATA && check_code==POWER_OFF_DATA_CHECK){

            pro_t.gKey_value = wifi_fun_on;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}

}
//control display panel of function of icon display or not display
static void voice_open_ptc(uint8_t data ,uint8_t check_code)
{
	if(data==OPEN_PTC_DATA && check_code==OPEN_PTC_DATA_CHECK){

           v_t.voice_ptc_flag= 1;
		   v_t.voice_ctl_flag =1;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}
}
static void voice_close_ptc(uint8_t data ,uint8_t check_code)
{
	if(data==CLOSE_PTC_DATA && check_code==CLOSE_PTC_DATA_CHECK){

           v_t.voice_ptc_flag= 0;
		   v_t.voice_ctl_flag =1;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}

}

static void voice_open_plasma(uint8_t data ,uint8_t check_code)
{
	if(data==OPEN_PLASMA_DATA && check_code==OPEN_PLASMA_DATA_CHECK){

           v_t.voice_plasma_flag= 1;
		   v_t.voice_ctl_flag =1;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}

}
static void voice_close_plasma(uint8_t data ,uint8_t check_code)
{
	if(data==CLOSE_PLASMA_DATA && check_code==CLOSE_PLASMA_DATA_CHECK){

           v_t.voice_plasma_flag= 0;
		   v_t.voice_ctl_flag =1;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}
}
static void voice_open_rat(uint8_t data ,uint8_t check_code)
{
	if(data==OPEN_RAT_DATA && check_code==OPEN_RAT_DATA_CHECK){

           v_t.voice_bug_flag= 1;
		   v_t.voice_ctl_flag =1;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}

}
static void voice_close_rat(uint8_t data ,uint8_t check_code)
{
	if(data==CLOSE_RAT_DATA && check_code==CLOSE_RAT_DATA_CHECK){

           v_t.voice_plasma_flag= 1;
		   v_t.voice_ctl_flag =1;
		   v_t.rxCounter =0;
	  }
	 else{
		v_t.rx_data_enable =0;
		v_t.rxCounter =0;
		v_t.voice_ctl_flag =0;

	}
}
/**********************************************************************************
 *  *
    *Function Name: static uint8_t voice_set_temp_data(uint8_t data,uint8_t check)
    *Function: voice set temperature value 
    *Input Ref: data- voice command , check- check code
    *Return Ref:  NO
    * 
***********************************************************************************/
static int8_t voice_set_temp_data(uint8_t data,uint8_t check_code)
{
    uint8_t key ,n;
    int8_t ret;
     key = data + check_code ;

	 //look up list .
     n = sizeof(voice_temp_value)/(sizeof(voice_temp_value[0]));

    ret = BinarySearch_Temp(voice_temp_value,key,n);

	if(ret == -1){
        ret = -1 ;
	}
	else{
		ret = 20 + ret;
	}
	return ret;

}
/**********************************************************************************
 *  *
    *Function Name: static int8_t BinarySearch(uint8_t *pta,uint8_t key,uint8_t n)
    *Function:  binary look up key
    *Input Ref: *pta is array ,key->look up data, n ->array of length
    *Return Ref:  NO
    * 
***********************************************************************************/
static int8_t BinarySearch_Temp(const uint8_t *pta,uint8_t key,uint8_t n)
{

      uint8_t left,right,mid;
	  left =0;
	  right = n -1;
	  while(left <= right){

		 mid = (left+right)/2;
		 if(pta[mid]==key){
			  return mid;
		 }
		 else if(pta[mid]>key){
			 right = mid -1;  //from  before middle look up this is key value 
		 }
		 else if(pta[mid] < key){
			 left = mid +1;  //from  before middle look up this is key value 
		 }

	  }

	  return -1;

}
/**********************************************************************************
 *  *
    *Function Name:static int8_t  voice_set_timer_data(uint8_t data,uint8_t chek_code)
    *Function: voice set timer timing value 
    *Input Ref: voice input data, check_code-> check code voice
    *Return Ref:  set timer timing value 
    * 
***********************************************************************************/
static int8_t  voice_set_timer_data(uint8_t data,uint8_t check_code)
{

    uint8_t key ,n;
    int8_t ret;
     key = data + check_code ;

	 //look up list .
     n = sizeof(voice_timer_array)/(sizeof(voice_timer_array[0]));

    ret = BinarySearch_Timer(voice_timer_array,key,n);

	if(ret == -1){
        ret = -1 ;
	}
	else{
		ret = 20 + ret;
	}
	return ret;



}
static int8_t BinarySearch_Timer(const uint8_t *pta,uint8_t key,uint8_t n)
{
   uint8_t left,right,mid;
   left = 0;
   right = n-1;

   while(left<= right){

      mid = (left + right )/2;

      if(mid == key){
         return mid;
	  }
	  else if(pta[mid]> key){

	      right = right -1;

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


