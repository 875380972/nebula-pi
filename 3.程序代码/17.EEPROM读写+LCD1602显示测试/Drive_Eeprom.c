#include<reg52.h>
#define uint unsigned int
#define uchar  unsigned char
/****************���⹦�ܼĴ�������****************/ 
sfr  ISP_DATA = 0xE2;
sfr ISP_ADDRH = 0xE3;
sfr ISP_ADDRL = 0xE4; 	
sfr   ISP_CMD = 0xE5;  
sfr  ISP_TRIG = 0xE6; 
sfr ISP_CONTR = 0xE7;
/******************���������ֽ�******************/  
#define  read_cmd    0x01   //������      
#define wirte_cmd    0x02   //д����      
#define erase_cmd    0x03 	//��������
/****��������ȴ�ʱ���Լ�����IAP����*******/ 
#define enable_waitTime 0x82  //ϵͳ����ʱ��<20MHz ʱ

void ISP_IAP_disable(void)//�ر�ISP_IAP   
{     
	EA=1;//�ָ��ж�
	ISP_CONTR = 0x00;          
	  ISP_CMD = 0x00;           
     ISP_TRIG = 0x00; 
} 
void ISP_IAP_trigger()//����  
{     
	EA=0;           //�����2��ָ���������ִ��,�ʹ��ж�
	ISP_TRIG = 0x46;//�ʹ���������0x46          
	ISP_TRIG = 0xB9;//�ʹ���������0xB9
}
void ISP_IAP_readData(uint beginAddr, uchar* pBuf, uint dataSize) //��ȡ���� 
{  
	ISP_DATA=0;          //����,����Ҳ����  
	ISP_CMD = read_cmd;        //ָ��:��ȡ  
	ISP_CONTR = enable_waitTime;//����ISP_IAP�����͵ȴ�ʱ��   
	while(dataSize--)        //ѭ����ȡ  
	{      
		ISP_ADDRH = (uchar)(beginAddr >> 8);     //�͵�ַ���ֽ�            
		ISP_ADDRL = (uchar)(beginAddr & 0x00ff); //�͵�ַ���ֽ�   
		ISP_IAP_trigger();     //����   
		beginAddr++;      //��ַ++   
		*pBuf++ = ISP_DATA;     //�����ݱ��浽���ջ�����  
	}  
	ISP_IAP_disable();//�ر�ISP_IAP���� 
} 

void ISP_IAP_writeData(uint beginAddr,uchar* pDat,uint dataSize) //д����     
{            
	ISP_CONTR = enable_waitTime;         //����ISP_IAP�����͵ȴ�ʱ��            
	ISP_CMD = wirte_cmd;                 //���ֽڱ��������  
	while(dataSize--)  
	{      
		ISP_ADDRH = (uchar)(beginAddr >> 8);   //�͵�ַ���ֽ�             
		ISP_ADDRL = (uchar)(beginAddr & 0x00ff);//�͵�ַ���ֽ�                 
		ISP_DATA = *pDat++;//������          
		beginAddr++;    
		ISP_IAP_trigger();//����  
	}                
	ISP_IAP_disable();   //�ر�                                       
}  

void ISP_IAP_sectorErase(uint sectorAddr)//�������� 
{                 
	ISP_CONTR = enable_waitTime; //����ISP_IAP;���͵ȴ�ʱ��            
	ISP_CMD = erase_cmd;         //����������������              
	ISP_ADDRH = (uchar)(sectorAddr >> 8); //�͵�ַ���ֽ�            
	ISP_ADDRL = (uchar)(sectorAddr & 0X00FF);//�͵�ַ���ֽ�             
	ISP_IAP_trigger();//����      
	ISP_IAP_disable();//�ر�ISP_IAP����          
} 















