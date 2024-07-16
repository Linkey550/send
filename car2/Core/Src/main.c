/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
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
#include "tftlcd.h"
#include "bmp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
unsigned int MotorSpeed1,MotorSpeed2;  // �����ǰ�ٶ���ֵ���ӱ������л�ȡ
int MotorOutput1,MotorOutput2;		  // ������
int MotorOutput_normal;
uint8_t data[5];
int Deviation;
float feedbackValue;

//#define motor_2_pwm_nomal 274
//#define motor_1_pwm_nomal 282
float motor_2_pwm_nomal=200;		//���Ե����ת���WPWM��274
float motor_1_pwm_nomal=200;

//short longnumber1;

uint8_t test=0;//���н׶μ���־λ
uint8_t turn=0;//ת�����־λ
uint8_t flag_go=1;
uint8_t flag_turn_go=0;//ȥ��ת��ָʾ��־λ
uint8_t flag_turn=0;//�س�ת��ָʾ��־λ
uint8_t turn_cross=0;//t��·�ڼ���־λ
uint8_t CS=0;
uint8_t cross=0;
int a=1;

uint8_t usart1_rxbuff;
uint8_t usart3_rxbuff;

char str[50] = {0};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//MotorOutput1=motor_1_pwm_nomal;
//MotorOutput2=motor_2_pwm_nomal;
//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MotorOutput1);
//__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,MotorOutput2);
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	LCD_Init();
//	LCD_Clear(BLACK); 		//����	
//	BACK_COLOR=BLACK;
//	POINT_COLOR=CYAN;
//	LCD_Show_Image(0, 0, 240, 135, gImage_cxk);
//	HAL_Delay(2000);
	LCD_Clear(BLACK); 		//����	
	BACK_COLOR=BLACK;
	POINT_COLOR=CYAN;
//  LCD_ShowString(0, 0, 160, 12, 12, "Boring_TECH");
//	LCD_ShowString(0, 15, 160, 12, 12, "TFTLCD TEST 135*240");
//  LCD_ShowNum(0, 15,CS,5, 12);
//	LCD_ShowString(0, 30, 160, 16, 12, "STM32F103RCT6");
//	LCD_ShowString(0, 45, 160, 12, 12, "2019/6/24");	
	
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);	    // TIM2_CH3(pwm)����
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);	    // TIM4_CH3(pwm)����
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1); // ����������A1
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2); // ����������B1	
	HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_1); // ����������A2
  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_2); // ����������B2	
	
	  HAL_UART_Receive_IT(&huart3,(void *)&usart3_rxbuff,1);
    HAL_UART_Receive_IT(&huart1,(void *)&usart1_rxbuff,1);

//    printf("P:%f I:%f D:%f",kp,ki,kd);

      MotorOutput1=motor_1_pwm_nomal;
      MotorOutput2=motor_2_pwm_nomal;

	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MotorOutput1);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MotorOutput2);
//    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
//	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);//���ǰ��
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
     
    /* USER CODE BEGIN 3 */
		feedbackValue=stright;
		a=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3);
		if(End_indication==1)
		{
		if(Turn_indication2==3)//�ж����ж˻���Զ�˲������ж�
		{
							
							
							if(a==0&&test==0)//��ҩ�׶�
							{
							set_stop();
							flag_turn_go=0;
							}	
							if(a==1&&test==1)//ǰ���׶�
							{  
											
												pid_go();
		                 if(at_terminal==1)//�յ�ֹͣ
												 {   
															 HAL_Delay(1000);
															 set_stop();
															 test++;
													} 	
								     if(Centre>0)//opmv��⵽ʮ��·��
												 {   
																	while(Centre!=0)
																	{ 
																		 pid_go();
																	}
																	turn++;
																 if(turn>=2)
													      {
												          if(Turn_indication1==1)
												 {  
													 if(flag_turn_go==0)
													 {
													set_stright_go(15000);//λ�ý���
													set_stright_turnleft(22000);
													flag_turn_go++;
//				                  flag_turn++;
//																 openmv_turnleft();
													 }
													}
												          if(Turn_indication1==2)
												 {	
													 if(flag_turn_go==0)
													 {
                          set_stright_go(15000);//λ�ý���
													set_stright_turnright(22000);
													flag_turn_go++;
//				                  flag_turn++;													 
//																openmv_turnright();		
													 }														 
													} 
												 
												 }
												 
												 }
											
							 }
              if(a==1&&test==2)//ǰ���׶�
							{  
								if(Travel_indication==1)
								{
								  set_stright_turnleft(44000);
									test++;
								}									
							}
              if(a==1&&test==3)//ǰ���յ�
							{  
								pid_go();
								 if(at_terminal==1)//�յ�ֹͣ
									 {   
											 HAL_Delay(1000);
											 set_stop();
											 test++;
									 }
							}
							  if(a==0&&test==4)//�յ�ת��
							{  
								
								  set_stright_turnleft(44000);
									test++;
																
							}
               if(a==0&&test==5)//�س̽׶�
							{  
								pid_go();
								if(Turn_indication1==2&&Turn_indication2==3)//2-1�ŷ�
										 { 
											 if(flag_turn==0)
												 {
											    openmv_turnright();
										     }
										  }
										 else if(Turn_indication1==1&&Turn_indication2==3)//2-2�ŷ�
										 {
											 if(flag_turn==0)
												 {
													openmv_turnleft();
												 }
										 }
										 if(at_terminal==1)//�յ�ͣת
										{
										 HAL_Delay(400);
										 set_stop();
											test++;	
										}							
						 }
		  }
		else//Զ��
		{  
			
		 if(Process_indication==1)//�ñ�־λ��ʾһ���ѿ�ʼ�س�
			{ 
			  if(test==0)//ȥ�̽׶�
				{
				if(flag_turn_go==0)//ȥ����ͣ��
				{
					  pid_go();
					 if(turn>=1)
							 {
							   openmv_turnright();
							 }
				   if(Centre>0&&right_flag==1)//opmv��⵽ʮ��·��
								{   
													while(Centre!=0)
													{ 
														 pid_go();
													}
													turn++;
								}
	
				}
				else if(flag_turn_go==1)//��ͣ�㵽��
				{    pid_go();
				     if(at_terminal==1)//�յ�ͣת
										{
										 HAL_Delay(400);
										 set_stop();
//											test++; 
                     flag_turn_go++;											
										}							
				}
				else if(flag_turn_go==2&&Travel_indication==1)//��ͣ���ͷ
				{
				 set_stright_turnleft(44000);
					flag_turn_go++;	
				}
				else if(flag_turn_go==3)//�ص�����
				{
				  pid_go();
				  openmv_turnright();
				}
				else if(flag_turn_go==4)//��һ��ת��
				{
					pid_go();
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
																												set_stright_go(15440);//λ�ý���
																											 set_stright_turnright(22000);
																												flag_turn_go++;
//				                                               flag_turn++;
																											}
																											else if(dis_cross_center==2)
																											{
																												set_stright_go(15440);//λ�ý���
																											set_stright_turnleft(22000);//ת180��
																												flag_turn_go++;
//				                                                flag_turn++;
																											}
																											else if(dis_cross_center==3)
																											{
																										  motor_2_pwm_nomal=300;		
																										  motor_1_pwm_nomal=300;
																										  __HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
																										  while(((short)(__HAL_TIM_GET_COUNTER(&htim5)))<3600)
																										  { 
																										  pid_go();
																										  }
																										  motor_2_pwm_nomal=180;		
																									  motor_1_pwm_nomal=180;
																									   }
																										 else if(dis_cross_center==4)
																										{
																												set_stright_go(15440);//λ�ý���
																											set_stright_turnleft(22000);//ת180��
                                                      motor_2_pwm_nomal=300;		
																										  motor_1_pwm_nomal=300;
																										  __HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
																										  while(((short)(__HAL_TIM_GET_COUNTER(&htim5)))<3600)
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
																												set_stright_go(15440);//λ�ý���
																											 set_stright_turnright(22000);
																												flag_turn_go++;
//				                                               flag_turn_go++;
																											}
																											else if(dis_cross_center==2)
																											{
																												set_stright_go(15440);//λ�ý���
																											set_stright_turnleft(22000);//ת180��
																												flag_turn_go++;
//				                                                flag_turn_go++;
																											}
																											if(dis_cross_center==4)
																										 {
																												set_stright_go(15440);//λ�ý���
																											set_stright_turnleft(22000);//ת180��
                                                      motor_2_pwm_nomal=300;		
																										  motor_1_pwm_nomal=300;
																										  __HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
																										  while(((short)(__HAL_TIM_GET_COUNTER(&htim5)))<3600)
																										  { 
																										  pid_go();
																										  }
																										  motor_2_pwm_nomal=180;		
																									   motor_1_pwm_nomal=180;
																										 }
																										 else if(dis_cross_center==5)
																										 {
																														 set_stright_turnleft(44000);//ת180��
																														 flag_turn_go++;
																														 motor_2_pwm_nomal=400;		
																														 motor_1_pwm_nomal=400;
																															__HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
																														 while(((short)(__HAL_TIM_GET_COUNTER(&htim5)))<8000)
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
																				 set_stright_turnleft(44000);//ת180��
																				 flag_turn_go++;
																	       motor_2_pwm_nomal=400;		
																				 motor_1_pwm_nomal=400;
																			  	__HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
																				 while(((short)(__HAL_TIM_GET_COUNTER(&htim5)))<8000)
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
				else if(flag_turn_go==5)//�ڶ���ת��
				{ 
					pid_go();	         
												          
																											 if(dis_cross_center_2==1)
																											 {
//																													set_stright_go(500);//λ�ý���
//																													set_stright_turnright(1000);//ת180��
																															 openmv_turnright();
//																															 flag_turn_go++;
																											 }
																											 else if(dis_cross_center_2==2)
																											 {
//																												 set_stright_go(500);//λ�ý���
//																											   set_stright_turnleft(1000);//ת180��
																															 openmv_turnleft();
//																															 flag_turn_go++;
																											 }	
																										 
				 }
				else if(flag_turn_go==6)//ǰ���յ�
				{ 
					pid_go();
				  if(at_terminal==1)//�յ�ֹͣ
						 {   
								 HAL_Delay(1000);
								 set_stop();
								 test++;	
                 flag_turn_go++;							 
		         }
				}
				




				}
				if(a==1&&test==2)//�յ�ת��
				{
					   HAL_Delay(50);
				     set_stright_turnleft(44000);
						 test++;	
             flag_turn=0;	
				}
				if(a==1&&test==3)//�س̽׶�
				{ 
					 pid_go();
				   if(dis_cross_center==2&&dis_cross_center_2==2)//3-1�ŷ�
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

					if(at_terminal==1)//�յ�ͣת
										{
										 HAL_Delay(400);
										 set_stop();
											test++;	
						//				 while(1);
										}				
				}

				}
			}				
		 
			
			
			
			
		
		}
		LCD_ShowNum(0,15,(short)(__HAL_TIM_GET_COUNTER(&htim5)),5, 12);
		LCD_ShowNum(30,15,(short)(__HAL_TIM_GET_COUNTER(&htim3)),5, 12);
		LCD_ShowNum(0, 0,MotorOutput1,5, 12);
		LCD_ShowNum(30, 0,MotorOutput2,5, 12);
	  LCD_ShowNum(0, 45,a,5, 12);
		LCD_ShowNum(30, 45,test,5, 12);
		LCD_ShowNum(60, 45,turn,5, 12);
		
//		sprintf(str,"%d %d %d %d %d %d %d %d",stright_or_cross,stright,dis_cross_center,at_terminal,control,dis_cross_center_2,Centre,right_flag);
//		        LCD_ShowString(0, 60, 240, 12, 12, str);
  }
  /* USER CODE END 3 */
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//�����жϻص�
{
  uint16_t tem3;
  uint16_t tem1;
  if(huart->Instance==USART3)
  {
    tem3=usart3_rxbuff;
    Bluetooth_Receive_Data(tem3);
  }
  if(huart->Instance==USART1)
  {
    tem1=usart1_rxbuff;
		Openmv_Receive_Data(tem1);
  }		
    HAL_UART_Receive_IT(&huart3,(void *)&usart3_rxbuff,1);
    HAL_UART_Receive_IT(&huart1,(void *)&usart1_rxbuff,1);
 }

 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//�����жϻص�
{
//  if (GPIO_Pin ==GPIO_PIN_13)
//  {
////  test++;
////  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);//������ҩ�׶Σ��ر��жϷ���
////		set_stright_turnright(1);
//		__HAL_TIM_SET_COUNTER(&htim5,0); // ���������� 
//		set_turn_left();
//		while((67295-((__HAL_TIM_GET_COUNTER(&htim5))))<22000)
//		{ 
////      CS=(short)(__HAL_TIM_GET_COUNTER(&htim5));
////			LCD_ShowNum(0, 15,CS,5, 12);
//			LCD_ShowNum(0, 15,(short)(__HAL_TIM_GET_COUNTER(&htim5)),5, 12);
//		}
//		
//		set_stop();
//  }
  if (GPIO_Pin ==GPIO_PIN_3)
  {  
     test++;
     HAL_NVIC_DisableIRQ(EXTI3_IRQn);//������ҩ�׶Σ��ر��жϷ���
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
