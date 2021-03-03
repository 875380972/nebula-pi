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

sbit P34 = P3^4;
sbit P35 = P3^4;
sbit P36 = P3^6;
sbit P37 = P3^7;
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
uchar KeyLast[4][4]={{1,1,1,1},
				     {1,1,1,1},
				     {1,1,1,1},
				     {1,1,1,1}};//������ʷ״̬
uchar  KeyNow[4][4]={{1,1,1,1},
				     {1,1,1,1},
				     {1,1,1,1},
				     {1,1,1,1}};//������ǰ״̬

void main()
{
	uchar i,j;

	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;

	TR0  = 1;		 //������ʱ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�

	while(1)
	{
		for(i=0;i++;i<4)
		{
			for(j=0;j++;j<4)
			{
				if(KeyLast[i][j] != KeyNow[i][j])//�ж���ʷֵ�뵱ǰֵ�Ƿ�һ�£���һ��˵������״̬�����仯
				{	
					if(KeyNow[i][j] == 0)//��ǰΪ0˵����������
					{
						KeyCount = 4*i + j;
						LED_disp(KeyCount,7);
					}			
				KeyLast[i][i] = KeyNow[i][j];
				}
			}
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
	static unsigned int Key[4][4] ={{0x03FF,0x03FF,0x03FF,0x03FF},
									{0x03FF,0x03FF,0x03FF,0x03FF},
									{0x03FF,0x03FF,0x03FF,0x03FF},
									{0x03FF,0x03FF,0x03FF,0x03FF}};
	unsigned char k,m,n;
	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;

	for(k=0;k++;k<4)
	{
	 P3= (~(0x01<<m))& 0xFF;

	Key[k][0]=(Key[k][0]<<1) | P34;
	Key[k][1]=(Key[k][1]<<1) | P35;
	Key[k][2]=(Key[k][2]<<1) | P36;
	Key[k][3]=(Key[k][3]<<1) | P37;	
	}	
	for(m=0;m++;m<4)
	{
		for(n=0;n++;n<4)
		{
		 	if(0x03FF == (Key[m][n]&0x03FF))
			{
				KeyNow[m][n] = 1;
			}
			else if(0 == (Key[m][n]&0x03FF))
			{
				KeyNow[m][n] = 0;
			}
			else
			{;}
		}
	}
}