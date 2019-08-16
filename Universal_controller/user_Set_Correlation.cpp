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

	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	if (Judgement_Data[7] == AT24CXX_ReadOneByte(12))//判断区域ID是否是12
	{
		if (Judgement_Data[8] == 0xC0 && Judgement_Data[9] == 0x03)
		{
			if (Judgement_Data[10] == 0x01)
			{
				//这里是数字输出【C003】的第1路设备,子设备类型ID14-15，工作组数组ID16-20
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i+3, Judgement_Data[i]);
					if (debug == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 3) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 3),HEX);
					}
				}

				E020_status = Set_subdevice_type_and_workgroup_success;
			}
			else if (Judgement_Data[10] == 0x02)
			{
				//这里是数字输出【C003】的第2路设备，子设备类型ID21-22，工作组数组ID23-27
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 10, Judgement_Data[i]);
					if (debug == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 10) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 10), HEX);
					}
				}

				E020_status = Set_subdevice_type_and_workgroup_success;
			}
			else if (Judgement_Data[10] == 0x01)
			{
				//这里是模拟输出【C003】的第3路设备，子设备类型ID28-29，工作组数组ID30-34
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 17, Judgement_Data[i]);
					if (debug == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 17) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 17), HEX);
					}
				}

				E020_status = Set_subdevice_type_and_workgroup_success;
			}
			else if (Judgement_Data[10] == 0x02)
			{
				//这里是模拟输出【C003】的第4路设备，子设备类型ID35-36，工作组数组ID37-41
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 24, Judgement_Data[i]);
					if (debug == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 24) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 24), HEX);
					}
				}

				E020_status = Set_subdevice_type_and_workgroup_success;
			}
			else
			{
				E020_status = Set_subdevice_type_and_workgroup_failed;
				if (debug == 1)
				{
					Serial.println("C003所不存在的设备路数");
				}
			}
		}
		else if (Judgement_Data[8] == 0xC0 && Judgement_Data[9] == 0x04)
		{
			if (Judgement_Data[10] == 0x01)
			{
				//这里是模拟输出【C004】的第一路设备，子设备类型ID28-29，工作组数组ID30-34
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 17, Judgement_Data[i]);
					if (debug == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 17) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 31), HEX);
					}
				}

				E020_status = Set_subdevice_type_and_workgroup_success;
			}
			else if (Judgement_Data[10] == 0x02)
			{
				//这里是模拟输出【C004】的第二路设备，子设备类型ID35-36，工作组数组ID37-41
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 24, Judgement_Data[i]);
					if (debug == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 24) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 38), HEX);
					}
				}

				E020_status = Set_subdevice_type_and_workgroup_success;
			}
			else
			{
				if (debug == 1)
				{
					Serial.println("C004所不存在的设备路数");
				}
				E020_status = Set_subdevice_type_and_workgroup_failed;
			}
		}
		else
		{
			if (debug == 1)
			{
				Serial.println("不存在的控制器设备类型ID");
			}
			E020_status = Set_subdevice_type_and_workgroup_failed;
		}
	}



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
	E020_init();//将E020的值重置为初始值

	E020_IsBroadcast = Receive_IsBroadcast;//E020的是否广播指令
	E020_Status = E020_status;

	E020[0] = E020_FrameHead;
	E020[1] = E020_FrameId1;
	E020[2] = E020_FrameId2;
	E020[3] = E020_DataLen;
	E020[4] = E020_DeviceTypeID1;
	E020[5] = E020_DeviceTypeID2;
	E020[6] = E020_IsBroadcast;
	E020[7] = E020_ZoneId;
	E020[8] = E020_Status;
	E020[9] = E020_Allocate1;
	E020[10] = E020_Allocate2;
	E020[11] = E020_Allocate3;
	E020[12] = E020_Allocate4;
	E020[13] = E020_Allocate5;
	E020[14] = E020_Allocate6;
	E020[15] = E020_Allocate7;
	E020[16] = E020_Allocate8;

	for (size_t i = 4; i <= E020_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E020[i];
		// Check_Data[Check_Length] = 0x55;
		if (debug == 1)
		{
			Serial.print("Check_Data ");
			Serial.print(Check_Length);
			Serial.print(" :");
			Serial.println(Check_Data[Check_Length], HEX);
		}
		Check_Length++;
		delay(1);
	}
	Serial.print("Check_Length = ");
	Serial.println(Check_Length);

	if (Check_Length > 0)
	{
		E020_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug == 1)
		{
			Serial.print("CRC8计算的值E020_CRC8 = 0x");
			Serial.println(E020_CRC8, HEX);
		}
		Check_Length = 0;
	}

	E020[17] = E020_CRC8;
	E020[18] = E020_FrameEnd1;
	E020[19] = E020_FrameEnd2;
	E020[20] = E020_FrameEnd3;
	E020[21] = E020_FrameEnd4;
	E020[22] = E020_FrameEnd5;
	E020[23] = E020_FrameEnd6;

	//该区域为串口查看E020回执的信息
	if (debug == 1)
	{
		for (int i = 0; i < 24; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E020[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E020, 24);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯

	return 0;
}

//将E020的值重置为初始值
unsigned char E020_init()
{
	E020_FrameHead = 0xFE;

	E020_FrameId1 = 0xE0;
	E020_FrameId2 = 0x20;

	E020_DataLen = 0x0D;

	E020_DeviceTypeID1 = 0xC0;
	E020_DeviceTypeID2 = 0x02;

	E020_IsBroadcast = 0x00;

	E020_ZoneId = AT24CXX_ReadOneByte(12);;

	E020_Status = 0x00;

	E020_Allocate1 = 0x00;
	E020_Allocate2 = 0x00;
	E020_Allocate3 = 0x00;
	E020_Allocate4 = 0x00;
	E020_Allocate5 = 0x00;
	E020_Allocate6 = 0x00;
	E020_Allocate7 = 0x00;
	E020_Allocate8 = 0x00;


	E020_CRC8 = 0x00;

	E020_FrameEnd1 = 0x0D;
	E020_FrameEnd2 = 0x0A;
	E020_FrameEnd3 = 0x0D;
	E020_FrameEnd4 = 0x0A;
	E020_FrameEnd5 = 0x0D;
	E020_FrameEnd6 = 0x0A;
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


