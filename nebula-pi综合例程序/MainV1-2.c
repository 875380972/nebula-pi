/*******************************************************************
*            �������ʾ����                                            
* ******************************************************************
* ����оƬ����STC89SC52/STC12C5A60S2
* ����Ƶ�ʡ�: 11.0592MHz 
*                                                                                                                               	
* ����  ������ V1.0  
* ����  �ߡ��� stephenhugh 
*
* ����  վ���� www.rymcu.com                            	
* ����  �䡿�� hugh@rymcu.com                                         	
* ����  �̡��� rymcu.taobao.com
*
* ����  Ȩ��All Rights Reserved 
* ����  �����˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��
         
* ����  �ܡ�����������                                                             	
*******************************************************************/
#include<reg52.h>
#include<intrins.h>

#define uchar  unsigned char
#define uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

uint count = 0;
uint flag  = 0;

uint Count_T  = 0;
uint Sec   = 0;

sbit DU = P2^7;
sbit WE = P2^6;	
sbit DU_L = P2^3; 
//KEY
//uchar KeyCount=0;//��������ֵ
//uchar KeyLast[4]= {1,1,1,1};//������ʷ״̬
//uchar KeyNow[4] = {1,1,1,1};//������ǰ״̬
//uchar Key_flag[4]={0,0,0,0};//�������±�־λ��1��ʾ����
//����
//uchar xdata KeyLastJZ[4][4];// = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
//uchar  KeyNowJZ[4][4];// =  {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
//uchar  Key_falg[4][4];//=   {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
uchar  Buf_LED[8] ={0};
//������(0~9,A,b,C,d,E,Fȫ��,ȫ��)��������
uchar code table_D[]={0xC0,0xF9,0xA4,0xB0,
					0x99,0x92,0x82,0xF8,
					0x80,0x90,0x88,0x83,
					0xC6,0xA1,0x86,0x8E,
					0x00,0xFF,
					0x89,0x86,0xC7,0xC7,0xC0};	
//λѡ����
uchar code table_W[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFF,0x00};

void LED_disp(unsigned char Num_DU,unsigned char Num_WE);

void	ShuMa_QuanLiang()//ȫ��
	{
		Buf_LED[7]= 16;
		Buf_LED[6]= 16;
		Buf_LED[5]= 16;
		Buf_LED[4]= 16;
		Buf_LED[0]= 16;
		Buf_LED[1]= 16;
		Buf_LED[2]= 16;
		Buf_LED[3]= 16;
	}
void	ShuMa_QuanMie()//ȫ��
	{
		Buf_LED[7]= 17;
		Buf_LED[6]= 17;
		Buf_LED[5]= 17;
		Buf_LED[4]= 17;
		Buf_LED[0]= 17;
		Buf_LED[1]= 17;
		Buf_LED[2]= 17;
		Buf_LED[3]= 17;
	}
void	ShuMa_Leijia()//�����ۼ�
	{
		Buf_LED[7]= Sec%10;
		Buf_LED[6]= Buf_LED[7];
		Buf_LED[5]= Buf_LED[7];
		Buf_LED[4]= Buf_LED[7];
		Buf_LED[0]= Buf_LED[7];
		Buf_LED[1]= Buf_LED[7];
		Buf_LED[2]= Buf_LED[7];
		Buf_LED[3]= Buf_LED[7];
	}
void	ShuMa_suiji()//0-7һ�ε���
	{
		uchar i = 0;
		for(i=0;i<8;i++)
		{	
			Buf_LED[i]=17;	
		}
		Buf_LED[Sec-12]=(Sec-12)%10;
	}
void	ShuMa_Hell0()
		{
			Buf_LED[5]= 17;
			Buf_LED[6]= 17;
			Buf_LED[7]= 17;
			Buf_LED[0]= 18;
			Buf_LED[1]= 19;
			Buf_LED[2]= 20;
			Buf_LED[3]= 21;
			Buf_LED[4]= 22;
		}
void main()
{
	uchar i=0;	

	TMOD |= 0x10;	 //��ʱ��1����ģʽ����
	TL1  = T_1ms;	//װ�س�ʼֵ
	TH1  = T_1ms>>8;

	TR1  = 1;		 //������ʱ��
	ET1  = 1;		 //����ʱ���ж�
	
	
	TMOD = 0x01;	 //��ʱ������ģʽ����
	TL0  = T_1ms;	//װ�س�ʼֵ
	TH0  = T_1ms>>8;
	DU_L = 1;
	TR0  = 1;		 //������ʱ��
	ET0  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�


	while(1)	  //ѭ��
	{					
//KEy
//		for(i=0;i<4;i++)
//		{
//			if(KeyLast[i] != KeyNow[i])//�жϰ���״̬�Ƿ����仯
//			{
// 				if(KeyNow[i] == 0)	Key_flag[i] = 1;//�������£���λ���±�־
//				KeyLast[i] = KeyNow[i];	
//			}
//		}
//		for(i=0;i<4;i++)
//		{
//			if(Key_flag[i])
//			{
//				Key_flag[i]=0;
//				KeyCount = i;
//				//LED_disp(KeyCount,7);
//			Buf_LED[6]= (17+i)/10;
//			Buf_LED[7]= (17+i)%10;
//			P1=0;				
//			}

//		}
//		
		if(Count_T>=400)
		{
			Count_T =0;
			Sec++;
			 if(Sec<=9)ShuMa_Leijia();//�ۼ�
			 else if(Sec==10) ShuMa_QuanLiang();//��
			 else if(Sec==11) ShuMa_QuanMie();//��
			 else if(Sec>11 && Sec<=19)	ShuMa_suiji();//		 
			 else if(Sec>19 && Sec<=20)ShuMa_Hell0();
			 else;
		}
	}
}

void timer0() interrupt 1
{
	static uchar LED = 0xFE;
	static LED_Count = 0;

	TL0 = T_1ms;//��װ��ʼֵ
	TH0 = T_1ms>>8;
	
	Count_T++;
	count++;
	LED_Count++;
	if(LED_Count>=200)
	{
		LED_Count = 0;
		LED = _crol_(LED,1);
		P1 = LED;  
	}
	if(count>= 2)//ÿһ�������һ���жϣ��ﵽ2����Ϊ2ms����һ������ܡ�
	{
		count = 0;

		switch(flag)
		{
			case 0:LED_disp(Buf_LED[0],flag++);break;
			case 1:LED_disp(Buf_LED[1],flag++);break;
			case 2:LED_disp(Buf_LED[2],flag++);break;
			case 3:LED_disp(Buf_LED[3],flag++);break;
			case 4:LED_disp(Buf_LED[4],flag++);break;
			case 5:LED_disp(Buf_LED[5],flag++);break;
			case 6:LED_disp(Buf_LED[6],flag++);break;
			case 7:LED_disp(Buf_LED[7],flag);flag=0;break;
		   default:break;
		}
	}
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
void timer1() interrupt 3
{
	static unsigned int Key_caiyang[4] = {0x03FF,0x03FF,0x03FF,0x03FF};
	static unsigned char KeyJZ_caiyang[4][4]={{0xFF,0xFF,0xFF,0xFF},
											  {0xFF,0xFF,0xFF,0xFF},
											  {0xFF,0xFF,0xFF,0xFF},
											  {0xFF,0xFF,0xFF,0xFF}};
	unsigned char Key_temp,i,j;

	TL1 = T_1ms;//��װ��ʼֵ
	TH1 = T_1ms>>8;
	//��������
//	Key_temp = P3 &0x0F;//
//	switch(Key_temp)
//	{
//		case 0x0E:
//		{	
//			Key_caiyang[0] = (Key_caiyang[0]<<1);
//			Key_caiyang[1] = (Key_caiyang[1]<<1)+1;
//			Key_caiyang[2] = (Key_caiyang[2]<<1)+1;
//			Key_caiyang[3] = (Key_caiyang[3]<<1)+1;
//			break;
//		}
//		case 0x0D:
//		{
//			Key_caiyang[0] = (Key_caiyang[0]<<1)+1;
//			Key_caiyang[1] = (Key_caiyang[1]<<1);
//			Key_caiyang[2] = (Key_caiyang[2]<<1)+1;
//			Key_caiyang[3] = (Key_caiyang[3]<<1)+1;
//			break;
//		}
//		case 0x0B:
//		{
//			Key_caiyang[0] = (Key_caiyang[0]<<1)+1;
//			Key_caiyang[1] = (Key_caiyang[1]<<1)+1;
//			Key_caiyang[2] = (Key_caiyang[2]<<1);
//			Key_caiyang[3] = (Key_caiyang[3]<<1)+1;
//			break;
//		}
//		case 0x07:
//		{
//			Key_caiyang[0] = (Key_caiyang[0]<<1)+1;
//			Key_caiyang[1] = (Key_caiyang[1]<<1)+1;
//			Key_caiyang[2] = (Key_caiyang[2]<<1)+1;
//			Key_caiyang[3] = (Key_caiyang[3]<<1);
//			break;
//		 }
//		default:
//		{
//			Key_caiyang[0] = (Key_caiyang[0]<<1)+1;
//			Key_caiyang[1] = (Key_caiyang[1]<<1)+1;
//			Key_caiyang[2] = (Key_caiyang[2]<<1)+1;
//			Key_caiyang[3] = (Key_caiyang[3]<<1)+1;
//		}
//	}
//			
//	//Key = (Key<<1) | Key17;
//	for(i=0;i<4;i++)
//	{
//		if(0x03FF == Key_caiyang[i]&0x03FF)
//		{
//			KeyNow[i] = 1;	
//		}
//		else if(0 == Key_caiyang[i]&0x03FF)
//		{
//			KeyNow[i] = 0;
//		}
//		else{;}	
//	}
//	//�������
//	for(j=0;j<4;j++)
//	{
//		P3 = ~(0x01<<j);//��һ��
//		for(i=0;i<4;i++)
//		{
//			KeyJZ_caiyang[j][i] = KeyJZ_caiyang[j][i]<<1 + ((P3>>i)&0x01);	
//		}
//		P3=0xFF;
//	}
//	for(i=0;i<4;i++)
//		for(j=0;j<4;j++)
//		{
//			if(0xFF == KeyJZ_caiyang[i][j])	    KeyNowJZ[i][j] = 1;
//			else if(0 == KeyJZ_caiyang[i][j])	KeyNowJZ[i][j] = 0;
//			else{;}	
//		}
}