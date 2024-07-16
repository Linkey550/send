#include "openmv.h"
#include "stdio.h"
#include "usart.h"
#include "motor.h"
#include "math.h"
#include "pid.h"


//static uint8_t  Cx=0,Cy=0,Cw=0,Ch=0;
uint8_t stright_or_cross;		
uint8_t stright;
uint8_t dis_cross_center=3;
uint8_t at_terminal;
uint8_t terminal_num;
uint8_t direction;
uint8_t control;
uint8_t stright_pid;
uint8_t dis_cross_center_2=3;
uint8_t Centre;
uint8_t right_flag=0;

uint8_t Travel_indication=0;
uint8_t Process_indication=0;
uint8_t Turn_indication1=0;
uint8_t Turn_indication2=0;
uint8_t End_indication=0;

void   Openmv_Receive_Data(int16_t com_data)
{
  
    uint8_t i;
		static uint8_t RxCounter1=0;//����
		static uint16_t RxBuffer1[15]={0};
		static uint8_t RxState = 0;	
		static uint8_t RxFlag1 = 0;

  if(RxState==0&&com_data==0x2C)  //0x2c֡ͷ
				{
          
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;

				}

				else if(RxState==1&&com_data==0x12)  //0x12֡ͷ
				{

					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
				else if(RxState==2)
				{
           
					RxBuffer1[RxCounter1++]=com_data;
					if(RxCounter1>=15||com_data == 0x5B)       //RxBuffer1��������,�������ݽ���
					{
						RxState=3;
						RxFlag1=1;
            
						stright_or_cross=RxBuffer1[RxCounter1-9];//·��
						stright=RxBuffer1[RxCounter1-8];//pidƫ����
						dis_cross_center=RxBuffer1[RxCounter1-7];//����תָʾ
						at_terminal=RxBuffer1[RxCounter1-6];//�յ��ʶ
						control=RxBuffer1[RxCounter1-5];	//12/3456789����
						dis_cross_center_2=RxBuffer1[RxCounter1-4];//��������ת����
						Centre=RxBuffer1[RxCounter1-3];//���ľ�
						right_flag=RxBuffer1[RxCounter1-2];
						if(stright!=0)
						{
						  stright_pid=stright;
						}
						
//						sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d",stright_or_cross,stright,dis_cross_center,at_terminal,control,dis_cross_center_2,Centre,right_flag);
//		        LCD_ShowString(0, 60, 240, 12, 12, str);
//						strcpy(str, "");
						  LCD_ShowNum(0, 60,stright_or_cross,5, 12);
						  LCD_ShowNum(30, 60,stright,5, 12);
						  LCD_ShowNum(60, 60,dis_cross_center,5, 12);
						  LCD_ShowNum(90, 60,at_terminal,5, 12);
						  LCD_ShowNum(120, 60,control,5, 12);
						  LCD_ShowNum(150, 60,dis_cross_center_2,5, 12);
						  LCD_ShowNum(180, 60,Centre,5, 12);
						  LCD_ShowNum(210, 60,right_flag,5, 12);
//            printf("%d\r   ",stright_or_cross);
//            printf("%d\r   ",stright);
//            printf("%d\r   ",dis_cross_center);
//						printf("%d\r   ",at_terminal);
//            printf("%d\r\n",control); 

		        
					}
			}
		
				else if(RxState==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
								
						}
						else   //���մ���
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
						}
				} 
	
				else   //�����쳣
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
				}
      }

void   Bluetooth_Receive_Data(int16_t com_data)
{
  
    uint8_t i;
		static uint8_t RxCounter2=0;//����
		static uint16_t RxBuffer2[15]={0};
		static uint8_t RxState = 0;	
		static uint8_t RxFlag2 = 0;

  if(RxState==0&&com_data==0xAA)  //0x2c֡ͷ
				{
          
					RxState=1;
					RxBuffer2[RxCounter2++]=com_data;

				}

				else if(RxState==1&&com_data==0xBB)  //0x12֡ͷ
				{

					RxState=2;
					RxBuffer2[RxCounter2++]=com_data;
				}
				else if(RxState==2)
				{
           
					RxBuffer2[RxCounter2++]=com_data;
					if(RxCounter2>=15||com_data == 0xCC)       //RxBuffer1��������,�������ݽ���
					{
						RxState=3;
						RxFlag2=1;
            
            Travel_indication=RxBuffer2[RxCounter2-6];	//ת���ָʾ
						Process_indication=RxBuffer2[RxCounter2-5];//������ָʾ
						Turn_indication1=RxBuffer2[RxCounter2-4];//����ת����
						Turn_indication2=RxBuffer2[RxCounter2-3];//��������ת����
						End_indication=RxBuffer2[RxCounter2-2];
						if(stright!=0)
						{
						  stright_pid=stright;
						}
						
//						sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d",stright_or_cross,stright,dis_cross_center,at_terminal,control,dis_cross_center_2,Centre,right_flag);
//		        LCD_ShowString(0, 60, 240, 12, 12, str);
//						strcpy(str, "");
						  LCD_ShowNum(0, 30, Travel_indication,5, 12);
						  LCD_ShowNum(30, 30,Process_indication,5, 12);
						  LCD_ShowNum(60, 30,Turn_indication1,5, 12);
						  LCD_ShowNum(90, 30,Turn_indication2,5, 12);
	            LCD_ShowNum(120, 30,Turn_indication2,5, 12);
//            printf("%d\r   ",stright_or_cross);
//            printf("%d\r   ",stright);
//            printf("%d\r   ",dis_cross_center);
//						printf("%d\r   ",at_terminal);
//            printf("%d\r\n",control); 

		        
					}
			}
		
				else if(RxState==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer2[RxCounter2-1] == 0xCC)
						{
									
									RxFlag2 = 0;
									RxCounter2 = 0;
									RxState = 0;
								
						}
						else   //���մ���
						{
									RxState = 0;
									RxCounter2=0;
									for(i=0;i<10;i++)
									{
											RxBuffer2[i]=0x00;      //�����������������
									}
						}
				} 
	
				else   //�����쳣
				{
						RxState = 0;
						RxCounter2=0;
						for(i=0;i<10;i++)
						{
								RxBuffer2[i]=0x00;      //�����������������
						}
				}
      }

/**
  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}
// 
/**
  * ��������: �ض���c�⺯��getchar,scanf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart3, &ch, 1, 0xffff);
  return ch;
}

