#ifndef __BSP_DECODER_H
#define __BSP_DECODER_H
#include "main.h"

typedef struct{

  uint8_t d_cmd[1];
  uint8_t single_data;


}DECODER_T;

extern DECODER_T decoder_t;

void Decode_Function(void);




#endif 

