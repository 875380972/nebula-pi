#ifndef __Eeprom_H__
#define __Eeprom_H__

extern void ISP_IAP_disable(void);//�ر�ISP_IAP  
extern void ISP_IAP_trigger();//����
extern void ISP_IAP_readData(unsigned int beginAddr, unsigned char* pBuf, unsigned int dataSize);//��ȡ����
extern void ISP_IAP_writeData(unsigned int beginAddr,unsigned char* pDat,unsigned int dataSize);//д���� 
extern void ISP_IAP_sectorErase(unsigned int sectorAddr);//��������

#endif

