/*******************************************************************
*  猜数字游戏：
*  按遥控器“+”，启动游戏，系统生成一个0-9的随机数字
*	 按遥控器0-9来猜测是否和系统生成的一样大！
*
* ******************************************************************
* 【主芯片】：STC89SC52/STC12C5A60S2
* 【主频率】: 11.0592MHz 
*                                                                                                                               	
* 【版  本】： V1.0                                          	
* 【作  者】： stephenhugh                            	
* 【网  站】：https://rymcu.taobao.com/                              	
* 【邮  箱】：                                          	
*                                                                 	
* 【版  权】All Rights Reserved 
* 【声  明】此程序仅用于学习与参考，引用请注明版权和作者信息！         
*                                                                 	
*******************************************************************/
#include<reg52.h>
#include"HongWai.h"
#include"Drive_1602.h"
#include"Rand.h"
unsigned char *Key_Str=0;
unsigned char KeyValue,RandNum = 0;

void GetKeyValue();	

#define START 22

void main()
{

	
	Init_1602();//1602初始化 

	Disp_1602_str(1,4,"Guess Game");//第1行第2列开始显示"Guess Game“
	Disp_1602_str(2,1,"Press '+' start!");//第1行第2列开始显示
	
	InitIR();//红外初始化
	InitRandTimer();//初始化随机数定时器

	while(1)
	{
		if(Flag_IR)//有按键按下了
		{
			Flag_IR = 0;
			GetKeyValue();

			if(KeyValue == START)
			{
				Disp_1602_str(2,1,"                ");	//清空第二行
				Disp_1602_str(2,7,"START");	//清空第二行
				
				RandNum = Rand();//更新随机值
			}
			else if(KeyValue<=9)
			{
				if(KeyValue == RandNum)//猜对了
				{
					Disp_1602_str(2,1,"                ");	//清空第二行
					Disp_1602_num(2,1,KeyValue);	//
					Disp_1602_str(2,2,":you got it!");	
					
				}
				else if(KeyValue > RandNum)//太大了
				{
					Disp_1602_str(2,1,"                ");	//清空第二行
					Disp_1602_num(2,4,KeyValue);	//
					Disp_1602_str(2,5,":too big!");	
				}
				else //太小了
				{
					Disp_1602_str(2,1,"                ");	//清空第二行
					Disp_1602_num(2,4,KeyValue);	//
					Disp_1602_str(2,5,":too small!");	
				}
					
			}
			else //无效值
			{
				Disp_1602_str(2,1,"                ");	//清空第二行;
				Disp_1602_str(2,1,"input num:0-9");	//清空第二行
			}				
		}		
	}
}

void GetKeyValue()	
{
		unsigned char Key;
	
		Key = (unsigned char)(Data_IR>>16);//数据码
		  switch(Key)
			{
				case 69:Key_Str = "CH-"; break;
				case 70:Key_Str = "CH";break;
				case 71:Key_Str = "CH+";break;
				case 68:Key_Str = "PREV";break;
				case 64:Key_Str = "NEXT";break;
				case 67:Key_Str = "PLAY/PAUSE";break;
				case  7:Key_Str = "-";break;
				case 21 :Key_Str = "+";KeyValue = START; break;
				case  9:Key_Str = "EQ";break;
				case 22:Key_Str = "0";KeyValue = 0;break;
				case 25:Key_Str = "100+";break;
				case 13:Key_Str = "200+";break;
				case 12:Key_Str = "1";KeyValue = 1;break;
				case 24:Key_Str = "2";KeyValue = 2;break;
				case 94:Key_Str = "3";KeyValue = 3;break;
				case  8:Key_Str = "4";KeyValue = 4;break;
				case 28:Key_Str = "5";KeyValue = 5;break;
				case 90:Key_Str = "6";KeyValue = 6;break;
				case 66:Key_Str = "7";KeyValue = 7;break;
				case 82:Key_Str = "8";KeyValue = 8;break;
				case 74:Key_Str = "9";KeyValue = 9;break;
				default:Key_Str = "error!";
			}
}