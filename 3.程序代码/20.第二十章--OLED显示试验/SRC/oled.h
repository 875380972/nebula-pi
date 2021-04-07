
#ifndef __OLED_H
#define __OLED_H		

#include "REG52.h"
  
#define  u8 unsigned char 
#define  u32 unsigned int 
	
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
#define OLED_MODE 0

 
#define Max_Column	128  

//-----------------OLED�˿ڶ���----------------  					   

void delay_ms(unsigned int ms);


//OLED�����ú���  
void OLED_Init(void);//��ʼ��
void OLED_Display_On(void);//����OLED
void OLED_Display_Off(void);//�ر�OLED	   							   		    
void OLED_Clear(void);//����
void OLED_On(void);//OLED������ȫ����ʾ

void OLED_Set_Pos(unsigned char x, unsigned char y);//��������


void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);//��ʾ�ַ�
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);//��ʾ����
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);//��ʾ�ַ���	 
void OLED_ShowCHinese(u8 x,u8 y,u8 no);//��ʾ�����ַ�
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);//��ʾͼƬ

void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void fill_picture(unsigned char fill_Data);


#endif  
	 



