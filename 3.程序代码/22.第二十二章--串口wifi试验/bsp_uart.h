#ifndef __RYUART_H
#define	__RYUART_H



void Uart_init(void);//���ڳ�ʼ����������
void Usart_SendString(char *s);//�ַ������ͺ�����

extern char UartRxBusy;
extern char UartRxFlag;
extern char RxLen;
extern char RxBuff[65];//oled�����ʾ64���ַ�
extern char UartRxDelay;

#endif /* __RYUART_H */