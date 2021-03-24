/*******************************************************************
*             AT24C256(I2C)���ܲ���                                            
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
#include <reg52.h>
#include"Drive_AT24Cxx.h" //����AT24Cxxͷ�ļ�
#include"Drive_1602.h"

#define uchar unsigned char
#define  uint unsigned int

sbit DU = P0^6;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P0^7;

uchar str1[]="AT24c256 Wr Str!";
uchar str2[20];

void main()
{
	P2 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 

	Init_1602();//1602��ʼ��

	WrStr_AT24Cxx(str1,0x05,16);//д��16���ֽ�
	RdStr_AT24Cxx(str2,0x05,16);//��ȡ16���ֽ�

	Disp_1602_str(1,1,str2); //�����ݴӵ�һ�е�һ�п�ʼ��ʾ

	while(1);
}
