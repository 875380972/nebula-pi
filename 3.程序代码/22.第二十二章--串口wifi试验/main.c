/*******************************************************************
*   ��Ƭ���ڲ��Դ�EEPROM��Flash����д���� (LCD��ʾ��Ƭ���ӵ����)                                          
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
#include "bsp_uart.h"
#include "bsp_wifi.h"

#define uchar unsigned char
#define  uint unsigned int

sbit DU = P0^6;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P0^7;

uchar pbuf[5] = {0};//���ݻ�����
uchar  str[8] = {0};//�ַ���ʱ����


void main()
{

	Uart_init(); //���ڳ�ʼ��
	WiFiInit(); //wif��ʼ��
	P2 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 

	

	while(1);

}
	
