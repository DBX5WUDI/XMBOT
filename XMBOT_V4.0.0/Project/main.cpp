#include "xm_hardware.h"
/******************************Initialize classes' constructor functions**************************/
void constructorInit(void)
{
	board_controller =Board_controller();
	queue = Queue();  	
	xm_gypos = Xm_Gypos();
	xm_servo = Xm_Servo();
	xm_motor = Xm_Motor();
	xm_platform = Xm_Platform();
	xm_hardware = Xm_Hardware();
	xm_robot = Xm_Abstract();
}
/************************Initialize the robot system**********************************************/
void systemInit(void)
{
	board_controller.boardBasicInit();
    xm_hardware.xmHardwareInit();
}
/**********************The main loop body*********************************************************/
int main ()
{
	constructorInit();
    systemInit();
	while(1)
	{
		if(queue.emptyCheck()==0)
		{
			hf_link_pc_node.byteAnalysisCall(queue.getData());	//update the queue data into the robot abstractor
		}
        if ( board_controller.cnt_1ms >= 1 )     
        {
            board_controller.cnt_1ms=0;
        }
		if ( board_controller.cnt_2ms >= 2 )     
        {
            board_controller.cnt_2ms=0;
        }
		if ( board_controller.cnt_5ms >= 5 )     
        {
            board_controller.cnt_5ms=0;
        }
        if ( board_controller.cnt_10ms >= 10 )    
        {
            board_controller.cnt_10ms=0;
        }
        if ( board_controller.cnt_20ms >= 20 )    
        {
            board_controller.cnt_20ms = 0 ;
			xm_hardware.xmHardwareTopCall();					//update some hardware state
        }
        if ( board_controller.cnt_50ms >= 50 )    
        {
            board_controller.cnt_50ms = 0 ;
			board_controller.SetLedState(1,2);					
			xm_platform.platform_top_call();					//set the platform state
        }	
		if(board_controller.cnt_100ms>=100)
		{
			board_controller.cnt_100ms = 0;
			xm_motor.arm_read();								//read the mechanical arm state
		}			
	}
}

