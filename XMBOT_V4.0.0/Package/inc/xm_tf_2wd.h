#ifndef XM_TF_2WD_H
#define XM_TF_2WD_H
#include "math.h"
class TF_2WD
{
	public:
		TF_2WD()
		{
			robot_wheel_radius_=0;
			robot_body_radius_=0;	
		}
		void  set_robot_wheel_radius(float wheel_r){robot_wheel_radius_ = wheel_r;}
		void  set_robot_body_radius(float body_r)  {robot_body_radius_ = body_r;  }	
		float get_robot_wheel_radius(void) const {return robot_wheel_radius_;}
		float get_robot_body_radius(void) const {return robot_body_radius_ ;}
		
		void  robotSpeedSet(const float* expect_robot_speed , float* expect_motor_speed);		
		void  getRobotSpeed(const float* measure_motor_speed , float* measure_robot_speed);
        void  getGlobalSpeed(const float* measure_motor_speed , float* measure_global_speed ,float global_coordinat_z );
		void  getRobotCoordinate(const float* d_motor_len_filter , float* measure_robot_coordinate);
		void  getGlobalCoordinate(const float* d_motor_len_filter , float* measure_global_coordinate);

	private:
		float robot_wheel_radius_;
		float robot_body_radius_;	
     	void robotToMotorTF(const float* robot , float* motor , float robot_r);   
		void robotToGlobalTF(const float* robot , float* global ,float R_theta);
    	void motorToRobotTF(const float* motor , float* robot , float robot_r);
		void motorToGlobalTF(const float* motor , float* global ,float R_theta ,float robot_r);

};



#endif
