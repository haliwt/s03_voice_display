#ifndef __BSP_VOICE_H
#define __BSP_VOICE_H
#include "main.h"

#include V_RX_BUF_SIZE  10


typedef struct{

    uint8_t voice_enable;
	uint8_t voice_ctl_flag;
	uint8_t RxBuf[V_RX_BUF_SIZE];
	uint8_t rx_data_enable;
	uint8_t rxCounter;

	//voice ctl display function "icon" 
	uint8_t voice_ptc_flag;
	uint8_t voice_plasma_flag;
	uint8_t voice_bug_flag;
	
   
	uint8_t RxStatus;
	
}voice_sound_t;


extern voice_sound_t v_t;



extern void (*rx_voice_data)(uint8_t data);
extern uint8_t (*hello_word_state)(void);

extern uint8_t (*voice_ptc_state)(void);
extern uint8_t (*voice_plasma_state)(void);
extern uint8_t (*voice_bug_state)(void);


void Voice_Init(void);

void Rx_Voice_Data_Handler(void(*rx_voice_handler)(uint8_t data));
void Voice_Hello_Word_Handler(uint8_t(*hell_handler)(void));

void Voice_Decoder_Handler(void);










#endif 

