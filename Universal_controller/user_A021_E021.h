// user_A021_E021.h

#ifndef _USER_A021_E021_h
#define _USER_A021_E021_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif




//引脚定义



//全局变量




//全局函数声明
void Receive_A021(unsigned char * Judgement_Data, int Judgement_Length);  //A013函数
unsigned char Send_E021(int Receive_IsBroadcast);  //E020函数
unsigned char E021_init();	//E011初始化函数


//类结构声明





#endif

