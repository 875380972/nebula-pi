/*******************************************************************
*            �ۺ�����                                          
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
         
* ����  �ܡ�                                                            	
*******************************************************************/
#include<reg52.h>
#include"Drive_1602.h"
#include"Drive_DS1302.h"
#include"Drive_DS18B20.h"
#include"Drive_AT24C01.h" 
#include"HongWai.h"
#include "zifu_show.h"
#include"Drive_NRF24L01.h"

#define uchar unsigned char
#define  uint unsigned int

#define FOSC 11059200 //��Ƭ������Ƶ��
#define T_1ms (65536 - FOSC/12/1000)  //��ʱ����ʼֵ����

sbit FM = P0^0;//������
sbit JDQ = P4^3;//�̵���
sbit DU = P0^6;//����ܶ�ѡ��λѡ���Ŷ���
sbit WE = P0^7;
//����ܶ���
uint count = 0;
uint flag  = 0;

uint Sec   = 0;

uchar  Buf_LED[4] ={0};
uchar 	flag_led=0;

//������(0~9,A,b,C,d,E,F,ȫ��)
uchar code table_D[]={0x3F,0x06,0x5B,0x4F,
					0x66,0x6D,0x7D,0x07,
					0x7F,0x6F,0xEE,0x3e,
					0x9c,0x7a,0x9e,0x8e,
					0x00};
//λѡ����
uchar code table_W[]={0x00,0x01,0x02,0x04,0x8};


uchar T_flag  = 0;
void delayms(unsigned int ms);//������ʱ
//AD
uchar str1[10]=0;
uchar val  = 0;
uchar T,Dir = 0;//AD������
void ValueToString(unsigned char *str,unsigned char val);
//ʱ��
uchar str[23]=0;  //�ַ���ʱ�洢����
unsigned char code SetTime[7]={//2020��,��������05��06��,23ʱ58��56�룬ʱ���ʼֵ
	 						//0x56,0x58,0x23,0x31,0x12,0x07,0x17};
							0x56,0x58,0x23,0x06,0x05,0x03,0x20};
uchar CurrentTime[7]={0};//�洢ʱ�����
//�¶�
uint Temp;
uchar str_T[5]=0;
//24C01
uchar str_E[4]=0;
uchar dat=0;
//����
#define BAUD 9600	  //����������Ϊ9600
uchar busy = 0;//������һ֡���ݱ�־λ
void Uart_init(void);//���ڳ�ʼ����������
void Send_String(char *s);//�ַ������ͺ�����
uchar code DisPlayUrat[]={"  Time:2020-05-06 23:58:56 3"};
						    //  AD:3.8V
						  // Temp:18.5
						 // E2Prom:133"};

uchar code DisPlayRYlogo[]={"\\-*-|-*-/    - -System for 51 MCU- - \r\n- RYMCU -    - -  www.rymcu.com  - - \r\n/-*-|-*-\\    Copyright by rymcu team \r\n\r\n"};

//�������
uchar code MotorCode[8]={0xE0,0xC0,0xD0,0x90,0xB0,0x30,0x70,0x60};//�������
sbit M_A = P2^4;
sbit M_B = P2^5;
sbit M_C = P2^6;
sbit M_D = P2^7;
bit Dir_M= 0;
bit M_Play = 0;
//����
uchar *Key_Str=0;
uchar Key;
//1602��ʼ����־
bit init_1602_done_flag =0;
bit NRFRevStart=0;

void Init_ShuMa(void);//�ر����������
void Init_FM(void);//�������ε�����
void Init_T1(void);//��ʱ��T1��ʼ�����������ж�
void Disp_time(uchar *str,uchar *CurrentTime);//��ʾ��ǰʱ��
void Disp_PowerUp_Times(uchar dat);//��ʾ�ϵ����

void main()
{

	 unchar RxDate[6]={0,1,2,3,4,5};//���߽���
	 unchar i;
	unint   RxDate10b[3]={0,0,0};
	unchar RxStr[12];
   NRF24L01Int();
	
	Init_ShuMa();//�ر����������
	Uart_init();  // ���ڳ�ʼ��,T2�������ʷ�����
	InitIR();//�����ʼ��
  	
	Init_T1();//��ʱ��T1��ʼ�����������ж� 	
	
 	Init_FM();//�������ε�����
	Init_1302(SetTime);//1302��ʼ��
	
	dat = RdByte_AT24C01(0x08);
	WrByte_AT24C01(0x08,dat+1);


	 while(1)
	 {
	 	if(Key==69)
		{
			EA=0;
			Key=0;
			init_1602_done_flag =1;
			Init_ShuMa();//1602��ʼ�����ر������
			Init_1602();//1602��ʼ��
			init_Gram(2,80);//��̬��ʾ�����׵��ӻ�ӭ������
			Disp_PowerUp_Times(dat);//��ʾ�ϵ����
			EA=1;
			Send_String(DisPlayRYlogo);
			 			
		}	
 
		
		if(T_flag&&init_1602_done_flag&&NRFRevStart==0)
		//if(T_flag&&init_1602_done_flag)
		{
			T_flag = 0;
			Disp_time(str,CurrentTime);
				if(CurrentTime[0]==0 &&CurrentTime[1]==0&&CurrentTime[2]==0)
				{
						Init_FM();//�������ε�����
				}
			
		   //�¶�
		   EA=0;
		   Temp =	GetT_18B20(); //�ɼ��¶�
		   EA=1;
		   str_T[0] = (Temp>>4)/10 + '0';//����4λ����¶���������
		   str_T[1] = (Temp>>4)%10 + '0';
		   str_T[2] = 0xDF;
		   str_T[3] = 0x43;
		   str_T[4] = '\0';

	//Disp_1602_str(2,10," T:");//��2�е�3�п�ʼ��ʾ�¶�ֵ
	Disp_1602_str(2,13,str_T);//��2�е�3�п�ʼ��ʾ�¶�ֵ

		   Send_String("�¶�: ");	//�����ַ��� 
		   str_T[2]= '\0';
		   Send_String(str_T);	//�����ַ���
		   Send_String("��");
		   //ʱ��
		   Send_String("   ʱ��: ");	//�����ַ���
		   Send_String(str);	//�����ַ���
		   Send_String(" ");	//�����ַ���
		   Send_String(str+11);	//�����ַ���
		   //AD
		   //Send_String("   AD: ");
		   //Send_String(str1);

		   //EEPROM
		   Send_String("    �ػ�(s): ");
		   Send_String(str_E);
			 Send_String("    ����ң�أ�");
			 Send_String(Key_Str);
		   Send_String("\r\n\r\n");				
		}
    if(NRFRevStart)
		{
			
			NRFSetRXMode();//����Ϊ����ģʽ
		 NRFRevDate(RxDate);//��ʼ�����¶�����
		 //Disp_1602_str(2,5,RxDate);//��ʾ�¶�����		
	
			for(i=0;i<3;i++)
			{
				RxDate10b[i]=0;
				RxDate10b[i]=RxDate[2*i];
				RxDate10b[i]=RxDate10b[i]*256 + RxDate[2*i+1];
				
				RxDate10b[i]=RxDate10b[i]*49;
				
				RxStr[i*4]=RxDate10b[i]/10000 + '0';
				RxStr[i*4+2]=RxDate10b[i]%10000/1000 + '0';
				RxStr[i*4+1]='.';
				RxStr[i*4+3]=' '; 
			}
			RxStr[11]='\0';
			//Send_String(RxStr);
			//Send_String("\r\n\r\n");
			Disp_1602_str(2,3,RxStr);//��ʾ�¶�����
			
			
		}
		//����
		if(Flag_IR)
		{
			Flag_IR = 0;
			Key = (unsigned char)(Data_IR>>16);//������
		   	switch(Key)
			{
				case 69:Key_Str = "CH-";break;
				case 70:Key_Str = "CH";break;
				case 71:Key_Str = "CH+";NRFRevStart=1;Init_1602();Disp_1602_str(1,2,"STC89 NRF Rx");break;
				case 68:Key_Str = "PREV";Dir_M=0;M_Play=1;break;
				case 64:Key_Str = "NEXT";Dir_M=1;M_Play=1;break;
				case 67:Key_Str = "PLAY";M_Play=~M_Play;break;
				case  7:Key_Str = "-";break;
				case 21:Key_Str = "+";break;
				case  9:Key_Str = "EQ";JDQ=~JDQ;break;
				case 22:Key_Str = "0";break;
				case 25:Key_Str = "100+";break;
				case 13:Key_Str = "200+";break;
				case 12:Key_Str = "1";break;
				case 24:Key_Str = "2";break;
				case 94:Key_Str = "3";break;
				case  8:Key_Str = "4";break;
				case 28:Key_Str = "5";break;
				case 90:Key_Str = "6";break;
				case 66:Key_Str = "7";break;
				case 82:Key_Str = "8";break;
				case 74:Key_Str = "9";break;
				default:Key_Str = "error!";
			}
			//Disp_1602_str(2,1,"IR:      ");	
			//Disp_1602_str(2,4,Key_Str);
			}	
	 }
}
//�ر����������
void Init_ShuMa(void)
{
	P2 = 0xFF;//�ر����������
	WE = 1;
	WE = 0; 
	//DU_L = 1;//����ˮ�Ƶ�573оƬ
}
//�������ε�����
void Init_FM(void)
{
	FM = 0;
	delayms(150);
	FM = 1;
	delayms(150);
	FM = 0;
	delayms(150);
	FM = 1;
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

//��ʱ��T1��ʼ�����������ж�
void Init_T1(void)
{
	TMOD |= 0x10;	 //��ʱ��1����ģʽ����
	TL1  = T_1ms;	//װ�س�ʼֵ
	TH1  = T_1ms>>8;
	TR1  = 1;		 //������ʱ��
	ET1  = 1;		 //����ʱ���ж�
	EA   = 1;		 //�����ж�
} 

//��ʱ��1�ж��ӳ���,��ʱ1ms
void timer1() interrupt 3
{
	static uint T_count = 0;
	static uchar index = 0;
	uchar tmp=0;
	
	static uchar flag_led=0;//��ˮ����λ��־

	TL1 = T_1ms;//��װ��ʼֵ
	TH1 = T_1ms>>8;	
	
	T_count++;

  //�����

	if(T_count%2)//ÿһ�������һ���жϣ��ﵽ2����Ϊ2ms����һ������ܡ�
	{
		if(init_1602_done_flag==0)
		{
			P2 =(~table_W[0])|0xF0;//�ر���������ܣ���������
			WE = 1;
			WE = 0;

			P2 = table_D[Buf_LED[flag]];//��ʾ��
			DU = 1;
			DU = 0;
		
			P2 = (~table_W[flag+1])|0xF0;//�����1~4ѭ������
			WE = 1;
			WE = 0;

			flag++;
			if(flag>=4)
				flag =0;
		}
	}
	
	//��ˮ��
	if(T_count>=1000)//1s,��λT_flag
	{
		//1s��ˮ��
		T_count = 0;
		T_flag = 1;	
		//��ˮ��
		//��ˮ��
		P1 = ~(0x01<<flag_led);//P1��ֵ����1����flagλ��ȡ����������flagλLEDС����

		if(flag_led>=8)	  //flag����7ʱ�����㣬���㿪ʼ
		{
			flag_led=0;
		}
		else
		{
			flag_led++;	 //flag�ۼ�
		}
		//1s�����������ʾ����
		Sec++;
		
		Buf_LED[3]= Sec%10;
		Buf_LED[2]= Sec/10%10;
		Buf_LED[1]= Sec/100%10;
		Buf_LED[0]= Sec/1000%10;
		
		if(Sec%5==0&&init_1602_done_flag==0) JDQ=~JDQ;
		
	}
 
//���
		if(M_Play)
		{
		P2=P2|0x0F;
		WE = 1;
		if(Dir_M)tmp = MotorCode[7-index];
		else     tmp = MotorCode[index];

		M_A = tmp & 0x80;
		M_B = tmp & 0x40;
		M_C = tmp & 0x20;
		M_D = tmp & 0x10;
		WE=0;
		index++;
		if(index>=8)
			index=0;
	   }
	   
}
//�����жϺ���
void Uart_r(void) interrupt 4
{
	if(RI)
	{
		RI = 0;		   //��������ж�
		
		if(SBUF==0x55)IAP_CONTR = 0x60;//�Զ�����
		
		SBUF = SBUF;   //��ȡ���յ������ݼ�1�����ͳ�ȥ		
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
//��ʾ��ǰʱ��
void Disp_time(uchar *str,uchar *CurrentTime)
{
//ʱ��
	EA=0;	
	GetTime(CurrentTime);//��ȡʱ��
	EA=1;
			str[0] = '2';	 
			str[1] = '0'; 	 
			str[2] = (CurrentTime[6]>>4)+'0';	 //��
			str[3] = (CurrentTime[6]& 0x0F)+'0'; 
			str[4] = '-';
			str[5] = (CurrentTime[4]>>4)+'0';	 //��
			str[6] = (CurrentTime[4]& 0x0F)+'0';
			str[7] = '-';
			str[8] = (CurrentTime[3]>>4)+'0';	 //��
			str[9] = (CurrentTime[3]& 0x0F)+'0'; 
		   str[10] = '\0';
		   str[11] = (CurrentTime[2]>>4)+'0';	 //ʱ
		   str[12] = (CurrentTime[2]& 0x0F)+'0';
		   str[13] = ':';
		   str[14] = (CurrentTime[1]>>4)+'0';	 //��
		   str[15] = (CurrentTime[1]& 0x0F)+'0'; 
		   str[16] = ':';	   
		   str[17] = (CurrentTime[0]>>4)+'0';	 //��
		   str[18] = (CurrentTime[0]& 0x0F)+'0';
		   str[19] = '\0';
		   str[20] = (CurrentTime[5]>>4)+'0';	 //����
		   str[21] = (CurrentTime[5]& 0x0F)+'0';
		   str[22] = '\0';
		    
		  Disp_1602_str(1,1,str);	//����õ�ʱ��ֱ���ʾ��1602�ĵ�һ����
			Disp_1602_str(1,12,str+21);
			Disp_1602_str(2,2,str+11);				
}

//��ʾ�ϵ����
void Disp_PowerUp_Times(uchar dat)
	{
		//��ȡAT24C01�洢����ַ0x08��������
		//dat = RdByte_AT24C01(0x08);
		str_E[0]=dat/100+'0';
		str_E[1]=dat%100/10+'0';
		str_E[2]=dat%10+'0';
		str_E[3]='\0';
		//��������ʾ��1602�ĵ�2�е�6�д�
		//Disp_1602_str(2,1,"NO.:");
		Disp_1602_str(1,14,str_E);
		//Disp_1602_str(2,8,"h");
		//WrByte_AT24C01(0x08,dat+1);		
	}//24C01
