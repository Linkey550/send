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
uint8_t right_flag;


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

/**
  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
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
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}

void UART_SendStr(uint8_t *pucstr,uint8_t longlen)
{
  uint8_t i;
	for(i=0;i<longlen;i++)
	{
	  while(HAL_UART_GetState(&huart1)==SET);
		HAL_UART_Transmit(&huart1,(uint8_t *)&pucstr[i],sizeof(pucstr[i]),HAL_MAX_DELAY);
	}


}

