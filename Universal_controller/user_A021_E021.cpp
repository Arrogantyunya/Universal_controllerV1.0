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

	//防止数据冲突，增加延时随机函数
	delay(random(0,5000));
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
	E021_init();

	E021_IsBroadcast = Receive_IsBroadcast;//E021的是否广播指令

	Send_Data_Lamp();//发送数据灯
	return 0;
}

unsigned char E021_init()
{
	E021_FrameHead = 0xFE;		//E021的帧头

	E021_FrameId1 = 0xE0;		//E021的帧ID1
	E021_FrameId2 = 0x21;		//E021的帧ID2

	E021_DataLen = 0x14;			//E021的数据长度

	E021_DeviceTypeID1 = 0xC0;	//E021的设备类型1
	E021_DeviceTypeID2 = 0x02;	//E021的设备类型2

	E021_IsBroadcast = 0x00;		//E021的是否广播指令

	E021_ZoneId = AT24CXX_ReadOneByte(12);			//E021的区域

	E021_GetDigitalStatus();
	E021_GetAnalogStatus();


	return 0;
}


//E021得到数字状态
int E021_GetDigitalStatus()
{
	byte DI_1[8] = { 0,0,0,0,0,0,0,0 }; String Str_DI1; int DIBin_1 = 0;
	byte DI_2[8] = { 0,0,0,0,0,0,0,0 }; String Str_DI2; int DIBin_2 = 0;
	byte DO_1[8] = { 0,0,0,0,0,0,0,0 }; String Str_DO1; int DOBin_1 = 0;
	byte DO_2[8] = { 0,0,0,0,0,0,0,0 }; String Str_DO2; int DOBin_2 = 0;

	DI_2[0] = 1;
	DI_2[1] = 0;
	DI_2[2] = 1;
	DI_2[3] = 1;
	DI_2[4] = 0;
	DI_2[5] = 0;
	DI_2[6] = digitalRead(DI2);	//digitalRead(DI2)
	DI_2[7] = digitalRead(DI1);	//digitalRead(DI1)

	for (int i = 7; i >= 0; i--)
	{
		DIBin_1 = DIBin_1 | (DI_1[7 - i] << i);
		DIBin_2 = DIBin_2 | (DI_2[7 - i] << i);
		if (debug == 1)
		{
			Serial.print(String("DIBin_1 = "));
			Serial.println(DIBin_1, BIN);
			Serial.print(String("DIBin_2 = "));
			Serial.println(DIBin_2, BIN);
		}
	}

	//Str_DI1 = String(DIBin_1,HEX); Str_DI2 = String(DIBin_2, HEX);

	/*if (debug == 1)
	{
		Serial.print("Str_DI1 = 0x");
		Serial.println(Str_DI1);
		Serial.print("Str_DI2 = 0x");
		Serial.println(Str_DI2);
	}

	long DI1_long = Str_DI1.toInt();
	long DI2_long = Str_DI2.toInt();
	if (debug == 1)
	{
		Serial.print("DI1_long = ");
		Serial.println(DI1_long,HEX);
		Serial.print("DI2_long = ");
		Serial.println(DI2_long,HEX);
	}*/

	E021_digIn1 = DIBin_1;
	E021_digIn2 = DIBin_2;

	if (debug == 1)
	{
		Serial.print("E021_digIn1,E021_digIn2 = ");
		Serial.println(E021_digIn1, HEX);
		Serial.print(" , ");
		Serial.println(E021_digIn2, HEX);
	}
//--------------------------------------------------
	DO_2[0] = 1;
	DO_2[1] = 0;
	DO_2[2] = 1;
	DO_2[3] = 0;
	DO_2[4] = 0;
	DO_2[5] = 0;
	DO_2[4] = digitalRead(KCZJ2);	//digitalRead(KCZJ2);
	DO_2[5] = digitalRead(KCZJ1);	//digitalRead(KCZJ1);
	DO_2[6] = digitalRead(DO2);		//digitalRead(D02);
	DO_2[7] = digitalRead(DO1);		//digitalRead(D01);

	for (int i = 7; i >= 0; i--)
	{
		DOBin_1 = DOBin_1 | (DO_1[7 - i] << i);
		DOBin_2 = DOBin_2 | (DO_2[7 - i] << i);
		if (debug == 1)
		{
			Serial.print(String("DOBin_1 = "));
			Serial.println(DOBin_1, BIN);
			Serial.print(String("DOBin_2 = "));
			Serial.println(DOBin_2, BIN);
		}
	}

	//Str_DO1 = String(DOBin_1, HEX); Str_DO2 = String(DOBin_2, HEX);

	/*if (debug == 1)
	{
		Serial.print("Str_DO1 = 0x");
		Serial.println(Str_DO1);
		Serial.print("Str_DO2 = 0x");
		Serial.println(Str_DO2);
	}
	long DO1_long = Str_DO1.toInt();
	long DO2_long = Str_DO2.toInt();
	if (debug == 1)
	{
		Serial.print("DI1_long = ");
		Serial.println(DI1_long, HEX);
		Serial.print("DI2_long = ");
		Serial.println(DI2_long, HEX);
	}*/
	E021_digOut1 = DOBin_1;
	E021_digOut2 = DOBin_2;

	if (debug == 1)
	{
		Serial.print("E021_digOut1,E021_digOut2 = ");
		Serial.println(E021_digOut1, HEX);
		Serial.print(" , ");
		Serial.println(E021_digOut2, HEX);
	}

	return 0;
}


//E021得到模拟状态
int E021_GetAnalogStatus()
{
	int analogRead1 = analogRead(VIN1);
	int analogRead2 = analogRead(VIN1);
	float ar1 = (analogRead1 * 0.8056) * 11;//4537.65
	float ar2 = (analogRead1 * 0.8056) * 11;
	if (debug == 1)
	{
		ar1 = 5.69;ar2 = 17.36;
		Serial.println(String("ar1 = ") + ar1 + String("mV"));
		Serial.println(String("ar2 = ") + ar2 + String("mV"));
	}


	if (floor(ar1) >= 0 && floor(ar1) <= 99)//[0],(0,99]
	{
		E021_anaIn1_1 = floor(ar1);
		E021_anaIn1_2 = (ar1 - E021_anaIn1_1) * 100;
		E021_anaIn1_3 = 'E2';
		if (debug == 1)
		{
			Serial.println(String("E021_anaIn1_1 = ") + E021_anaIn1_1);
			Serial.println(String("E021_anaIn1_2 = ") + E021_anaIn1_2);
			Serial.println(String("E021_anaIn1_3 = ") + String(E021_anaIn1_3));
		}
	}
	else//超出量程
	{
		Serial.println("模拟输入1超出量程");
		/*E021_anaIn1_1 = floor(ar1);
		E021_anaIn1_2 = (ar1 - E021_anaIn1_1) * 100;
		E021_anaIn1_3 = 0xE2;*/
		if (debug == 1)
		{
			Serial.println(String("E021_anaIn1_1 = ") + E021_anaIn1_1);
			Serial.println(String("E021_anaIn1_2 = ") + E021_anaIn1_2);
			Serial.println(String("E021_anaIn1_3 = ") + String(E021_anaIn1_3));
		}
	}

	if (floor(ar2) >= 0 && floor(ar2) <= 99)//[0],(0,99]
	{
		E021_anaIn2_1 = floor(ar2);
		E021_anaIn2_2 = (ar2 - E021_anaIn2_1) * 100;
		E021_anaIn2_3 = 'E2';
		if (debug == 1)
		{
			Serial.println(String("E021_anaIn2_1 = ") + E021_anaIn2_1);
			Serial.println(String("E021_anaIn2_2 = ") + E021_anaIn2_2);
			Serial.println(String("E021_anaIn2_3 = ") + String(E021_anaIn2_3));
		}
	}
	else//超出量程
	{
		Serial.println("模拟输入2超出量程");
		/*E021_anaIn2_1 = floor(ar2);
		E021_anaIn2_2 = (ar2 - E021_anaIn2_1) * 100;
		E021_anaIn2_3 = 0xE2;*/
		if (debug == 1)
		{
			Serial.println(String("E021_anaIn2_1 = ") + E021_anaIn2_1);
			Serial.println(String("E021_anaIn2_2 = ") + E021_anaIn2_2);
			Serial.println(String("E021_anaIn2_3 = ") + String(E021_anaIn2_3));
		}
	}


	return 0;
}
