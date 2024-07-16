#include "pid.h"

#include "stdio.h"
#include "usart.h"
#include <math.h>

float kp= 2;//三个系数
float ki= 0;
float kd= 0;
float error, lastError;//误差、上次误差
float integral, maxIntegral;//积分、积分限幅
float output, maxOutput=50;//输出、输出限幅
int stright_max=93;
int   stright_normal=90;
int stright_min=87;
//用于初始化pid参数的函数

 
//进行一次pid计算
//参数为(目标值,反馈值)，计算结果放在pid结构体的output成员中
void PID_Calc(float reference,float feedback)
{
	      lastError = error;//将旧error存 起来
        error = reference - feedback;//计算新error
        //计算微分
        float dout = (error - lastError) * kd;
        //计算比例
        float pout = error * kp;
        //计算积分
        integral += error * ki;
	      output = dout + pout + integral;
	      //输出限幅
        if (output > maxOutput) output = maxOutput;

        else if (output < -maxOutput)output = -maxOutput;
        
	    printf("output:%f\r\n", output);
}

