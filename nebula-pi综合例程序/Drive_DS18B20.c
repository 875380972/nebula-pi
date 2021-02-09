#include<reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define  uint unsigned int

sbit DS18B20 = P3^7; //DS18B20������I/O�ڶ���

void DelayT_10us(uchar count)
{
	while(count--)
	{	//ģ��10us��ʱ
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		_nop_();
		_nop_();
		_nop_();
		_nop_();
	}
}
void Init_DS18B20(void)
{ 
	//��Ƭ���������߲���ʱ600us
	DS18B20 = 0;
	DelayT_10us(50);
	//��Ƭ���ͷ����߲���ʱ60us
	DS18B20 = 1;
	DelayT_10us(6);
	//��DS18B20���ص͵�ƽʱ����ʾ�����ϴ��ڴ�����
	while(!DS18B20);
	DelayT_10us(50);
}
void WrByte_18B20(uchar dat)
{
	uchar j;
	bit flag;

	for(j=1;j<=8;j++)
 	{	//�ӵ͵���һ�ν�1Byte����д��DS18B20
		flag = dat&0x01;
    	dat=dat>>1;

		DS18B20 = 0;//�������߲���ʱ2us
		_nop_();
		_nop_();

		DS18B20 = flag;//��Ҫд��λ�ŵ�����
		DelayT_10us(6);//��ʱ60us
			  
		DS18B20 = 1;//�����ͷ�����
	}
}
uchar RdByte_18B20(void)
{
	uchar dat,flag,j;
	for(j=1;j<=8;j++)
	{		
		DS18B20 = 0;//�������߲���ʱ2us
		_nop_();
		_nop_();
		DS18B20 = 1;//�����ͷ����߲���ʱ2us
		_nop_();
		_nop_();

		flag = DS18B20;//�ɼ�
		DelayT_10us(6);//��ʱ60us

		//������ֵ���λ��ǰ��
		dat=(dat>>1)|(flag<<7);
	}
	return dat;	
}
uint GetT_18B20(void)
{ 
	uchar Temp_L,Temp_H;
	uint  Temp;

	Init_DS18B20();	   //��ʼ��
	WrByte_18B20(0xCC);//����ROM
	WrByte_18B20(0x44);//�����¶�ת��
	Init_DS18B20();	   //��ʼ��
	WrByte_18B20(0xCC);//����ROM
	WrByte_18B20(0xBE);//���Ͷ��¶�����
	//��ȡ�����ֽڵ��¶�ֵ
	Temp_L = RdByte_18B20();
	Temp_H = RdByte_18B20();

	Temp = ((uint)Temp_H<<8) + Temp_L;//���¶���ϳ�16����
	return Temp;
}