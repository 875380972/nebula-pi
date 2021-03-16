/*******************************************************************
*                                                        
* ******************************************************************
* ����оƬ����STC89SC52/STC12C5A60S2
* ����Ƶ�ʡ�: 11.0592MHz 
*                                                                                                                               	
* ����  ������ V1.0                                          	
* ����  �ߡ��� hugh                            	
* ����  վ���� www.rymcu.com                            	
* ����  �䡿�� hugh@rymcu.com                                         	
* ����  �̡��� rymcu.taobao.com                                          	
*                                                                 	
* ����  Ȩ��All Rights Reserved 
* ����  �����˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��
         
* ����  �ܡ���ʱ���жϺ�������ʾ�����                                                        	
*******************************************************************/
#include<reg52.h>

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����
unsigned int count = 0;

unsigned int T_count  = 0;//��¼ms��
unsigned int Sec   = 0; //��¼s��
unsigned int  Buf_LED[4] ={0}; //�洢4������ܵ���ʱֵ

sbit DU = P0^6;//����ܶ�ѡ����
sbit WE = P0^7;//�����λѡ����

//������(0~9,A,b,C,d,E,F,ȫ��)
unsigned char code table_D[]={0x3F,0x06,0x5B,0x4F,
															0x66,0x6D,0x7D,0x07,
															0x7F,0x6F,0x77,0x7C,
															0x39,0x5E,0x79,0x71,
															0xFF};
//λѡ����,��Ӧ�����λ1,2,3,4
unsigned char code table_W[]={0xFE,0xFD,0xFB,0xF7};

void main()
{
	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;

	TR0  = 1;		 //������ʱ��
	
	//�ж���أ������½ڻὲ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�

	while(1)
	{
		if(T_count>=1000)//1000ms����һ������
		{
			T_count =0;
			Sec++;
		
		Buf_LED[3]= Sec%10;      //��λ
		Buf_LED[2]= Sec/10%10;   //ʮλ
		Buf_LED[1]= Sec/100%10;  //��λ
		Buf_LED[0]= Sec/1000%10; //ǧλ
		}
	}

}

void timer0() interrupt 1 //��ʱ��0�жϺ����Ĺ̶�д��
{
	static unsigned char flag=0;
	
	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;

	T_count++; //ÿ1ms�Լ�һ��
	
	count++;
	if(count>=2) //ע����һ����䣬ʹ����һ����������ʲô��һ����Ч���ɣ�
	{	
		count = 0;
		
		P2 = 0x00;//����Ӱ����,������������еĶζ�Ϩ�𣬼�ʱλѡ����Ҳ�������
		DU = 1;
		DU = 0;//�����
		
		P2 = table_W[flag];
		WE = 1;
		WE = 0;//����λ
		
		P2 = table_D[Buf_LED[flag]];
		DU = 1;
		DU = 0;//�����
		
		flag++;
		if(flag>=4) flag = 0;//flag��0-3֮��ѭ��
	}
}
