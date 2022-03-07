#ifndef XM_ABSTRACT_H
#define XM_ABSTRACT_H

struct MSGServo3
{
    float  servo1;
    float  servo2;
		float  servo3;
};

struct MSGServo4
{
    float  servo1;
    float  servo2;
    float  servo3;
    float  servo4;
};

struct MSGServo5
{
    float  servo1;
    float  servo2;
    float  servo3;
    float  servo4;
		float  servo5;
};

struct MSGServo6
{
    float  servo1;
    float  servo2;
    float  servo3;
    float  servo4;
    float  servo5;
    float  servo6;
};

struct MSGCoord
{
    float  x;
    float  y;
    float  z;
};

struct MSGPose
{
    float  pitch;
    float  roll;
    float  yaw;
};


struct MSGRobotParameters
{
    float robot_wheel_radius;
    float robot_body_radius;
    float speed_low_filter;
};

struct MSGMotorParameters
{
    float p1;
    float i1;
    float d1;
    float p2;
    float i2;
    float d2;
};

class Xm_Abstract
{
	public:
    Xm_Abstract()
    {
		robot_parameters.robot_wheel_radius=0.071f;
        robot_parameters.robot_body_radius=0.241f;
		
        expect_global_speed.x=0;
        expect_global_speed.y=0;
        expect_global_speed.z=0;

        measure_global_speed.x=0;
        measure_global_speed.y=0;
        measure_global_speed.z=0;

        expect_robot_speed.x=0;
        expect_robot_speed.y=0;
        expect_robot_speed.z=0;

        measure_robot_speed.x =0;
        measure_robot_speed.y =0;
        measure_robot_speed.z =0;

        expect_motor_speed.servo1=0;
        expect_motor_speed.servo2=0;
        expect_motor_speed.servo3=0;

        measure_motor_speed.servo1=0;
        measure_motor_speed.servo2=0;
        measure_motor_speed.servo3=0;

        measure_motor_mileage.servo1=0;
        measure_motor_mileage.servo2=0;
        measure_motor_mileage.servo3=0;

        measure_global_coordinate.x=0;
        measure_global_coordinate.y=0;
        measure_global_coordinate.z=0;

        measure_robot_coordinate.x=0;
        measure_robot_coordinate.y=0;
        measure_robot_coordinate.z=0;

        measure_imu_euler_angle.pitch=0;
        measure_imu_euler_angle.roll=0;
        measure_imu_euler_angle.yaw=0;

		claw_state_ =0;
		claw_state_back=0;
		wrist_angle_=0;
		wrist_angle_back=0;	
		plat_height_=0;
		plat_height_back=0;
	}
    /************************************parameters***********************************/
		MSGRobotParameters robot_parameters;
		MSGMotorParameters motor_parameters;	
	/*************************************classic*************************************/
		MSGCoord   expect_robot_speed;
		MSGServo4  expect_motor_speed;
		MSGCoord   expect_global_speed;
		MSGCoord   measure_robot_speed;	
		MSGServo4  measure_motor_speed;	
		MSGCoord   measure_global_speed;
		MSGServo4  measure_motor_mileage;
		MSGCoord   measure_robot_coordinate;	
		MSGCoord   measure_global_coordinate; 
	/************************************IMU Sensors***********************************/
		MSGPose   measure_imu_euler_angle; 
	/************************************arm*******************************************/
		MSGServo4 expect_arm_state;
		MSGServo4 measure_arm_state;  
	/************************************claw******************************************/
		unsigned char  claw_state_;
		unsigned char  claw_state_back;
	/************************************wrist*****************************************/	
		float wrist_angle_;
		float wrist_angle_back;	
	/************************************platform**************************************/	
		float plat_height_; 
		float plat_height_back;	
};
extern Xm_Abstract xm_robot;
#endif
