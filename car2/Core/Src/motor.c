#include "motor.h"
#include "stdio.h"
#include "usart.h"
#include "openmv.h"
#include "pid.h"
#include "main.h"
#include "tim.h"
#include <math.h>


void set_go(void)
{   
    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//���ǰ��
    HAL_Delay(20);
}

 void pid_go(void)
{  
	
	if(stright>=stright_max||stright<=stright_min) 
   {
//		 if(stright_pid>100)
//		   {
		     PID_Calc(stright_normal,stright_pid);

			   MotorOutput2=motor_2_pwm_nomal+output;//�ҵ��������ƫ
				 MotorOutput1=motor_1_pwm_nomal;


//			 else if(stright_pid<80)
//			 {
//				MotorOutput2=motor_1_pwm_nomal-(stright_pid-stright_normal);//�ҵ��������ƫ
//				MotorOutput1=motor_1_pwm_nomal;
//			 }
			 
		 if(MotorOutput2>motor_2_pwm_nomal+50)
      {

			  MotorOutput2=motor_2_pwm_nomal+50;
			}
		if(MotorOutput2<motor_2_pwm_nomal-50)
		  {
			  MotorOutput2=motor_2_pwm_nomal-50;
			}


		  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MotorOutput1);
	    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,MotorOutput2);
			printf("MotorOutput1:%d",MotorOutput1);
			printf("MotorOutput2:%d",MotorOutput2);

			
	 }
	 else if(stright_pid<=100&&stright_pid>=80)
		  { 
				MotorOutput2=motor_2_pwm_nomal;
				MotorOutput1=motor_1_pwm_nomal;
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MotorOutput1);
	    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,MotorOutput2);
	    } 
//   else
//   {
//	   MotorOutput2=motor_2_pwm_nomal;
//		 MotorOutput1=motor_1_pwm_nomal;
//   }
	 set_go();
}


void set_turn_right(void)
{
   	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//���ǰ��
    HAL_Delay(20);
}

void set_turn_left(void)
{
  	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);//���ǰ��
    HAL_Delay(20);
}

void set_stop(void)
{
  	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//���ǰ��
    HAL_Delay(20);

}

/*
�������ã����õ����ָ������
������longnumber1��ָ������
��ע��667Ԥ�����ԼΪ9cm
*/
void set_stright_go(int	longnumber_set)
{     
   	__HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
	  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_2_pwm_nomal);
	  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
	  set_go();//�򿪵��
		while(((__HAL_TIM_GET_COUNTER(&htim5)))<longnumber_set)
		{ 
			LCD_ShowNum(0, 15,(__HAL_TIM_GET_COUNTER(&htim5)),5, 12);
		}
		
		set_stop();
    __HAL_TIM_SET_COUNTER(&htim5,0);
	  HAL_Delay(100);
}


void set_stright_turnleft(int longnumber_set)//ͨ������������������תһ������
{     
   __HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
	  HAL_Delay(50);
	 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_1_pwm_nomal);
	 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
	  set_turn_left();
		while((67295-((__HAL_TIM_GET_COUNTER(&htim5))))<longnumber_set)
		{ 
			LCD_ShowNum(0, 15,(__HAL_TIM_GET_COUNTER(&htim5)),5, 12);
		}
		
		set_stop();
     __HAL_TIM_SET_COUNTER(&htim5,0);
	  HAL_Delay(100);
}

//22000Ϊ90��
void set_stright_turnright(int longnumber_set)//ͨ������������������תһ������
{     
   	__HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
	 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_1_pwm_nomal);
	 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
		set_turn_right();
		while(((__HAL_TIM_GET_COUNTER(&htim5)))<longnumber_set)
		{ 
			LCD_ShowNum(0, 15,(__HAL_TIM_GET_COUNTER(&htim5)),5, 12);
		}
		
		set_stop();
    __HAL_TIM_SET_COUNTER(&htim5,0);
	  HAL_Delay(100);
}

void openmv_turnright(void)//ͨ��openmv������תһ������
{
 if(Centre>0)//opmv��⵽ʮ��·��
		   { 
				 
				 while(Centre!=0)
				{ 
           pid_go();
				}
				set_stop();//��openmv�պü�ⲻ��ʮ��·��ʱֹͣ
        motor_1_pwm_nomal=180;
				motor_2_pwm_nomal=180;
				 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_1_pwm_nomal);
	       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
				set_stright_go(15440);//λ�ý���
				set_stright_turnright(22000);
				flag_turn_go++;
				flag_turn++;
//				motor_1_pwm_nomal=300;
//				motor_2_pwm_nomal=300;
//        flag_go=1;
//			  set_turn_right();//��ת����
//        HAL_Delay(1000);

//        while(stright<=stright_max&&stright>=stright_min)
//				{ 
//           printf(" ");
//				}
////			  printf("end");
//		    set_stop();//����⵽ֱ��ʱֹͣ
////		    HAL_Delay(500);  
//				while(1);
		   }
}


void openmv_turnleft(void)//ͨ��openmv����תһ������
{
 if(Centre>0)//opmv��⵽ʮ��·��
		  {   
					
				while(Centre!=0)
				{ 
           pid_go();
				}
				set_stop();//��openmv�պü�ⲻ��ʮ��·��ʱֹͣ
        motor_1_pwm_nomal=180;
				motor_2_pwm_nomal=180;
				 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_1_pwm_nomal);
	       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
				set_stright_go(15440);//λ�ý���
				set_stright_turnleft(22000);
				flag_turn_go++;
				flag_turn++;
//				motor_1_pwm_nomal=300;
//				motor_2_pwm_nomal=300;
//        flag_go=1;

		   }
}





