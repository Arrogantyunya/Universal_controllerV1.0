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
unsigned char Send_E020(int Receive_IsBroadcast,int E020_status );  //E020函数
unsigned char E020_init();	//E011初始化函数
unsigned char SN_ZoneISOK(unsigned char * Judgement_Data, int Judgement_Length);	//测试SN区域是否写入成功函数


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
	Digital_output_device1_turn_on = 0x0E,//数字输出设备1开启
	Digital_output_device1_turn_off = 0x0F,//数字输出设备1关闭
	Digital_output_device2_turn_on = 0x10,//数字输出设备2开启
	Digital_output_device2_turn_off = 0x11,//数字输出设备2关闭
	Analog_output_device1_turn_on = 0x12,//模拟输出设备1开启
	Analog_output_device1_turn_off = 0x13,//模拟输出设备1关闭
	Analog_output_device2_turn_on = 0x14,//模拟输出设备1开启
	Analog_output_device2_turn_off = 0x15,//模拟输出设备1关闭
	Data_loss_due_to_abnormal_power_off = 0x16//异常断电数据丢失
}E020_status = FactoryMode;

////继电器的状态(结构类型，枚举)
//static enum RD1S
//{
//	KCZJ1_ON = 1,//继电器1开
//	KCZJ2_ON = 2,//继电器2开
//	LED2_ON = 3,//LED2开								
//	Stateless = 0//无状态指令
//}rd1 = Stateless;

//union DEVICE_SN
//{
//	String str_SN;
//	byte SN[9];
//};
//DEVICE_SN Device_SN1, Device_SN2;

#endif

