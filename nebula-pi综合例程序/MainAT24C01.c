#include <reg52.h>
#include"Drive_AT24C01.h" //����AT24C01ͷ�ļ�
#include"Drive_1602.h"

#define uchar unsigned char
#define  uint unsigned int

sbit DU = P2^7;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P2^6;	
uchar str[10]=0;
void main()
{
	uchar dat=0;
	Init_1602();
	P0 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 

	//��AT24C01�洢����ַ0x08��д������110
	WrByte_AT24C01(0x08,110);
	Disp_1602_str(1,2,"AT24C02 test!");
	//��ȡAT24C01�洢����ַ0x08��������
	dat = RdByte_AT24C01(0x08);

	str[0]=dat/100+'0';
	str[1]=dat%100/10+'0';
	str[2]=dat%10+'0';
	//��������ʾ��1602�ĵ�2�е�6�д�
	Disp_1602_str(2,6,str);

	while(1);
}
