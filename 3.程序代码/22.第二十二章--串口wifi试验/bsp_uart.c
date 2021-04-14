#include "bsp_uart.h" 
#include "REG52.h"

char UartRxBusy;
char UartRxFlag;
char RxLen=0;
char RxBuff[65];//oled�����ʾ64���ַ�
char UartRxDelay;

bit busy = 0;
sbit led0 = P1^0;

#define FOSC 11059200 //��Ƭ������Ƶ��
#define BAUD 9600	  //����������Ϊ9600

sfr ISP_CONTR = 0xe7;
sfr AUXR   = 0x8E;

void exUartInit(void)		//115200bps@11.0592MHz
{
     SCON=0x50; //���ڹ�����ʽ1��8λUART�������ʿɱ�  
     TH2=0xFF;           
     TL2=0xFD;    //������:115200 ����=11.0592MHz 
     RCAP2H=0xFF;   
     RCAP2L=0xFD; //16λ�Զ���װ��ֵ
/*****************/
     TCLK=1;   
     RCLK=1;   
     C_T2=0;   
     EXEN2=0; //�����ʷ�����������ʽ
/*****************/
    TR2=1 ; //��ʱ��2��ʼ
}
//���ڳ�ʼ������
void Uart_init(void) 
{
	exUartInit();
//		SCON = 0x50;//��������Ϊ������ʽ1
//	PCON = 0;   //�����ʲ��ӱ�

//	TMOD |= 0x20;//���ö�ʱ��1Ϊ8λ�Զ���װģʽ
//	TH1=TL1= 256- FOSC/32/6/BAUD;//��ʱ��1����ʼֵ
//	
//	ET1 = 0;//��ֹ��ʱ��1�ж�
//	TR1 = 1;//������ʱ��1

	ES = 1;//�������ж�
	
	EA = 1;           //�����ж�
}

//�ַ������ͺ�
void Usart_SendString(char *s)
{	
	while(*s)   //����ַ����Ƿ��˽�β
	{	
		while(busy);  //�ȴ���һ֡���ݷ������
		busy = 1;
		SBUF = *s++;  //���͵�ǰ�ַ��������ַ�ָ���Ƶ���һ���ַ�
	}	
}

//�����жϺ���
void Uart_r(void) interrupt 4
{
	if(RI)
	{
		RI = 0;	
		
		UartRxBusy=1;//���ڽ��մ�������
		UartRxDelay=5;//5ms�ӳ�
		
		RxBuff[RxLen]=SBUF;
		//SBUF=RxBuff[RxLen];
		
		RxLen++; 
		if(RxLen>=64) RxLen = 0;
		
		//led0 = ~led0;  //��תled0	
	}
	if(TI)
	{
		TI = 0;		   //���㷢���ж�
		//led1 = ~led1;  //��תled1
		busy = 0;      //���������ݣ�����������־λ
		
	}
}

