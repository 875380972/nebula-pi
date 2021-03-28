/************************************************************
*             ���ڹ��ܲ���                                            
* ***********************************************************
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
* ����  �ܡ�
*       	���ڹ�����ʽ1����ʱ��1����ģʽ2,9600,8,1
*  			�����յ������ݼ�1���ͻ�ȥ���յ�����ʱ��תled0
* 			����������ʱ��תled1,���������ַ���
*                                                              	
************************************************************/
#include<reg52.h>
#include <oled.h>
#include "bmp.h"

sfr AUXR  = 0x8E; //Auxiliary Register  T0x12 T1x12 UART_M0x6 BRTR S2SMOD BRTx12 EXTRAM S1BRS  0000,0000
//-----------------------------------
sfr AUXR1 = 0xA2; //Auxiliary Register 1  -  PCA_P4  SPI_P4  S2_P4  GF2    ADRJ   -    DPS  0000,0000

#define uchar  unsigned char
#define uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define BAUD 345600	  //1T��Ƭ���������

sbit led0 = P1^0; //led0λ����
sbit led1 = P1^1; //led1λ����

uchar busy = 0;//������һ֡���ݱ�־λ
 uchar number,flag =0;
uchar xdata DataBuff[1024];//ʹ�ùؼ���Xdataʹ��STC12�ڲ�1024Byte�ڲ���չRAM

void Uart_init(void);//���ڳ�ʼ����������
void Send_String(char *s);//�ַ������ͺ�����

void main()
{
	Uart_init();  // ���ڳ�ʼ��
	EA = 1;           //�����ж�
	
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 
	
	Send_String("Nebula-PI Uart Test!\n");	//�����ַ���
	
	OLED_Clear();
	OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
	while(1)
	{
		if(flag == 1)
		{
			flag = 0;
			//Send_String(DataBuff);
			//OLED_Clear();
			SBUF = number++;
			OLED_DrawBMP(0,0,128,8,DataBuff);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
		}
	}
}
//�����жϺ���
void Uart_r(void) interrupt 4
{
	if(RI)
	{
		static unsigned int count  = 0;
		RI = 0;		   //��������ж�
		
		DataBuff[count] = SBUF;

		if(count==0&&DataBuff[count]==0xEB)
			{
				count = 1;
			}
			else if(count==1&&DataBuff[count]==0x90)
			{
				count = 2;
			}	
			else if(count >= 2 && count < 1022)
			{
				count ++;
			}
			else if(count == 1022)
			{
					count = 0;
					flag = 1;
				DataBuff[1023] = 0;
			}
		else
			{
					count = 0;
			}	
			
		led0 = ~led0;  //��תled0
		
	}
	if(TI)
	{
		TI = 0;		   //���㷢���ж�
		led1 = ~led1;  //��תled1
		busy = 0;      //���������ݣ�����������־λ
		
	}
}

//���ڳ�ʼ������
void Uart_init(void) 
{
	//Max baud 345600bps
	
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFF;		//�趨��ʱ��ֵ
	TH1 = 0xFF;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1

	ES = 1;//�������ж�
}
//�ַ������ͺ�
void Send_String(char *s)
{	
	while(*s)   //����ַ����Ƿ��˽�β
	{	
		while(busy);  //�ȴ���һ֡���ݷ������
		busy = 1;
		SBUF = *s++;  //���͵�ǰ�ַ��������ַ�ָ���Ƶ���һ���ַ�
	}	
}