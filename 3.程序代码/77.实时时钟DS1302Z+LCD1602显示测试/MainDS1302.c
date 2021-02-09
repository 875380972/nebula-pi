/*******************************************************************
*             ʵʱʱ��DS1302��ʾ����                                            
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
*                                                                 	
*******************************************************************/
#include<reg52.h>
#include"Drive_1602.h"
#include"Drive_DS1302.h"

#define uchar unsigned char
#define  uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

sbit FM = P0^0;//������
sbit DU = P0^6;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P0^7;
	
uchar T_flag  = 0;//��ʱ500ms��־λ
uchar str[23]=0;  //�ַ���ʱ�洢����
unsigned char code SetTime[7]={//2017��,�����գ�12��31��,23ʱ58��56�룬ʱ���ʼֵ
	 						0x56,0x58,0x23,0x31,0x12,0x07,0x17};
uchar CurrentTime[7]={0};//�洢ʱ�����

void main()
{
 	Init_1602();//1602��ʼ

	P2 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 

	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;
	TR0  = 1;		 //������ʱ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�


	Init_1302(SetTime);//1302��ʼ��

	while(1)
	{
		if(T_flag)//500ms��ʱ
		{
			T_flag = 0;
			GetTime(CurrentTime);//��ȡʱ��

			str[0] = '2';	 
			str[1] = '0'; 	 
			str[2] = (CurrentTime[6]>>4)+'0';	 //��
			str[3] = (CurrentTime[6]& 0x0F)+'0'; 
			str[4] = '-';
			str[5] = (CurrentTime[4]>>4)+'0';	 //��
			str[6] = (CurrentTime[4]& 0x0F)+'0';
			str[7] = '-';
			str[8] = (CurrentTime[3]>>4)+'0';	 //��
			str[9] = (CurrentTime[3]& 0x0F)+'0'; 
		   str[10] = '\0';
		   str[11] = (CurrentTime[2]>>4)+'0';	 //ʱ
		   str[12] = (CurrentTime[2]& 0x0F)+'0';
		   str[13] = ':';
		   str[14] = (CurrentTime[1]>>4)+'0';	 //��
		   str[15] = (CurrentTime[1]& 0x0F)+'0'; 
		   str[16] = ':';	   
		   str[17] = (CurrentTime[0]>>4)+'0';	 //��
		   str[18] = (CurrentTime[0]& 0x0F)+'0';
		   str[19] = ' ';
		   str[20] = (CurrentTime[5]>>4)+'0';	 //����
		   str[21] = (CurrentTime[5]& 0x0F)+'0';
		   str[22] = '\0';
		    
		  	Disp_1602_str(1,4,str);	//����õ�ʱ��ֱ���ʾ��1602�ĵ�һ����
			Disp_1602_str(2,3,str+11);	
		}
	}
}

//��ʱ��0�ж��ӳ���,��ʱ1ms
void timer0() interrupt 1
{
	static uint T_500ms = 0;

	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;	

	T_500ms++;
	if(T_500ms>=500)//500ms,��λT_flag
	{
		T_500ms = 0;
		T_flag = 1;	
	}
}










