#include "bsp_cmd_link.h"
#include "bsp.h"




volatile static uint8_t transOngoingFlag; //interrupt Transmit flag bit , 1---stop,0--run
uint8_t outputBuf[8];
static uint8_t transferSize;
static uint8_t state;
uint8_t inputBuf[MAX_BUFFER_SIZE];
uint8_t voice_inputBuf[MAX_BUFFER_SIZE];
uint8_t voice_outputBuf[16];



/****************************************************************************************************
**
*Function Name:static void selectLight(uint8_t index)
*Function: UART2 transmit interrupt process ---4D 58 4C 53 32 30 32 
*Input Ref: LED number 
*Return Ref:NO
*
****************************************************************************************************/
void SendData_PowerOnOff(uint8_t index)
{
	
   //crc=0x55;
	outputBuf[0]='T'; //4D //Touch Key
	outputBuf[1]='K'; //58
	outputBuf[2]='P'; //4C	// 'P' power
	outputBuf[3]=index; //53	// 'S' select light command, 'C' close all light command
	
    transferSize=4;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}
void SendData_Buzzer(void)
{
	
   //crc=0x55;
	outputBuf[0]='T'; //4D
	outputBuf[1]='K'; //58
	outputBuf[2]='Z'; //4C	// 'L' for light board
	outputBuf[3]='Z'; //53	// 'S' select light command, 'C' close all light command
	
    transferSize=4;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}

void SendData_Set_Command(uint8_t hdata)
{
	    outputBuf[0]='T'; //4D
		outputBuf[1]='K'; //58
		outputBuf[2]='C'; //"C" ->command
		outputBuf[3]=hdata; //53	//
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
	
}
void SendData_Set_Wifi(uint8_t hdata)
{
	    outputBuf[0]='T'; //
		outputBuf[1]='K'; //58
		outputBuf[2]='W'; //W ->WIFI
		outputBuf[3]=hdata; 
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
	
}
/*********************************************************
 * 
 * Function Name:void SendData_Temp_Data(uint8_t tdata)
 * Function:send temperature value 
 * 
*********************************************************/
void SendData_Temp_Data(uint8_t tdata)
{

        outputBuf[0]='T'; //4D
		outputBuf[1]='K'; //58
		outputBuf[2]='M'; //"T"->temperature
		outputBuf[3]=tdata; //53	//
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}

}
/*********************************************************
 * 
 * Function Name:void SendData_Time_Data(uint8_t tdata)
 * Function:send to set  timer timing value
 * 
*********************************************************/
void SendData_Time_Data(uint8_t tdata)
{

        outputBuf[0]='T'; //4D
		outputBuf[1]='K'; //58
		outputBuf[2]='T'; //"T"->temperature
		outputBuf[3]=tdata; //53	//
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}

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
    
	if(huart==&huart1) // Motor Board receive data (filter)
	{
		switch(state)
		{
		case 0:  //#0
			if(inputBuf[0]=='M')  //hex :4D - "M" -fixed mainboard
				state=1; //=1
			break;
		case 1: //#1
			if(inputBuf[0]=='A') //hex : 41 -'A'  -fixed master
			{
				state=2; 
			}
			else
				state=0; 
			break;
		case 2://#2
			if(inputBuf[0]=='D' || inputBuf[0]=='W'   ||inputBuf[0] =='C' || inputBuf[0] == 'B' \
			 ||inputBuf[0] == 'S' || inputBuf[0]=='T'||inputBuf[0]=='E'|| inputBuf[0] =='N'|| inputBuf[0] =='M') //'D'->data , 'W' ->wifi
			{
				
				if(inputBuf[0]=='D') decoder_t.single_data=PANEL_DATA; //receive data is single data
                else if(inputBuf[0]=='W') decoder_t.single_data = WIFI_INFO; //wifi data
				else if(inputBuf[0]=='C') decoder_t.single_data = WIFI_CMD; //command 
				else if(inputBuf[0]=='B') decoder_t.single_data = BEIJING_HOURS_TIME;
				else if(inputBuf[0]=='S') decoder_t.single_data = WIFI_WIND_SPEED;
				else if(inputBuf[0]=='T') decoder_t.single_data = PHONE_SET_TIMER_TIMING;
				else if(inputBuf[0]=='E') decoder_t.single_data = PHONE_SET_TEMPERATURE;
				else if(inputBuf[0]=='M') decoder_t.single_data = BEIJING_MINUTES_TIME;
				else if(inputBuf[0]=='N') decoder_t.single_data = BEIJING_SECOND_TIME;
			    state=3;
			}
			else
				state=0;
			break;
            
        case 3:

            switch(decoder_t.single_data){
             case PANEL_DATA://1
                 ctl_t.gReal_humidity_value  =inputBuf[0]; //Humidity value 
                 state = 4;  
            break;
            case WIFI_INFO ://2
                  if(inputBuf[0]==0x01){
                     ctl_t.gWifi_flag =1;
					 
				   }
                  else if(inputBuf[0]==0x0){
                     ctl_t.gWifi_flag =0;
                  }
				  else if(inputBuf[0]==0x52){ //answer signal 
				        pro_t.ack_wifi_led =1;
                    
				  }
                  else if(inputBuf[0]==0x54){
                    
                     // pro_t.wifi_receive_power_on_flag =1;
					 pro_t.ack_power_on_sig =1;

                  }
                  else if(inputBuf[0]==0x53){
                    
                      //pro_t.wifi_receive_power_off_flag =1;
					  pro_t.ack_power_off_sig =1;

                  }
                  
                 
                   pro_t.decodeFlag=0; 
                   state=0;
                 
             
            break;

            case WIFI_CMD://5
                 decoder_t.d_cmd[0] =inputBuf[0];
                 state=0;
                  pro_t.decodeFlag=1;
            break;

            case WIFI_WIND_SPEED:
                 //pro_t.wifi_set_wind_speed=inputBuf[0];
				 //fan_speed_state()=inputBuf[0];
				 ctl_t.gFan_speed_value = inputBuf[0];
                 state=0;
                  pro_t.decodeFlag=1;

             break;
			

             case PHONE_SET_TIMER_TIMING:
             		ctl_t.gSet_timer_hours  = inputBuf[0];
             		 state=0;
                    pro_t.decodeFlag=1; 

             break;

			 case PHONE_SET_TEMPERATURE:
			     ctl_t.gSet_temperature_value=inputBuf[0]; 
                 state=0;
                 pro_t.decodeFlag=1;

			 break;


			  case BEIJING_HOURS_TIME:
			 	
			  	 
                   disp_t.disp_works_hours_time  = inputBuf[0];
				
					 state=0;
		              pro_t.decodeFlag=1;
              
                 
             break;

			 case  BEIJING_MINUTES_TIME:
			 	
			 	   disp_t.disp_works_minutes_time = inputBuf[0];
			
				   state=0;
		           pro_t.decodeFlag=1;
			 		


			 break;

			 case BEIJING_SECOND_TIME:
				
	
				disp_t.gTimer_disp_minutes_time = inputBuf[0]+1;
		
				// pro_t.decodeFlag=1;
				state=0;
			 break;

         	}

            
        break;
        
		case 4: //

		switch(decoder_t.single_data==PANEL_DATA){

				case PANEL_DATA:

			  disp_t.disp_dht11_temp_value= inputBuf[0]; //DHT11 temperature value
              //pro_t.gReal_humtemp[1]=inputBuf[0]; //temperature value
			
		     state=0;
		     pro_t.decodeFlag=1;
	         
           
		    break;

			}

		 break;
           
    
		
		
		default:
			state=0;
			 pro_t.decodeFlag=0;  //
		break;

		}
      HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte

	__HAL_UART_CLEAR_NEFLAG(&huart1);
	__HAL_UART_CLEAR_FEFLAG(&huart1);
	__HAL_UART_CLEAR_OREFLAG(&huart1);
	__HAL_UART_CLEAR_OREFLAG(&huart1);
	__HAL_UART_CLEAR_TXFECF(&huart1);

	}
    #if NORMAL_USART2
	//Voice USART 2 
	if(huart==&huart2){ // Motor Board receive data (filter)
	
      if(voice_inputBuf[pro_t.v_usart2_rx_numbers]==0xA5){
        pro_t.v_usart2_rx_flag =1;
		pro_t.v_usart2_rx_numbers =0;
	  }
	  if( pro_t.v_usart2_rx_flag==0)pro_t.v_usart2_rx_numbers =0;

	  
	  if(pro_t.v_usart2_rx_flag  ==1){
	      v_rx_data[pro_t.v_usart2_rx_numbers]=voice_inputBuf[pro_t.v_usart2_rx_numbers];
		  pro_t.v_usart2_rx_numbers++;
          if(pro_t.v_usart2_rx_numbers==8){
		  	pro_t.v_usart2_rx_flag=2;
		   v_t.rx_voice_data_flag = 1;

          }
		 
      }

	HAL_UART_Receive_IT(&huart2,voice_inputBuf,8);//UART receive data interrupt 1 byte

	  
	__HAL_UART_CLEAR_NEFLAG(&huart2);
	__HAL_UART_CLEAR_FEFLAG(&huart2);
	__HAL_UART_CLEAR_OREFLAG(&huart2);
	__HAL_UART_CLEAR_OREFLAG(&huart2);
	__HAL_UART_CLEAR_TXFECF(&huart2);

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
void USART1_Cmd_Error_Handler(void)
{
    uint32_t temp;
	if(pro_t.gTimer_usart_error > 9 ){
		pro_t.gTimer_usart_error=0;
		__HAL_UART_CLEAR_NEFLAG(&huart1);
		__HAL_UART_CLEAR_FEFLAG(&huart1);
		__HAL_UART_CLEAR_OREFLAG(&huart1);
		__HAL_UART_CLEAR_OREFLAG(&huart1);
		__HAL_UART_CLEAR_TXFECF(&huart1);

		temp = USART1->RDR;

		UART_Start_Receive_IT(&huart1,inputBuf,1);
			
	}
}
/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}
	
}

