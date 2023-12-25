#include "bsp_buzzer.h"
#include "bsp.h"

static void Buzzer_KeySound_Off(void);

void Buzzer_KeySound_Off(void)
{
  HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	
}

/********************************************************
***
* Buzzer of is 4KHz 
********************************************************/
void Key_Sound(void)
{
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_Delay(40); ////HAL_Delay(60); //
  Buzzer_KeySound_Off();
  

}


void Voice_Buzzer_Sound(void)
{

	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_Delay(40); ////HAL_Delay(60); //
	Buzzer_KeySound_Off();

	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_Delay(40); ////HAL_Delay(60); //
	Buzzer_KeySound_Off();





}

void Error_Sound(void)
{
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_Delay(5); ////HAL_Delay(60); //
  Buzzer_KeySound_Off();

  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_Delay(5); ////HAL_Delay(60); //
  Buzzer_KeySound_Off();

  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_Delay(5); ////HAL_Delay(60); //
  Buzzer_KeySound_Off();

  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_Delay(5); ////HAL_Delay(60); //
  Buzzer_KeySound_Off();

  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_Delay(5); ////HAL_Delay(60); //
  Buzzer_KeySound_Off();



}
