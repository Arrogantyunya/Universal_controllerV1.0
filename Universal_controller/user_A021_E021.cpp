// 
// 
// 

#include "user_A021_E021.h"
#include "user_initialization.h"

void Receive_A021(unsigned char * Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A021函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug == 1)
	{
		Serial.println("进入Receive_A021函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A021Judgement_Data ");
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


	//进行状态的回执
	Send_E021(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A021状态回执");
		Serial.println("结束Receive_A021函数");
	}
}

unsigned char Send_E021(int Receive_IsBroadcast)
{
	return 0;
}

unsigned char E021_init()
{
	return 0;
}
