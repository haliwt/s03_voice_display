#ifndef __BSP_LED_H_
#define __BSP_LED_H_
#include "main.h"



#define KEY_POWER_ON_LED()             HAL_GPIO_WritePin(LED_KEY_POWER_GPIO_Port, LED_KEY_POWER_Pin,GPIO_PIN_SET)
#define KEY_POWER_OFF_LED()            HAL_GPIO_WritePin(LED_KEY_POWER_GPIO_Port, LED_KEY_POWER_Pin,GPIO_PIN_RESET)


#define LED_MODEL_UP_DOWN_ON()				HAL_GPIO_WritePin(LED_KEY_TIM_GPIO_Port , LED_KEY_TIM_Pin,GPIO_PIN_SET)
#define LED_MODEL_UP_DOWN_OFF()             HAL_GPIO_WritePin(LED_KEY_TIM_GPIO_Port , LED_KEY_TIM_Pin,GPIO_PIN_RESET)


#define POWER_TOGGLE()            HAL_GPIO_TogglePin(LED_KEY_POWER_GPIO_Port, LED_KEY_POWER_Pin)







void Breath_Led(void);
void Lcd_PowerOn_Fun(void);

void Lcd_PowerOff_Fun(void);

void Panel_Led_OnOff_RunCmd(void (*panelledHandler)(void));


void Panel_Led_OnOff_Function(void);

void IWDG_Init(uint8_t prer,uint16_t rlr);
void IWDG_Feed(void);



#endif 
