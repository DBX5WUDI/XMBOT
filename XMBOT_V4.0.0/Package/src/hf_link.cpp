#include "hf_link.h"

HFLink hf_link_pc_node=HFLink(&xm_robot);
HFLink* hf_link_node_pointer=&hf_link_pc_node;

void HFLink::sendSignal(unsigned char signal)
{
	board_controller.rs485_cmd(1);
	board_controller.rs485_sendchar(signal);
	board_controller.rs485_cmd(0);
}
void HFLink::sendBuffer(unsigned char* buffer, unsigned short int size)
{
     while(size--)sendSignal(*buffer++);
}
void HFLink::sendStruct(const Command command_state , unsigned char* p , const unsigned short int len)
{
    tx_message_.sender_id = my_id;
    tx_message_.receiver_id = friend_id;
    tx_message_.length=len+1;
    tx_message_.data[0] = (unsigned char)command_state;
	if(len > 0)
    {
        memcpy(&tx_message_.data[1] , p , len);
    }
    sendMessage();
}

void HFLink::sendMessage(void)
{
    unsigned short int tx_i;
    unsigned int check_sum_=0;

    tx_buffer[0]=0xff;
    check_sum_ += 0xff;

    tx_buffer[1]=0xff;
    check_sum_ += 0xff;

    tx_buffer[2]=tx_message_.sender_id;
    check_sum_ += tx_buffer[2];

    tx_buffer[3]=tx_message_.receiver_id;
    check_sum_ += tx_buffer[3];

    tx_buffer[4]=(unsigned char)( tx_message_.length >> 8); 
    check_sum_ += tx_buffer[4];

    tx_buffer[5]=(unsigned char)tx_message_.length;   
    check_sum_ += tx_buffer[5];

    for(tx_i=0; tx_i < tx_message_.length ; tx_i++)   
    {
        tx_buffer[6+tx_i]=tx_message_.data[tx_i];
        check_sum_ += tx_buffer[6+tx_i];
    }
    check_sum_=check_sum_%255;
    tx_buffer[6+tx_i] = check_sum_;

    tx_buffer_length = 7 + tx_i;

    sendBuffer( tx_buffer , tx_buffer_length);

}
unsigned char HFLink::byteAnalysisCall(const unsigned char rx_byte)
{
    unsigned char package_update=0;
    unsigned char receive_message_update=0;
	
    receive_message_update=receiveFiniteStates(rx_byte) ;  

    if( receive_message_update ==1)
    {
		receive_message_update = 0;
        receive_message_count++;
        package_update=packageAnalysis();
        if(package_update==1) receive_package_count++;			
        return package_update;
    }
    return 0;
}
unsigned char HFLink::receiveFiniteStates(const unsigned char rx_data)
{
    switch (receive_state_)
    {
    case WAITING_FF1:
        if (rx_data == 0xff)
        {
            receive_state_ = WAITING_FF2;
            receive_check_sum_ =0;
            receive_message_length_ = 0;
            byte_count_=0;
            receive_check_sum_ += rx_data;
        }
        break;

    case WAITING_FF2:
        if (rx_data == 0xff)
        {
            receive_state_ = SENDER_ID;
            receive_check_sum_ += rx_data;
        }
        else
            receive_state_ = WAITING_FF1;
        break;

    case SENDER_ID:
        rx_message_.sender_id = rx_data ;
        if (rx_message_.sender_id == friend_id)  
        {
            receive_check_sum_ += rx_data;
            receive_state_ = RECEIVER_ID;
        }
        else
        {
			#if HF_LINK_NODE_MODE==0
				sendSignal(0xa1);
			#endif
            receive_state_ = WAITING_FF1;
        }
        break;

    case RECEIVER_ID:
        rx_message_.receiver_id = rx_data ;
        if (rx_message_.receiver_id == my_id)  
        {
            receive_check_sum_ += rx_data;
            receive_state_ = RECEIVE_LEN_H;
        }
        else
        {	
			#if HF_LINK_NODE_MODE==0
				sendSignal(0xa2);
			#endif
            receive_state_ = WAITING_FF1;
        }
        break;

    case RECEIVE_LEN_H:
        receive_check_sum_ += rx_data;
        receive_message_length_ |= rx_data<<8;
        receive_state_ = RECEIVE_LEN_L;
        break;

    case RECEIVE_LEN_L:
        receive_check_sum_ += rx_data;
        receive_message_length_ |= rx_data;
        rx_message_.length = receive_message_length_;
        receive_state_ = RECEIVE_PACKAGE;
        break;

    case RECEIVE_PACKAGE:
        receive_check_sum_ += rx_data;
        rx_message_.data[byte_count_++] = rx_data;
        if(byte_count_ >= receive_message_length_)
        {
            receive_state_ = RECEIVE_CHECK;
            receive_check_sum_=receive_check_sum_%255;
        }
        break;

    case RECEIVE_CHECK:
        if(rx_data == (unsigned char)receive_check_sum_)
        {
            receive_check_sum_=0;
            receive_state_ = WAITING_FF1;
            return 1 ;
        }
        else
        {
			#if HF_LINK_NODE_MODE==0
				sendSignal(0xa3);
			#endif
            receive_state_ = WAITING_FF1;
        }
        break;
		
    default:
        receive_state_ = WAITING_FF1;
    }
    return 0;
}
unsigned char HFLink::setCommandAnalysis(const Command command_state , unsigned char* p , const unsigned short int len)
{
    void *ack;
	char message[]="i catch the master";
	char *buf= message;
	if(hf_link_node_model==1)
	{
		if(command_state==SHAKING_HANDS)
		{
			shaking_hands_state=1;
		}
		receive_package_renew[(unsigned char)command_state]=1;
	}
	else if(hf_link_node_model==0)
	{
		if((rx_message_.length-1) != len)
		{
			#if HF_LINK_NODE_MODEL==0			
				sendSignal(len);
				sendSignal(0xb1);
			#endif
			return 0;
		}
		memcpy(p , &rx_message_.data[1] , len);
		if(command_state==SHAKING_HANDS)
		{
			shaking_hands_state=1;   
			board_controller.rs485_cmd(1);
			while(*(buf))
			{
				board_controller.rs485_sendchar(*buf);
				buf++;
			}
			board_controller.rs485_cmd(0);
		}
		else sendStruct(command_state  , (unsigned char *)ack , 0); 
		receive_package_renew[(unsigned char)command_state] = 1 ;   
	}
	return 1;
}

unsigned char HFLink::readCommandAnalysis(const Command command_state , unsigned char* p , const unsigned short int len)
{    
    if (hf_link_node_model==1)
    { 
		if((rx_message_.length-1) != len)
        {
			#if HF_LINK_NODE_MODEL == 1
				printf("I'm a master , can not read the message from slave , the length is not mathcing to struct \n");
			#endif
            return 0;
        }
        memcpy(p, &rx_message_.data[1] , len);
        receive_package_renew[(unsigned char)command_state] = 1 ;
    }
	else if(hf_link_node_model==0)
	{
		sendStruct(command_state  , p , len);
		receive_package_renew[(unsigned char)command_state] = 1 ;
    }
	return 1;
}

unsigned char HFLink::packageAnalysis(void)
{
    unsigned char analysis_state=0;
    void* single_command;
	
	command_state_=(Command)rx_message_.data[0];
    if (hf_link_node_model== 0)  //the slave need to check the SHAKING_HANDS"s state
    {	
		if(shaking_hands_state==0 && command_state_ != SHAKING_HANDS) //if not  shaking hands
		{
			sendStruct(SHAKING_HANDS  , (unsigned char *)single_command, 0);
			return 1;
		}
	}
    switch (command_state_)
    {
		case SHAKING_HANDS :
			analysis_state=setCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->measure_global_coordinate , sizeof(xm_robot->measure_global_coordinate));
			break;
		
		case SET_ROBOT_SPEED :
			analysis_state=setCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->expect_robot_speed , sizeof(xm_robot->expect_robot_speed));
			break;

		case READ_ROBOT_SPEED :
			analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->measure_robot_speed , sizeof(xm_robot->measure_robot_speed));
			break;

		case READ_GLOBAL_COORDINATE :
			analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->measure_global_coordinate , sizeof(xm_robot->measure_global_coordinate));
			break;

		case READ_ROBOT_COORDINATE :
			analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->measure_robot_coordinate , sizeof(xm_robot->measure_robot_coordinate));
			break;

		case CLEAR_COORDINATE_DATA :
			if(hf_link_node_model==0)
			{
				sendStruct(command_state_ , (unsigned char *)single_command , 0);
				analysis_state=1;
				receive_package_renew[(unsigned char)command_state_] = 1 ;
			}
			break;
		
		case SET_CLAW :
			analysis_state=setCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->claw_state_, sizeof(xm_robot->claw_state_));
			break;

		case SET_WRIST :
			analysis_state=setCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->wrist_angle_, sizeof(xm_robot->wrist_angle_));
			break;
			
		case READ_WRIST :
			analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->wrist_angle_, sizeof(xm_robot->wrist_angle_));
			break;
			
		case SET_ARM_TOTAL :
			analysis_state=setCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->expect_arm_state, sizeof(xm_robot->expect_arm_state));
			break;
					 
		case READ_ARM_TOTAL :
			analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->measure_arm_state , sizeof(xm_robot->measure_arm_state));
			break;
					 
		case PLAT_MOVE :
			analysis_state=setCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->plat_height_, sizeof(xm_robot->plat_height_));
			break;
		
		case READ_PLAT :
			analysis_state=readCommandAnalysis(command_state_ , (unsigned char *)&xm_robot->plat_height_back, sizeof(xm_robot->plat_height_back));
			break;
		
		default :
			analysis_state=0;
			break;	
	}	
    rx_message_.sender_id=0;    //clear flag
    rx_message_.receiver_id=0;
    rx_message_.length=0;
    rx_message_.data[0]=0;	

    return analysis_state;	
}

unsigned char HFLink::masterSendCommand(const Command command_state)
{

    unsigned char analysis_state =1;
    void* single_command;
    if(hf_link_node_model != 1){return 0;}
    
    switch (command_state)
    {
    case SHAKING_HANDS :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        shaking_hands_state = 1;
        sendStruct(command_state , (unsigned char *)&xm_robot->measure_global_coordinate , sizeof(xm_robot->measure_global_coordinate));
        break;
 
    case SET_ROBOT_SPEED :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)&xm_robot->expect_robot_speed , sizeof(xm_robot->expect_robot_speed));
        break;
 
    case READ_ROBOT_SPEED :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)single_command , 0);
        break;
 
    case READ_GLOBAL_COORDINATE :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)single_command , 0);
        break;
 
    case READ_ROBOT_COORDINATE :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)single_command , 0);
        break;
 
    case CLEAR_COORDINATE_DATA :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)single_command , 0);
        break; 

    case SET_CLAW :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)&xm_robot->claw_state_, sizeof(xm_robot->claw_state_));
        break;

	case SET_WRIST :
		receive_package_renew[(unsigned char)command_state] = 0 ;
		sendStruct(command_state , (unsigned char *)&xm_robot->wrist_angle_, sizeof(xm_robot->wrist_angle_));
		break;
		
	case READ_WRIST :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)single_command , 0);
        break;
		

    case SET_ARM_TOTAL :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state , (unsigned char *)&xm_robot->expect_arm_state, sizeof(xm_robot->expect_arm_state));
        break;
                 
    case READ_ARM_TOTAL :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state ,(unsigned char *)&xm_robot->measure_arm_state ,0);
        break;
                 
    case PLAT_MOVE :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state ,  (unsigned char *)&xm_robot->plat_height_, sizeof(xm_robot->plat_height_));      
        break;

    case READ_PLAT :
        receive_package_renew[(unsigned char)command_state] = 0 ;
        sendStruct(command_state ,(unsigned char *)&xm_robot->plat_height_back, 0);      
        break;

    default :
        analysis_state=0;
        break;

    }

    return analysis_state;
}






