#include "bsp_key.h"
#include "bsp.h"



key_types key_t;
uint8_t power_key_detected;
uint16_t key_mode_counter;

uint8_t (*power_on_off_state)(void);

static uint8_t power_default_fun(void);

uint8_t key_set_timer_flag;

void Key_Init(void)
{
   Power_Handler(power_default_fun);

}


uint8_t KEY_Scan(void)
{

   uint8_t  reval = 0;
 
  key_t.read = _KEY_ALL_OFF; //0xFF 
  
  
    if(POWER_KEY_VALUE() ==KEY_DOWN )// high level
    {
        key_t.read &= ~0x01; // 0xff & 0xfe =  0xFE
    }
//    if(DEC_KEY_VALUE()==KEY_DOWN )
//	{
//		  key_t.read &= ~0x04; // 0xFf & 0xfB =  0xFB
//	}
//    else if(ADD_KEY_VALUE() ==KEY_DOWN )
//	{
//		  key_t.read &= ~0x08; // 0x1f & 0xf7 =  0xF7
//	 }
    else if(MODE_KEY_VALUE() ==KEY_DOWN )
	{
		key_t.read &= ~0x02; // 0xFf & 0xfd =  0xFD
	}
    
   

    switch(key_t.state )
	{
		case start:
		{
			if(key_t.read != _KEY_ALL_OFF)
			{
				key_t.buffer   = key_t.read; //??:key.buffer = 0xFE  POWER KEY 
				key_t.state    = first;
				key_t.on_time  = 0;
				key_t.off_time = 0;
                
			}
			break;
		}
		case first:
		{
			if(key_t.read == key_t.buffer) // adjust key be down ->continunce be pressed key
			{

			 if(++key_t.on_time>59 ){

					key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0xFE ^ 0xFF = 0x01
					key_t.on_time = 0;                        //key .value = 0xEF ^ 0XFF = 0X10
                   
					key_t.state   = second;


				 }
			}
			else
			{
				key_t.on_time = 0; 
				key_t.state   = start;
			}
			break;
		}
		case second:
		{
			if(key_t.read == key_t.buffer) //again adjust key if be pressed down 
			{
				if(++key_t.on_time> 1000 && pro_t.gPower_On ==1)// 500 long key be down
				{
					
					key_t.value = key_t.value|0x80; //key.value(power_on) = 0x01 | 0x80  =0x81  
					key_t.on_time = 0;               //key.vaule(model_key) = 0x01 | 0x80 = 0x82
					key_t.state   = finish; 
                   
				}
			}
			else if(key_t.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key_t.off_time>1) //8 //30 don't holding key dithering
					{
						key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
						key_t.state   = finish; // loose hand
					}
					
				}
		   
			break;
		}
		case finish:
		{
			
			reval = key_t.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key_t.state   = end;
         
			break;
		}
		case end:
		{
			if(key_t.read == _KEY_ALL_OFF)
			{
				if(++key_t.off_time>0)//50 //100
				{
					key_t.state   = start;
                   
                  
				}
				
			}
			break;
		}
		default:
		{
			key_t.state   = start;
            
			break;
		}
	}
	return  reval;


}



/********************************************************************
*
*Function Name:
*Function: interrupt of GPIO of call back function
*
*
*
*********************************************************************/
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
   //static uint16_t key_power_counter,add_key_counter,dec_key_counter;
 
    uint16_t K1,K2;
	switch(GPIO_Pin){

	case KEY_POWER_Pin:

		if(POWER_KEY_VALUE() == KEY_DOWN && pro_t.gPower_On ==0){

			pro_t.gKey_value = power_on;
			//pro_t.gPower_On=1;
			K1=0;
		}
		else if(POWER_KEY_VALUE() == KEY_DOWN){

		    while(POWER_KEY_VALUE() == KEY_DOWN){

               K1++;
			   if(K1 > 60000){
                  K1= 0;
				 // ctl_t.gWifi_flag =1;
				  pro_t.gKey_value = wifi_fun_on;
                  return ;
              
			   }
			}
			K1=0;
			//pro_t.gPower_On=0;
			pro_t.gKey_value = power_off;

		}


    break;

	case KEY_MODE_Pin:


	if(MODE_KEY_VALUE() ==KEY_DOWN && pro_t.gPower_On==1 ){

        while(ADD_KEY_VALUE() ==KEY_DOWN){
            K2++;
		
			if(K2 > 60000){
                  K2= 0;
				 // ctl_t.gWifi_flag =1;
				 pro_t.key_set_timer_flag =1;
                 return ;
              
			}
		}
       
		//pro_t.gKey_command_tag = ADD_KEY_ITEM;
		if(ctl_t.gAi_flag == mode_ai){
		     pro_t.gKey_value = mode_no_ai;
		}
	    else{
			pro_t.gKey_value = mode_ai;
		}
		

	}
	break;

	case KEY_DEC_Pin:

	if(DEC_KEY_VALUE() ==KEY_DOWN &&  pro_t.gPower_On==1){

	    while(DEC_KEY_VALUE() == KEY_DOWN);

		//pro_t.gKey_command_tag = DEC_KEY_ITEM;
		pro_t.gKey_value = dec_key;
	
	}

	break;


	case KEY_ADD_Pin:

	if(ADD_KEY_VALUE() == KEY_DOWN && pro_t.gPower_On ==1){

        while(ADD_KEY_VALUE() == KEY_DOWN);

		//pro_t.gKey_command_tag = ADD_KEY_ITEM;
		pro_t.gKey_value = add_key;

	}


	break;



	}

}


/***********************************************************
 *  *
    *Function Name: uint8_t ReadKey(void)
    *Function: 
    *Input Ref: NO
    *Return Ref: 
    * 
***********************************************************/
#if 0
uint8_t ReadKey(void)
{


 // static uint16_t  K1=0;
 // static uint16_t  K2=0;

//  static uint8_t cnt;
  //uint8_t 	 	value1 = 0;
 // uint8_t   	value2 = 0;

//	if(!T1msFlag)  //10ms check once 
//		return value1;
//	T1msFlag = 0;
	
  if(FUN_KEY_VALUE() ==KEY_DOWN && CONFIRM_KEY_VALUE()==KEY_UP){ //KEY1 =POWER_KEY ,KEY2 = MODES
		cnt = 0;
		pro_t.long_key_flag =0;
		K1++;	 //Fun_key press 
  }
  else if( CONFIRM_KEY_VALUE()==KEY_DOWN && pro_t.long_key_flag ==0){
		cnt = 0;
		K2++;   //Confirm_key press
		if(pro_t.keep_temp_flag ==1){
           if(K2 > 199000){
              K2=0;
			  cnt = 0;
		      K1 = 0;
			  value1=0;
			  value2=0;
			  pro_t.long_key_flag =1;
			  
			  return 0x82;
            }


		}
  }
  else if(FUN_KEY_VALUE()==0 && CONFIRM_KEY_VALUE()==0 && pro_t.long_key_flag ==0){ //oneself key 
		cnt++;
		if(cnt<70){ //按键松开消抖,一定要大于短按键次数 > 20
		    return 0; 

		}
		
		cnt = 0;//
		if(K1>60){ //KEY_FUN
			value1 = 0x01;	//short time power press ---power on 
		}
		else{
			value1 = 0;

		}

		//KEY_CONFIRM 
		if(K2>60 ){//short time modes press 
            value2 = 0x02;

		}
//		else if(K2>60000){
//			value2 = 0x82;  //long time power press
//		}
		else{ 
			value2 = 0;
		}
		 	
		
		K1 = 0;
		K2 = 0;		

		return (value1+value2);
	}

   //judge key combination
    #if 0
	if((K1==500) && (K2<50)) //combination key 
		value1 = 0x03;
	else if(K2==500 && K1<50)
		value2 = 0x30;
	else if(K1==100 && K2>100)
		value1 = 0x44;
	else if(K1>100 && K2==100)
		value1 = 0x44;
	

  return (value1+value2);
  #endif 
	
   return 0;
}
#endif 
/***********************************************************
 *  *
    *Function Name: static uint8_t power_default_fun(void);
    *Function: power turn on or turn off
    *Input Ref: NO
    *Return Ref:  1->turn on ,0-> turn off
    * 
***********************************************************/
static uint8_t power_default_fun(void)
{
      if(pro_t.gPower_On ==1) return 1;
	  else return 0;

}





