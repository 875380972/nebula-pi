#ifndef __DS1302_H__
#define __DS1302_H__

//1302��ʼ��
extern void Init_1302(unsigned char *SetTime);
//��ȡʱ��
extern void GetTime(unsigned char *CurrentTime); 
//���ֽ�ģʽд
void WrSingle_1302(unsigned char addr,unsigned char dat);
//���ֽ�ģʽ��		  
unsigned char RdSingle_1302(unsigned char addr);
//ͻ��ģʽд
void WrBurst_1302(unsigned char *SetTime);
//ͻ��ģʽ��
void RdBurst_1302(unsigned char *CurrentTime);

#endif
													 
