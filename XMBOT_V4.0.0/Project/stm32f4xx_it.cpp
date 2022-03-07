#include "xm_hardware.h"

#ifdef __cplusplus
extern "C" {
#endif
	
void USART2_IRQHandler(void)
{
    unsigned char data;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        data = USART2->DR;
		if(queue.fullCheck()==0)
		{
           queue.putData(data);
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);   
    }
}
void UART5_IRQHandler(void)
{
    unsigned char data;

    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        data = UART5->DR;
		if(queue.fullCheck()==0)
		{
           queue.putData(data);
        }
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);   
    }
}

void USART3_IRQHandler(void)
{
    unsigned char data;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        data=USART_ReceiveData(USART3);
        xm_servo.gbpRxInterruptBuffer[(xm_servo.gbRxBufferWritePointer++)] = data;
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);  
    }

}

void TIM6_DAC_IRQHandler(void)
{ 

    if(TIM_GetITStatus(TIM6 , TIM_IT_Update)== SET  )
    {
        board_controller.cnt_1ms++;
        board_controller.cnt_2ms++;
        board_controller.cnt_5ms++;
        board_controller.cnt_10ms++;
        board_controller.cnt_20ms++;
        board_controller.cnt_50ms++;
		board_controller.cnt_100ms++;
        TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);     
    }
}

void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	CAN_Receive(CAN1, 0 ,&RxMessage);

	if(RxMessage.StdId==0X11B)
    {
		memcpy(xm_motor.byte, (RxMessage.Data+2),2*sizeof(RxMessage.Data[0]));
		xm_motor.Flag1_CAN_Receive=0XFF;
	}
	if(RxMessage.StdId==0X13B)
	{
		memcpy((xm_motor.byte+2), (RxMessage.Data+2),2*sizeof(RxMessage.Data[0]));
		xm_motor.Flag1_CAN_Receive=0XFF;
	}	
	if(RxMessage.Data[0]==0x08&&RxMessage.Data[2]==0x9B)
	{
		if(RxMessage.Data[1] == 0x2C)
		{
			xm_motor.arm_cmd[0] = RxMessage.Data[7];  
			xm_motor.arm_cmd[1] = RxMessage.Data[6];
			xm_motor.arm_cmd[2] = RxMessage.Data[5];
			xm_motor.arm_cmd[3] = RxMessage.Data[4];		
		}
		if(RxMessage.Data[1] == 0x2D)
		{
			xm_motor.arm_cmd[4] = RxMessage.Data[7];  
			xm_motor.arm_cmd[5] = RxMessage.Data[6];
			xm_motor.arm_cmd[6] = RxMessage.Data[5];
			xm_motor.arm_cmd[7] = RxMessage.Data[4];		
		}
		if(RxMessage.Data[1] == 0x2E)
		{
			xm_motor.arm_cmd[8] = RxMessage.Data[7];  
			xm_motor.arm_cmd[9] = RxMessage.Data[6];
			xm_motor.arm_cmd[10] = RxMessage.Data[5];
			xm_motor.arm_cmd[11] = RxMessage.Data[4];		
		}
		if(RxMessage.Data[1] == 0x2F)
		{
			xm_motor.arm_cmd[12] = RxMessage.Data[7];  
			xm_motor.arm_cmd[13] = RxMessage.Data[6];
			xm_motor.arm_cmd[14] = RxMessage.Data[5];
			xm_motor.arm_cmd[15] = RxMessage.Data[4];		
		}
		xm_motor.Flag2_CAN_Receive=0XFF;
	}
	else
	{
		xm_motor.Flag1_CAN_Receive=0;
		xm_motor.Flag2_CAN_Receive=0;
	}
}

void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	
	CAN_Receive(CAN2, 0 ,&RxMessage);

	if(RxMessage.StdId==0X0401)
	 {
		memcpy(xm_gypos.GYPOS_data,RxMessage.Data,4);
		xm_gypos.can2_flag=0xff; 
	 }
}
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
	{
		xm_platform.Pulse_Num++;
		if(xm_platform.flag_dir==0xff)
			xm_platform.Pulse_counter++;
		if(xm_platform.flag_dir==0x01)
			xm_platform.Pulse_counter--;
			xm_platform.current_h=((float)xm_platform.Pulse_counter)/xm_platform.per_pulse*xm_platform.per_s;  
		if(xm_platform.Pulse_Num>=xm_platform.Desp_Num)    
		{
			xm_platform.Pulse_Num=0;
			TIM_Cmd(TIM3, DISABLE);
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); 
}

void HardFault_Handler(void)
{
	board_controller.mmp++;
}


#ifdef __cplusplus
}
#endif
