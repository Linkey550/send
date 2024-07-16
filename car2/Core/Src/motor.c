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
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//电机前进
    HAL_Delay(20);
}

 void pid_go(void)
{  
	
	if(stright>=stright_max||stright<=stright_min) 
   {
//		 if(stright_pid>100)
//		   {
		     PID_Calc(stright_normal,stright_pid);

			   MotorOutput2=motor_2_pwm_nomal+output;//右电机减速左偏
				 MotorOutput1=motor_1_pwm_nomal;


//			 else if(stright_pid<80)
//			 {
//				MotorOutput2=motor_1_pwm_nomal-(stright_pid-stright_normal);//右电机减速左偏
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
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//电机前进
    HAL_Delay(20);
}

void set_turn_left(void)
{
  	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);//电机前进
    HAL_Delay(20);
}

void set_stop(void)
{
  	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);//电机前进
    HAL_Delay(20);

}

/*
函数作用：设置电机走指定距离
参数：longnumber1：指定距离
备注：667预设距离约为9cm
*/
void set_stright_go(int	longnumber_set)
{     
   	__HAL_TIM_SET_COUNTER(&htim5,0); // 计数器清零 
	  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_2_pwm_nomal);
	  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
	  set_go();//打开电机
		while(((__HAL_TIM_GET_COUNTER(&htim5)))<longnumber_set)
		{ 
			LCD_ShowNum(0, 15,(__HAL_TIM_GET_COUNTER(&htim5)),5, 12);
		}
		
		set_stop();
    __HAL_TIM_SET_COUNTER(&htim5,0);
	  HAL_Delay(100);
}


void set_stright_turnleft(int longnumber_set)//通过编码器技术来向左转一定距离
{     
   __HAL_TIM_SET_COUNTER(&htim5,0); // 计数器清零 
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

//22000为90度
void set_stright_turnright(int longnumber_set)//通过编码器计数来向右转一定距离
{     
   	__HAL_TIM_SET_COUNTER(&htim5,0); // 计数器清零 
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

void openmv_turnright(void)//通过openmv来向右转一定距离
{
 if(Centre>0)//opmv检测到十字路口
		   { 
				 
				 while(Centre!=0)
				{ 
           pid_go();
				}
				set_stop();//当openmv刚好检测不到十字路口时停止
        motor_1_pwm_nomal=180;
				motor_2_pwm_nomal=180;
				 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_1_pwm_nomal);
	       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
				set_stright_go(15440);//位置矫正
				set_stright_turnright(22000);
				flag_turn_go++;
				flag_turn++;
//				motor_1_pwm_nomal=300;
//				motor_2_pwm_nomal=300;
//        flag_go=1;
//			  set_turn_right();//右转开启
//        HAL_Delay(1000);

//        while(stright<=stright_max&&stright>=stright_min)
//				{ 
//           printf(" ");
//				}
////			  printf("end");
//		    set_stop();//当检测到直线时停止
////		    HAL_Delay(500);  
//				while(1);
		   }
}


void openmv_turnleft(void)//通过openmv来左转一定距离
{
 if(Centre>0)//opmv检测到十字路口
		  {   
					
				while(Centre!=0)
				{ 
           pid_go();
				}
				set_stop();//当openmv刚好检测不到十字路口时停止
        motor_1_pwm_nomal=180;
				motor_2_pwm_nomal=180;
				 __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,motor_1_pwm_nomal);
	       __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,motor_2_pwm_nomal);
				set_stright_go(15440);//位置矫正
				set_stright_turnleft(22000);
				flag_turn_go++;
				flag_turn++;
//				motor_1_pwm_nomal=300;
//				motor_2_pwm_nomal=300;
//        flag_go=1;

		   }
}





