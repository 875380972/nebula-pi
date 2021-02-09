#include<reg52.h>
#include"Drive_I2C.h"
//������תģ����������valΪ��ת������������ģ������Vout�������
void DAC(unsigned char val)
{
	Start_I2C();//����I2C����
	//ѰַPCF8591������Ϊ��д������δ��Ӧ����ֹͣ������
	if(Wr_I2C(0x48<<1)) {Stop_I2C();return;}
	Wr_I2C(0x40);//д������ӣ�ʹ��ģ�����
	Wr_I2C(val); //����DAC�ֽ�
	Stop_I2C();  //����I2C����
}
//ģ����ת��������������ͨ��chn��ֵת��Ϊ������val,������val
unsigned char ADC(unsigned char chn)
{
	unsigned char val;//�������洢����

	Start_I2C();//����I2C����
	//ѰַPCF8591������Ϊ��д������δ��Ӧ����ֹͣ������0
	if(Wr_I2C(0x48<<1)){Stop_I2C();return 0;} 
	Wr_I2C(0x40|chn);//д������ֲ�ѡ��ת��ͨ��chn������

	Start_I2C();//��������I2C����
	Wr_I2C((0x48<<1)|0x01);//ѰַPCF8591������Ϊ������
	      RdACK_I2C();//��һ�����ݲ���������һ�����ݲ���ת��������
	val = RdNAK_I2C();//�����ݲ�����

	return val;
}

