#ifndef __AT24C01_H__
#define __AT24C02_H__

extern void WrByte_AT24C01(unsigned char addr,unsigned char dat);//д���ֽ�
extern unsigned char RdByte_AT24C01(unsigned char addr); //�����ֽ�
extern void WrStr_AT24C01(unsigned char *str,unsigned char addr,unsigned char len);//д���ֽ�
extern void RdStr_AT24C01(unsigned char *str,unsigned char addr,unsigned char len);//�����ֽ�

#endif

