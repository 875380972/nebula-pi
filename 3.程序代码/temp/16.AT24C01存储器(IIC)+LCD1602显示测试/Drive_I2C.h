#ifndef __I2C_H__
#define __I2C_H__

extern void Start_I2C(void); //��ʼ�ź�
extern void Stop_I2C(void);	 //ֹͣ�ź�
extern unsigned char RdACK_I2C(void); //���ֽڲ�����Ӧ���ź�
extern unsigned char RdNAK_I2C(void); //���ֽڲ����ͷ�Ӧ���ź�
extern bit Wr_I2C(unsigned char dat); //���ֽ��ź�

#endif

