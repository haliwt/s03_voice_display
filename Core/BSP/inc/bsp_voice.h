#ifndef __BSP_VOICE_H
#define __BSP_VOICE_H
#include "main.h"

#include V_RX_BUF_SIZE  10


typedef struct{

    uint8_t voice_enable;
	uint8_t RxBuf[V_RX_BUF_SIZE];
	uint8_t rx_data_enable;
	uint8_t rxCounter;
   
	uint8_t RxStatus;
	
}voice_sound_t;


extern voice_sound_t v_t;



extern void (*rx_voice_data)(uint8_t data);
extern uint8_t (*hello_word_state)(void);

void Rx_Voice_Data_Handler(void(*rx_voice_handler)(uint8_t data));
void Voice_Hello_Word_Handler(uint8_t(*hell_handler)(void));

void v_Power_On(void);
void v_Power_Off(void);

void v_Link_Net(void);

void v_Open_Ptc(void);
void v_Close_Ptc(void);

void v_Open_Plasma(void);
void v_Close_Plasma(void);

void v_Open_Bug(void);
void v_Close_Bug(void);

void v_Set_Temp_20d(void);
void v_Set_Temp_21d(void);
void v_Set_Temp_22d(void);
void v_Set_Temp_23d(void);
void v_Set_Temp_24d(void);
void v_Set_Temp_25d(void);








#endif 

