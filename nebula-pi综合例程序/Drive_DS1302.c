#include<reg52.h>
#include"Drive_DS1302.h"

#define uchar unsigned char
#define  uint unsigned int

sbit   CE_1302 = P0^5;	//DS1302ͨ������CE��I/O��SCLK����
sbit   IO_1302 = P0^4;
sbit SCLK_1302 = P0^3;	

//д�ֽ�
void WrByte_1302(uchar dat)
{
	uchar j;
	bit flag;

	for(j=1;j<=8;j++)
 	{	//�ӵ͵������ν�1Byte����д��DS1302
		flag = dat&0x01;

		IO_1302 = flag;//��Ҫд��λ�ŵ�����
		SCLK_1302 = 0;
		SCLK_1302 = 1;//����һ�������أ����1λ����д��

		dat=dat>>1;//�������Ƶ���һλ
	}	
}
//���ֽ�
uchar RdByte_1302(void)
{
	uchar dat,flag,j;
	for(j=1;j<=8;j++)
	{		
		SCLK_1302 = 1;//����һ���½���
		SCLK_1302 = 0;

		flag = IO_1302;//��ȡDS1302������һλ����
		dat=(dat>>1)|(flag<<7);//������ֵ���λ��ǰ��
	}
	return dat;	
}
//���ֽ�дģʽ
void WrSingle_1302(uchar addr,uchar dat)
{
	CE_1302 = 1;//����Ƭѡ
	WrByte_1302(addr);//д���ַ������ָ��
	WrByte_1302(dat);//д������
	CE_1302 = 0;//����Ƭѡ
	SCLK_1302 = 0;//�ͷ�ʼ�����ߣ������´β���ʱ��Ҫ��(�ǳ���Ҫ)

}
//���ֽڶ�ģʽ
uchar RdSingle_1302(uchar addr)
{
	uchar dat;

	CE_1302 = 1;//����Ƭѡ
	WrByte_1302(addr);//д���ַ������ָ��
	dat = RdByte_1302();//��ȡһ���ֽ�����
 	CE_1302 = 0;//����Ƭѡ

	return dat;
}
//ͻ��дģʽ
void WrBurst_1302(uchar *SetTime)
{
	uchar j;

	CE_1302 = 1;//����Ƭѡ
	WrByte_1302(0xBE);//Burstģʽдר��ָ��
	for(j=0;j<=6;j++)
	{
		WrByte_1302(SetTime[j]);//д��7λʱ������
	}
	CE_1302 = 0;//����Ƭѡ	
}
//ͻ����ģʽ
void RdBurst_1302(uchar *CurrentTime)
{
	uchar j;

	CE_1302 = 1;//����Ƭѡ
	WrByte_1302(0xBF);//Burstģʽ��ר��ָ��
	for(j=0;j<=6;j++)
	{
		*CurrentTime = RdByte_1302();//��ȡһ���ֽ�����;
		CurrentTime++;
	}
	CE_1302 = 0;//����Ƭѡ	
}
//1302��ʼ��
void Init_1302(uchar *SetTime)
{ 
	  uchar j;

	  CE_1302 = 0;//��ʼ��ͨ������
	SCLK_1302 = 0;

	WrSingle_1302(0x8E,0x00);//���д������WP=0��
	
	for(j=0;j<=6;j++)
	{
		WrSingle_1302(0x80+2*j,SetTime[j]);//д��7��ʱ������
	}
	//WrBurst_1302(SetTime);//������Burstģʽʱ��ʹ�ô�����������forѭ�����
}
//��ȡ��ǰʱ��ֵ
void GetTime(uchar *CurrentTime)
{
	  uchar j;

	  CE_1302 = 0;//��ʼ��ͨ������
	SCLK_1302 = 0;

	for(j=0;j<=6;j++)
	{
		 *CurrentTime = RdSingle_1302(0x81+2*j);//��ȡ7��ʱ������
		 CurrentTime++;
	}
	
	//RdBurst_1302(CurrentTime); //������Burstģʽʱ��ʹ�ô�����������forѭ�����
}
















