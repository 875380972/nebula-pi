/********************************************************
* �����ܣ�
*ʹ��switch-case����жϣ�������������֣���ʾ���ڼ���
*1-7�ֱ��Ӧ����һ-������
*����������Ч
*********************************************************/
#include <stdio.h>
void main()
{
    int a;
    printf("���������֣��س�����: ");
    scanf("%d",&a);
    switch(a) //��������a,������case��������ֶԱȣ���ͬ��ִ�к�������
    {
        case 1:printf("\n����һ\n");
        break;
        case 2:printf("\n���ڶ�\n");
        break;
        case 3:printf("\n������\n");
        break;
        case 4:printf("\n������\n");
        break;
        case 5:printf("\n������\n");
        break;
        case 6:printf("\n������\n");
        break;
        case 7:printf("\n������\n");
        break;
        default:printf("\n�������\n");
    }
    return;
}
