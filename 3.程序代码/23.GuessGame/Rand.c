#include<reg52.h>

void InitRandTimer() //��ʼ������������Ķ�ʱ��
{
	TMOD |= 0x10;//����T1Ϊģʽ1
	
	TR1  = 1;		 //������ʱ��

	ET1  = 0;		 //�ر�����ʱ���ж�
}

unsigned char Rand() //����0-9���������
{
	return TL1 % 10;
}