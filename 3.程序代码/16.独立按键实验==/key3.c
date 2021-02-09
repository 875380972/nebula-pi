#include<reg52.h>

#define uchar  unsigned char
#define uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

sbit led0 = P1^0;//LEDС�ƹܽŶ���
sbit FM = P2^4;//�������ܽ�λ����

sbit Key17 = P3^0;//���������ܽŶ���
sbit Key20 = P3^3;

sbit DU = P2^7;
sbit WE = P2^6;	
//������(0~9,A,b,C,d,E,F,ȫ��,ȫ��)��������
uchar code table_D[]={0xC0,0xF9,0xA4,0xB0,
					0x99,0x92,0x82,0xF8,
					0x80,0x90,0x88,0x83,
					0xC6,0xA1,0x86,0x8E,
					0x00,0xFF};	
//λѡ����
uchar code table_W[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFF,0x00};
void LED_disp(unsigned char Num_DU,unsigned char Num_WE);
void delayms(unsigned int ms);

uchar KeyCount=0;//��������ֵ
bit KeyLast=1;//������ʷ״̬
bit KeyNow=1;//������ǰ״̬

void main()
{
	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;

	TR0  = 1;		 //������ʱ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�

	while(1)
	{
		if(KeyLast != KeyNow)//�ж���ʷֵ�뵱ǰֵ�Ƿ�һ�£���һ��˵������״̬�����仯
		{	
			if(KeyNow == 0)//��ǰΪ0˵����������
			{
				KeyCount++;
				if(KeyCount > 9)
				{
					KeyCount = 0;
				}
				LED_disp(KeyCount,7);
			}			
			KeyLast = KeyNow;
		}			
	}
}
//������ʱ����
void delayms(unsigned int ms)
{
	unsigned int x,y;
	for(x=ms;x>0;x--)
		for(y=70;y>0;y--);
}
/*----------------------------------------------------
** �����������ʾ����
**
** Num_DU:��ʾ���ַ�
** Num_WE:��ʾ��λ
----------------------------------------------------*/
void LED_disp(unsigned char Num_DU,unsigned char Num_WE)
{
		//�ر����������,��������
		P0 =table_W[8];
		WE = 1;
		WE = 0;
		//�����ַ�
		P0 = ~table_D[Num_DU];
		DU = 1;
		DU = 0;	
		//����λ
		P0 = ~table_W[Num_WE];
		WE = 1;
		WE = 0;
}
//��ʱ���жϺ���
void timer0() interrupt 1
{
	static unsigned int Key = 0x03FF;

	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;
			
	if(Key17)
	{
		Key = (Key<<1) + 1;
		
	}
	else
	{	
		 Key = Key<<1;
	}
	//Key = (Key<<1) | Key17;
	if(0x03FF == (Key&0x03FF))
	{
		KeyNow = 1;
	}
	else if(0 == (Key&0x03FF))
	{
		KeyNow = 0;
		led0 = KeyNow;
	}
	else
	{;}
}