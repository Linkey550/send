#ifndef __openmv_H
#define	__openmv_H

#include "stm32f1xx.h"
#include "main.h"
extern uint8_t stright_or_cross;//ֱ���ж�	1	
extern uint8_t stright;//ֱ����� 2
extern uint8_t dis_cross_center;//����תָʾ 3
extern uint8_t at_terminal;//�յ��ж� 4
extern uint8_t control;//�����ж� 5
extern uint8_t stright_pid;//pid�����ع�
extern uint8_t dis_cross_center_2;//ת��ָʾ2 6
extern uint8_t Centre;//���ľ� 7
extern uint8_t right_flag;//������ 8

extern uint8_t Travel_indication;
extern uint8_t Process_indication;
extern uint8_t Turn_indication1;
extern uint8_t Turn_indication2;
extern uint8_t End_indication;

void  Openmv_Receive_Data(int16_t data);
void   Bluetooth_Receive_Data(int16_t com_data);


 
#endif

