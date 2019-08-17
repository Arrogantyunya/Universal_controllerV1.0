// 
// 
// 

#include "user_A025_E025.h"

//函 数 名：Receive_A025() 
//功能描述：A025的执行函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A025(unsigned char * Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A025函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug == 1)
	{
		Serial.println("进入Receive_A025函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A025Judgement_Data ");
			Serial.print(i);
			Serial.print(" :");
			Serial.println(Judgement_Data[i], HEX);
			delay(1);
		}
		delay(200);
		Serial.print("Judgement_Length = ");
		Serial.println(Judgement_Length);
	}
	//--------------------------------------------------------


	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	//进行状态的回执
	Send_E025(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A025状态回执");
		Serial.println("结束Receive_A025函数");
	}
}

//函 数 名：Send_E025() 
//功能描述：E025的的回执函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E025(int Receive_IsBroadcast)
{
	return 0;
}

//函 数 名：E025_init() 
//功能描述：E025的的初始化函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E025_init()
{
	return 0;
}
