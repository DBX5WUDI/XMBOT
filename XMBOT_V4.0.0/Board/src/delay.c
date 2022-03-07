#include "delay.h"

float reload = 0;
float count_time = 0;
void System_Timer_Init(void)   
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

    reload = 16777215;

    SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk; 	//开启中断
    SysTick->LOAD =reload;						//LOAD装载初值 		
    SysTick->VAL  = reload;						//同步寄存器VAL装载初值
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk; 	//开启SYSTICK
}

void delay_us(uint16_t t)
{
    int i;	
    for( i=0 ; i<t ; i++)
    {
        int a = 25 ;
        while(a--) 
        __nop();
    }
}

void delay_ms(uint16_t t)
{
    unsigned int i;
    for( i=0 ; i<t ; i++)
    {
        int a = 33568;
        while(a--) 
         __nop();
    }
}
void SysTick_Handler(void)
{
    count_time++;
    if(count_time >= 0xffffffff)
    {
        count_time=0;
    }
}


