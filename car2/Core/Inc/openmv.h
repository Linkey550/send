#ifndef __openmv_H
#define	__openmv_H

#include "stm32f1xx.h"
#include "main.h"
extern uint8_t stright_or_cross;//直线判定	1	
extern uint8_t stright;//直线误差 2
extern uint8_t dis_cross_center;//左右转指示 3
extern uint8_t at_terminal;//终点判定 4
extern uint8_t control;//病房判定 5
extern uint8_t stright_pid;//pid计算特供
extern uint8_t dis_cross_center_2;//转向指示2 6
extern uint8_t Centre;//中心距 7
extern uint8_t right_flag;//防报错 8

extern uint8_t Travel_indication;
extern uint8_t Process_indication;
extern uint8_t Turn_indication1;
extern uint8_t Turn_indication2;
extern uint8_t End_indication;

void  Openmv_Receive_Data(int16_t data);
void   Bluetooth_Receive_Data(int16_t com_data);


 
#endif

