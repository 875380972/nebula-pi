#include<reg52.h>

sbit led0 = P1^0;//LEDС�ƹܽŶ���
sbit FM = P2^4;//�������ܽ�λ����

sbit Key17 = P3^0;//���������ܽŶ���

void delayms(unsigned int z)//��ʱ����
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=210;y>0;y--);
}

void main()
{
	while(1)
	{
		P3 = ;
		key = P3;
		
		
		
		
		if(Key17==0)//��������
		{
			delayms(10);
			if(Key17==0)//��������
			{
				led0 = ~led0;//��ֵȡ��
			}	 
		}
	}
}

