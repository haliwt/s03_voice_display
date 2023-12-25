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

voice_sound_t v_t;

void (*rx_voice_data)(uint8_t data);
uint8_t (*hello_word_state)(void);


static void rx_voice_data_default_fun(uint8_t data);
static uint8_t v_hello_21h(void);

static void voice_power_on(void);
static void voice_power_off(void);

static void voice_link_net(void);

static void voice_open_ptc(void);
static void voice_close_ptc(void);

static void voice_open_plasma(void);
static void voice_close_plasma(void);

static void voice_open_rat(void);
static void voice_close_rat(void);

static void voice_set_temp_data(uint8_t data,uint8_t check);


/***********************************************************
 *  *
    *Function Name: void voice_Init(void)
    *Function: 
    *Input Ref: NO
    *Return Ref:  NO
    * 
***********************************************************/
void voice_Init(void)
{

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
		return;
	}

    if(v_t.RxBuf[7] == 0xFB){
      v_t.rx_data_enable =0;

	  if(v_t.RxBuf[4]==0x01 && v_t.RxBuf[6]==0x21){

           v_t.voice_enable = 1;
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
void Voice_Decoder_Handler(void);
{
    /*
	  协议：
		语音IC发送:
			A5 头文件
			FA 协议一
			00 协议二
			81 协议三
			00 协议四
			02 开机 --功能码 “你好，小优”
			00 默认
			22 开机序列号
			FB 结束标志位

		
	*/
    if(hello_word_state() ==1){
      
    if(v_t.rxCounter != 8){
		v_t.rx_data_enable =0;			/* 数据值域错误 */
		v_t.rxCounter =0;
		return;
	}

    if(v_t.RxBuf[7] == 0xFB){
      v_t.rx_data_enable =0;

      switch(v_t.RxBuf[4]){

	  case POWER_ON_DATA:
            voice_power_on();
	  break;

	  case POWER_OFF_DATA:
			voice_power_off();
	  break;

	  case LINK_NET_DATA:
	  	voice_link_net();

	  break;

	  case OPEN_PTC_DATA:
		voice_open_ptc();
	  break;

	  case CLOSE_PTC_DATA:
	  	voice_close_ptc();

	  break;

	  case OPEN_PLASMA_DATA:
	      voice_open_plasma();

	  break;

	  case CLOSE_PLASMA_DATA:
	      voice_close_plasma();

	  break;

	  case OPEN_RAT_DATA:
	  	 voice_open_rat();

	  break;

	  case CLOSE_RAT_DATA:
	      voice_close_rat();

	  break;

	  case SET_TEMP_20D:

	  break;

	  case SET_TEMP_21D:

	  break;

	  case SET_TEMP_22D:

	  break;

	  case SET_TEMP_23D:

	  break;

	  case SET_TEMP_24D:

	  break;

	  case SET_TEMP_25D:

	  break;

	  case SET_TEMP_26D:

	  break;

	  case SET_TEMP_27D:

	  break;

	  case SET_TEMP_28D:

	  break;

	  case SET_TEMP_29D:

	  break;

	  case SET_TEMP_30D:

	  break;

	  case SET_TEMP_31D:

	  break;

	  case SET_TEMP_32D:

	  break;

	  case SET_TEMP_33D:

	  break;

	  case SET_TEMP_34D:

	  break;

	  case SET_TEMP_35D:

	  break;

	  case SET_TEMP_36D:

	  break;

	  case SET_TEMP_37D:

	  break;

	  case SET_TEMP_38D:

	  break;

	  case SET_TEMP_39D:

	  break;

	  case SET_TEMP_40D:

	  break;

	  default:

	  break;
	  
	}
	}

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
static void voice_power_on(void)
{
	if(v_t.RxBuf[4]==POWER_ON_DATA && v_t.RxBuf[6]==POWER_ON_DATA_CHECK){

           pro_t.gKey_value = power_on;//pro_t.gPower_On = power_on;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}

}

static void voice_power_off(void)
{
	if(v_t.RxBuf[4]==POWER_OFF_DATA && v_t.RxBuf[6]==POWER_OFF_DATA_CHECK){

           pro_t.gKey_value = power_off;//pro_t.gPower_On = power_off;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}
}

static void voice_link_net(void)
{
	if(v_t.RxBuf[4]==POWER_OFF_DATA && v_t.RxBuf[6]==POWER_OFF_DATA_CHECK){

            pro_t.gKey_value = wifi_fun_on;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}

}

static void voice_open_ptc(void)
{
	if(v_t.RxBuf[4]==OPEN_PTC_DATA && v_t.RxBuf[6]==OPEN_PTC_DATA_CHECK){

           ctl_t.gPtc_flag = 1;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}
}
static void voice_close_ptc(void)
{
	if(v_t.RxBuf[4]==CLOSE_PTC_DATA && v_t.RxBuf[6]==CLOSE_PTC_DATA_CHECK){

           ctl_t.gPtc_flag = 0;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}

}

static void voice_open_plasma(void)
{
	if(v_t.RxBuf[4]==OPEN_PLASMA_DATA && v_t.RxBuf[6]==OPEN_PLASMA_DATA_CHECK){

           ctl_t.gPlasma_flag = 1;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}

}
static void voice_close_plasma(void)
{
	if(v_t.RxBuf[4]==CLOSE_PLASMA_DATA && v_t.RxBuf[6]==CLOSE_PLASMA_DATA_CHECK){

           ctl_t.gPlasma_flag = 0;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}
}

static void voice_open_rat(void)
{
	if(v_t.RxBuf[4]==OPEN_RAT_DATA && v_t.RxBuf[6]==OPEN_RAT_DATA_CHECK){

           ctl_t.gBug_flag = 1;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}

}
static void voice_close_rat(void)
{
	if(v_t.RxBuf[4]==CLOSE_RAT_DATA && v_t.RxBuf[6]==CLOSE_RAT_DATA_CHECK){

           ctl_t.gBug_flag = 0;
		   v_t.rxCounter =0;
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;

	}

	
}

static uint8_t voice_set_temp_data(uint8_t data,uint8_t check)
{
    if(v_t.RxBuf[4]==data && v_t.RxBuf[6]==check){

           ctl_t.gSet_temp_value = data;
		   v_t.rxCounter =0;
		   
	  }
	 else{
	   v_t.rx_data_enable =0;
	  v_t.rxCounter =0;
	  ctl_t.gSet_temp_value = 0;

	 }
    return ctl_t.gSet_temp_value = data;
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


