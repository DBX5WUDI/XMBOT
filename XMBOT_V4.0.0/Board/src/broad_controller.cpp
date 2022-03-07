#include "board_controller.h"

Board_controller  board_controller;

Board_controller::Board_controller()
{
    cnt_1ms = 0;          
    cnt_2ms = 0;
    cnt_5ms = 0;
    cnt_10ms = 0;
    cnt_20ms = 0;
    cnt_50ms  = 0;
}
void Board_controller::boardBasicInit(void)
{
	Xm_System_timer_Init();
	Xm_NVIC_Init();
	Xm_Key_Init();
	Xm_Led_Init();
	Xm_Communicate_Init();
	Xm_Timer_Init();
	Xm_Motor_Communicate_Init();
	Xm_GYPOS_Communicate_Init();
	Xm_Platform_Init();
	Xm_Servo_Init();
}
void Board_controller::Xm_System_timer_Init()
{
	System_Timer_Init();
}
void Board_controller::Xm_NVIC_Init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}
void Board_controller::Xm_Key_Init()
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);    
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
}
void Board_controller::Xm_Led_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;    
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1|GPIO_Pin_2 ;
    GPIO_Init(GPIOC , &GPIO_InitStruct);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_2);
}
void Board_controller::Xm_Communicate_Init(void)
{
#if communicate_mode == 0
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,  ENABLE);
		
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; 

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2|GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);

	
	USART_InitStructure.USART_BaudRate = 921600 ;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
	
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	USART_Cmd(USART2, ENABLE);
#endif
#if communicate_mode == 1

#endif
}
void Board_controller::Xm_Timer_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler     = (84 - 1);
	TIM_TimeBaseStructure.TIM_Period        = 1000-1 ;               
    TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; 		
    TIM_TimeBaseStructure.TIM_CounterMode   =TIM_CounterMode_Up;   
    TIM_TimeBaseInit(TIM6 , &TIM_TimeBaseStructure);
	
    TIM_ITConfig(TIM6 ,TIM_IT_Update,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
                    
    TIM_Cmd(TIM6 , ENABLE);
}
void Board_controller::Xm_Motor_Communicate_Init(void)
{
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11| GPIO_Pin_12;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);

    CAN_InitStructure.CAN_TTCM = DISABLE;			  
    CAN_InitStructure.CAN_AWUM = DISABLE;			 
    CAN_InitStructure.CAN_NART = ENABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	 
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1  = CAN_BS2_6tq;
    CAN_InitStructure.CAN_BS2  = CAN_BS1_7tq;
    CAN_InitStructure.CAN_Prescaler =3;               
    CAN_Init(CAN1, &CAN_InitStructure);
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;
    CAN_FilterInitStructure.CAN_FilterMode  =CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale =CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow =0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
	
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);  	
  
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	          
    NVIC_Init(&NVIC_InitStructure);
}
void Board_controller::Xm_GYPOS_Communicate_Init(void)
{
	GPIO_InitTypeDef       GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
   	NVIC_InitTypeDef  NVIC_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	                   											 
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12|GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_CAN2); 
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_CAN2); 

   	CAN_InitStructure.CAN_TTCM=DISABLE;
  	CAN_InitStructure.CAN_ABOM=DISABLE;	
  	CAN_InitStructure.CAN_AWUM=DISABLE;
  	CAN_InitStructure.CAN_NART=ENABLE;	
  	CAN_InitStructure.CAN_RFLM=DISABLE;	
  	CAN_InitStructure.CAN_TXFP=DISABLE;	
  	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;	 
  	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;	
  	CAN_InitStructure.CAN_BS1=CAN_BS2_6tq; 
  	CAN_InitStructure.CAN_BS2=CAN_BS1_7tq;
  	CAN_InitStructure.CAN_Prescaler=3;  	
  	CAN_Init(CAN2, &CAN_InitStructure);  

	CAN_FilterInitStructure.CAN_FilterNumber=14;	  
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
  	CAN_FilterInit(&CAN_FilterInitStructure);

	CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;     
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;           
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure); 
}
void Board_controller::Xm_Platform_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_9;
    GPIO_Init(GPIOC, &GPIO_InitStructure);	
 
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);	

	
    TIM_TimeBaseStructure.TIM_Prescaler = 84-1;    
    TIM_TimeBaseStructure.TIM_Period = 200-1;          
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 100;	
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);	
	TIM_Cmd(TIM3, DISABLE);
  
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        
	GPIO_Init(GPIOA,&GPIO_InitStructure);  
}
void Board_controller::Xm_Servo_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);   
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
	
    USART_InitStructure.USART_BaudRate = 115200 ; 
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);	

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); 
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    USART_Cmd(USART3, ENABLE);   
}

void Board_controller::Motor_Sendmessage(unsigned int ID, uint8_t *TxBuf)
{
    CanTxMsg TxMessageBuffer;
    uint8_t i;
	uint8_t Length=8;
    TxMessageBuffer.StdId=ID;
    TxMessageBuffer.RTR=0;
    TxMessageBuffer.IDE=0;
    TxMessageBuffer.DLC=Length;
    
    for(i=0;i<Length;i++)
    {
        TxMessageBuffer.Data[i]=*(TxBuf+i);
    }
    CAN_Transmit(CAN1, &TxMessageBuffer);  

}  
void Board_controller::SetLedState(uint8_t led_id, uint8_t operation)
{
	if ( led_id == 0)
	{
		if(operation == 0){ GPIO_SetBits(GPIOC , GPIO_Pin_1);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_1);}
		else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_1);}
	}
    else if(led_id == 1)
	{
        if(operation == 0){ GPIO_SetBits(GPIOC , GPIO_Pin_2);}
        else if(operation == 1) { GPIO_ResetBits(GPIOC , GPIO_Pin_2);}
		else if(operation == 2) { GPIO_ToggleBits(GPIOC , GPIO_Pin_2);}
    }

}
void Board_controller::rs485_cmd(unsigned char state)
{
	if(state==0)GPIO_ResetBits (GPIOA,GPIO_Pin_1);
	if(state==1)GPIO_SetBits   (GPIOA,GPIO_Pin_1);
}
void Board_controller::rs485_sendchar(uint8_t Tx_Byte)
{
    USART_SendData(USART2 , (uint8_t)Tx_Byte);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	delay_us(20);
}
void Board_controller::Foreward_Move(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}	
void Board_controller::Backward_Move(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
void Board_controller::axServoTxModel(void)	
{
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	
}
void Board_controller::axServoRxModel(void)
{
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}	
void Board_controller::axServoSendTxByte(uint8_t tx_byte)
{
    USART_SendData(USART3 , tx_byte);
    while(USART_GetFlagStatus(USART3 , USART_FLAG_TC) == RESET);		
}

