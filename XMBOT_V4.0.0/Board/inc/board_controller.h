#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#ifdef __cplusplus
extern "C" {											//board supporting files must write these lines, many.c files are linked.
#endif

#include "stm32f4xx.h"	
#include "delay.h"

#define communicate_mode 0								//0:rs485 1:HC_05

class Board_controller
{
	public:
		/***************************************some timer counter********************************/
		uint16_t cnt_1ms;						
		uint16_t cnt_2ms;
		uint16_t cnt_5ms;
		uint16_t cnt_10ms;
		uint16_t cnt_20ms;
		uint16_t cnt_50ms;
		uint16_t cnt_100ms;
		uint16_t mmp;
		/*****************************************************************************************/
	public:
		/*****************************************************************************************/
		Board_controller();											//board_control constructor
		void boardBasicInit(void);									//Initialize classes' constructor functions
		void Motor_Sendmessage(unsigned int ID, uint8_t *TxBuf);	//motor driver box send message
		void SetLedState(uint8_t led_id, uint8_t operation);		//set led's state
		void rs485_cmd(unsigned char state);						//enable/disable rs485
		void rs485_sendchar(uint8_t Tx_Byte);
		void Foreward_Move(void);									//platform move foreward
		void Backward_Move(void);									//platform move backward
		void axServoTxModel(void);									//enable the board to send servo message
		void axServoRxModel(void);									//enable the board to receive servo's message
		void axServoSendTxByte(uint8_t tx_byte);					//send data to servo message
		void HF_Flash_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite);
		void HF_Flash_Read(uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead);  //read half word data(16 bits) from assign address
		/*****************************************************************************************/
	private:
		/*****************************************************************************************/
		void Xm_System_timer_Init(void);							//initialize the system timer
		void Xm_NVIC_Init(void);									//initialize the interrupt
		void Xm_Key_Init(void);										//initialize the Key
		void Xm_Led_Init(void);										//initialize the led
		void Xm_Communicate_Init(void);								//initialize the communication between singlechip and computer 
		void Xm_Timer_Init(void);									//initialize the TIM timer
		void Xm_Motor_Communicate_Init(void);						//initialize the moter communication
		void Xm_GYPOS_Communicate_Init(void);						//initialize the gyroscope communication
		void Xm_Platform_Init(void);								//initialize the platform
		void Xm_Servo_Init(void);									//initialize the servo commuincation
		/*****************************************************************************************/
};	

extern Board_controller board_controller;

#ifdef __cplusplus
}
#endif
#endif
