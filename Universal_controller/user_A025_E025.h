// user_A025_E025.h

#ifndef _USER_A025_E025_h
#define _USER_A025_E025_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<arduino.h>	//引用标准库的头文件
#include"user_initialization.h"//初始化
#include"user_crc8.h"//CRC校验
#include"user_judgement.h"//判断


//引脚定义



//全局变量




//全局函数声明
void Receive_A025(unsigned char * Judgement_Data, int Judgement_Length);  //A013函数
unsigned char Send_E025(int Receive_IsBroadcast);  //E020函数
unsigned char E025_init();	//E011初始化函数


//类结构声明






#endif

