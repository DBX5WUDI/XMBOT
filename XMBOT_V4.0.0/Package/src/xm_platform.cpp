#include "xm_platform.h"

Xm_Platform xm_platform;

void Xm_Platform::platform_home(void)
{
	set_height(0.6);
}

void Xm_Platform::platform_top_call(void)
{
	if (flag_home == 0)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 0)
		{
			delay_ms(20);
			if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == 0)
			{
				Pulse_counter=22178;
	            current_h=((float)xm_platform.Pulse_counter)/xm_platform.per_pulse*xm_platform.per_s;
	            set_height(0);
				flag_home=1;
			}
		}
	}
	if(plat_state==1)
	{
		plat_state=0;	
		TIM_Cmd(TIM3, DISABLE);
		Pulse_Num=0;
		if(dest_height>current_h)
		{
			board_controller.Foreward_Move();
			flag_dir=0xff;   
		}
		else
		{
			board_controller.Backward_Move();
			flag_dir=0x01; 
		}
		TIM_Cmd(TIM3, ENABLE); 
		Desp_Num=(int)(fabs(dest_height-current_h)/per_s*per_pulse);
	}
}
void Xm_Platform::set_height(float height_)
{
	plat_state=1;
	dest_height= height_*100;
}
