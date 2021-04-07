
#include "REG52.h"
#include "oled.h"
#include "Drive_DS18B20.h"
#include "Drive_DS1302.h"

#define uchar unsigned char
#define uint  unsigned int
#include <intrins.h>
sbit 	DQ = P3^7;                       //���ݿ�define interface
/***********************DS1302�˿ڶ���*******************************************/
sbit clock_rst=P0^5;  //1302��λ�ܽŶ���
sbit clock_dat=P0^4;  //1302I/O�ܽŶ���
sbit clock_clk=P0^3;  //1302ʱ�ӹܽŶ���  
/***************�Ĵ������壨���ڼ�¼1302IO������������*************************/
sbit a0=ACC^0;
sbit a1=ACC^1;
sbit a2=ACC^2;
sbit a3=ACC^3;
sbit a4=ACC^4;
sbit a5=ACC^5;
sbit a6=ACC^6;
sbit a7=ACC^7;

/**********************1302ȫ�ֱ�������******************************************/
uchar sec,min,hour,day,month,year1,year2=20;//�룬�֣�ʱ���գ��£����ڣ���
/************************�������˿ڶ���******************************************/
sbit beep=P0^0;
/***********************��������*************************************************/
sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;
uchar status=0;//��������ѡ���壨��0����1����2��ʱ3����4 ��



uint tmp;                           //�¶�ֵ variable of temperature
uint Temp_Buffer = 0;
uint t1;
uint  t2;
uint   t3;
float tt;

void main()
{
	//0.96 II2C OLED  test
	OLED_Init();//��ʼ��OLED  
	OLED_Clear();//�����Ļ
	OLED_Display_On();//����OLED
	//OLED_Display_Off();//�ر�OLED	 
	//OLED_On();
	OLED_ShowChar(0,0,'A',16);
	OLED_ShowChar(8,0,'.',8);
	while(1);

}
/*
 void delay2(unsigned char i)           //��ʱ����
{
	while(--i); 
}
 
void delay(uint t)  
{
 uint b;
 for(;t;t--)
  for(b=0;b<121;b++); 
}


 void Display_Temp()
{
	
	Temp_Buffer = Get_Tmp() ;  					//��ȡDS18B20��ֵ
	t1=(Temp_Buffer%1000/100);	   //��ʾ�¶�ʮλֵ
	t2=(Temp_Buffer%100/10);	   //��ʾ�¶ȸ�λֵ
						   
	t3=(Temp_Buffer%10);		   //��ʾ�¶�ʮ��λֵ
						   
		
}
 

void get_time()
{
 sec=read_dat_clock(0x81);    //��ȡ��
 sec=(sec>>4)*10+(sec&0x0f);  //�������ת��
 delay(1);
 min=read_dat_clock(0x83);    //��ȡ����
 min=(min>>4)*10+(min&0x0f);  //�ֶ�����ת��
 delay(1);
 hour=read_dat_clock(0x85);   //��ȡСʱ
 hour=(hour>>4)*10+(hour&0x0f);//Сʱ������ת��
 delay(1);
 day=read_dat_clock(0x87);     //��ȡ����
 day=(day>>4)*10+(day&0x0f);   //���ڶ�����ת��
 delay(1);
 month=read_dat_clock(0x89);   //��ȡ�·�
 month=(month>>4)*10+(month&0x0f);//�¶�����ת��
 delay(1);
 //week=read_dat_clock(0x8b);    //��ȡ����
 //week=(week>>4)*10+(week&0x0f);//���ڶ�����ת��
 delay(1);
 year1=read_dat_clock(0x8d);     //��ȡ���
 year1=(year1>>4)*10+(year1&0x0f); //��ݶ�����ת��
}          
 
void key_1()     //ѡ���������
{
 key1=1;
 if(key1==0)
  delay(10);																												
 {
  if(key1==0)
  {
   if(++status>5)status=0; //1������ı仯��2�����µı仯,3�����յı仯
  }       //4����ʱ�ı仯��5���Ʒֵı仯
  while(key1==0);
 }
}
void key_2()       //�Ӻ��� 
{
 key2=1;
 if(key2==0)
 {
  delay(10);
  if(key2==0)
  {
   switch(status)
   {
    case 1:if(++year1>99)year1=0;break;
    case 2:if(++month>12)month=1;break;
    case 3:if(++day>31)day=1;break;
    case 4:if(++hour>=24)hour=0;break;
    case 5:if(++min>=60)min=0;break;
   }
  }
while(key2==0);
 }
}
void key_3()//������ 
{
  key3=1;
 if(key3==0)
 {
  delay(10);
  if(key3==0)
  {
   switch(status)
   {
    case 1:if((year1--)<=0)year1=99;break;
    case 2:if((month--)<=1)month=12;break;
    case 3:if((day--)<=1)day=31;break;
    case 4:if((hour--)<=0)hour=23;break;
    case 5:if((min--)<=0)min=59;break;
   }
  }
  while(key3==0);
 }
}

void key_time()    //��������ʱ��Ĵ���
{
 if(status>0)
 {
 write_dat_clock(0x8e,0x00);  //����д����
 write_dat_clock(0x8c,(year1/10)*16+year1%10);  //��
 //write_dat_clock(0x8a,(week/10)*16+week%10);  //����
 write_dat_clock(0x88,(month/10)*16+month%10);  //��
 write_dat_clock(0x86,(day/10)*16+day%10);  //��
 write_dat_clock(0x84,(hour/10)*16+hour%10);  //Сʱ
 write_dat_clock(0x82,(min/10)*16+min%10);  //��
 write_dat_clock(0x8e,0x80);  //��ֹд����
 }
} 
 */
//void  main()
// {	   
//	    OLED_Init();			//��ʼ��OLED  
//		OLED_Clear(); 
//		Init_Ds18b20(); 
//		Get_Tmp();
//		 delay(10);
//		 set_time();
		 
//	while(1) 
//	{		
		
		
	//	Display_Temp();
		//OLED_Clear();
//		OLED_ShowCHinese(0,0,0);//��
//		OLED_ShowCHinese(18,0,1);//��
//		OLED_ShowCHinese(36,0,2);//��
//		OLED_ShowCHinese(54,0,3);//��
//		OLED_ShowCHinese(72,0,4);//��
//		OLED_ShowCHinese(90,0,5);//��
//		OLED_ShowCHinese(108,0,6);//��
		

		
//		OLED_ShowCHinese(0,2,7);//ʵ
//	    OLED_ShowCHinese(18,2,8);//��
//		OLED_ShowCHinese(36,2,9);//��
//		OLED_ShowCHinese(54,2,10);//��
//		 OLED_ShowCHinese(36,4,11);//��
//		 OLED_ShowCHinese(74,4,12);//��
//		 OLED_ShowCHinese(110,4,13);//��
////		  get_time();
//		 OLED_ShowCHinese(28,6,14);//ʱ
//		 OLED_ShowCHinese(66,6,15);//��
//		 OLED_ShowCHinese(102,6,16);//��
//		 
//		 OLED_ShowString(120,2,"C",16);  
//		 OLED_ShowNum(84,2,t1,1,16);//�¶�ʮλ	
//		 OLED_ShowNum(92,2,t2,1,16);//��ʾ��λ	
//		 OLED_ShowString(100,2,".",16);  
//		 OLED_ShowNum(108,2,t3,1,16);//С�����һλ
//	     OLED_ShowNum(0,4,year2,2,16);	
//		 OLED_ShowNum(18,4,year1,2,16);	
//		 OLED_ShowNum(54,4,month,2,16);	
//		 OLED_ShowNum(91,4,day,2,16);	
//		 OLED_ShowNum(10,6,hour,2,16);	
//		 OLED_ShowNum(46,6,min,2,16);	
//		 OLED_ShowNum(84,6,sec,2,16);
		
//		    key_1();
//        key_2();
 //       key_3();
//        key_time();
//	}	  
//	
//}

