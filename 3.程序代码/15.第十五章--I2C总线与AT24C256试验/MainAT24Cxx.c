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
	
uchar str[10]=0;

void delayms(unsigned int z)//��ʱ����
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=78;y>0;y--);
}

void main()
{
	uchar dat=0;
	Init_1602();

	P2 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 

	//��AT24Cxx�洢����ַ0x08��д������110
	WrByte_AT24Cxx(0x08,110);
	Disp_1602_str(1,2,"AT24C0x test!");
	//����д֮��������Ҫ���10ms���������´���ﵽ��ʱ��Ŀ��
	delayms(10);
	//��ȡAT24Cxx�洢����ַ0x08��������
	dat = RdByte_AT24Cxx(0x08);

	str[0]=dat/100+'0';
	str[1]=dat%100/10+'0';
	str[2]=dat%10+'0';
	//��������ʾ��1602�ĵ�2�е�6�д�
	Disp_1602_str(2,6,str);

	while(1);
}
