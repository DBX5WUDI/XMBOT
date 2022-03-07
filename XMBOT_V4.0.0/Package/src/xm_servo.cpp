#include "xm_servo.h"

static const float radian_to_degree = 57.2958f;

Xm_Servo xm_servo;

void Xm_Servo::set_wrist_angle(float angle)
{
	float angle_wrist;
	const float pulse=1024.0/300.0;
		
	if(angle>=0)
	{
		angle_wrist=0x170+(uint16_t)(pulse*angle*radian_to_degree);
	}
	if(angle<0)
	{
		angle=-angle;
		angle_wrist=0x170-(uint16_t)(pulse*angle*radian_to_degree);
	}
	axSendPosition(0x04,angle_wrist, 0x90);	
}

void Xm_Servo::set_claw_state(uint8_t claw_state)
{
	float angle_claw;
	    
    switch (claw_state)
		{
			case 0 : angle_claw=(uint16_t)484;break;
			case 1 : angle_claw=(uint16_t)550;break;
			case 2 : angle_claw=(uint16_t)816;break;
		}
	axSendPosition(0x03, angle_claw , 0x90);
}

void Xm_Servo::wrist_claw_home(void)
{
	axTorqueOn(0x03);									
	delay_ms(500);
	set_claw_state(0);  							
	delay_ms(500);
	axSendPosition(0x04,0x170,0x90);		
	delay_ms(500);
}
