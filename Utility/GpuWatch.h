#pragma once
#ifndef UTILITY_H
#define UTILITY_H
#include "utility.h"



////基类
//class GpuInterface
//{
//public:
//	virtual int GetGpuUsage(){	return -1;	};
//	virtual int GetGpuTemp(){	return -1;	};
//};


//获取显卡利用率和温度信息的类
class GpuWatch
{
public:
	GpuWatch(void);
	~GpuWatch(void);
	//初始化显卡
	static bool InitGpuInterface(void);
	static int GetGpuUsage();	//获取GPU利用率
	static int GetGpuTemp();	//获取GPU温度
	static void GetGpuInformation(char *buf,int size);	//获取GPU描述信息
	static int gpuUtilization , gpuTemp , graNum;	//gpu利用率和温度,显卡数目
	/*static GpuInterface* pInterface;*/
	static std::string graInfo;	//显卡信息
	static void ChangeToLower(std::string &str);
	static int type;

private:
	bool isInit;	//显卡是否已经初始化
};


//AMD显卡相关的类,继承GpuInterface类
class AMDInterface/*: public GpuInterface*/
{
public:
	AMDInterface(void);	//构造函数
	~AMDInterface();
	static void* _stdcall ADLMainMemoryAlloc(int size);	//申请空间
	static void _stdcall ADLMainMemoryFree(void **buf);	//释放空间

	int GetGpuUsage();	//获取GPU负载
	int GetGpuTemp();	//获取GPU温度

	//定义函数指针
	static ADL_MAIN_CONTROL_CREATE  AdlMainControlCreate;
	static ADL_MAIN_CONTROL_REFRESH AdlMainControlRefresh;
	static ADL_OVERDRIVE5_TEMPERATURE_GET AdlOverDrive5TemperatureGet;
	static ADL_OVERDRIVE5_CURRENTACTIVITY_GET AdlOverDrive5CurrentActivityGet;

private:
	bool InitAdlApi();	//初始化API
	bool isInit;	//是否已经初始化
};

//Nvidia显卡相关的类，继承GpuInterface类
class NvidiaInterface/*: public GpuInterface*/
{
public:
	NvidiaInterface(void);	//构造函数
	~NvidiaInterface();
	int GetGpuUsage();	//获取GPU利用率
	int GetGpuTemp();	//获取GPU温度

private:
	bool InitNvApi();	//初始化N卡
	bool isInit;
	NvPhysicalGpuHandle phys;
};

#endif
