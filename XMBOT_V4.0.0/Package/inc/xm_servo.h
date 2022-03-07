#ifndef XM_SERVO_H
#define XM_SERVO_H

#include "servo_digital.h"

class Xm_Servo:public ServoDigital
{
	public:
		Xm_Servo()
		{
			
		}
		void set_wrist_angle(float angle);
		void set_claw_state(uint8_t claw_state);
		void wrist_claw_home(void);
	private:


};

extern Xm_Servo xm_servo;
#endif
