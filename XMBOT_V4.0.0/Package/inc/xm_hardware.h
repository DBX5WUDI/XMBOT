#ifndef XM_HARDWARE_H
#define XM_HARDWARE_H
#include "queue.h"
#include "hf_link.h"
#include "xm_tf_2wd.h"
#include "xm_motor.h"
#include "xm_platform.h"
#include "xm_servo.h"
#include "xm_gypos.h"

class Xm_Hardware:public TF_2WD
{
	public:
		Xm_Hardware()
		{
		
		}
		void xmHardwareInit   (void);
		void xmHardwareTopCall(void);

	private:
		
		struct
		{
			float  m1;
			float  m2;
		}d_motor_len_filter_ ;
		
	    void robotDataUpdate (void);
		void robotCoordCalc  (void);
	    void chassisControl  (void);
		void wristControl    (void);
		void clawControl     (void);
		void platControl     (void);
		void armControl      (void);	
};
extern Queue queue;
extern Xm_Gypos xm_gypos;
extern Xm_Servo xm_servo;
extern Xm_Motor xm_motor;
extern Xm_Abstract xm_robot;
extern Xm_Platform xm_platform;
extern Xm_Hardware xm_hardware;
extern HFLink hf_link_pc_node;
extern Board_controller board_controller;
extern HFLink *hf_link_node_pointer;

#endif
