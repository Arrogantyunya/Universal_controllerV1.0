// user_lorainit.h

#ifndef _USER_LORAINIT_h
#define _USER_LORAINIT_h


#if defined(ARDUINO) && ARDUINO >= 100
	#include <arduino.h>//引用标准库的头文件
#else
	#include "WProgram.h"
#endif

#include "user_initialization.h"	//引用头文件
//#include ""

//引脚定义


//全局函数声明
int LORA_Initialization(void);//初始化函数
String addr_write();

//全局变量
static unsigned char lora_data[200];
static unsigned char lora_len = 0;
static unsigned int lora_Completion_Degree = 0;


//类结构声明



#endif

