#include<reg52.h>

sbit led0 = P1^0;//LEDС�ƹܽŶ���
sbit FM = P2^4;//�������ܽ�λ����

sbit Key17 = P3^0;//���������ܽŶ���
sbit Key20 = P3^3;

void main()
{
	while(1)
	{
		led0 = Key17;//����17����ʱ������led0
		FM = Key20;//  ����20����ʱ���򿪷�����
	}
}

