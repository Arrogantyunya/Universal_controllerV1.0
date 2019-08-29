// user_Set_Correlation.h

#ifndef _USER_SET_CORRELATION_h
#define _USER_SET_CORRELATION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include<arduino.h>	//引用标准库的头文件
#include"user_initialization.h"//初始化
#include"user_crc8.h"//CRC校验
#include"user_judgement.h"//判断
#include "user_A021_E021.h"


//引脚定义



//全局变量
static int Storage_bytes_Flag = 100;			//存储字节的标志位

static unsigned char Out_State[6];              //用来存放状态值rd1
static unsigned long duration[6];               //用来存放持续时间值Duration_time
static unsigned long remaining[6];              //用来存放剩余时间值Remaining
static unsigned long ot[6];                     //用来存放旧时间值oldtime

static unsigned long time_huns = 0;             //时间百位
static unsigned long time_tens = 0;             //时间十位
static unsigned long time_ones = 0;             //时间个位

static unsigned long Duration_time = 0;         //持续时间
static unsigned long Remaining = 0;             //剩余时间
static unsigned long oldtime = 0;				//旧时间

static float Set_AOVoltage1 = 0;			//设置模拟输出电压值1
static float Set_AOVoltage2 = 0;			//设置模拟输出电压值2
static int Analog_Value1 = 0;				//analogwrite时输出的值1
static int Analog_Value2 = 0;				//analogwrite时输出的值2
//------------------------------------------------------------------------

static unsigned char E020[24];//用来存放E020发送出去的数组

static int E020_FrameHead = 0xFE;		//E020的帧头

static int E020_FrameId1 = 0xE0;		//E020的帧ID1
static int E020_FrameId2 = 0x20;		//E020的帧ID2

static int E020_DataLen = 0x0D;			//E020的数据长度

static int E020_DeviceTypeID1 = 0xC0;	//E020的设备类型1
static int E020_DeviceTypeID2 = 0x02;	//E020的设备类型2

static int E020_IsBroadcast = 0x00;		//E020的是否广播指令

static int E020_ZoneId = 0x00;			//E020的区域

static int E020_Status = 0x00;			//E020的状态值被声明成了枚举

static int E020_Allocate1 = 0x00;		//E020的Allocate1
static int E020_Allocate2 = 0x00;		//E020的Allocate2
static int E020_Allocate3 = 0x00;		//E020的Allocate3
static int E020_Allocate4 = 0x00;		//E020的Allocate4
static int E020_Allocate5 = 0x00;		//E020的Allocate5
static int E020_Allocate6 = 0x00;		//E020的Allocate6
static int E020_Allocate7 = 0x00;		//E020的Allocate7
static int E020_Allocate8 = 0x00;		//E020的Allocate8

static int E020_CRC8 = 0x00;			//E020的CRC8校验码

static int E020_FrameEnd1 = 0x0D;		//E020的帧尾1
static int E020_FrameEnd2 = 0x0A;		//E020的帧尾2
static int E020_FrameEnd3 = 0x0D;		//E020的帧尾3
static int E020_FrameEnd4 = 0x0A;		//E020的帧尾4
static int E020_FrameEnd5 = 0x0D;		//E020的帧尾5
static int E020_FrameEnd6 = 0x0A;		//E020的帧尾6

static unsigned char E020_Check_Data[50];   //用来存放接收到的数据
static int E020_Check_Length = 0;

//static String AssStat, AssStat1, AssStat2;//Association_statement，关联语句1
static String condition_1, implement_1;//判断语句以及执行语句
static String con0[5], con1[5], con2[5], con3[5], con4[5];//条件语句块数组
static String imp0[5], imp1[5], imp2[5], imp3[5], imp4[5];//执行语句块数组
static String Strcon[5],Strimp[5];//实际使用到的条件语句块以及执行语句块，用来充当变量的数组赋值
static size_t i_0 = 0, i_1 = 0, i_2 = 0, i_3 = 0;//循环次数函数

//static unsigned char Receive_Data[128];//用来存放接收到的数据
//static int Receive_Length = 0;//接收数据的长度
//static int CRC_Check_num = 0x00;//CRC校验的数值


//全局函数声明
//void LORA_Receive_information(void);//LORA接收函数
void Receive_A013(unsigned char * Judgement_Data, int Judgement_Length);  //A013函数
void Receive_A020(unsigned char * Judgement_Data, int Judgement_Length);  //A020函数
void Receive_A022(unsigned char * Judgement_Data, int Judgement_Length);  //A022函数
void Receive_A023(unsigned char * Judgement_Data, int Judgement_Length);  //A023函数
void Receive_A024(unsigned char * Judgement_Data, int Judgement_Length);  //A024函数
unsigned char Send_E020(int Receive_IsBroadcast,int E020_status );  //E020函数
unsigned char E020_init();	//E011初始化函数
unsigned char SN_ZoneISOK(unsigned char * Judgement_Data, int Judgement_Length);	//测试SN区域是否写入成功函数
int Verification_Reserved_field(unsigned char * Judgement_Data, int Initial);
void forswitch();
void Analog1_Write();
void Analog2_Write();
int data_processing(String data_1);//数据处理函数，分割# 处理判断以及执行
int condition_test(String con1);//处理判断语句的函数
int implement_test(String imp1);//处理执行语句的函数
int Condition_Judgment(int conx, int ret_condition_test);//条件语句判断函数
int Implement_Handle(int impx, int ret_Implement_test);
void array_empty_test();//数组清空函数
void array_print_test();//数组打印测试函数
void celue();//策略函数

//类结构声明
//LORA开关型设备的通用回执状态(结构类型，枚举)
static enum Device_status
{
	FactoryMode = 0x00,//出厂模式
	SetArea_and_SN_Success = 0x01,//设置主设备区域及SN成功
	Set_Area_and_SN_Failure = 0x02,//设置主设备区域及SN失败
	Set_subdevice_type_and_workgroup_success = 0x03,//设置子设备类型及工作组成功
	Set_subdevice_type_and_workgroup_failed = 0x04,//设置子设备类型及工作组失败
	Set_digital_output_status_success = 0x05,//设置数字输出状态成功
	Set_digital_output_status_failed = 0x06,//设置数字输出状态失败
	Set_analog_output_status_success = 0x07,//设置模拟输出成功
	Set_analog_output_status_failed = 0x08,//设置模拟输出失败
	Set_association_status_succeed = 0x09,//设置关联状态成功
	Set_association_status_failed = 0x0A ,//设置关联状态失败
	State_Storage_Exceeding_the_Upper_Limit = 0x0B,//关联状态失败，存储超上限
	Set_reserved_field_success = 0x0C,//设置预留字段成功
	Set_reserved_field_failed = 0x0D,//设置预留字段失败
	Data_loss_due_to_abnormal_power_off = 0x0E//异常断电数据丢失
}E020_status = FactoryMode;

//输出状态(结构类型，枚举)
static enum OUT_STATES
{
	DO1_ON = 1,//数字输出1开
	DO2_ON = 2,//数字输出2开
	DO3_ON = 3,//数字输出3开
	DO4_ON = 4,//数字输出4开
	AO1_ON = 5,//模拟输出1开
	AO2_ON = 6,//模拟输出2开

	Stateless = 0//无状态指令
}out_state = Stateless;

//union DEVICE_SN
//{
//	String str_SN;
//	byte SN[9];
//};
//DEVICE_SN Device_SN1, Device_SN2;

#endif

