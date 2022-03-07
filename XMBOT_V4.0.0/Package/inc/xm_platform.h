#ifndef XM_PLATFORM_H
#define XM_PLATFORM_H

#include "Xm_Abstract.h"
#include "board_controller.h"
#include "math.h"
class Xm_Platform
{
	public:
		Xm_Platform()
		{
			flag_home=0;
			Desp_Num = 0;
			current_h = 0; 
			Pulse_Num = 0;
			per_s = 0.505f;
			flag_dir = 0xff;
			dest_height = 0;
			per_pulse = 1600;
			Pulse_counter = 0;
			plat_state=0;
		}
	/**************************************************************************************************/
		void platform_home(void);
		void set_height(float height_);	
		void platform_top_call(void);		
	/**************************************************************************************************/		
		float current_h;
		float dest_height;
		float per_s;
		int Pulse_Num;    	
		int Desp_Num;     	
		int Pulse_counter;
		uint8_t flag_home;
		uint8_t flag_dir ;	
		uint16_t per_pulse; 
		uint8_t plat_state;
};
extern Xm_Platform xm_platform;
#endif
