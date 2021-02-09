#include<reg52.h>
#include"Drive_1602.h"
#include"Drive_PCF8591.h"

#define uchar unsigned char
#define  uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

sbit DU = P2^7;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P2^6;	

uchar str[10]=0;
uchar T_flag  = 0;
uchar val  = 0;
void ValueToString(unsigned char *str,unsigned char val);
void main()
{
	Init_1602();//1602��ʼ��
	P0 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 
	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;
	TR0  = 1;		 //������ʱ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�


	Disp_1602_str(1,1,"A0  A1  A2  A3  ");//��ʾͨ����ʼ��
	 while(1)
	 {
	 	if(T_flag)
		{
			T_flag = 0;

			val = ADC(0);
			DAC(val);//��ͨ����ɼ���������DA���
			ValueToString(str,val);
			Disp_1602_str(2,1,str);//��ʾͨ��0��ѹ

			val = ADC(1);
			ValueToString(str,val);
			Disp_1602_str(2,5,str);//��ʾͨ��1��ѹ

			val = ADC(2);
			ValueToString(str,val);
			Disp_1602_str(2,9,str);//��ʾͨ��2��ѹ
	
			val = ADC(3);
			ValueToString(str,val);
			Disp_1602_str(2,13,str);//��ʾͨ��3��ѹ
		}
	 }
}
//��AD������ֵת�����ַ���
void ValueToString(unsigned char *str,unsigned char val)
{
	//��ѹ=����ֵ*5V/255
	val = (val*50)/255;	//�Ŵ���10��
	str[0] = (val/10) + '0';//����λ
	str[1] = '.';//С����
	str[2] = (val%10) + '0';//С��λ
}
//��ʱ��0�ж��ӳ���,��ʱ1ms
void timer0() interrupt 1
{
	static uint T_500ms = 0;

	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;	

	T_500ms++;
	if(T_500ms>=500)//500ms,��λT_flag
	{
		T_500ms = 0;
		T_flag = 1;	
	}
}