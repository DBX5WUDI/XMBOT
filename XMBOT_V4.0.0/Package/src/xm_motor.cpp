#include "xm_motor.h"

Xm_Motor xm_motor;

void Xm_Motor::motor_config(unsigned int CAN_ID,unsigned char temp_time)
{
		
    uint8_t can_cmd[8];
     
    can_cmd[0] = temp_time;
    can_cmd[1] = 0x00;
    can_cmd[2] = 0x55;
    can_cmd[3] = 0x55;
    can_cmd[4] = 0x55;
    can_cmd[5] = 0x55;
    can_cmd[6] = 0x55;
    can_cmd[7] = 0x55;
    
   
    board_controller.Motor_Sendmessage(CAN_ID,can_cmd);
}
void Xm_Motor::motor_speed(unsigned int CAN_ID,short temp_velocity)
{
	 
	uint8_t can_cmd[8];
    if(temp_velocity > 2000)
    {
        temp_velocity = 2000;
    }
    else if(temp_velocity < -2000)
    {
        temp_velocity = -2000;
    }
    
    can_cmd[0] = (unsigned char)(5000>>8)&0xff;
    can_cmd[1] = (unsigned char)5000&0xff;
    can_cmd[2] = (unsigned char)((temp_velocity>>8)&0xff);
    can_cmd[3] = (unsigned char)(temp_velocity&0xff);
    can_cmd[4] = 0x55;
    can_cmd[5] = 0x55;
    can_cmd[6] = 0x55;
    can_cmd[7] = 0x55;
    
    board_controller.Motor_Sendmessage(CAN_ID,can_cmd);
}
void Xm_Motor::motor_clear(unsigned int CAN_ID)
{
		uint8_t can_cmd[8];
    
    can_cmd[0] = (unsigned char)(5000>>8)&0xff;
    can_cmd[1] = (unsigned char)5000&0xff;
    can_cmd[2] = (unsigned char)(0);
    can_cmd[3] = (unsigned char)(0);
    can_cmd[4] = 0x55;
    can_cmd[5] = 0x55;
    can_cmd[6] = 0x55;
    can_cmd[7] = 0x55;
    board_controller.Motor_Sendmessage(CAN_ID,can_cmd);
   
}
void Xm_Motor::motor_reset(unsigned int CAN_ID)
{
	uint8_t can_cmd[8];
      
	can_cmd[0] = 0x55;
	can_cmd[1] = 0x55;
	can_cmd[2] = 0x55;
	can_cmd[3] = 0x55;
	can_cmd[4] = 0x55;
	can_cmd[5] = 0x55;
	can_cmd[6] = 0x55;
	can_cmd[7] = 0x55;
    
    board_controller.Motor_Sendmessage(CAN_ID,can_cmd);
}
void Xm_Motor::motor_mode(unsigned int CAN_ID,unsigned char mode)
{
	
    uint8_t can_cmd[8];
    
    can_cmd[0] = mode;
    can_cmd[1] = 0x55;
    can_cmd[2] = 0x55;
    can_cmd[3] = 0x55;
    can_cmd[4] = 0x55;
    can_cmd[5] = 0x55;
    can_cmd[6] = 0x55;
    can_cmd[7] = 0x55;
    
    board_controller.Motor_Sendmessage(CAN_ID,can_cmd);
}
void Xm_Motor::motor_math_itoh(int N, uint8_t *h)
{
	int count=0;
	uint8_t a[10]={0};

    while(N != 0)
    {
       a[count++]=N&0xf;
       N>>=4;
			if(count==8) break;
    }
		
    *h=(a[1]<<4)|a[0];
    *(h+1)=(a[3]<<4)|a[2];
    *(h+2)=(a[5]<<4)|a[4];
    *(h+3)=(a[7]<<4)|a[6];
}
void Xm_Motor::chassis_clear(void)
{
	motor_clear(0x104);
	motor_clear(0x114);
}
void Xm_Motor::chassis_init(void)
{
	delay_ms(1000);
	motor_reset(0x100);
	delay_ms(1000);
	motor_mode(0x111,0x03);
	motor_mode(0x131,0x03);
	delay_ms(1000);
	motor_config(0x11a,0x02);
    motor_config(0x13a,0x02);
	delay_ms(1000);		
	chassis_clear();
	delay_ms(1000);	
}
void Xm_Motor::wheel_control(void)
{
	short Speed_M1,Speed_M2;

	Speed_M1=(xm_robot.expect_motor_speed.servo1)/(2*3.1416)*2940;		
	motor_speed(0x114,(short)(-Speed_M1));
	Speed_M2=(xm_robot.expect_motor_speed.servo2)/(2*3.1416)*2940;		
	motor_speed(0x134,(short)Speed_M2);
}
void Xm_Motor::can_timeout(void)
{
	uint32_t i = 0;
	while(Flag2_CAN_Receive==0)
	{
			i++;
				if(i>0x2fff)
				{
					i=0;
					break;
				}	
			}	
}
void Xm_Motor::chassis_read_speed(void)
{
	speed[0] = -((byte[0]<<8)|byte[1]);
	speed[1] = (byte[2]<<8)|byte[3];
}
void Xm_Motor::arm_angle(unsigned char ARM_ID,float angle)
{
	float pluse;
	uint8_t pdata[4];
	uint8_t can_cmd[8];

		
	can_cmd[3] = 0x00;
	can_cmd[2] = 0x99;
	can_cmd[1] = ARM_ID;
	can_cmd[0] = 0x08;
			
	pluse = (angle/(2*3.1416))*PULSE[(ARM_ID-0X2C)];
			
	motor_math_itoh(pluse,pdata); 
	
	can_cmd[4]=*pdata;
	can_cmd[5]=*(pdata+1);
	can_cmd[6]=*(pdata+2);
	can_cmd[7]=*(pdata+3);
	board_controller.Motor_Sendmessage(ARM_ID,can_cmd);
	can_timeout();
}
void Xm_Motor::arm_clear(void)
{
	unsigned int CAN_ID=0x2D;
	uint8_t can_cmd[8]={0x08,0x2D,0x98,0x00,0x00,0x00,0x00,0x00};
	for(int i=0;i<3;i++)
	{
		board_controller.Motor_Sendmessage(CAN_ID,can_cmd);
		delay_us(1000);
	}
}
void Xm_Motor::arm_home(void)
{
	float cmd1 = 0.0, cmd2 = 1.57, cmd3 = 0, cmd4 = 0; 
	uint8_t num;
	float action[4];
	*(action) = cmd1;
	*(action+1) = -3*cmd2;
	*(action+2) = cmd3;
	*(action+3) =  cmd4 +3/4*cmd3;
	
	for(num=0;num<4;num++)
	{
		arm_angle(num+0X2C,*(action+num));
	}
	delay_ms(5000);
	arm_clear();
}
void Xm_Motor::arm_motor_read(unsigned int CAN_ID)
{
	uint8_t can_cmd[8];
	can_cmd[3] = 0x00;
	can_cmd[2] = 0x9B;
	can_cmd[1] = CAN_ID;
	can_cmd[0] = 0x08;
	can_cmd[4] = 0x00;
	can_cmd[5] = 0x00;
	can_cmd[6] = 0x00;
	can_cmd[7] = 0x00;
	board_controller.Motor_Sendmessage(CAN_ID,can_cmd);
	can_timeout();
	
}
void Xm_Motor::motor_math_htoi(uint8_t *h, int *a)
{
    *a=((*h)<<24|(*(h+1)<<16)|(*(h+2)<<8)|*(h+3));
}
void Xm_Motor::arm_read(void)
{
	uint8_t num;
	float pluse;
	int pluse_t;
	float angle[4];
	float cmd[4]={0};
		for(num=0;num<4;num++)
	{
		arm_motor_read(num+0X2C);
		motor_math_htoi((arm_cmd+num*4),&pluse_t);
		pluse=pluse_t;
		angle[num] = (pluse/PULSE[num])*(2*3.1416);
		
	}
	cmd[0] = angle[0];
	cmd[1] = -angle[1]/3;
	cmd[2] = angle[2];
	cmd[3] = angle[3]-(float)0.8*angle[2] ;
	memcpy(&(xm_robot.measure_arm_state),cmd,sizeof(xm_robot.measure_arm_state));
}

void Xm_Motor::arm_control(void)
{
	uint8_t num;
	float action[4];
	*(action)   = xm_robot.expect_arm_state.servo1;
	*(action+1) = -3*xm_robot.expect_arm_state.servo2;
	*(action+2) = xm_robot.expect_arm_state.servo3;
	*(action+3) = xm_robot.expect_arm_state.servo4 + (float)0.8*xm_robot.expect_arm_state.servo3;
	
	for(num=0;num<4;num++)
	{
		arm_angle(num+0X2C,*(action+num));
	}

}



