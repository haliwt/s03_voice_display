#include "interrupt_manager.h"
#include "bsp.h"


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
 #if 0
	uint32_t temp;
	if(huart->Instance==USART2){

		if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_ORE)!=RESET){

             __HAL_UART_CLEAR_OREFLAG(&huart2);
		
			UART_Start_Receive_IT(&huart2,UART2_DATA.UART_DataBuf,1);

		}
		__HAL_UNLOCK(&huart2);
		   
       
          temp = USART2->RDR;
		UART_Start_Receive_IT(&huart2,UART2_DATA.UART_DataBuf,1);


	}
	if(huart->Instance==USART1){
	
		if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE)!=RESET){

		__HAL_UART_CLEAR_OREFLAG(&huart1);
		UART_Start_Receive_IT(&huart1,inputBuf,1);

		}
		__HAL_UNLOCK(&huart1);
		//  temp = USART1 ->ISR;
		temp = USART1->RDR;
		UART_Start_Receive_IT(&huart1,inputBuf,1);
	
		}


#endif 

}


/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timing 10ms interrupt call back function call back function
	*
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t tm0,tm1;
    
   if(htim->Instance==TIM17){
    
    tm0++;  //10ms
	tm1++;

    lcd_t.gTimer_wifi_500ms++;
	lcd_t.gTimer_fan_10ms++;
	pro_t.gTimer_pro_ms++;
	pro_t.gTimer_pro_disp_ms++;
	
    if(tm1>9){ //100ms 
       tm1=0;
       lcd_t.gTimer_colon_ms++ ;
	   lcd_t.gTimer_numbers_one_two_blink++;
	   lcd_t.gTimer_digital5678_ms++;
       lcd_t.gTimer_ptc_fan_blink_warning++ ;
	   
    }

    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;

	    pro_t.gTimer_key_timing++;
		pro_t.gTimer_wifi_connect_counter++;
		pro_t.gTimer_pro_temp ++;
	    pro_t.gTimer_pro_temp_delay ++ ;
		lcd_t.gTimer_ptc_fan_warning ++;
		disp_t.gTimer_disp_timer_timing++;
		disp_t.gTimer_disp_minutes_time++;
	
		pro_t.gTimer_pro_fan++;
		pro_t.gTimer_usart_error++;
		pro_t.gTimer_pro_disp_timer ++;
		ctl_t.gTimer_ctl_timer_time ++ ;
		
	    if(disp_t.gTimer_disp_seconds_time >59){//60s ->1 minute 
	      disp_t.gTimer_disp_seconds_time=0;
		}

	}
	
   }


}

