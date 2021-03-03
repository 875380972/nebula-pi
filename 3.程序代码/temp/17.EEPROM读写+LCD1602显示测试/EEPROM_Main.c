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
#include"Drive_1602.h"
#include"Drive_Eeprom.h"

#define uchar unsigned char
#define  uint unsigned int

sbit DU = P0^6;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P0^7;

uchar pbuf[5] = {0};//���ݻ�����
uchar  str[8] = {0};//�ַ���ʱ����

void main()
{
	Init_1602();//1602��ʼ��

	P2 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 

	ISP_IAP_readData(0x21f0,pbuf,sizeof(pbuf));  //��ȡ�ڲ��洢������ֵ

	pbuf[0]++;

	str[0] = pbuf[0]/100 + '0';
	str[1] = (pbuf[0]%100)/10 + '0';
	str[2] = pbuf[0]%10 + '0';
	str[4] = '\0';

   	Disp_1602_str(1,1,str);//��ʾ�ϵ����

	ISP_IAP_sectorErase(0x2000);                //��������,һ��512�ֽ�            
	ISP_IAP_writeData(0x21f0,pbuf,sizeof(pbuf));  //дEEPROM

	while(1);

}
	
