// 
// 
// 

#include "user_Set_Correlation.h"
#include "user_initialization.h"

//函 数 名：Receive_A013() 
//功能描述：A013的执行函数
//函数说明：设置LORA主设备的区域以及SN
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

//函 数 名：Receive_A020() 
//功能描述：A020的执行函数
//函数说明：设置没类型接口挂载的某一路子设备以及工作组数组
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

	if (Judgement_Data[7] == AT24CXX_ReadOneByte(12))//判断区域ID是否是12
	{
		if (Judgement_Data[8] == 0xC0 && Judgement_Data[9] == 0x03)
		{
			//判断设备路数
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


	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	//进行状态的回执
	Send_E020(Receive_IsBroadcast, E020_status);
	if (debug == 1)
	{
		Serial.println("完成A020状态回执");
		Serial.println("结束Receive_A020函数");
	}
}

//函 数 名：Receive_A022() 
//功能描述：A022的执行函数
//函数说明：设置某路（或某组）的输出设备状态
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

	//判断区域
	if (Judgement_Data[7] == AT24CXX_ReadOneByte(12))
	{
		//判断为单播
		if (Judgement_Data[6] == 0x00)
		{
			//判断为数字输出【C003】
			if (Judgement_Data[9] == 0xC0 && Judgement_Data[10] == 0x03)
			{
				//判断数据长度是否正确
				if (Judgement_Data[3] == 0x0E)
				{
					//判断路数为1路
					if (Judgement_Data[11] == 0x01)
					{
						//1路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(DO1, HIGH);

							//将1路开的状态值写入
							out_state = DO1_ON;
							Out_State[0] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[0] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[0]=");
								Serial.println(duration[0]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[0] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[0]=");
								Serial.println(ot[0]);
							}

							if (Out_State[0] == DO1_ON)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
							
						}
						//1路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将1路关的状态值写入
							out_state = Stateless;
							Out_State[0] = out_state;
							digitalWrite(DO1, LOW);

							if (debug == 1)
							{
								Serial.println("数字输出1关");
							}

							if (Out_State[0] == Stateless)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为2路
					else if (Judgement_Data[11] == 0x02)
					{
						//2路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(DO2, HIGH);

							//将2路开的状态值写入
							out_state = DO2_ON;
							Out_State[1] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[1] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[1]=");
								Serial.println(duration[1]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[1] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[1]=");
								Serial.println(ot[1]);
							}

							if (Out_State[1] == DO2_ON)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						//2路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将2路关的状态值写入
							out_state = Stateless;
							Out_State[1] = out_state;
							digitalWrite(DO2, LOW);

							if (debug == 1)
							{
								Serial.println("数字输出2关");
							}

							if (Out_State[1] == Stateless)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为3路
					else if (Judgement_Data[11] == 0x03)
					{
						//3路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(KCZJ1, );

							//将3路开的状态值写入
							out_state = DO3_ON;
							Out_State[2] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[2] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[2]=");
								Serial.println(duration[2]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[2] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[2]=");
								Serial.println(ot[2]);
							}

							if (Out_State[2] == DO3_ON)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						//3路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将3路关的状态值写入
							out_state = Stateless;
							Out_State[2] = out_state;
							digitalWrite(KCZJ1, HIGH);

							if (debug == 1)
							{
								Serial.println("数字输出3关");
							}

							if (Out_State[1] == Stateless)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为4路
					else if (Judgement_Data[11] == 0x04)
					{
						//4路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(KCZJ2, LOW);

							//将4路开的状态值写入
							out_state = DO4_ON;
							Out_State[3] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[3] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[3]=");
								Serial.println(duration[3]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[3] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[3]=");
								Serial.println(ot[3]);
							}

							if (Out_State[3] == DO4_ON)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						//4路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将4路关的状态值写入
							out_state = Stateless;
							Out_State[3] = out_state;
							digitalWrite(KCZJ2, HIGH);

							if (debug == 1)
							{
								Serial.println("数字输出4关");
							}

							if (Out_State[3] == Stateless)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为全部路
					else if (Judgement_Data[11] == 0x55)
					{
						//全部路开
						if (Judgement_Data[14] == 0x01)
						{

							//将全部路开的状态值写入
							out_state = DO1_ON;
							Out_State[0] = out_state;
							out_state = DO2_ON;
							Out_State[1] = out_state;
							out_state = DO3_ON;
							Out_State[2] = out_state;
							out_state = DO4_ON;
							Out_State[3] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[0] = Duration_time;
							duration[1] = Duration_time;
							duration[2] = Duration_time;
							duration[3] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[0,1,2,3]=");
								Serial.println(duration[0]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[0] = oldtime;
							ot[1] = oldtime;
							ot[2] = oldtime;
							ot[3] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[0,1,2,3]=");
								Serial.println(ot[0]);
							}

							if (Out_State[0] == DO1_ON && Out_State[1] == DO2_ON &&
								Out_State[2] == DO3_ON && Out_State[3] == DO4_ON)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						//全部路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将4路关的状态值写入
							out_state = Stateless;
							Out_State[0] = out_state;
							Out_State[1] = out_state;
							Out_State[2] = out_state;
							Out_State[3] = out_state;
							digitalWrite(DO1, LOW);
							digitalWrite(DO2, LOW);
							digitalWrite(KCZJ1, HIGH);
							digitalWrite(KCZJ2, HIGH);

							if (debug == 1)
							{
								Serial.println("数字输出全关");
							}

							if (Out_State[0] == Stateless && Out_State[1] == Stateless &&
								Out_State[2] == Stateless && Out_State[3] == Stateless)
							{
								E020_status = Set_digital_output_status_success;
							}
							else
							{
								E020_status = Set_digital_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//不存在的设备路数
					else
					{
						Serial.println("不存在的设备路数");
					}
				}
				else
				{
					//数据长度不正确
					Serial.println("数据长度不正确");
				}
			}
			//判断为模拟输出【C004】
			else if (Judgement_Data[9] == 0xC0 && Judgement_Data[10] == 0x04)
			{
				//判断数据长度是否正确
				if (Judgement_Data[3] == 0x10)
				{
					//判断路数为模拟输出1路
					if (Judgement_Data[11] == 0x01)
					{
						//模拟输出1路开
						if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
						{
							//analogWrite
							//将1路开的状态值写入
							out_state = AO1_ON;
							Out_State[4] = out_state;

							//在这里得到需要设定的电压值
							if (Judgement_Data[16] == 0xE2)
							{
								Set_AOVoltage1 = (Judgement_Data[14] + Judgement_Data[15] * 0.01);
								if (debug == 1)
								{
									Serial.println("Set_AOVoltage1 = " + String(Set_AOVoltage1) + "V");
								}
							}
							//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
							//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
							float AV1 = (Set_AOVoltage1 / 0.011) / 0.8056;
							if (AV1 - floor(AV1) >= 0.5)
							{
								Analog_Value1 = floor(AV1) + 1;
							}
							else if (AV1 - floor(AV1) < 0.5)
							{
								Analog_Value1 = floor(AV1);
							}
							else
							{
								if (debug == 1)
								{
									Serial.println("意外BUG区");
								}
							}
							if (debug == 1)
							{
								Serial.println("AV1 = " + String(AV1));
								Serial.println("Analog_Value1 = " + String(Analog_Value1));
							}

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[17] * 0x1000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
							duration[4] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[4]=");
								Serial.println(duration[4]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[4] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[4]=");
								Serial.println(ot[4]);
							}

							if (Out_State[4] == AO1_ON)
							{
								E020_status = Set_analog_output_status_success;
							}
							else
							{
								E020_status = Set_analog_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						//模拟输出1路关
						else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
						{
							//将模拟输出1路关的状态值写入
							out_state = Stateless;
							Out_State[4] = out_state;
							analogWrite(AO1, 0);
							if (debug == 1)
							{
								Serial.println("模拟输出1关");
							}

							if (Out_State[4] == Stateless)
							{
								E020_status = Set_analog_output_status_success;
							}
							else
							{
								E020_status = Set_analog_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("意外BUG区");
							}
						}
					}
					//判断路数为模拟输出2路
					else if (Judgement_Data[11] == 0x02)
					{
					//模拟输出2路开
					if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
					{
						//analogWrite
						//将2路开的状态值写入
						out_state = AO2_ON;
						Out_State[5] = out_state;

						//在这里得到需要设定的电压值
						if (Judgement_Data[16] == 0xE2)
						{
							Set_AOVoltage2 = (Judgement_Data[14] + Judgement_Data[15] * 0.01);
							if (debug == 1)
							{
								Serial.println("Set_AOVoltage2 = " + String(Set_AOVoltage2) + "V");
							}
						}
						//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
						//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
						float AV2 = (Set_AOVoltage2 / 0.011) / 0.8056;
						if (AV2 - floor(AV2) >= 0.5)
						{
							Analog_Value2 = floor(AV2) + 1;
						}
						else if (AV2 - floor(AV2) < 0.5)
						{
							Analog_Value2 = floor(AV2);
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("意外BUG区");
							}
						}
						if (debug == 1)
						{
							Serial.println("AV2 = " + String(AV2));
							Serial.println("Analog_Value2 = " + String(Analog_Value2));
						}

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[17] * 0x1000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
						duration[5] = Duration_time;
						if (debug == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[5]=");
							Serial.println(duration[5]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[5] = oldtime;
						if (debug == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[5]=");
							Serial.println(ot[5]);
						}

						if (Out_State[5] == AO2_ON)
						{
							E020_status = Set_analog_output_status_success;
						}
						else
						{
							E020_status = Set_analog_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);

						forswitch();
					}
					//模拟输出2路关
					else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
					{
						//将模拟输出1路关的状态值写入
						out_state = Stateless;
						Out_State[5] = out_state;
						analogWrite(AO2, 0);
						if (debug == 1)
						{
							Serial.println("模拟输出2关");
						}

						if (Out_State[5] == Stateless)
						{
							E020_status = Set_analog_output_status_success;
						}
						else
						{
							E020_status = Set_analog_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);

						forswitch();
					}
					else
					{
						if (debug == 1)
						{
							Serial.println("意外BUG区");
						}
					}
					}
					//判断路数为模拟输出全部路
					else if (Judgement_Data[11] == 0x55)
					{
						//模拟输出全部路开
						if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
						{
							//analogWrite
							//将全部路开的状态值写入
							out_state = AO1_ON;
							Out_State[4] = out_state;
							out_state = AO2_ON;
							Out_State[5] = out_state;

							//在这里得到需要设定的电压值
							if (Judgement_Data[16] == 0xE2)
							{
								Set_AOVoltage1 = Judgement_Data[14] + Judgement_Data[15] * 0.01;
								Set_AOVoltage2 = Judgement_Data[14] + Judgement_Data[15] * 0.01;
								if (debug == 1)
								{
									Serial.println("Set_AOVoltage1,2 = " + String(Set_AOVoltage2) + "mv");
								}
							}
							//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
							//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
							float AV1 = (Set_AOVoltage1 / 0.011) / 0.8056;
							float AV2 = (Set_AOVoltage2 / 0.011) / 0.8056;
							if (AV2 - floor(AV2) >= 0.5)
							{
								Analog_Value1 = floor(AV1) + 1;
								Analog_Value2 = floor(AV2) + 1;
							}
							else if (AV2 - floor(AV2) < 0.5)
							{
								Analog_Value1 = floor(AV1);
								Analog_Value2 = floor(AV2);
							}
							else
							{
								if (debug == 1)
								{
									Serial.println("意外BUG区");
								}
							}
							if (debug == 1)
							{
								Serial.println("AV1,2 = " + String(AV2));
								Serial.println("Analog_Value1,2 = " + String(Analog_Value2));
							}

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[17] * 0x1000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
							duration[4] = Duration_time;
							duration[5] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[4，5]=");
								Serial.println(duration[5]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[4] = oldtime;
							ot[5] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[4，5]=");
								Serial.println(ot[5]);
							}

							if (Out_State[4] == AO1_ON && Out_State[5] == AO2_ON)
							{
								E020_status = Set_analog_output_status_success;
							}
							else
							{
								E020_status = Set_analog_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						//模拟输出全部路关
						else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
						{
							//将模拟输出2路关的状态值写入
							out_state = Stateless;
							Out_State[4] = out_state;
							Out_State[5] = out_state;
							analogWrite(AO1, 0);
							analogWrite(AO2, 0);
							if (debug == 1)
							{
								Serial.println("模拟输出全部路关");
							}

							if (Out_State[4] == Stateless && Out_State[5] == Stateless)
							{
								E020_status = Set_analog_output_status_success;
							}
							else
							{
								E020_status = Set_analog_output_status_failed;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E020(Receive_IsBroadcast, E020_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("意外BUG区");
							}
						}
					}
					//不存在的设备路数
					else
					{
						if (debug == 1)
						{
							Serial.println("不存在的设备路数");
						}
					}
				}
				else
				{
					if (debug == 1)
					{
						Serial.println("数据长度不正确");
					}
				}
			}
			//不存在的设备类型
			else
			{
				if (debug == 1)
				{
					Serial.println("不存在的设备类型");
				}
			}
		}
		//判断为组播
		else if (Judgement_Data[6] == 0x55)
		{
			//判断是否属于DO1的组
			if (Judgement_Data[8] == AT24CXX_ReadOneByte(16) || Judgement_Data[8] == AT24CXX_ReadOneByte(17) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(18) || Judgement_Data[8] == AT24CXX_ReadOneByte(19) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(20))
			{
				//判断是否属于DO1的子设备类型
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(14) && Judgement_Data[13] == AT24CXX_ReadOneByte(15))
				{
					//1路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(DO1, HIGH);

						//将1路开的状态值写入
						out_state = DO1_ON;
						Out_State[0] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[0] = Duration_time;
						if (debug == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[0]=");
							Serial.println(duration[0]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[0] = oldtime;
						if (debug == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[0]=");
							Serial.println(ot[0]);
						}

						if (Out_State[0] == DO1_ON)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					//1路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将1路关的状态值写入
						out_state = Stateless;
						Out_State[0] = out_state;
						digitalWrite(DO1, LOW);

						if (debug == 1)
						{
							Serial.println("数字输出1关");
						}

						if (Out_State[0] == Stateless)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					else
					{
						if (debug == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于DO2的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(23) || Judgement_Data[8] == AT24CXX_ReadOneByte(24) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(25) || Judgement_Data[8] == AT24CXX_ReadOneByte(26) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(27))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(21) && Judgement_Data[13] == AT24CXX_ReadOneByte(22))
				{
					//2路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(DO2, HIGH);

						//将2路开的状态值写入
						out_state = DO2_ON;
						Out_State[1] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[1] = Duration_time;
						if (debug == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[1]=");
							Serial.println(duration[1]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[1] = oldtime;
						if (debug == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[1]=");
							Serial.println(ot[1]);
						}

						if (Out_State[1] == DO2_ON)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					//2路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将2路关的状态值写入
						out_state = Stateless;
						Out_State[1] = out_state;
						digitalWrite(DO2, LOW);

						if (debug == 1)
						{
							Serial.println("数字输出2关");
						}

						if (Out_State[1] == Stateless)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					else
					{
						if (debug == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于DO3的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(30) || Judgement_Data[8] == AT24CXX_ReadOneByte(31) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(32) || Judgement_Data[8] == AT24CXX_ReadOneByte(33) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(34))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(28) && Judgement_Data[13] == AT24CXX_ReadOneByte(29))
				{
					//3路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(KCZJ1, );

						//将3路开的状态值写入
						out_state = DO3_ON;
						Out_State[2] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[2] = Duration_time;
						if (debug == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[2]=");
							Serial.println(duration[2]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[2] = oldtime;
						if (debug == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[2]=");
							Serial.println(ot[2]);
						}

						if (Out_State[2] == DO3_ON)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					//3路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将3路关的状态值写入
						out_state = Stateless;
						Out_State[2] = out_state;
						digitalWrite(KCZJ1, HIGH);

						if (debug == 1)
						{
							Serial.println("数字输出3关");
						}

						if (Out_State[1] == Stateless)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					else
					{
						if (debug == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于DO4的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(37) || Judgement_Data[8] == AT24CXX_ReadOneByte(38) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(39) || Judgement_Data[8] == AT24CXX_ReadOneByte(40) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(41))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(35) && Judgement_Data[13] == AT24CXX_ReadOneByte(36))
				{
					//4路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(KCZJ2, LOW);

						//将4路开的状态值写入
						out_state = DO4_ON;
						Out_State[3] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[3] = Duration_time;
						if (debug == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[3]=");
							Serial.println(duration[3]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[3] = oldtime;
						if (debug == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[3]=");
							Serial.println(ot[3]);
						}

						if (Out_State[3] == DO4_ON)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					//4路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将4路关的状态值写入
						out_state = Stateless;
						Out_State[3] = out_state;
						digitalWrite(KCZJ2, HIGH);

						if (debug == 1)
						{
							Serial.println("数字输出4关");
						}

						if (Out_State[3] == Stateless)
						{
							E020_status = Set_digital_output_status_success;
						}
						else
						{
							E020_status = Set_digital_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					else
					{
						if (debug == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于AO1的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(44) || Judgement_Data[8] == AT24CXX_ReadOneByte(45) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(46) || Judgement_Data[8] == AT24CXX_ReadOneByte(47) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(48))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(42) && Judgement_Data[13] == AT24CXX_ReadOneByte(43))
				{
					//模拟输出1路开
					if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
					{
						//analogWrite
						//将1路开的状态值写入
						out_state = AO1_ON;
						Out_State[4] = out_state;

						//在这里得到需要设定的电压值
						if (Judgement_Data[16] == 0xE2)
						{
							Set_AOVoltage1 = (Judgement_Data[14] + Judgement_Data[15] * 0.01);
							if (debug == 1)
							{
								Serial.println("Set_AOVoltage1 = " + String(Set_AOVoltage1) + "V");
							}
						}
						//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
						//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
						float AV1 = (Set_AOVoltage1 / 0.011) / 0.8056;
						if (AV1 - floor(AV1) >= 0.5)
						{
							Analog_Value1 = floor(AV1) + 1;
						}
						else if (AV1 - floor(AV1) < 0.5)
						{
							Analog_Value1 = floor(AV1);
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("意外BUG区");
							}
						}
						if (debug == 1)
						{
							Serial.println("AV1 = " + String(AV1));
							Serial.println("Analog_Value1 = " + String(Analog_Value1));
						}

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[17] * 0x1000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
						duration[4] = Duration_time;
						if (debug == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[4]=");
							Serial.println(duration[4]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[4] = oldtime;
						if (debug == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[4]=");
							Serial.println(ot[4]);
						}

						if (Out_State[4] == AO1_ON)
						{
							E020_status = Set_analog_output_status_success;
						}
						else
						{
							E020_status = Set_analog_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					//模拟输出1路关
					else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
					{
						//将模拟输出1路关的状态值写入
						out_state = Stateless;
						Out_State[4] = out_state;
						analogWrite(AO1, 0);
						if (debug == 1)
						{
							Serial.println("模拟输出2关");
						}

						if (Out_State[4] == Stateless)
						{
							E020_status = Set_analog_output_status_success;
						}
						else
						{
							E020_status = Set_analog_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					else
					{
						if (debug == 1)
						{
							Serial.println("意外BUG区");
						}
					}
				}
			}
			//判断是否属于AO2的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(51) || Judgement_Data[8] == AT24CXX_ReadOneByte(52) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(53) || Judgement_Data[8] == AT24CXX_ReadOneByte(54) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(55))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(49) && Judgement_Data[13] == AT24CXX_ReadOneByte(50))
				{
					//模拟输出2路开
					if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
					{
						//analogWrite
						//将2路开的状态值写入
						out_state = AO2_ON;
						Out_State[5] = out_state;

						//在这里得到需要设定的电压值
						if (Judgement_Data[16] == 0xE2)
						{
							Set_AOVoltage2 = Judgement_Data[14] + Judgement_Data[15] * 0.01;
							if (debug == 1)
							{
								Serial.println("Set_AOVoltage1 = " + String(Set_AOVoltage2) + "mv");
							}
						}
						//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
						//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
						float AV2 = (Set_AOVoltage2 / 0.011) / 0.8056;
						if (AV2 - floor(AV2) >= 0.5)
						{
							Analog_Value2 = floor(AV2) + 1;
						}
						else if (AV2 - floor(AV2) < 0.5)
						{
							Analog_Value2 = floor(AV2);
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("意外BUG区");
							}
						}
						if (debug == 1)
						{
							Serial.println("AV2 = " + String(AV2));
							Serial.println("Analog_Value2 = " + String(Analog_Value2));
						}

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[17] * 0x1000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
						duration[5] = Duration_time;
						if (debug == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[5]=");
							Serial.println(duration[5]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[5] = oldtime;
						if (debug == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[5]=");
							Serial.println(ot[5]);
						}

						if (Out_State[5] == AO2_ON)
						{
							E020_status = Set_analog_output_status_success;
						}
						else
						{
							E020_status = Set_analog_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					//模拟输出2路关
					else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
					{
						//将模拟输出2路关的状态值写入
						out_state = Stateless;
						Out_State[5] = out_state;
						analogWrite(AO2, 0);
						if (debug == 1)
						{
							Serial.println("模拟输出2关");
						}

						if (Out_State[5] == Stateless)
						{
							E020_status = Set_analog_output_status_success;
						}
						else
						{
							E020_status = Set_analog_output_status_failed;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E020(Receive_IsBroadcast, E020_status);
					}
					else
					{
						if (debug == 1)
						{
							Serial.println("意外BUG区");
						}
					}
				}
			}
			else
			{
				//不存在的任何组
				if (debug == 1)
				{
					Serial.println("不存在的任何组");
				}
			}
		}
		//不存在的广播功能
		else
		{
			if (debug == 1)
			{
				Serial.println("不存在的广播功能");
			}
		}
	}
	else
	{
		if (debug == 1)
		{
			Serial.println("不属于本设备的区域");
		}
	}

	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];


	//进行状态的回执
	Send_E021(Receive_IsBroadcast);
	if (debug == 1)
	{
		Serial.println("完成A022状态回执");
		Serial.println("结束Receive_A022函数");
	}
}

//函 数 名：Receive_A023() 
//功能描述：A023的执行函数
//函数说明：设置输入关联输出
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

	if (Judgement_Data[7] == 0x01/*AT24CXX_ReadOneByte(12)*/)
	{
		//先将字符串数组拼接成Strring字符串，读取出来
		for (size_t i = 8; i <= Judgement_Length-7; i++)
		{
			//强制转换为char类型
			AssStat1.concat(String(char(Judgement_Data[i])));
		}
		if (debug == 1)
		{
			Serial.println(AssStat1);
		}
		Serial.println(AssStat1);
	}

	//先分割#，分割为条件语句以及执行语句
	data_processing(AssStat1);

	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	//进行状态的回执
	Send_E020(Receive_IsBroadcast, E020_status);
	if (debug == 1)
	{
		Serial.println("完成A023状态回执");
		Serial.println("结束Receive_A023函数");
	}
}

//函 数 名：Receive_A024() 
//功能描述：A024的执行函数
//函数说明：设置预留字段B、I、T、C、D的值
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

	//判断区域
	if (Judgement_Data[7] == AT24CXX_ReadOneByte(12))
	{
		//设置Bool类型的预留字段
		if (Judgement_Data[8] == 0x01)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x06)
			{
				AT24CXX_WriteOneByte(56, Judgement_Data[9]);
				if (AT24CXX_ReadOneByte(56) == Judgement_Data[9])
				{
					E020_status = Set_reserved_field_success;
					
				}
				else
				{
					E020_status = Set_reserved_field_failed;
				}
			}
		}
		//设置Int类型预留字段
		else if (Judgement_Data[8] == 0x02)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				Serial.println("...........");
				//57-64,9-16
				AT24CXX_WriteOneByte(57, Judgement_Data[9]);
				AT24CXX_WriteOneByte(58, Judgement_Data[10]);
				AT24CXX_WriteOneByte(59, Judgement_Data[11]);
				AT24CXX_WriteOneByte(60, Judgement_Data[12]);
				AT24CXX_WriteOneByte(61, Judgement_Data[13]);
				AT24CXX_WriteOneByte(62, Judgement_Data[14]);
				AT24CXX_WriteOneByte(63, Judgement_Data[15]);
				AT24CXX_WriteOneByte(64, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, 57) == 1)
				{
					E020_status = Set_reserved_field_success;
				}
				else
				{
					E020_status = Set_reserved_field_failed;
				}
			}
			else
			{
				if (debug == 1)
				{
					Serial.println("数据长度错误");
				}
			}
		}
		//设置T定时器预留字段
		else if (Judgement_Data[8] == 0x03)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				//65-72,9-16
				AT24CXX_WriteOneByte(65, Judgement_Data[9]);
				AT24CXX_WriteOneByte(66, Judgement_Data[10]);
				AT24CXX_WriteOneByte(67, Judgement_Data[11]);
				AT24CXX_WriteOneByte(68, Judgement_Data[12]);
				AT24CXX_WriteOneByte(69, Judgement_Data[13]);
				AT24CXX_WriteOneByte(70, Judgement_Data[14]);
				AT24CXX_WriteOneByte(71, Judgement_Data[15]);
				AT24CXX_WriteOneByte(72, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, 65) == 1)
				{
					E020_status = Set_reserved_field_success;
				}
				else
				{
					E020_status = Set_reserved_field_failed;
				}
			}
			else
			{
				if (debug == 1)
				{
					Serial.println("数据长度错误");
				}
			}
		}
		//设置C计数器预留字段
		else if (Judgement_Data[8] == 0x04)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				//73-80,9-16
				AT24CXX_WriteOneByte(73, Judgement_Data[9]);
				AT24CXX_WriteOneByte(74, Judgement_Data[10]);
				AT24CXX_WriteOneByte(75, Judgement_Data[11]);
				AT24CXX_WriteOneByte(76, Judgement_Data[12]);
				AT24CXX_WriteOneByte(77, Judgement_Data[13]);
				AT24CXX_WriteOneByte(78, Judgement_Data[14]);
				AT24CXX_WriteOneByte(79, Judgement_Data[15]);
				AT24CXX_WriteOneByte(80, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, 73) == 1)
				{
					E020_status = Set_reserved_field_success;
				}
				else
				{
					E020_status = Set_reserved_field_failed;
				}
			}
			else
			{
				if (debug == 1)
				{
					Serial.println("数据长度错误");
				}

			}
		}
		//设置D延时预留字段
		else if (Judgement_Data[8] == 0x05)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				//81-88,9-16
				AT24CXX_WriteOneByte(81, Judgement_Data[9]);
				AT24CXX_WriteOneByte(82, Judgement_Data[10]);
				AT24CXX_WriteOneByte(83, Judgement_Data[11]);
				AT24CXX_WriteOneByte(84, Judgement_Data[12]);
				AT24CXX_WriteOneByte(85, Judgement_Data[13]);
				AT24CXX_WriteOneByte(86, Judgement_Data[14]);
				AT24CXX_WriteOneByte(87, Judgement_Data[15]);
				AT24CXX_WriteOneByte(88, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, 73) == 1)
				{
					E020_status = Set_reserved_field_success;
				}
				else
				{
					E020_status = Set_reserved_field_failed;
				}
			}
			else
			{
				if (debug == 1)
				{
					Serial.println("数据长度错误");
				}
			}
		}
		else
		{
			if (debug == 1)
			{
				Serial.println("不存在的字段");
			}
		}
	}


	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	//进行状态的回执
	Send_E020(Receive_IsBroadcast, E020_status);
	if (debug == 1)
	{
		Serial.println("完成A024状态回执");
		Serial.println("结束Receive_A024函数");
	}
}

//函 数 名：Send_E020() 
//功能描述：E020的的回执函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

//函 数 名：E025_init() 
//功能描述：E025的的初始化函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

//函 数 名：SN_ZoneISOK() 
//功能描述：判断SN以及ZoneID是否写入成功的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
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

int Verification_Reserved_field(unsigned char * Judgement_Data, int Initial)
{
	int Check_Value = 0;
	if (debug == 1)
	{
		Serial.println("Initial = " + String(Initial));
	}
	for (size_t i = 0; i < 8; i++)
	{
		if (AT24CXX_ReadOneByte(Initial + i) == Judgement_Data[9 + i])
		{
			Check_Value++;
			if (debug == 1)
			{
				Serial.println("AT24CXX_ReadOneByte[ " + String(Initial + i) + " ] = " + String(Check_Value));
				Serial.println("Check_Value = " + String(Check_Value));
			}
		}
	}
	if (Check_Value == 8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void forswitch()
{
	if (Out_State[0] == Stateless && Out_State[1] == Stateless &&
		Out_State[2] == Stateless && Out_State[3] == Stateless &&
		Out_State[4] == Stateless && Out_State[5] == Stateless)
	{

	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			switch (Out_State[i])
			{
				/*状态：无状态
				 *在此状态中需要不断检测接收的值，
				 *接收到值后进行判断进入下一个状态。*/
			case Stateless:
				//无状态
				//无状态指令
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					Serial.print(i);
					Serial.println("进入case：Stateless");
				}
				//--------------------------------------
				break;

				/*状态：DO1开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO1_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					Serial.print(i);
					Serial.println("进入case：DO1_ON");
				}
				//--------------------------------------
				digitalWrite(DO1, HIGH);
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
				
				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug == 1)
					{
						Serial.println("DO1设定的时间到了呀");
					}
					digitalWrite(DO1, LOW);
					Out_State[i] = Stateless;
				}
				////进行状态的回执
				//Send_E021(Receive_IsBroadcast);
				break;

				/*状态：DO2开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO2_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					Serial.print(i);
					Serial.println("进入case：DO2_ON");
				}
				//--------------------------------------
				digitalWrite(DO2, HIGH);
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------

				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug == 1)
					{
						Serial.println("DO2设定的时间到了呀");
					}
					digitalWrite(DO2, LOW);
					Out_State[i] = Stateless;
				}
				break;

				/*状态：DO3开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO3_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					Serial.print(i);
					Serial.println("进入case：DO3_ON");
				}
				//--------------------------------------
				digitalWrite(KCZJ1, LOW);
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------

				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug == 1)
					{
						Serial.println("DO3设定的时间到了呀");
					}
					digitalWrite(KCZJ1, HIGH);
					Out_State[i] = Stateless;
				}
				break;

				/*状态：DO4开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO4_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					Serial.print(i);
					Serial.println("进入case：DO4_ON");
				}
				//--------------------------------------
				digitalWrite(KCZJ2, LOW);
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------

				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug == 1)
					{
						Serial.println("DO4设定的时间到了呀");
					}
					digitalWrite(KCZJ2, HIGH);
					Out_State[i] = Stateless;
				}
				break;

				/*状态：AO1开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case AO1_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					Serial.print(i);
					Serial.println("进入case：AO1_ON");
				}
				//--------------------------------------
				analogWrite(AO1, Analog_Value1);
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------

				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug == 1)
					{
						Serial.println("AO1设定的时间到了呀");
					}
					analogWrite(AO1, 0);
					Out_State[i] = Stateless;
				}
				break;

				/*状态：AO2开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case AO2_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					Serial.print(i);
					Serial.println("进入case：AO2_ON");
				}
				//--------------------------------------
				analogWrite(AO2, Analog_Value2);
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------

				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug == 1)
					{
						Serial.println("AO2设定的时间到了呀");
					}
					analogWrite(AO2, 0);
					Out_State[i] = Stateless;
				}
				break;

			default:
				//--------------------------------------
				delay(500);
				Serial.println("Instruction error指令错误");
				//--------------------------------------
				break;
			}
		}
	}
}

//函 数 名：Analog1_Write()
//功能描述：
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Analog1_Write()
{
	
}

//函 数 名：Analog2_Write()
//功能描述：
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Analog2_Write()
{

}

//函 数 名：int data_processing(String data_1)
//功能描述：数据处理函数，分割# 处理判断以及执行
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int data_processing(String data_1)
{
	return 0;
}

//函 数 名：int condition_test(String con1)
//功能描述：处理判断语句的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int condition_test(String con1)
{
	return 0;
}

//函 数 名：int implement_test(String imp1)
//功能描述：处理执行语句的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int implement_test(String imp1)
{
	return 0;
}


