// user_Set_Correlation.h

#ifndef _USER_SET_CORRELATION_h
#define _USER_SET_CORRELATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


//引脚定义



//全局变量




//全局函数声明
void Receive_A013(unsigned char * Judgement_Data, int Judgement_Length);  //A013函数
void Receive_A020(unsigned char * Judgement_Data, int Judgement_Length);  //A020函数
void Receive_A022(unsigned char * Judgement_Data, int Judgement_Length);  //A022函数
void Receive_A023(unsigned char * Judgement_Data, int Judgement_Length);  //A023函数
void Receive_A024(unsigned char * Judgement_Data, int Judgement_Length);  //A024函数
unsigned char Send_E020(int Receive_IsBroadcast);  //E020函数
unsigned char E020_init();	//E011初始化函数


//类结构声明




#endif

