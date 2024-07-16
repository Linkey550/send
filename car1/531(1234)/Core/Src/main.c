/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "openmv.h"
#include "stdio.h"
#include "math.h"
#include "pid.h"
//#ifdef  __GNUC__
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
//#endif 
//PUTCHAR_PROTOTYPE{
//	HAL_UART_Transmit(&huart3, (uint8_t *)&ch,1,HAL_MAX_DELAY);
//	return ch;
//}//��ʽ���������
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

unsigned int MotorSpeed1,MotorSpeed2;  // �����ǰ�ٶ���ֵ���ӱ������л�ȡ
int MotorOutput1,MotorOutput2;		  // ������
int MotorOutput_normal;
uint8_t data[8]={0xAA,0xBB,0,0,0,0,0,0xCC};
int Deviation;
float feedbackValue;

//#define motor_2_pwm_nomal 274
//#define motor_1_pwm_nomal 282
float motor_2_pwm_nomal=400;		//���Ե����ת���WPWM��274
float motor_1_pwm_nomal=400;

//short longnumber1;

uint8_t test=0;//���н׶μ���־λ
uint8_t turn=0;//ת�����־λ
uint8_t flag_go=1;
uint8_t flag_turn_go=0;//ȥ��ת��ָʾ��־λ
uint8_t flag_turn=0;//�س�ת��ָʾ��־λ
uint8_t turn_cross=0;//t��·�ڼ���־λ
uint8_t cross=0;
int a=1;

uint8_t usart1_rxbuff;
uint8_t usart3_rxbuff;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//int fputc(int ch, FILE *p)
//{
//	while(!(USART1->SR & (1<<7)));    //���SR��־λ�Ƿ�����
//	USART1->DR = ch;                  //�����ݸ���DRλ���
//	
//	return ch;
//}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

   float targetValue=90;//�����ȡ��Ŀ��ֵ
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);	    // TIM2_CH3(pwm)
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);	    // TIM4_CH3(pwm)
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1); // ����������A1
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2); // ����������B1	
	HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_1); // ����������A2
  HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_2); // ����������B2	
  HAL_TIM_Base_Start_IT(&htim1);                // ʹ�ܶ�ʱ��1�ж�
	
HAL_UART_Receive_IT(&huart3,(void *)&usart3_rxbuff,1);
HAL_UART_Receive_IT(&huart1,(void *)&usart1_rxbuff,1);

printf("P:%f I:%f D:%f",kp,ki,kd);

MotorOutput1=motor_1_pwm_nomal;
MotorOutput2=motor_2_pwm_nomal;
__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,MotorOutput1);
__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MotorOutput2);
//HAL_ADCEx_Calibration_Start(&hadc1); 
//HAL_ADC_Start_IT(&hadc1);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {    
//		printf("a:%d",a);
//	  rintf("test:%d",test);
		HAL_Delay(100);
		a=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);	
    UART_SendStr(data,8);
		feedbackValue=stright;
		if(a==0&&test==0)//��ҩ�׶�
		{
		   set_stop();
			flag_turn_go=0;
		}
		if(a==0&&test==1)//ǰ���׶�
		{  
		   if(flag_go==1)//ǰ���ж�
		   {
			   pid_go();
				 
		   }
	
			 if(control == 1||control == 2)//12��3-7�ŷ�����
						 { 
							 motor_2_pwm_nomal=200;		
               motor_1_pwm_nomal=200;
							 if(control == 1)//1�ŷ�
							 { 			  
										openmv_turnleft();//·����ת
			//					 turn++;
							 }
							 else if(control == 2)//opmvָʾ��ת
							 {   
										 openmv_turnright();
			//							 turn++;
									 }
						 
						 }
						 else//3-8�ŷ�
						 {		 										  
											 if(flag_turn_go==0)//��һ��ת��
											 {	 
																 if(dis_cross_center==1)
																 {
																				 openmv_turnright();
//																				 flag_turn_go++;
//																	       printf("1");
																 }
																 if(dis_cross_center==2)
																 {
																  
                                        openmv_turnleft();
                                        
																 }
																 if(dis_cross_center==3)
																 {
																       if(Centre>0)//opmv��⵽ʮ��·��
																						{   
																											while(Centre!=0)
																											{ 
																												 pid_go();
																											}
																											if(dis_cross_center==1)
																											{
																												set_stright_go(500);//λ�ý���
																											 set_stright_turnright(1000);
																												flag_turn_go++;
				                                               flag_turn++;
																											}
																											else if(dis_cross_center==2)
																											{
																												set_stright_go(500);//λ�ý���
																											set_stright_turnleft(1000);//ת180��
																												flag_turn_go++;
				                                                flag_turn++;
																											}
																											else if(dis_cross_center==3)
																											{
																										  motor_2_pwm_nomal=300;		
																										  motor_1_pwm_nomal=300;
																										  __HAL_TIM_SET_COUNTER(&htim3,0); // ���������� 
																										  while(((short)(__HAL_TIM_GET_COUNTER(&htim3)))<3600)
																										  { 
																										  pid_go();
																										  }
																										  motor_2_pwm_nomal=180;		
																									  motor_1_pwm_nomal=180;
																									   }
																										 else if(dis_cross_center==4)
																										{
																												set_stright_go(500);//λ�ý���
																											set_stright_turnleft(1000);//ת180��
                                                      motor_2_pwm_nomal=300;		
																										  motor_1_pwm_nomal=300;
																										  __HAL_TIM_SET_COUNTER(&htim3,0); // ���������� 
																										  while(((short)(__HAL_TIM_GET_COUNTER(&htim3)))<3600)
																										  { 
																										  pid_go();
																										  }
																										  motor_2_pwm_nomal=180;		
																									  motor_1_pwm_nomal=180;
																										}

																								
																						}
																	}																						
																 if(dis_cross_center==4)
																 {
                                   if(Centre>0)//opmv��⵽ʮ��·��
																						{   
																											while(Centre!=0)
																											{ 
																												 pid_go();
																											}
																											if(dis_cross_center==1)
																											{
																												set_stright_go(500);//λ�ý���
																											 set_stright_turnright(1000);
																												flag_turn_go++;
				                                               flag_turn_go++;
																											}
																											else if(dis_cross_center==2)
																											{
																												set_stright_go(500);//λ�ý���
																											set_stright_turnleft(1000);//ת180��
																												flag_turn_go++;
				                                                flag_turn_go++;
																											}
																											if(dis_cross_center==4)
																										 {
																												set_stright_go(500);//λ�ý���
																											set_stright_turnleft(1000);//ת180��
                                                      motor_2_pwm_nomal=300;		
																										  motor_1_pwm_nomal=300;
																										  __HAL_TIM_SET_COUNTER(&htim3,0); // ���������� 
																										  while(((short)(__HAL_TIM_GET_COUNTER(&htim3)))<3600)
																										  { 
																										  pid_go();
																										  }
																										  motor_2_pwm_nomal=180;		
																									   motor_1_pwm_nomal=180;
																										 }
																										 else if(dis_cross_center==5)
																										 {
																														 set_stright_turnleft(2000);//ת180��
																														 flag_turn_go++;
																														 motor_2_pwm_nomal=400;		
																														 motor_1_pwm_nomal=400;
																															__HAL_TIM_SET_COUNTER(&htim3,0); // ���������� 
																														 while(((short)(__HAL_TIM_GET_COUNTER(&htim3)))<8000)
																														 { 
																														 pid_go();
																														 }
																														motor_2_pwm_nomal=180;		
																														motor_1_pwm_nomal=180;
																										 }
																											
																 }
															 }
																 if(dis_cross_center==5)
																 {
																	 
																	if(Centre>0)//opmv��⵽ʮ��·��
																						{   
																											while(Centre!=0)
																											{ 
																												 pid_go();
																											}
																				if(dis_cross_center==5)
																				{																					
																				 set_stright_turnleft(2000);//ת180��
																				 flag_turn_go++;
																	       motor_2_pwm_nomal=400;		
																				 motor_1_pwm_nomal=400;
																			  	__HAL_TIM_SET_COUNTER(&htim3,0); // ���������� 
																				 while(((short)(__HAL_TIM_GET_COUNTER(&htim3)))<8000)
																				 { 
																				 pid_go();
																				 }
																				motor_2_pwm_nomal=180;		
																				motor_1_pwm_nomal=180;
																				 
																      }
															    }
																						
																 HAL_Delay(50);
														 
												}
											}
											 else if(flag_turn_go==1)//�ڶ���ת��
											 {	         
												          
																											 if(dis_cross_center_2==1)
																											 {
//																													set_stright_go(500);//λ�ý���
//																													set_stright_turnright(1000);//ת180��
																															 openmv_turnright();
																															 flag_turn_go++;
																											 }
																											 else if(dis_cross_center_2==2)
																											 {
//																												 set_stright_go(500);//λ�ý���
//																											   set_stright_turnleft(1000);//ת180��
																															 openmv_turnleft();
																															 flag_turn_go++;
																											 }	
																										 
											 }
						 }
						 if(at_terminal==1)//�յ�ֹͣ
						 {   
							   data[6]=1;
							   data[5]=dis_cross_center_2;
                 data[4]=dis_cross_center;
							   data[3]=0;
                 data[2]=0;
								 HAL_Delay(1000);
								 set_stop();
								 test++;
                 
//                 for(int i;i<6;i++)
//                  {
//									  UART_SendStr(data,7);
//									}							 
		         }
     UART_SendStr(data,8);
		}
		if(a==1&&test==2)//�յ�ת��
		{        
			       data[6]=1;
             data[5]=dis_cross_center_2;
             data[4]=dis_cross_center;
						 data[3]=1;
             data[2]=0;
			       set_stright_turnleft(1980);
						 test++;	
             flag_turn=0;	
			       
			       for(int i;i<6;i++)
                  {
									  UART_SendStr(data,8);
									}							 
			      
		}
		if(a==1&&test==3)//�س̽׶�
		{        
		
								pid_go();
                UART_SendStr(data,8);
             if(cross>=1)
                   {
										data[6]=1;
									  data[5]=dis_cross_center_2;
                    data[4]=dis_cross_center;
						        data[3]=1;
                    data[2]=1;
//										 for(int i;i<6;i++)
//                     {
//									  UART_SendStr(data,7);
//									   }							 
									 }
  
						 if(control == 1||control == 2)//1��2��3-7�ŷ�����
										{
											 motor_2_pwm_nomal=200;		
                       motor_1_pwm_nomal=200;
											 if(control == 2)//2��
											 { 
												 openmv_turnleft();
			//									 turn--;
											 }
											 else if(control == 1)//1��
											 {  
												 openmv_turnright();
			//									 turn--;

											 }
										 } 
						 else//3-7�ŷ�
										{

										 if(dis_cross_center==2&&dis_cross_center_2==3)//2-1�ŷ�
										 { 
											 if(flag_turn==0)
												 {
											    openmv_turnright();
                          
													motor_2_pwm_nomal=300;
						              motor_1_pwm_nomal=300;
                          cross++;
										     }
										  }
										 else if(dis_cross_center==1&&dis_cross_center_2==3)//2-2�ŷ�
										 {
											 if(flag_turn==0)
												 {
													openmv_turnleft();
//													 flag_turn++;
													motor_2_pwm_nomal=300;
						              motor_1_pwm_nomal=300;
                          cross++;
												 }
										 }
										 else if(dis_cross_center==2&&dis_cross_center_2==2)//3-1�ŷ�
										 {
											 if(flag_turn==0)
											 {
													openmv_turnright();
//												 flag_turn++;
											 }
											 else if(flag_turn==1)
											 {
												 openmv_turnright();
//												 flag_turn++;
												 motor_2_pwm_nomal=300;
						             motor_1_pwm_nomal=300;
											 }
											 else if(flag_turn==2)
											 {
											    if(Centre>0)//opmv��⵽ʮ��·��
											    {   
													while(Centre!=0)
													{ 
														 pid_go();
													}
													cross++;																									 
											    }
										   }
										 }
										 else if(dis_cross_center==2&&dis_cross_center_2==1)//3-2�ŷ�
										 {
											 if(flag_turn==0)
											 {
													openmv_turnleft();
//												 flag_turn++;

											 }
											 else if(flag_turn==1)
											 {
												 openmv_turnright();
//												 flag_turn++;
												 motor_2_pwm_nomal=300;
						             motor_1_pwm_nomal=300;
											 }
											 else if(flag_turn==2)
											 {
											    if(Centre>0)//opmv��⵽ʮ��·��
											    {   
													while(Centre!=0)
													{ 
														 pid_go();
													}
													cross++;																									 
											    }
										   }
										 }
										 else if(dis_cross_center==1&&dis_cross_center_2==1)//3-3�ŷ�
										 {
												if(flag_turn==0)
											 {
													openmv_turnleft();
//												 flag_turn++;

											 }
											 else if(flag_turn==1)
											 {
												 openmv_turnleft();
//												 flag_turn++;
												 motor_2_pwm_nomal=300;
						             motor_1_pwm_nomal=300;
										  }
											 else if(flag_turn==2)
											 {
											    if(Centre>0)//opmv��⵽ʮ��·��
											    {   
													while(Centre!=0)
													{ 
														 pid_go();
													}
													cross++;																									 
											    }
										   }
									 }								 
										 else if(dis_cross_center==1&&dis_cross_center_2==2)//3-4�ŷ�
										 {
											 if(flag_turn==0)
											 {
													openmv_turnright();
//												 flag_turn++;
											 }
											 else if(flag_turn==1)
											 {
												 openmv_turnleft();
//												 flag_turn++;
												 	 motor_2_pwm_nomal=300;
						             motor_1_pwm_nomal=300;
										   }
											 else if(flag_turn==2)
											 {
											    if(Centre>0)//opmv��⵽ʮ��·��
											    {   
													while(Centre!=0)
													{ 
														 pid_go();
													}
													cross++;																									 
											    }
										   }
											}

									}
						 if(at_terminal==1)//�յ�ͣת
										{
										 HAL_Delay(400);
										 set_stop();
											test++;	
						//				 while(1);
										}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */
     }
	}
}	

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//��ʱ���жϻص�
{    

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//�����жϻص�
{
  uint16_t tem3;
  uint16_t tem1;
  if(huart->Instance==USART3)
  {
    tem3=usart3_rxbuff;
    Openmv_Receive_Data(tem3);
  }


  if(huart->Instance==USART1)
  {
    tem1=usart1_rxbuff;
  }		
    HAL_UART_Receive_IT(&huart3,(void *)&usart3_rxbuff,1);
    HAL_UART_Receive_IT(&huart1,(void *)&usart1_rxbuff,1);
 }
  


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//�����жϻص�
{
  if (GPIO_Pin ==GPIO_PIN_1)
  {
  test++;
  HAL_NVIC_DisableIRQ(EXTI1_IRQn);//������ҩ�׶Σ��ر��жϷ���
  }
  if (GPIO_Pin ==GPIO_PIN_0)
  {  

  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
