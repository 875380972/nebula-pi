#ifndef __AT24Cxx_H__
#define __AT24Cxx_H__

extern void WrByte_AT24Cxx(unsigned int addr,unsigned char dat);//д���ֽ�
extern unsigned char RdByte_AT24Cxx(unsigned int addr); //�����ֽ�
extern void WrStr_AT24Cxx(unsigned char *str,unsigned int addr,unsigned char len);//д���ֽ�
extern void RdStr_AT24Cxx(unsigned char *str,unsigned int addr,unsigned char len);//�����ֽ�

#endif

