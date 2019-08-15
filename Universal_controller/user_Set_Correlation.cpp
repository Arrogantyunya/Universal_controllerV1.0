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
		Serial.print("ZoneID = ");
		Serial.println(ZoneID, HEX);
	}
	AT24CXX_WriteOneByte(12, ZoneID);	//将区域ID写入EEPROM
	for (size_t i = 8; i <= 16; i++)	//将SN写入EEPROM
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



	if (SN_ZoneISOK(Judgement_Data, Judgement_Length) == 1)
	{
		E020_status = SetArea_and_SN_Success;
		if (debug == 1)
		{
			Serial.println(String("E020_status = SetSnAndSlaverCountOk") + String(E020_status));
		}
	}
	else
	{
		E020_status = Set_Area_and_SN_Failure;
		if (debug == 1)
		{
			Serial.println(String("E020_status = SetSnAndSlaverCountErr") + String(E020_status));
		}
	}


	//进行状态的回执
	Send_E020(Receive_IsBroadcast, E020_status);
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
	Send_E020(Receive_IsBroadcast, E020_status);
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
	Send_E020(Receive_IsBroadcast, E020_status);
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
	Send_E020(Receive_IsBroadcast, E020_status);
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
	Send_E020(Receive_IsBroadcast, E020_status);
	if (debug == 1)
	{
		Serial.println("完成A024状态回执");
		Serial.println("结束Receive_A024函数");
	}
}

unsigned char Send_E020(int Receive_IsBroadcast,int E020_status)
{
	Send_Data_Lamp();
	return 0;
}

unsigned char E020_init()
{
	return 0;
}

unsigned char SN_ZoneISOK(unsigned char * Judgement_Data, int Judgement_Length)
{
	int A013_Checknum = 0;
	if (AT24CXX_ReadOneByte(3) == Judgement_Data[8])//7,8-16
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(4) == Judgement_Data[9])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(5) == Judgement_Data[10])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(6) == Judgement_Data[11])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(7) == Judgement_Data[12])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(8) == Judgement_Data[13])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(9) == Judgement_Data[14])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(10) == Judgement_Data[15])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(11) == Judgement_Data[16])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(12) == Judgement_Data[7])
	{
		A013_Checknum++;
		if (debug == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (A013_Checknum == 10)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	//判断是否写入成功
	/*static union DEVICE_SN
	{
		String str_SN;
		byte SN[9];
	};
	DEVICE_SN Device_SN1, Device_SN2;;*/
	//for (size_t i = 0; i < 9; i++)
	//{
	//	Device_SN1.SN[i] = AT24CXX_ReadOneByte(i + 3);
	//	if (debug == 1)
	//	{
	//		Serial.print(String("Device_SN1.SN[ ") + String(i) + String(" ]="));
	//		Serial.println(Device_SN1.SN[i], HEX);
	//	}
	//}
	//Serial.println(String("Device_SN1.str_SN = ") + Device_SN1.str_SN);

	//for (size_t i = 0; i < 9; i++)
	//{
	//	Device_SN1.SN[i] = Judgement_Data[i + 8];
	//	if (debug == 1)
	//	{
	//		Serial.print(String("Device_SN1.SN[ ") + String(i) + String(" ]="));
	//		Serial.println(Device_SN1.SN[i], HEX);
	//	}
	//}
	//Serial.println(String("Device_SN1.str_SN = ") + Device_SN1.str_SN);
}


