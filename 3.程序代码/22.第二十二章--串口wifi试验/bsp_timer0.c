#include "bsp_uart.h" 
#include "REG52.h" 

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����
sbit led1 = P1^1;

void Timer0_1ms_init(void)//1ms��ʱ����ʼ��
{
	TMOD |= 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;

	TR0  = 1;		 //������ʱ��
	
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�
}

void timer0() interrupt 1 //��ʱ��0�жϺ����Ĺ̶�д��
{

	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;

	if(UartRxBusy)//���ڽ�������
	{
		UartRxDelay--;
		if(UartRxDelay == 0)
		{
			UartRxBusy = 0;
			UartRxFlag = 1; //�������ݽ������
			led1=0;
		}
	}
}

