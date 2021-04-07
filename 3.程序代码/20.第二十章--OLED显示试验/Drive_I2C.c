#include<reg52.h>
#include<intrins.h>


sbit SCL_I2C = P2^1;//���߹ܽŶ���
sbit SDA_I2C = P3^6;

void Delay_I2C(void) 
{//��ʱ���������ô�������
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	
}
//������ʼ�ź�
void Start_I2C(void)
{
	//SCL�ߵ�ƽ�ڼ䣬����SDA
	SCL_I2C = 0;
	SDA_I2C = 1;//��SCL�͵�ƽ�ڼ��Ƚ�SDA���ߣ�Ϊ��ʼ�ź���׼��
	Delay_I2C();
	SCL_I2C = 1;
	Delay_I2C();		
	SDA_I2C = 0;//����SDA��������ʼ�ź�
	Delay_I2C();	
	SCL_I2C = 0;  
}
//����ֹͣ�ź�
void Stop_I2C(void)
{
	//SCL�ߵ�ƽ�ڼ䣬����SDA
	SCL_I2C = 0;
	SDA_I2C = 0;//��SCL�͵�ƽ�ڼ��Ƚ�SDA���ͣ�Ϊֹͣ�ź���׼��
	Delay_I2C();
	SCL_I2C = 1;
	Delay_I2C();		
	SDA_I2C = 1;//����SDA������ֹͣ�ź�
	Delay_I2C();	
	SCL_I2C = 0;	
}
//I2Cд���ֽ�dat,����Ӧ���ź�
bit Wr_I2C(unsigned char dat)
{
	bit ack; //�洢Ӧ��λ
	unsigned char mask;	//̽���ֽ���ĳһλֵ���������

	for(mask=0x80;mask!=0;mask>>=1)//�Ӹ�λ���ε���λ
	{
		if((mask & dat)==0) SDA_I2C=0;
		else                SDA_I2C=1;

		Delay_I2C();
		SCL_I2C = 1;
		Delay_I2C();		
		SCL_I2C = 0;  //���һλ�Ĵ���
	}

	SDA_I2C=1;	//�����ͷ�����
	Delay_I2C();
	SCL_I2C = 1;
	ack = SDA_I2C;//��ȡӦ��λ
	Delay_I2C();
	SCL_I2C = 0;

	return ack; //����0д��ɹ�������1д��ʧ��
}

//I2C������,�����ͷ�Ӧ���ź�
unsigned char RdNAK_I2C(void)
{
	unsigned char mask;	//̽���ֽ���ĳһλֵ���������
	unsigned char dat;

	 SDA_I2C=1;//ȷ�������ͷ�SDA
	for(mask=0x80;mask!=0;mask>>=1)//�Ӹ�λ���ε���λ
	{
		Delay_I2C();	
		SCL_I2C = 1;
		if(SDA_I2C==0) dat &= ~mask;//Ϊ0ʱ��dat��Ӧλ����
		else           dat |=  mask;//������1
		 Delay_I2C();
		 SCL_I2C = 0;
	 }
	SDA_I2C=1;	  //8λ���ݴ����������SDA���ͷ�Ӧ���ź�
	Delay_I2C();
	SCL_I2C = 1;
	Delay_I2C();
	SCL_I2C = 0;

	return dat; 
}

//I2C������,������Ӧ���ź�
unsigned char RdACK_I2C(void)
{
	unsigned char mask;	//̽���ֽ���ĳһλֵ���������
	unsigned char dat;

	 SDA_I2C=1;//ȷ�������ͷ�SDA
	for(mask=0x80;mask!=0;mask>>=1)//�Ӹ�λ���ε���λ
	{
		Delay_I2C();	
		SCL_I2C = 1;
		if(SDA_I2C==0) dat &= ~mask;//Ϊ0ʱ��dat��Ӧλ����
		else           dat |=  mask;//������1
		 Delay_I2C();
		 SCL_I2C = 0;
	 }
	SDA_I2C=0;	 //8λ���ݴ����������SDA����Ӧ���ź�
	Delay_I2C();
	SCL_I2C = 1;
	Delay_I2C();
	SCL_I2C = 0;

	return dat; 
}