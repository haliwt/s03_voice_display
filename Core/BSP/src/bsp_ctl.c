#include "bsp_ctl.h"
#include "bsp.h"


bsp_ctl ctl_t;


uint8_t (*wifi_state)(void);
uint8_t (*ptc_state)(void);
uint8_t (*ai_state)(void);
uint8_t (*fan_speed_state)(void);
uint8_t (*plasma_state)(void);
uint8_t (*bug_state)(void);
uint8_t (*humidity_value)(void);
uint8_t (*temperature_value)(void);

uint8_t (*smartphone_set_timer_timing)(void);
uint8_t (*smartphone_set_temp_value)(void);


uint8_t (*beijing_hours_time)(void);
uint8_t (*beijing_minutes_time)(void);




static uint8_t wifi_default_fun(void);
static uint8_t ptc_default_fun(void);
static uint8_t ai_default_fun(void);
static uint8_t fan_default_fun(void);
static uint8_t plasma_default_fun(void);
static uint8_t bug_default_fun(void);

static uint8_t humidity_default_fun(void);
static uint8_t temp_default_fun(void);

static uint8_t smartphone_set_timer_default_fun(void);
static uint8_t smartphone_set_temp_default_fun();


static uint8_t beijing_hours_fun(void);
static uint8_t beijing_minutes_fun(void);




/**********************************************************************************************************
*	函 数 名: void bsp_ctlint(void)
*	功能说明: 
*			 
*	形    参: 输入按键的键值
*	返 回 值: 无
**********************************************************************************************************/
void bsp_ctlint(void)
{
 
	Wifi_Handler(wifi_default_fun);
	Ptc_Handler(ptc_default_fun);
	Ai_Handler(ai_default_fun);
	Fan_Handler(fan_default_fun);
	Plasma_Handler(plasma_default_fun);
	Bug_Handler(bug_default_fun);
	
	Humidity_Handler(humidity_default_fun);
    Temp_Handler(temp_default_fun);

	Smartphone_Set_Timer_Handler(smartphone_set_timer_default_fun);
    Smartphone_Set_Temp_Handler(smartphone_set_temp_default_fun);

	
   Beijing_hours_Handler(beijing_hours_fun);
   Beijing_minutes_handler(beijing_minutes_fun);

}

/**********************************************************************************************************
	*	函 数 名: static uint8_t wifi_default_fun(void)
	*	功能说明: 
	*			 
	*	形    参: 输入按键的键值
	*	返 回 值: 1-link wifi net . 0-don't link wifi net
**********************************************************************************************************/
static uint8_t wifi_default_fun(void)
{
        if(ctl_t.gWifi_flag ==1) return 1;
		else return 0;


}
/**********************************************************************************************************
	*
	*	函 数 名: static uint8_t ptc_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-ptc    on. 0- ptc off 
	*
**********************************************************************************************************/
static uint8_t ptc_default_fun(void)
{
	if(ctl_t.gPtc_flag ==1) return 1;
	else return 0;


}
/************************************************************
	*
	*	函 数 名: static uint8_t ai_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-AI    on. 0- AI off 
	*
************************************************************/
static uint8_t ai_default_fun(void)
{
	if(ctl_t.gAi_flag ==1) return 1;
	else return 0;


}
/************************************************************
	*
	*	函 数 名: static uint8_t ai_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-AI    on. 0- AI off 
	*
************************************************************/
static uint8_t fan_default_fun(void)
{
	 return  ctl_t.gFan_speed_value;
	

}
/************************************************************
	*
	*	函 数 名: static uint8_t ai_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-plasma    on. 0- plasma off 
	*
************************************************************/
static uint8_t plasma_default_fun(void)
{
	if(ctl_t.gPlasma_flag ==1) return 1;
	else return 0;

}
/************************************************************
	*
	*	函 数 名: static uint8_t ai_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-bug    on. 0- bug off 
	*
************************************************************/
static uint8_t bug_default_fun(void)
{
	if(ctl_t.gBug_flag ==1) return 1;
	else return 0;


}
/************************************************************
	*
	*	函 数 名: static uint8_t ai_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-bug    on. 0- bug off 
	*
************************************************************/
static uint8_t humidity_default_fun(void)
{
	 return  ctl_t.gReal_humidity_value ;
}
/************************************************************
	*
	*	函 数 名: static uint8_t ai_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-bug    on. 0- bug off 
	*
************************************************************/
static uint8_t temp_default_fun(void)
{
   return ctl_t.gReal_tem_value;

}



static uint8_t smartphone_set_timer_default_fun(void)
{
     return ctl_t.gSet_timer_value;
}
static uint8_t smartphone_set_temp_default_fun()
{
    return ctl_t.gSet_temperature_value;
}


static uint8_t beijing_hours_fun(void)
{
    return ctl_t.gBeijing_hours_time;

}
static uint8_t beijing_minutes_fun(void)
{
   return ctl_t.gBeijing_minutes_time;
}

/************************************************************
	*
	*	函 数 名: static uint8_t ai_default_fun(void)
	*	功能说明: 
	*	形    参: NO
	*	返 回 值: 1-bug    on. 0- bug off 
	*
************************************************************/
void Wifi_Handler(uint8_t(*wifi_handler)(void))
{
     wifi_state = wifi_handler;

}
void Ptc_Handler(uint8_t(*ptc_handler)(void))
{
    ptc_state = ptc_handler;
}
void Ai_Handler(uint8_t(*ai_handler)(void))
{
	ai_state = ai_handler;
}
void Fan_Handler(uint8_t(*fan_handler)(void))
{
	fan_speed_state = fan_handler
}
void Plasma_Handler(uint8_t(*plasma_handler)(void))
{
    plasma_state = plasma_handler;
}
void Bug_Handler(uint8_t(*bug_handler)(void))
{
   bug_state = bug_handler;
}
void Humidity_Handler(uint8_t(*humi_handler)(void))
{
    humidity_value = humi_handler;
}
void Temp_Handler(uint8_t(*temp_handler)(void))
{
   temperature_value = temp_handler;
}

void Smartphone_Set_Timer_Handler(uint8_t(*set_timer_timing)(void))
{
  smartphone_set_timer_timing = set_timer_timing;
}

void Smartphone_Set_Temp_Handler(uint8_t(*set_temp_value)(void))
{
  smartphone_set_temp_value = set_temp_value;
}

void Beijing_hours_Handler(uint8_t(*beijing_hours_handler)(void))
{
	beijing_hours_time = beijing_hours_handler;

}
void Beijing_minutes_handler(uint8_t(*beijing_minutes_handler)(void))
{
    beijing_minutes_time = beijing_minutes_handler;

}



	
