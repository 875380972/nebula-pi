#include "REG52.h"
#include <intrins.h>
#include "oled.h"
#include "bmp.h"
#include "Drive_DS18B20.h"
#include "Drive_DS1302.h"
#include "AutoDownload.h"

#define uchar unsigned char
#define uint  unsigned int
	
sbit DU = P0^6;//����ܶ�ѡ����
sbit FM = P0^0;//������λ����

sbit KeySet = P1^0;//�����������壬����
sbit KeyAdd = P1^1;//+
sbit KeySub = P1^2;//-

uchar xdata TempStr[10]=0;

unsigned char code SetTime[7]={0x50,0x59,0x23,0x01,0x06,0x02,0x21};//ʱ���ʼֵ:2021��,���ڶ���06��01��,23ʱ59��50�룬

uchar xdata CurrentTime[7]={0};//�洢ʱ�����
uchar xdata TimeStr[23]=0;  //��ʱ�洢ʱ���ַ���

uchar KeySetValue=0,KeyAddValue=0,KeySubValue=0;//��������ֵ

void Time(uchar *str);//��ȡDS1302��ʱ�䲢ת��Ϊ�ַ���
void TimeToStr(uchar *str);//ʱ�����ת��Ϊ�ַ���
void Temperature(uchar *str);//�ɼ��¶Ȳ�ת�����ַ���

void SetTimeByKey(void);//ͨ����������ʱ��
void Alarm(void);//�������������
void delayms(unsigned int z);//ms��ʱ����

void main()
{
	uchar flag=0;
	uchar chargeFlag = 6;
	
	P2 = 0x00;//�ر����������
	DU = 1;
	DU = 0;//�����
	
	AutoDownload_init();//�Զ����س�ʼ������
	Init_1302(SetTime);//1302��ʼ��
	OLED_Init();//��ʼ��OLED  
	OLED_Clear();//�����Ļ
	OLED_Display_On();//����OLED
	
/*****************************************
	*
	*0.96 OLED �ַ���ʾ����
	*
*******************************************/
	OLED_ShowChar( 0,0,'A',16,0);
	OLED_ShowChar( 8,0,'B',16,0);
	OLED_ShowChar(16,0,'C',16,0);
	OLED_ShowChar(24,0,'D',16,0);
	
	OLED_ShowChar( 0,2,'A',8,0);
	OLED_ShowChar( 8,2,'B',8,0);
	OLED_ShowChar(16,2,'C',8,0);
	OLED_ShowChar(24,2,'D',8,0);
	
	OLED_ShowString(25,6,"Char Test!",16,1);

	delayms(5000);
	OLED_Clear();//�����Ļ
	
/*****************************************
	*
	*0.96 OLED ������ʾ����
	*
*******************************************/	

	OLED_ShowNum(  0,1,12,2,16,0);
	OLED_ShowNum( 48,1,34,2,16,0);
	OLED_ShowNum( 96,1,56,2,16,0);
	
	OLED_ShowString(25,6,"Num Test!",16,1);
	
	delayms(5000);
	OLED_Clear();//�����Ļ

/*****************************************
	*
	*0.96 OLED ������ʾ����
	*
*******************************************/	
	OLED_ShowCHinese(22   ,3,1,0);//��
	OLED_ShowCHinese(22+16,3,2,0);//��
	OLED_ShowCHinese(22+32,3,3,0);//��
	OLED_ShowCHinese(22+48,3,4,0);//ɢ
	OLED_ShowCHinese(22+64,3,5,0);//��
	
	OLED_ShowString(25,6,"CHN Test!",16,1);
	
	delayms(5000);
	OLED_Clear();//�����Ļ
	
/*****************************************
	*
	*0.96 OLED �ַ�����ʾ����
	*
*******************************************/	

	OLED_ShowString(0,2,"Nebula-Pi,RYMCU!",16,0);
	
	OLED_ShowString(25,6,"Str Test!",16,1);
	
	delayms(5000);
	OLED_Clear();//�����Ļ
/*****************************************
	*
	*0.96 OLED �ַ�����ʾ����
	*
*******************************************/	

	OLED_DrawBMP(0,0,Logo,0);//��ʾͼƬ
	
	OLED_ShowString(25,6,"PIC Test!",16,1);
	
	delayms(5000);

	while(1)
	{
		/*****************************************
			*
			*ѭ����ʾ��綯��
			*
		*******************************************/	
		chargeFlag++;
		if(chargeFlag > 9) chargeFlag = 6;
		OLED_ShowCHinese(111,0,chargeFlag,0);//ѭ����ʾ���

		/*****************************************
			*
			*�ɼ��¶Ȳ���LED��ʾ
			*
		*******************************************/		
		Temperature(TempStr);//DS18B20�ɼ��¶�
		OLED_ShowString(40,0,TempStr,16,0);//��ʾ�¶�
		OLED_ShowCHinese(75,0,0,0);//��ʾ��
	
		/*****************************************
			*
			*��ȡDS1302ʱ��
			*
		*******************************************/			
		if(KeySetValue==0)//ʱ��������ʾģʽ
		{
			Time(TimeStr);//��ȡDS1302��ʱ��
			flag = 0; 
		}
		else   //��������ʱ��ģʽ           
		{
			TimeToStr(TimeStr);//ʱ�����ת��Ϊ�ַ���
			flag = 1;//������ʾ
		}
	
		/*****************************************
			*
			*��ʱ����ʾ��OLED��
			*
		*******************************************/
		OLED_ShowString(35,5,TimeStr,8,flag);
		OLED_ShowString(20,6,&TimeStr[11],16,flag);	
	
		/*****************************************
			*
			*ɨ��ʱ�����ð���
			*
		*******************************************/
		SetTimeByKey();	
	
		/*****************************************
			*
			*���㱨ʱ
			*
		*******************************************/
			Alarm();//�������������
	}
}
void Alarm(void)//�������������
{
	if(CurrentTime[1]==0 && CurrentTime[0]==0)//����ε�����
	{
		FM = 0;
		delayms(500);
		FM = 1;
		delayms(50);
		FM = 0;
		delayms(500);
		FM = 1;
	}
}
void SetTimeByKey(void) //ͨ����������ʱ��
{
	static temp = 0;
	if(KeySet == 0)
	{
		delayms(1);
		if(KeySet== 0) KeySetValue++;	
		if(KeySetValue>8) KeySetValue=0;
	}
	if(KeyAdd == 0)
	{
		delayms(1);
		if(KeyAdd == 0) KeyAddValue++;	
	}
	if(KeySub == 0)
	{
		delayms(1);
		if(KeySub == 0) KeySubValue++	;
	}

	switch (KeySetValue)
	{
		case 1://������		
			temp=(CurrentTime[6]>>4)*10 +(CurrentTime[6]&0x0F);
		
			if(KeyAddValue) {temp++;KeyAddValue = 0;}
			if(KeySubValue) {temp--;KeySubValue = 0;}
			
			if(temp>99) temp = 0;
			temp = ((temp/10)<<4) + (temp%10);
			CurrentTime[6]= temp;
			
			OLED_ShowChar( 35+12,5,TimeStr[2],8,0);
			OLED_ShowChar( 35+18,5,TimeStr[3],8,0);
			
			break;
		case 2://������
			temp=(CurrentTime[4]>>4)*10 +(CurrentTime[4]&0x0F);
		
			if(KeyAddValue) {temp++;KeyAddValue = 0;}
			if(KeySubValue) {temp--;KeySubValue = 0;}
			
			if(temp>12) temp = 0;
			temp = ((temp/10)<<4) + (temp%10);
			CurrentTime[4]= temp;
			
			OLED_ShowChar( 35+30,5,TimeStr[5],8,0);
			OLED_ShowChar( 35+36,5,TimeStr[6],8,0);
			
			break;			
		case 3://������
			temp=(CurrentTime[3]>>4)*10 +(CurrentTime[3]&0x0F);
		
			if(KeyAddValue) {temp++;KeyAddValue = 0;}
			if(KeySubValue) {temp--;KeySubValue = 0;}
			
			if(temp>31) temp = 0;
			temp = ((temp/10)<<4) + (temp%10);
			CurrentTime[3]= temp;
			
			OLED_ShowChar( 35+48,5,TimeStr[8],8,0);
			OLED_ShowChar( 35+54,5,TimeStr[9],8,0);
			
			break;
		case 4://����Сʱ
			temp=(CurrentTime[2]>>4)*10 +(CurrentTime[2]&0x0F);
		
			if(KeyAddValue) {temp++;KeyAddValue = 0;}
			if(KeySubValue) {temp--;KeySubValue = 0;}
			
			if(temp>23) temp = 0;
			temp = ((temp/10)<<4) + (temp%10);
			CurrentTime[2]= temp;
			
			OLED_ShowChar( 20,6,TimeStr[11],16,0);
			OLED_ShowChar( 28,6,TimeStr[12],16,0);
			
			break;
		case 5://���÷�
			temp=(CurrentTime[1]>>4)*10 +(CurrentTime[1]&0x0F);
		
			if(KeyAddValue) {temp++;KeyAddValue = 0;}
			if(KeySubValue) {temp--;KeySubValue = 0;}
			
			if(temp>59) temp = 0;
			temp = ((temp/10)<<4) + (temp%10);
			CurrentTime[1]= temp;
			
			OLED_ShowChar( 20+24,6,TimeStr[14],16,0);
			OLED_ShowChar( 28+24,6,TimeStr[15],16,0);
			
			break;
		case 6://������
			temp=(CurrentTime[0]>>4)*10 +(CurrentTime[0]&0x0F);
		
			if(KeyAddValue) {temp++;KeyAddValue = 0;}
			if(KeySubValue) {temp--;KeySubValue = 0;}
			
			if(temp>59) temp = 0;
			temp = ((temp/10)<<4) + (temp%10);
			CurrentTime[0]= temp;
			
			OLED_ShowChar( 20+48,6,TimeStr[17],16,0);
			OLED_ShowChar( 28+48,6,TimeStr[18],16,0);	

			break;
		case 7://��������
			temp=(CurrentTime[5]>>4)*10 +(CurrentTime[5]&0x0F);
		
			if(KeyAddValue) {temp++;KeyAddValue = 0;}
			if(KeySubValue) {temp--;KeySubValue = 0;}
			
			if(temp>7) temp = 0;
			temp = ((temp/10)<<4) + (temp%10);
			CurrentTime[5]= temp;
			
			OLED_ShowChar( 20+72,6,TimeStr[20],16,0);
			OLED_ShowChar( 28+72,6,TimeStr[21],16,0);	
			
			break;
		case 8: //����DS1302
			Init_1302(CurrentTime);
			break;
			
		default:
			break;
			
	}

}

void Temperature(uchar *str)
{
	uint Temp;
	
	Temp =	GetT_18B20(); //�ɼ��¶�
	str[0] = (Temp>>4)/10 + '0';//����4λ����¶���������
	str[1] = (Temp>>4)%10 + '0';
	str[2] = '.';
	str[3] = '0'+(Temp>>3)%10;
	str[4] = '\0';	
}

void Time(uchar *str)
{
		GetTime(CurrentTime);//��ȡʱ��
		TimeToStr(str);

}
void TimeToStr(uchar *str)//ʱ�����ת��Ϊ�ַ���
{
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
		   str[19] = ' ';
		   str[20] = (CurrentTime[5]>>4)+'0';	 //����
		   str[21] = (CurrentTime[5]& 0x0F)+'0';
		   str[22] = '\0';	
}

void delayms(unsigned int z)//ms��ʱ����
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=78;y>0;y--);
}
