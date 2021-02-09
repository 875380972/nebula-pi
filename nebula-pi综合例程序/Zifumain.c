 #include<reg52.h>
//#include<intrins.h>
#include"Drive_1602.h"


#define uchar unsigned char
#define  uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

sbit FM = P2^4;//������
sbit DU = P2^7;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P2^6;
sbit DU_L = P2^3; 
	
uchar T_flag  = 0;
void delayms(unsigned int ms);//������ʱ

//����
#define BAUD 9600	  //����������Ϊ9600
uchar busy = 0;//������һ֡���ݱ�־λ
void Uart_init(void);//���ڳ�ʼ����������
void Send_String(char *s);//�ַ������ͺ�����
 
//�ַ�
uchar code row[8][5] ={{0x22,0x0A,0xA3,0x28,0x80},
			{0x66,0x0B,0xE2,0xA0,0x80},
			{0x56,0x0A,0xC2,0x40,0x00},
			{0x59,0x0A,0x80,0x80,0x00},
			{0x89,0x08,0x86,0x88,0x80},
			{0x09,0x18,0x86,0x94,0x80},
			{0x10,0x97,0xFA,0x14,0x00},
			{0x20,0x40,0x03,0xF0,0x00}};//������˸�
uchar  zifu[8][8]={0};
void main()
{
	uchar i=0;
	uchar str_zifu[16]={"zifuceshi"} ;
//	Init_1602();//1602��ʼ��
	//Uart_init();  // ���ڳ�ʼ��
	
	P0 = 0xff;//�ر����������
	WE = 1;
	WE = 0; 
	DU_L = 1;
	//
  	for(i=0;i<8;i++)
{
	zifu[0][i]=row[i][0]>>3;
	zifu[1][i]=((row[i][0]&0x07)<<2)+(row[i][1]>>6);
	zifu[2][i]=(row[i][1]>>1)&0x1F;
	zifu[3][i]=((row[i][1]&0x01)<<4)+(row[i][2]>>4);
	zifu[4][i]=((row[i][2]&0x0F)<<1)+(row[i][3]>>7);
	zifu[5][i]=(row[i][3]&0x7C)>>2;
	zifu[6][i]=((row[i][3]&0x03)<<3)+ (row[i][4]>>5);
	zifu[7][i]=row[i][4]&0x1F;
}
for(i=0;i<8;i++) str_zifu[i]= zifu[0][i];
	Disp_1602_str(1,1,"                ");//��ʾͨ����ʼ��

	 //����
	 Send_String("1111111");	//�����ַ���
	 Send_String( str_zifu);	 
	 while(1)
	 {
		   
		   ;	
	 }
}

//�����жϺ���
void Uart_r(void) interrupt 4
{
	if(RI)
	{
		RI = 0;		   //��������ж�
		SBUF = SBUF+1;   //��ȡ���յ������ݼ�1�����ͳ�ȥ		
	}
	if(TI)
	{	
		TI = 0;		   //���㷢���ж�
		busy = 0;      //���������ݣ�����������־λ
		
	}
}

//���ڳ�ʼ������,��ʱ��2�������ʷ�����
void Uart_init(void) 
{
	SCON = 0x50;//��������Ϊ������ʽ1
	//PCON = 0;   //�����ʲ��ӱ�

	//TMOD |= 0x20;//���ö�ʱ��1Ϊ8λ�Զ���װģʽ
	//TH1=TL1= 256- FOSC/32/12/BAUD;//��ʱ��1����ʼֵ
	TL2 = RCAP2L = (65536-(FOSC/32/BAUD)); //Set auto-reload vaule
	TH2 = RCAP2H = (65536-(FOSC/32/BAUD)) >> 8;
	T2CON = 0x34; //Timer2 start run

	//ET1 = 0;//��ֹ��ʱ��1�ж�
	//TR1 = 1;//������ʱ��1

	ES = 1;//�������ж�
	EA= 1;
}
//�����ַ������ͺ�
void Send_String(char *s)
{	
	while(*s)   //����ַ����Ƿ��˽�β
	{	
		while(busy);  //�ȴ���һ֡���ݷ������
		busy = 1;
		SBUF = *s++;  //���͵�ǰ�ַ��������ַ�ָ���Ƶ���һ���ַ�
	}	
}
//������ʱ����
void delayms(unsigned int ms)
{
	unsigned int x,y;
	for(x=ms;x>0;x--)
		for(y=70;y>0;y--);
}