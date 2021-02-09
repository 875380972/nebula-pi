#include<reg52.h>
#include"Drive_I2C.h"

//��AT24C01��ַaddrд�뵥�ֽ�����dat
void WrByte_AT24C01(unsigned char addr,unsigned char dat)
{
	Start_I2C();
	Wr_I2C(0x50<<1);//֪ͨ��ַ50��������������д����

	Wr_I2C(0);  	//д��Ҫ�����ĵ�ַaddr
	Wr_I2C(addr);  	//д��Ҫ�����ĵ�ַaddr
	Wr_I2C(dat);		//��addrд������dat
	Stop_I2C();
}
//��ȡAT24C01�洢��ַaddr��������
unsigned char RdByte_AT24C01(unsigned char addr)
{
	unsigned char dat;	

	Start_I2C();
	Wr_I2C(0x50<<1);//֪ͨ��ַ50��������������д����

	Wr_I2C(0); //д��Ҫ�����ĵ�ַaddr  
	Wr_I2C(addr); //д��Ҫ�����ĵ�ַaddr   
	Start_I2C();
	Wr_I2C((0x50<<1)|0x01);//֪ͨ��ַ50��������������������
	dat = RdNAK_I2C();//�ӵ�ַaddr�������ݣ��������ݺ�Ӧ��E2Prom
	Stop_I2C();

	return dat;
}
//���ֽ�д
void WrStr_AT24C01(unsigned char *str,unsigned char addr,unsigned char len)
{
	while(len > 0)//�����һ���Ƿ������������д����
	{	
		while(1)
		{//ѭ���������Ӧ���ź�
			Start_I2C();
			if(0 == Wr_I2C(0x50<<1)) break;//�յ�Ӧ������ѭ��
			Stop_I2C();//û�յ�Ӧ�𣬷���ֹͣ�źţ�����ѭ�����
		}
		Wr_I2C(addr); //д��Ҫ�����ĳ�ʼ��ַaddr 
		
		while(len > 0)
		{
			Wr_I2C(*str++);//д��һ���ֽڣ������ַ���ָ��ָ����һ���ַ�
			len--;//�ַ�����1
			addr++;//�洢��ַ��1	
			if(0 == (addr & 0x07))//����Ƿ񵽴�����һҳ����ʼ��ַ�� 
				break;			//����һ���ֽ��Ѿ�д��ҳ�����߽���
				           		//����ֹͣ����д��ÿҳ����ʼ��ַ��3λΪ0
								//����ж�addr��3Ϊ�Ƿ�Ϊ0����	   
		}
		Stop_I2C();	
	}			
}
//���ֽڶ�
void RdStr_AT24C01(unsigned char *str,unsigned char addr,unsigned char len)
{
	while(1)
	{//ѭ���������Ӧ���ź�
		Start_I2C();
		if(0 == Wr_I2C(0x50<<1)) break;//�յ�Ӧ������ѭ��
		Stop_I2C();//û�յ�Ӧ�𣬷���ֹͣ�źţ�����ѭ�����
	}
	Wr_I2C(addr); //д��Ҫ�����ĳ�ʼ��ַaddr 
    Start_I2C();//�ٴη�����ʼ�ź�
	Wr_I2C((0x50<<1)|0x01);//֪ͨ��ַ50��������������������
	while(len > 1)
	{
		*str++ = RdACK_I2C();//���ֽڲ�Ӧ��
		len--;
	}
	*str = RdNAK_I2C();//���һ���ֽڣ����ֽڲ���Ӧ��
	Stop_I2C();		
}
//ѰַAT24C01
bit Addressing_AT24C01(unsigned char addr)
{
	bit ack;

	Start_I2C();
	ack =  Wr_I2C(addr<<1);
	Stop_I2C();

	return ack;
}