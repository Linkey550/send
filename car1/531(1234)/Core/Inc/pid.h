#ifndef __pid_H
#define	__pid_H

#include "stm32f1xx.h"
#include "main.h"
//首先定义PID结构体用于存放一个PID的数据

extern float kp;//三个系数
extern float ki;
extern float kd;
extern float error, lastError;//误差、上次误差
extern float integral, maxIntegral;//积分、积分限幅
extern float output, maxOutput;//输出、输出限幅
extern int   stright_max;
extern int   stright_normal;
extern int   stright_min;
void PID_Calc(float reference,float feedback);

 
#endif
