#include <reg52.h>
#include"Drive_AT24C01.h" //����AT24C01ͷ�ļ�
#include"Drive_1602.h"

#define uchar unsigned char
#define  uint unsigned int

sbit DU = P2^7;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P2^6;	

uchar str1[]="AT24c01 Wr Str!";
uchar str2[20];

void main()
{
	uchar dat=0;
	P0 = 0;//�ر����������
	WE = 1;
	WE = 0; 

	Init_1602();//1602��ʼ��

	WrStr_AT24C01(str1,0x05,16);//д��16���ֽ�
	RdStr_AT24C01(str2,0x05,16);//��ȡ16���ֽ�

	Disp_1602_str(1,1,str2); //�����ݴӵ�һ�е�һ�п�ʼ��ʾ

	while(1);
}

