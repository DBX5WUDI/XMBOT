#include "xm_gypos.h"
Xm_Gypos xm_gypos;
float Xm_Gypos::get_gypos(void)
{
	float temp_yaw_angle;
	float this_yaw_angle;
	float d_this_yaw_angle;

	temp_yaw_angle = (int32_t)(GYPOS_data[0]<<24)|(int32_t)(GYPOS_data[1]<<16) 
            |(int32_t)(GYPOS_data[2]<<8)|(int32_t)(GYPOS_data[3]);
  
	this_yaw_angle = ((float)temp_yaw_angle*gypos_fliter);
		 
	if(this_yaw_angle>36000||this_yaw_angle<-36000)
	{
		this_yaw_angle =  yaw_angle;
	}			
	
	d_this_yaw_angle=(this_yaw_angle -yaw_angle);			
	
	if(d_this_yaw_angle > 500||d_this_yaw_angle<-500)
	{
		d_this_yaw_angle=d_last_yaw_angle;
	}
						
	d_last_yaw_angle=d_this_yaw_angle;
	yaw_angle  = yaw_angle + d_this_yaw_angle;	
	
	return yaw_angle;
}


