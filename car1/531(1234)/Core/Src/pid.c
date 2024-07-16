#include "pid.h"

#include "stdio.h"
#include "usart.h"
#include <math.h>

float kp= 2;//����ϵ��
float ki= 0;
float kd= 0;
float error, lastError;//���ϴ����
float integral, maxIntegral;//���֡������޷�
float output, maxOutput=50;//���������޷�
int stright_max=93;
int   stright_normal=90;
int stright_min=87;
//���ڳ�ʼ��pid�����ĺ���

 
//����һ��pid����
//����Ϊ(Ŀ��ֵ,����ֵ)������������pid�ṹ���output��Ա��
void PID_Calc(float reference,float feedback)
{
	      lastError = error;//����error�� ����
        error = reference - feedback;//������error
        //����΢��
        float dout = (error - lastError) * kd;
        //�������
        float pout = error * kp;
        //�������
        integral += error * ki;
	      output = dout + pout + integral;
	      //����޷�
        if (output > maxOutput) output = maxOutput;

        else if (output < -maxOutput)output = -maxOutput;
        
	    printf("output:%f\r\n", output);
}

