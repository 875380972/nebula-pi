/********************************************************
* �����ܣ�
*�Ƚ���������ֵ������ʾ��С��ֵ
* ѭ����ӡ����ֵ
*********************************************************/
#include <stdio.h>
//�����Сֵ�ú���
int Min(int num1,int num2)
{
   int result;

   if(num1<num2)
   {
       result=num1;
   }
   else
   {
       result=num2;
   }
   return result;
}
//������
void main()
{
    int a = 1,b=2;
    int c;
    //���ú���Min(),���ؽ�Сֵ
    c=Min(a,b);
    printf("\n��Сֵ��Ϊ��%d\n",c);
   return;
}
