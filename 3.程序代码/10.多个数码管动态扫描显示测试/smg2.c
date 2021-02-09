/*******************************************************************
*            �������ʾ����                                            
* ******************************************************************
* ����оƬ����STC89SC52/STC12C5A60S2
* ����Ƶ�ʡ�: 11.0592MHz 
*                                                                                                                               	
* ����  ������ V1.0                                          	
* ����  �ߡ��� stephenhugh                            	
* ����  վ����https://rymcu.taobao.com/                              	
* ����  �䡿��                                          	
*                                                                 	
* ����  Ȩ��All Rights Reserved 
* ����  �����˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��
         
* ����  �ܡ������1~4ѭ����ʾ����1~4,��̬ɨ�跨�����仯�ٶȺܿ죬�˴�Ϊ2ms                                                           	
*******************************************************************/
#include<reg52.h>

#define uchar  unsigned char
#define uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

uint count = 0;
uint flag  = 0;

sbit DU = P0^6;
sbit WE = P0^7;

//������(0~9,A,b,C,d,E,F,ȫ��)
uchar code table_D[]={0x3F,0x06,0x5B,0x4F,
					0x66,0x6D,0x7D,0x07,
					0x7F,0x6F,0xEE,0x3e,
					0x9c,0x7a,0x9e,0x8e,
					0x00};

uchar code table_W[]={0x00,0x01,0x02,0x04,0x8};
//λѡ����
//uchar code table_W[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFF,0x00};
void main()
{
	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;

	TR0  = 1;		 //������ʱ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�

	while(1);	  //ѭ��
}

void timer0() interrupt 1
{
	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;

	count++;
	if(count>= 2)//ÿһ�������һ���жϣ��ﵽ2����Ϊ2ms,����һ���������ʾ��
	{
		count = 0;

		P2 =~table_W[0];//�ر���������ܣ���������
		WE = 1;
		WE = 0;
		
		flag++;

		P2 = table_D[flag];//����1~4ѭ��
		DU = 1;
		DU = 0;
	
		P2 = ~table_W[flag];//�����1~4ѭ������
		WE = 1;
		WE = 0;

		
		if(flag>=4)
			flag =0;
	}
}
