#ifndef __pid_H
#define	__pid_H

#include "stm32f1xx.h"
#include "main.h"
//���ȶ���PID�ṹ�����ڴ��һ��PID������

extern float kp;//����ϵ��
extern float ki;
extern float kd;
extern float error, lastError;//���ϴ����
extern float integral, maxIntegral;//���֡������޷�
extern float output, maxOutput;//���������޷�
extern int   stright_max;
extern int   stright_normal;
extern int   stright_min;
void PID_Calc(float reference,float feedback);

 
#endif
