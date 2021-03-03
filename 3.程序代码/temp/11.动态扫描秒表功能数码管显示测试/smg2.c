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
         
* ����  �ܡ�����������                                                             	
*******************************************************************/
#include<reg52.h>

#define uchar  unsigned char
#define uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

uint count = 0;
uint flag  = 0;

uint T_count  = 0;
uint Sec   = 0;

sbit DU = P0^6;
sbit WE = P0^7;	

uchar  Buf_LED[4] ={0};


//������(0~9,A,b,C,d,E,F,ȫ��)
uchar code table_D[]={0x3F,0x06,0x5B,0x4F,
					0x66,0x6D,0x7D,0x07,
					0x7F,0x6F,0xEE,0x3e,
					0x9c,0x7a,0x9e,0x8e,
					0x00};
//λѡ����
uchar code table_W[]={0x00,0x01,0x02,0x04,0x8};

void main()
{
	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;

	TR0  = 1;		 //������ʱ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�

	while(1)	  //ѭ��
	{
		if(T_count>=1000)//1000ms����һ������
		{
			T_count =0;
			Sec++;
		
		Buf_LED[3]= Sec%10;
		Buf_LED[2]= Sec/10%10;
		Buf_LED[1]= Sec/100%10;
		Buf_LED[0]= Sec/1000%10;
		}
	}
}

void timer0() interrupt 1
{
	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;
	
	T_count++;
	count++;
	if(count>= 2)//ÿһ�������һ���жϣ��ﵽ2����Ϊ2ms����һ������ܡ�
	{
		count = 0;

		P2 =~table_W[0];//�ر���������ܣ���������
		WE = 1;
		WE = 0;

		P2 = table_D[Buf_LED[flag]];//��ʾ��
		DU = 1;
		DU = 0;
	
		P2 = ~table_W[flag+1];//�����1~4ѭ������
		WE = 1;
		WE = 0;

		flag++;
		if(flag>=4)
			flag =0;
	}
}
