#ifndef XM_MOTOR_H
#define XM_MOTOR_H

#include "Xm_Abstract.h"
#include "board_controller.h"
#include "string.h" 
const int PULSE[4]={503808,440000,335000,75000}; 
class Xm_Motor
{
	public:
		
		Xm_Motor()
		{
			memset(arm_cmd,16*sizeof(uint8_t),0);
			memset(byte,4*sizeof(uint8_t),0);
			memset(speed,2*sizeof(short),0);
			Flag1_CAN_Receive=0;
			Flag2_CAN_Receive=0;		
		}
		short speed[2];
		uint8_t byte[4];	
		uint8_t arm_cmd[16];
		uint8_t Flag1_CAN_Receive;
		uint8_t Flag2_CAN_Receive;
	/*****************************************************************************/		
		short get_speed_m1(void){chassis_read_speed();return speed[0];}
		short get_speed_m2(void){chassis_read_speed();return speed[1];}
		void wheel_control(void);
		void chassis_init(void);
		void arm_control(void);
		void arm_read(void);
		void arm_home(void);
	/*****************************************************************************/
	private:
		void motor_speed(unsigned int CAN_ID,short temp_velocity);
		void motor_reset(unsigned int CAN_ID);
		void motor_clear(unsigned int CAN_ID);
		void motor_mode(unsigned int CAN_ID,unsigned char mode);
		void motor_config(unsigned int CAN_ID,unsigned char temp_time);
		void motor_math_itoh(int N, uint8_t *h);
		void motor_math_htoi(uint8_t *h, int *a);
		void chassis_read_speed(void);
		void chassis_clear(void);
		void arm_motor_read(unsigned int CAN_ID);
		void arm_angle(unsigned char ARM_ID,float angle);
		void arm_clear(void);
		void can_timeout(void);
		
};

extern Xm_Motor xm_motor;

#endif

