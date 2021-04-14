/****************************************************
 * �����嵥��wifi����
 *
 * 
 ****************************************************
 * www.rymcu.com
 * Change Logs: 
 * Date           Author       Notes 
 * 2020-08-25     Hugh         the first version 
 ***************************************************/
#include "bsp_wifi.h"
#include "bsp_uart.h"


		
	char code           Plus3[]="+++";//�˳�͸��
	
	char code     AT_RESTORE[]="AT+RESTORE\r\n";//�ָ�����ֵ
	char code         AT_RST[]="AT+RST\r\n";//��λģ��

	char codeAT_CWMODE_DEF_1[]="AT+CWMODE_DEF=1\r\n";//����Ĭ��ΪSTAģʽ	
	char code    AT_CWMODE_2[]="AT+CWMODE=2\r\n";//����Ϊ AP ģʽ
	char code    AT_CWMODE_3[]="AT+CWMODE=3\r\n"; //����Ϊ AP+STA ģʽ	

	char code    AT_CIPMUX_1[]="AT+CIPMUX=1\r\n";//����������	
	char code       AT_CIFSR[]="AT+CIFSR\r\n";//�鿴 mac ��ַ�� IP
	
	char code   AT_CIPMODE_1[]="AT+CIPMODE=1\r\n";//͸��ģʽ
	char code     AT_CIPSEND[]="AT+CIPSEND\r\n";//����͸��	
	char code AT_CIPCLOSE_4[]="AT+CIPCLOSE=4\r\n";//close udp
	
	char code   AT_CWJAP_DEF[]="AT+CWJAP_DEF=\"TP-LINK_wj\",\"wj81004\"\r\n";//����wifi
	
	char code AT_CWJAP_DEF_0[]="AT+CWJAP_DEF=\"";	
	char code AT_CWJAP_DEF_wifi[100]="TP-LINK_wj";		
	char code AT_CWJAP_DEF_2[]="\",\"";	
	char code AT_CWJAP_DEF_pwd[100]="wj871004";		
	char code AT_CWJAP_DEF_4[]="\"\r\n";	
	
	char code       AT_CWSAP[]="AT+CWSAP=\"rymcu\",\"rymcu.com\",11,3\r\n";//���� wifi �ȵ�
	char code    AT_CIPSTART[]="AT+CIPSTART=\"TCP\",\"192.168.0.104\",5001\r\n";//���ӷ�����

	char code AT_CIPSERVER_1[]="AT+CIPSERVER=1,5000\r\n";//���������
	char code   AT_CIPSEND_0[]="AT+CIPSEND=0,5\r\n";//��������
	char code  AT_CIPSTART_4[]="AT+CIPSTART=4,\"UDP\",\"255.255.255.255\",8080,1112,0\r\n";////set udp brodcast,remote port: 8080 local port: 1112
	char code           ATE0[]="ATE0\r\n";

void delayms(unsigned int z)//ms��ʱ����
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=210;y>0;y--);
}

int WiFiInit(void)
{
	
//	 //APģʽ
//	 delayms(1500);
//	 
//	 Usart_SendString( QuitWifi);//�˳�͸��
//	 delayms(1500);
//	 Usart_SendString( ReStoreWifi);//�ָ�����ֵ
//	 delayms(1500);
//	 Usart_SendString( ResetWifi);//��λģ��
//	 delayms(1500);
//	 
//	 Usart_SendString( SetApWifi);//����Ϊ AP ģʽ
//	 delayms(1500);
//	 Usart_SendString( SetWifi);//���� wifi �ȵ�		
//	 delayms(6000);
//	 //Usart_SendString( ApServWifi);//����AP������
//	 delayms(1500);	 
//	 
////	 Usart_SendString( StartServWifi);//�鿴 mac ��ַ�� IP
////	 delayms(1500);
////	 
////	 Usart_SendString( GetMacWifi);//���������
////	 delayms(1500);	 
////	 
////	 //Usart_SendString( ModeWifi);//͸��ģʽ		
////	 delayms(1500);
////	 //Usart_SendString( StartWifi);//͸��ģʽ��������		
	
	
//	 //������ģʽ
//	 delayms(1500);
//	 
//	 Usart_SendString( QuitWifi);//�˳�͸��
//	 delayms(1500);
//	 Usart_SendString( ReStoreWifi);//�ָ�����ֵ
//	 delayms(1500);
//	 Usart_SendString( ResetWifi);//��λģ��
//	 delayms(1500);
//	 
//	 Usart_SendString( SetApWifi);//����Ϊ AP ģʽ
//	 delayms(1500);
//	 Usart_SendString( SetWifi);//���� wifi �ȵ�		
//	 delayms(6000);
//	 Usart_SendString( MutiWifi);//����������
//	 delayms(1500);	 
//	 Usart_SendString( StartServWifi);//�鿴 mac ��ַ�� IP
//	 delayms(1500);
//	 
//	 Usart_SendString( GetMacWifi);//���������
//	 delayms(1500);	 
//	 
//	 //Usart_SendString( ModeWifi);//͸��ģʽ		
//	 delayms(1500);
//	 //Usart_SendString( StartWifi);//͸��ģʽ��������	

//
  //Usart_SendString( AT_CIPCLOSE_4);//
	delayms(1500);
	//Usart_SendString( Plus3);//�˳�͸��
	delayms(500);
	Usart_SendString( AT_RESTORE);//�ָ�����ֵ
	delayms(3500);
  Usart_SendString( AT_CWMODE_3);//AT+STA
	delayms(3500);
	Usart_SendString( AT_CWJAP_DEF_0);//����wifi	
  Usart_SendString( AT_CWJAP_DEF_wifi);//����wifi�˺�	
	Usart_SendString( AT_CWJAP_DEF_2);//����wifi	
	Usart_SendString( AT_CWJAP_DEF_pwd);//����wifi����
	Usart_SendString( AT_CWJAP_DEF_4);//����wifi
	delayms(6000);
	Usart_SendString( AT_CIFSR);//git device ip
	delayms(2500);
	Usart_SendString( AT_CIPMUX_1);//������
	delayms(2500);
	Usart_SendString( AT_CIPSTART_4);//����UDP
	delayms(2500);
	Usart_SendString( ATE0);//AP		
//

//// //�ͻ���͸��ģʽ
////  Usart_SendString( AT_CIPCLOSE_4);//�˳�͸��
////	 delayms(500);
////	 Usart_SendString( Plus3);//�˳�͸��
////	 delayms(500);
////	 Usart_SendString( AT_RESTORE);//�ָ�����ֵ
////	 delayms(500);
////	 Usart_SendString( AT_RST);//��λģ��
////	 delayms(500);
////	 Usart_SendString( AT_CWMODE_DEF_1);//
////	 delayms(500);
////	 //Usart_SendString( AT_CWJAP_DEF);//����wifi	
////	 Usart_SendString( AT_CWJAP_DEF_0);//����wifi	
////   Usart_SendString( AT_CWJAP_DEF_1_wifi);//����wifi�˺�	
////	 Usart_SendString( AT_CWJAP_DEF_2);//����wifi	
////	 Usart_SendString( AT_CWJAP_DEF_3_pwd);//����wifi����
////	 Usart_SendString( AT_CWJAP_DEF_4);//����wifi		


////	 delayms(6000);
////	 Usart_SendString( AT_CIPSTART);//���ӷ�����
////	 delayms(1500);
////	 Usart_SendString( AT_CIPMODE_1);//͸��ģʽ		
////	 delayms(500);
////	 Usart_SendString( AT_CIPSEND);//͸��ģʽ��������
////	 delayms(500);

//	 //�ͻ���͸��ģʽ
//	 delayms(1500);
//	 Usart_SendString( Plus3);//�˳�͸��
//	 delayms(1500);
//	 Usart_SendString( AT_RESTORE);//�ָ�����ֵ
//	 delayms(1500);
//	 Usart_SendString( AT_RST);//��λģ��
//	 delayms(1500);
//	 Usart_SendString( AT_CWMODE_3);//
//	 delayms(1500);
//	 Usart_SendString( AT_CWJAP_DEF);//����wifi		
//	 delayms(6000);
//	 Usart_SendString( AT_CIFSR);//git device ip
//	 delayms(1500);
//	 Usart_SendString( AT_CIPMUX_1);//������	
//	 delayms(1500);
//	 Usart_SendString( AT_CIPSTART_4);//����UDP
//	 delayms(1500);
//	 //Usart_SendString( SentDataWifi);//���ӷ�����
	 
    return 0;
}

//uint8_t SetEndPoint(void)
//{
//	Usart_SendString( Plus3);//�˳�͸��
//	delayms(500);
//	Usart_SendString( AT_RESTORE);//�ָ�����ֵ
//	delayms(500);
//	Usart_SendString( AT_CWMODE_2);//AP
//	delayms(500);
//	Usart_SendString( AT_CWSAP);//set wifi
//	delayms(500);
//	Usart_SendString( AT_CIPMUX_1);//muti connect
//	delayms(500);
//	Usart_SendString( AT_CIFSR);//get ip
//	delayms(500);
//	Usart_SendString( AT_CIPSTART_4);//AP
//	delayms(500);
//	Usart_SendString( ATE0);//AP
//	delayms(500);
//	return 0;
//}
/******************END OF FILE*********************/
