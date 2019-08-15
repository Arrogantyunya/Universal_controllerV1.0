// 
// 
// 

#include "user_Set_Correlation.h"
#include "user_initialization.h"


void Receive_A013(unsigned char * Judgement_Data, int Judgement_Length)//A013函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A013函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug == 1)
	{
		Serial.println("进入Receive_A013函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A013Judgement_Data ");
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
	int ZoneID = Judgement_Data[7];
	if (debug == 1)
	{
		Serial.println(ZoneID, HEX);
	}
	AT24CXX_WriteOneByte(12, ZoneID);//将区域ID写入数组
	for (size_t i = 8; i <= 16; i++)
	{
		AT24CXX_WriteOneByte(i - 5, Judgement_Data[i]);
		if (debug == 1)
		{
			Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i-5) + String(" ]="));
			Serial.println(AT24CXX_ReadOneByte(i - 5), HEX);
		}
	}

	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	//进行状态的回执
	Send_E020(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A013状态回执");
		Serial.println("结束Receive_A013函数");
	}
}

void Receive_A020(unsigned char * Judgement_Data, int Judgement_Length)//A020函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A020函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug == 1)
	{
		Serial.println("进入Receive_A020函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A020Judgement_Data ");
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
	Send_E020(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A020状态回执");
		Serial.println("结束Receive_A020函数");
	}
}

void Receive_A022(unsigned char * Judgement_Data, int Judgement_Length)//A022函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A022函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug == 1)
	{
		Serial.println("进入Receive_A022函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A022Judgement_Data ");
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
	Send_E020(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A022状态回执");
		Serial.println("结束Receive_A022函数");
	}
}

void Receive_A023(unsigned char * Judgement_Data, int Judgement_Length)//A023函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A023函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug == 1)
	{
		Serial.println("进入Receive_A023函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A023Judgement_Data ");
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
	Send_E020(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A023状态回执");
		Serial.println("结束Receive_A023函数");
	}
}

void Receive_A024(unsigned char * Judgement_Data, int Judgement_Length)//A024函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A024函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug == 1)
	{
		Serial.println("进入Receive_A024函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A024Judgement_Data ");
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
	Send_E020(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A024状态回执");
		Serial.println("结束Receive_A024函数");
	}
}

unsigned char Send_E020(int Receive_IsBroadcast)
{
	Send_Data_Lamp();
	return 0;
}

unsigned char E020_init()
{
	return 0;
}


