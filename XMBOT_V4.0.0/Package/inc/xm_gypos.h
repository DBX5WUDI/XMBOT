#ifndef XM_GYPOS_H
#define XM_GYPOS_H

#include "board_controller.h"
#include "string.h"

	
class Xm_Gypos 
{
	public:
		Xm_Gypos()
		{
			yaw_angle=0;
			can2_flag=0;
			gypos_fliter=0.01;
			d_last_yaw_angle=0;
			memset(GYPOS_data,4*sizeof(uint8_t),0);
		}
		uint8_t GYPOS_data[4];//CAN2接受数据后首先存储地址
		uint8_t can2_flag;
		float  get_gypos(void);
	/****************************************************************************************/
	private:
		float yaw_angle;
		float gypos_fliter;
		float d_last_yaw_angle;	
};
extern Xm_Gypos xm_gypos;
#endif
