/*******************************************************************
*                                                        
* ******************************************************************
* ����оƬ����STC89SC52/STC12C5A60S2
* ����Ƶ�ʡ�: 11.0592MHz 
*                                                                                                                               	
* ����  ������ V1.0                                          	
* ����  �ߡ��� hugh                            	
* ����  վ���� www.rymcu.com                            	
* ����  �䡿�� hugh@rymcu.com                                         	
* ����  �̡��� rymcu.taobao.com                                          	
*                                                                 	
* ����  Ȩ��All Rights Reserved 
* ����  �����˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��
         
* ����  �ܡ�����Ʋ���                                                         	
*******************************************************************/
#include<reg52.h> //����ͷ�ļ�

sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED3 = P1^2;
sbit LED4 = P1^3;

sbit LED5 = P1^4;
sbit LED6 = P1^5;
sbit LED7 = P1^6;
sbit LED8 = P1^7;

void delay(void);

int i;
int flag=0;
 
void main()//���������

{ 
 P0 = 0xff;
	while(1)
	{
		int leds[8]={LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8};
		while(1)
		{
			;
		}
	}


}
void delay(void)
{
	int i;
	for(i=0;i<25000;i++);//��ʱһ��ʱ
}