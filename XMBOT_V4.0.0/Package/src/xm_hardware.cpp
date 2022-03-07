#include "xm_hardware.h"

static const float degree_to_radian = 0.017453f;


Xm_Abstract xm_robot;
Xm_Hardware xm_hardware;

void Xm_Hardware::xmHardwareInit(void)
{
    set_robot_wheel_radius(xm_robot.robot_parameters.robot_wheel_radius);
    set_robot_body_radius (xm_robot.robot_parameters.robot_body_radius );		

	xm_motor.chassis_init();
	xm_motor.arm_home();
	xm_platform.platform_home();
	xm_servo.wrist_claw_home();
	
}
void Xm_Hardware::xmHardwareTopCall(void)
{
	robotDataUpdate();
	robotCoordCalc();
	chassisControl(); 
	platControl();
	armControl();
	wristControl();	
	clawControl();
}	

void Xm_Hardware::robotDataUpdate(void)
{
    xm_robot.measure_robot_speed.x =0;
    xm_robot.measure_robot_speed.y =0;
    xm_robot.measure_robot_speed.z =0;

    xm_robot.measure_motor_speed.servo1 = xm_motor.get_speed_m1() /(2940.0)*2*3.1416;
    xm_robot.measure_motor_speed.servo2 = xm_motor.get_speed_m2() /(2940.0)*2*3.1416;

	xm_robot.plat_height_back = xm_platform.current_h/100;
	
    getRobotSpeed((float* )&xm_robot.measure_motor_speed , (float* )&xm_robot.measure_robot_speed);
    getGlobalSpeed((float* )&xm_robot.measure_motor_speed , (float*)&xm_robot.measure_global_speed , xm_robot.measure_global_coordinate.z);
	xm_robot.measure_global_coordinate.z =xm_gypos.get_gypos()*degree_to_radian;	
}
void Xm_Hardware::robotCoordCalc(void)
{
		
	d_motor_len_filter_.m1 = (float)0.02* xm_robot.measure_motor_speed.servo1*get_robot_wheel_radius();
    d_motor_len_filter_.m2 = (float)0.02* xm_robot.measure_motor_speed.servo2*get_robot_wheel_radius();

    getGlobalCoordinate( (float* )&d_motor_len_filter_ , (float* )&xm_robot.measure_global_coordinate);
    getRobotCoordinate( (float* )&d_motor_len_filter_ , (float* )&xm_robot.measure_robot_coordinate);
	
	if(hf_link_node_pointer->receive_package_renew[CLEAR_COORDINATE_DATA]==1)
    {
        hf_link_node_pointer->receive_package_renew[CLEAR_COORDINATE_DATA]=0;
        xm_robot.measure_global_coordinate.x=0;
        xm_robot.measure_global_coordinate.y=0;
        xm_robot.measure_global_coordinate.z=0;
        xm_robot.measure_robot_coordinate.x=0;
        xm_robot.measure_robot_coordinate.y=0;
        xm_robot.measure_robot_coordinate.z=0;
    }		
}
void Xm_Hardware::chassisControl(void)    
{
	if( hf_link_node_pointer->receive_package_renew[SET_ROBOT_SPEED]==1)
	{
		hf_link_node_pointer->receive_package_renew[SET_ROBOT_SPEED ]=0;
		robotSpeedSet((float* )&xm_robot.expect_robot_speed , (float* )&xm_robot.expect_motor_speed);
	}		
	xm_motor.wheel_control();
}

void Xm_Hardware::platControl(void)
{
	if( hf_link_node_pointer->receive_package_renew[PLAT_MOVE]==1)
	{
		hf_link_node_pointer->receive_package_renew[PLAT_MOVE]=0;
		xm_platform.set_height(xm_robot.plat_height_);
	}
}
void Xm_Hardware::armControl(void)
{
	if(hf_link_node_pointer->receive_package_renew[SET_ARM_TOTAL])
	{
		hf_link_node_pointer->receive_package_renew[SET_ARM_TOTAL]=0;						
		xm_motor.arm_control();			
	}
}

void Xm_Hardware::wristControl(void)
{
	if(hf_link_node_pointer->receive_package_renew[SET_WRIST]==1)
	{
		hf_link_node_pointer->receive_package_renew[SET_WRIST]=0;
		xm_servo.set_wrist_angle(xm_robot.wrist_angle_);
	}
}

void Xm_Hardware::clawControl(void)
{
	if( hf_link_node_pointer->receive_package_renew[SET_CLAW]==1 ){
        hf_link_node_pointer->receive_package_renew[SET_CLAW]=0;
        xm_servo.set_claw_state(xm_robot.claw_state_);
	}
}


