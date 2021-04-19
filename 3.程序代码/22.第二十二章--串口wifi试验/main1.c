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
			
		P2 = 0xff;//�ر����������
		WE = 1;
		WE = 0; 
	
	
		//���ӵ���������ͨ��
	
		Usart_SendString("AT+RESTORE\r\n"); //�ָ�����ֵ
		Usart_SendString("AT+RST\r\n"); 		//��λģ��
	
		Usart_SendString("AT+CWMODE_DEF=3\r\n"); 		//AT+STAģʽ
	
		Usart_SendString("AT+CWJAP_DEF=\"TP-LINK_wj\",\"wj81004\"\r\n");//���ӵ�wifi
	
		Usart_SendString("AT+CIPSTART=\"TCP\",\"192.168.150.1\",5001\r\n");//���ӵ�������	
	
		Usart_SendString("AT+CIPSEND=5\r\n");//��������	
	
	
	
	
	
	
	
	
	
	
		while(1);
	
}