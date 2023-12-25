#include "bsp_voice.h"
#include "bsp.h"


#define HELLO     							0x01 
#define HELLO_CHECK         				0x21 

#define POWER_ON_DATA      					0x02
#define POWER_ON_DATA_CHECK        			0x22



voice_sound_t v_t;

void (*rx_voice_data)(uint8_t data);
uint8_t (*hello_word_state)(void);


static void rx_voice_data_default_fun(uint8_t data);
static uint8_t v_hello_21h(void);



void voice_Init(void)
{

	Rx_Voice_Data_Handler(rx_voice_data_default_fun);
	Voice_Hello_Word_Handler(v_hello_21h);


}
/***********************************************************
 *  *
    *Function Name: static uint8_t power_default_fun(void);
    *Function: power turn on or turn off
    *Input Ref: NO
    *Return Ref:  1->turn on ,0-> turn off
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
 
}

void Rx_Voice_Data_Handler(void(*rx_voice_handler)(uint8_t data))
{

   rx_voice_data = rx_voice_handler;

}







/***********************************************************
 *  *
    *Function Name: static uint8_t power_default_fun(void);
    *Function: power turn on or turn off
    *Input Ref: NO
    *Return Ref:  1->turn on ,0-> turn off
    * 
***********************************************************/
void v_Power_Off(void)
{


    
}

/*
*********************************************************************************************************
*	函 数 名: MODS_01H
*	功能说明: 读取线圈状态（对应远程开关D01/D02/D03）
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
/* 说明:这里用LED代替继电器,便于观察现象 */
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
	

	/** 第1步： 判断接到指定个数数据 ===============================================================*/
	/*  没有外部继电器，直接应答错误 
		地址（8bit）+指令（8bit）+寄存器起始地址高低字节（16bit）+寄存器个数（16bit）+ CRC16
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
    *Function Name: void v_Power_On(void)
    *Function: power turn on or turn off
    *Input Ref: NO
    *Return Ref:  1->turn on ,0-> turn off
    * 
***********************************************************/
void v_Power_On(void)
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
	  
	  

	  if(v_t.RxBuf[4]==POWER_ON_DATA && v_t.RxBuf[6]==POWER_ON_DATA_CHECK){

           pro_t.gPower_On = power_on;
		   v_t.rxCounter =0;
	  }
	  else{
	  	   pro_t.gPower_On = power_off;
		  v_t.rxCounter =0;
	      
	  }

	}
    }
	else{
	v_t.rx_data_enable =0;
	 v_t.rxCounter =0;

	}
	
}



void Voice_Hello_Word_Handler(uint8_t(*hello_handler)(void))
{
   hello_word_state = hello_handler  ;

}


