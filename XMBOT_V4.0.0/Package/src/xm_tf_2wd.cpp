#include "xm_tf_2wd.h"


/**************************robot speed -> wheel line speed**********************************/
void TF_2WD::robotToMotorTF(const float* robot , float* motor , float robot_r)   
{	
    *motor = 1 * (*robot) + 0 * (*(robot+1)) + robot_r * (*(robot+2)) ;			//轮1线速度=机器人线速度速度+机器人半径*机器人转速
    *(motor + 1) =  1 * (*robot) + 0 * (*(robot+1)) - robot_r * (*(robot+2)) ;	//轮2线速度=机器人线速度速度-机器人半径*机器人转速
}
void TF_2WD::robotToGlobalTF(const float* robot , float* global ,float R_theta)   
{
    *global = cos(R_theta)*(*robot) - sin(R_theta) * (*(robot+1)) +  0 * (*(robot+2)) ;
    *(global + 1) =  sin(R_theta) * (*robot) + cos(R_theta) * (*(robot+1))  + 0 * (*(robot+2)) ;
    *(global + 2) =  0 * (*robot) + 0 * (*(robot+1)) + 1 * (*(robot+2)) ;
}
void TF_2WD::motorToRobotTF(const float* motor , float* robot , float robot_r)
{
    *robot 			 = 	0.5f * (*motor) + 0.5f* (*(motor+1));
    *(robot + 1) =  0;									//0 * (*motor)  + 0 * (*(motor+1));
    *(robot + 2) =  ( 0.5f/ (float)robot_r ) * ( (*motor) - (*(motor+1)) );
}

void TF_2WD::motorToGlobalTF(const float* motor , float* global ,float R_theta ,float robot_r)   
{
	float robot[3];
	motorToRobotTF(motor,robot,robot_r);
	robotToGlobalTF(robot,global,R_theta);
}
/**************************robot speed -> motor speed**************************************/
void TF_2WD::robotSpeedSet(const float* expect_robot_speed , float* expect_motor_speed)  
{
    float Motor_Line_Speed[3] ;
    robotToMotorTF(expect_robot_speed , Motor_Line_Speed , robot_body_radius_) ;
    *expect_motor_speed  = ( Motor_Line_Speed[0] / robot_wheel_radius_ );
    *(expect_motor_speed+1)  = ( Motor_Line_Speed[1] / robot_wheel_radius_ );
}
void TF_2WD::getRobotSpeed(const float* measure_motor_speed , float* measure_robot_speed)
{
    float measure_motor_line_speed[3];
    measure_motor_line_speed[0]=*measure_motor_speed * robot_wheel_radius_;
    measure_motor_line_speed[1]=*(measure_motor_speed+1) * robot_wheel_radius_;
    motorToRobotTF(measure_motor_line_speed , measure_robot_speed , robot_body_radius_) ;
}
void TF_2WD::getGlobalSpeed(const float* measure_motor_speed , float* measure_global_speed ,float global_coordinat_z )
{
    float measure_motor_line_speed[3];
    measure_motor_line_speed[0]=*measure_motor_speed * robot_wheel_radius_;
    measure_motor_line_speed[1]=*(measure_motor_speed+1) * robot_wheel_radius_;
    motorToGlobalTF(measure_motor_line_speed , measure_global_speed , global_coordinat_z , robot_body_radius_);
}	
void TF_2WD::getRobotCoordinate(const float* d_motor_len_filter , float* measure_robot_coordinate)  
{
    float D_Robot_Coordinate[3] ;
    motorToRobotTF( d_motor_len_filter , D_Robot_Coordinate , robot_body_radius_) ;
	*measure_robot_coordinate += D_Robot_Coordinate[0];//机器人坐标
    *(measure_robot_coordinate+1) += D_Robot_Coordinate[1];
    *(measure_robot_coordinate+2) += D_Robot_Coordinate[2];
}	
void TF_2WD::getGlobalCoordinate(const float* d_motor_len_filter , float* measure_global_coordinate)  
{
    float D_Global_Coordinate[3] ;
    motorToGlobalTF(d_motor_len_filter , D_Global_Coordinate , *(measure_global_coordinate+2) , robot_body_radius_);
    *measure_global_coordinate += D_Global_Coordinate[0];
    *(measure_global_coordinate+1) += D_Global_Coordinate[1];
    *(measure_global_coordinate+2) += D_Global_Coordinate[2];
}

