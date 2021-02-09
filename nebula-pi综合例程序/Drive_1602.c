#include <reg52.h>
#include "Drive_1602.h"

sbit RS_1602 = P3^6; //1602��RS��R/W��E���Ŷ���
sbit RW_1602 = P3^5;
sbit EN_1602 = P3^4;

//�ַ�����ʾ���ܣ��ӵ�row�У���column�п�ʼ��ʾ�ַ���str
void Disp_1602_str(unsigned char row,unsigned char column,char *str)
{
	unsigned char addr;
  //P0=P0&0x07;
	EA=0;
	addr = 	(row-1)*0x40 + (column-1);//��ϳɵ�ַ
	WR_Cmd(0x80+addr);//д��ַ����

	while(*str)//�ж�str�ַ����Ƿ��ѽ���
	{
		WR_Dat(*str++);//��str�ַ�����������д��
	}
	EA=1;
}

void Init_1602() //1602��ʼ����
{
	WR_Cmd(0x38);//����16x2��ʾ��5x7����8λ���ݽӿ�
	WR_Cmd(0x0C);//����ʾ���رչ��
	WR_Cmd(0x06);//����д��һ���ַ��󣬵�ַָ�롢������1
	WR_Cmd(0x01);//����ָ�����㡢��ʾ��ʾ����
}
void Ready() //���м�⺯��
{
	P2 = 0xFF;//P2�˿�����Ϊ����ʱ���ȸ�ֵ0xFF
	while(RD_sta() & 0x80);//bit7����1��ʾæ��һֱ��⵽0Ϊֹ	
}

unsigned char RD_sta()//��״̬����
{
	unsigned char sta;

	RS_1602 = 0;
   	RW_1602 = 1;//�����1602״̬ģʽ

	EN_1602 = 1;//����ʹ���ź�
	sta = P2;	//��1602״̬���ݶ�ȡ
	EN_1602 = 0;//����ʹ�ܣ���ɶ�����

	return sta; //��״ֵ̬��
}
void WR_Cmd(unsigned char cmd)//дָ���
{
	Ready();    //���1602�Ƿ��ڿ���״̬
	
	RS_1602 = 0;
    RW_1602 = 0;//����дָ��ģʽ

	P2 = cmd;   //��ָ���������

	EN_1602 = 1;//����ʹ���ź�
	EN_1602 = 0;//����ʹ�ܣ����д����	
}
void WR_Dat(unsigned char dat)//д���ݺ���
{
	Ready();    //���1602�Ƿ��ڿ���״̬

	RS_1602 = 1;
    RW_1602 = 0;//����д����ģʽ

	P2 = dat;   //���������

	EN_1602 = 1;//����ʹ���ź�
	EN_1602 = 0;//����ʹ�ܣ����д����	
}