#include<reg52.h>

#define HIGH_IR 1	 //�ߵ�ƽ
#define  LOW_IR 0	 //�͵�ƽ

#define  Min_9ms	 8000	   //8ms
#define  Max_9ms	 10000	   //10ms
#define  Min_4_5ms	 3500	   //3.5ms
#define  Max_4_5ms	 5000	   //5ms
#define  Min_560us	 300	   //300us
#define  Max_560us	 700	   //700us
#define  Min_1680us	 1300	   //1.3ms
#define  Max_1680us	 1800	   //1.8ms
#define  Time_16ms   16000	   //16ms

sbit Led1  = P1^1;
sbit IR_in = P3^3;//����������ţ�Ҳ���ⲿ�ж�0�����
bit Flag_IR = 0;//������ձ�־���յ���ȷ֡���ݺ��ɳ�����1
unsigned long Data_IR;//4���ֽڵ����ݣ�[31:0]���ݷ���->������->�û�����->�û���
//������ճ�ʼ��
void InitIR()
{
	IR_in = 1;//�ͷ�
	TMOD &= 0xF0;//����T0����λ
	TMOD |= 0x01;//����T0Ϊģʽ1
	TR0 = 0; //ֹͣT0����
	ET0 = 0;//�ض�ʱ��0�ж�
	IT1 = 1;//����INT1Ϊ�½��ش���
	EX1 = 1;//��INT1�ж�
	EA=1; //�����ж�
}
unsigned int T_Count(bit flag)//��ƽ��ʱ��
{
	TH0 = 0; //����T0
	TL0 = 0;
	TR0 = 1;//����T0
	//�жϸߵ�ƽ�Ƿ񳬹�16ms,����������Ϊ�쳣��ֱ������ѭ��,��ֹ������ѭ��
	while(IR_in==flag){if(TH0 >= (Time_16ms>>8)) break;}
	TR0 = 0;
	return (TH0*256 + TL0);//���ؼ���ֵ����ֵ��λΪus		
}
//�ⲿ�ж�0���ж��ӳ���,�½��ش��������ж�
void Int0() interrupt 2	
{
	unsigned int i;
	unsigned int T_Low,T_High;

	T_Low = T_Count( LOW_IR);//����9ms��������͵�ƽ	
	T_High = T_Count(HIGH_IR);//����4.5ms������ߵ�ƽ
	//�ж���������ȷ��
	if(T_Low<Min_9ms || T_Low>Max_9ms || T_High<Min_4_5ms || T_High>Max_4_5ms){IE0=0; return;}
    //����4���ֽڵ����ݣ���32λ
	for(i=0;i<32;i++)
	{
		T_Low = T_Count( LOW_IR);//����560usλ�͵�ƽ		
		T_High = T_Count(HIGH_IR);//����560us��1680usλ�ߵ�ƽ
		//�ж�λ��ƽ����ȷ��
		if(T_Low<Min_560us || T_Low>Max_560us || T_High<Min_560us || T_High>Max_1680us) {IE0=0;return;}			
		Data_IR>>=1; //Ϊ0ʱ��λ��0
		if(T_High>Min_1680us) Data_IR |= 0x80000000;//Ϊ1ʱ��λ��1
	}
	Flag_IR = 1; //���յ�����ֵ����λ
	Led1 = 0;//��˸С��
	//for(i=0;i<5000;i++);
	Led1 = 1;
	IE0=0;//����жϱ�־λ��ȷ������Ӧ�ⲿ�ж�0�����в������ⲿ�ж������ٱ���Ӧ��
}

