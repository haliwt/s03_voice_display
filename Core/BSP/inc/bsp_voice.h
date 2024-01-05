#ifndef __BSP_VOICE_H
#define __BSP_VOICE_H
#include "main.h"

#define  RX_BUF_SIZE  10

typedef enum{
	voice_power_on=0x01,
	voice_power_off=0x02,
	voice_link_wifi=0x03,
	voice_open_ptc=0x04,
	voice_close_ptc=0x05,
	voice_open_plasma=0x06,
	voice_close_plasma=0x07,
	voice_open_rat=0x08,
	voice_close_rat=0x09,
}voice_cmd;



typedef struct{

    uint8_t voice_enable;
	uint8_t voice_ctl_flag;
	uint8_t RxBuf[RX_BUF_SIZE];
	uint8_t rx_data_enable;
	uint8_t rxCounter;
	uint8_t rx_voice_data_flag;

	//voice ctl display function "icon" 
	uint8_t voice_ptc_flag;
	uint8_t voice_plasma_flag;
	uint8_t voice_bug_flag;
	
   
	uint8_t RxStatus;
	
}voice_sound_t;


extern voice_sound_t v_t;




extern uint8_t (*hello_word_state)(void);

void Voice_Init(void);

void Voice_Hello_Word_Handler(uint8_t(*hell_handler)(void));

void Voice_Decoder_Handler(void);










#endif 

