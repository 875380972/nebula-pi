#ifndef __1602_H__
#define __1602_H__

//�ַ�����ʾ��������
extern void Disp_1602_str(unsigned char row,unsigned char column,char *str);
//������ʾ���ܣ��ӵ�row�У���column�п�ʼ����num
void Disp_1602_num(unsigned char row,unsigned char column,char num);
extern void Init_1602();//1602��ʼ����������

void Ready();//���м�⺯������
void WR_Cmd(unsigned char cmd);//дָ�������
void WR_Dat(unsigned char dat);//д���ݺ�������
unsigned char RD_sta();//��״̬��������

#endif

