


#include "bsp_uart.h" 
#include "REG52.h"
bit busy = 0;
#define FOSC 11059200 //��Ƭ������Ƶ��
#define BAUD 9600	  //����������Ϊ9600
//���ڳ�ʼ������
void Uart_init(void) 
{
	SCON = 0x50;//��������Ϊ������ʽ1
	PCON = 0;   //�����ʲ��ӱ�

	TMOD = 0x20;//���ö�ʱ��1Ϊ8λ�Զ���װģʽ
	TH1=TL1= 256- FOSC/32/12/BAUD;//��ʱ��1����ʼֵ
	
	ET1 = 0;//��ֹ��ʱ��1�ж�
	TR1 = 1;//������ʱ��1

	ES = 1;//�������ж�
	
	EA = 1;           //�����ж�
}
//�ַ������ͺ�
void Usart_SendString(char *s)
{	
	while(*s)   //����ַ����Ƿ��˽�β
	{	
		while(busy);  //�ȴ���һ֡���ݷ������
		busy = 1;
		SBUF = *s++;  //���͵�ǰ�ַ��������ַ�ָ���Ƶ���һ���ַ�
	}	
}

//�����жϺ���
void Uart_r(void) interrupt 4
{
	if(RI)
	{
		RI = 0;		   //��������ж�
		SBUF = SBUF;   //��ȡ���յ������ݼ�1�����ͳ�ȥ
		//led0 = ~led0;  //��תled0
		
	}
	if(TI)
	{
		TI = 0;		   //���㷢���ж�
		//led1 = ~led1;  //��תled1
		busy = 0;      //���������ݣ�����������־λ
		
	}
}