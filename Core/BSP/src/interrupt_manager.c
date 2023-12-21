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
/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  
   #if 0
	static uint8_t state=0;
    uint32_t temp ;
    //wifi usart2
    if(huart->Instance==USART2)
    {
           
         
        //  USART2->ISR = 0xf5; 
	
	      if(esp8266data.linking_tencent_cloud_doing ==1){

			UART2_DATA.UART_Data[UART2_DATA.UART_Cnt] = UART2_DATA.UART_DataBuf[0];
			UART2_DATA.UART_Cnt++;

			if(*UART2_DATA.UART_DataBuf==0X0A) // 0x0A = "\n"
			{
				UART2_DATA.UART_Flag = 1;
				Wifi_Rx_InputInfo_Handler();
				UART2_DATA.UART_Cnt=0;
			}

	      } 
		  else{

		         if(wifi_t.get_rx_beijing_time_enable==1){
					UART2_DATA.UART_Data[UART2_DATA.UART_Cnt] = UART2_DATA.UART_DataBuf[0];
					UART2_DATA.UART_Cnt++;
					//Subscribe_Rx_Interrupt_Handler();
				}
				else
				Subscribe_Rx_Interrupt_Handler();
	      }
	  __HAL_UART_CLEAR_OREFLAG(&huart2);
      HAL_UART_Receive_IT(&huart2,UART2_DATA.UART_DataBuf,1);
	}

	
	if(huart->Instance==USART1)//if(huart==&huart1) // Motor Board receive data (filter)
	{
        //test_counter_usat1++;
		switch(state)
		{
		case 0:  //#0
			if(inputBuf[0] == 'T')  //hex :54 - "T" -fixed
				state=1; //=1
		
			break;
		case 1: //#1
             if(inputBuf[0] == 'K')  //hex :4B - "K" -fixed
				state=2; //=1
			else
			   state =0;
			break;
            
        case 2:
             inputCmd[0]= inputBuf[0];
             state = 3;
        
        break;
        
        case 3:
            inputCmd[1]= inputBuf[0];
            pro_t.decodeFlag =1;
            state = 0;
        
        break;
	
		default:
			state=0;
			pro_t.decodeFlag =0;
		}
		__HAL_UART_CLEAR_OREFLAG(&huart1); //WT.EDIT 2023.06.16
		HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
		
	 }
    
  #endif 
 }


/**
  * Function Name: void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
  * Function: Tim3 interrupt call back function
  * Tim3 timer :timing time 10ms
  * 
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    static uint8_t tm0;
    if(htim->Instance==TIM3){
		
	   tm0 ++ ;
      
	 if(tm0 > 99){//100ms *10 = 1000ms =1s
        tm0 =0;
	
       
	  }
 	}
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
    
   if(htim->Instance==TIM3){
    
    tm0++;  //10ms
	tm1++;
 
    lcd_t.gTimer_wifi_500ms++;
	lcd_t.gTimer_fan_10ms++;
	
    if(tm1>9){ //100ms 
       tm1=0;
       lcd_t.gTimer_colon_ms++ ;
	   lcd_t.gTimer_numbers_one_two_blink++;
	   lcd_t.gTimer_digital5678_ms++;
       lcd_t.gTimer_ptc_fan_blink_warning++ ;
	   
    }

    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;
		
		
		pro_t.gTimer_pro_temp ++;
	    pro_t.gTimer_pro_temp_delay ++ ;
		lcd_t.gTimer_ptc_fan_warning ++;
		

	    if(disp_t.gTimer_disp_seconds_time >59){//60s ->1 minute 
	      disp_t.gTimer_disp_seconds_time=0;
		  disp_t.gTimer_disp_minutes_time++;
		 
		 }

		
		
	   
     

   }
	
   }


}

