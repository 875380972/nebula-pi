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
#include "oled.h"
#include "bsp_timer0.h"

#define uchar unsigned char
#define  uint unsigned int

sbit DU = P0^6;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P0^7;

sbit led2 = P1^2;

extern char UartRxBusy;
extern char UartRxFlag;
extern char RxLen;
extern char RxBuff[65];//oled�����ʾ64���ַ�
extern char UartRxDelay;

ShowRxBuff(void);

void main()
{

	Uart_init(); //���ڳ�ʼ��
	
	OLED_Init();//��ʼ��OLED 
	
	Timer0_1ms_init();
	
	OLED_Clear();//�����Ļ
	
	PT0=0;
	PS =1;
	
	
	P2 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 

	OLED_ShowString(0,2,"Nebula-Pi,RYMCU!",16,0);
	
	WiFiInit(); //wif��ʼ��
	
	while(1)
	{
			ShowRxBuff();
//		if(UartRxFlag)
//		{
//			UartRxFlag = 0;
//			led2=~led2;
//			
//			OLED_ShowNum(0,0,RxLen,3,16,0);
//		}
	}

}

ShowRxBuff(void)
{
	char i = 0;
	
	if(UartRxFlag)
	{
		
		led2=0;
		for(i=0;i< RxLen;i++)
		{
			if(RxBuff[i]<'!' || RxBuff[i]>'z') RxBuff[i]= ' ';//���ɴ�ӡ�ַ�ȫ��ת���ɣ�
		}
		RxBuff[RxLen]=0;//�ַ�������
		OLED_Clear();//�����Ļ
		//OLED_ShowNum(0,0,RxLen,3,16,0);
		OLED_ShowString(0,0,RxBuff,16,0);
		RxLen = 0;//��ͷ��ʼ������	
		//Usart_SendString(RxBuff);
		UartRxFlag = 0;//������ձ�־λ
	}
}