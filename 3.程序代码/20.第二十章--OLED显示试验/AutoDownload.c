#include "REG52.h"

#define FOSC 11059200 //��Ƭ������Ƶ��
#define BAUD 9600	  //����������Ϊ9600

sfr ISP_CONTR = 0xe7;

//�����жϺ���
void Uart_r(void) interrupt 4
{
	if(RI)
	{
		RI = 0;		   //��������ж�
		
		if(SBUF == 0x55) ISP_CONTR |= 0x60;//��λ��Ƭ�� 	
	}

}

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
	EA = 1;//�����ж�
}

void AutoDownload_init(void)
{
	Uart_init(); 
}