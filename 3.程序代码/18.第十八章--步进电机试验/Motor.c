/*******************************************************************
*   �������ת������                                          
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
#include<reg52.h>

unsigned char code MotorCode[8]={0xDF,0xCF,0xEF,0x5F,0x7F,0x3F,0xBF,0x9F};

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_2ms (65536 - FOSC/12*2/1000)  //��ʱ����ʼֵ����

sbit DU = P0^6;//����ܶ�ѡ����

void main(void)
{
		P2 = 0x00;//�ر����������
		DU = 1;
		DU = 0;//�����
	
		TMOD = 0x01;  //��ʱ������ģʽ����
		TL0  = T_2ms;
		TH0  = T_2ms>>8;
	
		TR0  = 1;//������ʱ��
		ET0  = 1;//����ʱ���ж�
		EA   = 1;//�����ж�
	
		while(1);
}

//��ʱ��1�жϺ���
void timer0() interrupt 1
{
	static unsigned char index = 0;
		
		TL0  = T_2ms;//��װ��ʼֵ
		TH0  = T_2ms>>8;
	
		P2 =MotorCode[index];
		index++;
		if(index >= 8) index = 0;
	
}
