//观测CPU信息的类
#include "StdAfx.h"
#include "CpuWatch.h"
#include "TlHelp32.h"

void CpuWatch::init(){
	last_sys_idle = 0;
	last_sys_user = 0;
	last_sys_kernel = 0;

	last_time = 0;
	last_sys_time = 0;
	processor_num = 0;
}

CpuWatch::CpuWatch(void)
{
	memset(processName,0,sizeof(processName));
	init();
	this->processor_num = this->GetProcessorNum();
}

CpuWatch::CpuWatch(char *procName)
{
	//初始化进程名
	memcpy(processName,procName,strlen(procName));
	init();
	procName[strlen(procName)]='\0';
}

CpuWatch::~CpuWatch(void)
{

}

//时间转换函数
int64_t CpuWatch::FileTimeToDouble(FILETIME &t)
{
	LARGE_INTEGER li;
	li.LowPart = t.dwLowDateTime;
	li.HighPart = t.dwHighDateTime;
	return li.QuadPart;

}

//获取CPU核数
unsigned int CpuWatch::GetProcessorNum()
{
	SYSTEM_INFO sys;
	GetSystemInfo(&sys);
	return sys.dwNumberOfProcessors;
}

//获取CPU频率
int64_t CpuWatch::GetCpuFreq()
{
	long start,end;
	_asm{
		RDTSC
			mov start,eax
	}
	Sleep(Freq_Interval);
	
	_asm{
		RDTSC
			mov end,eax
	}
	return ((end-start)/Freq_Interval)/s_unit/1000;
}

//获取系统CPU利用率
double CpuWatch::GetSysCpuUtilization()
{
	FILETIME idle,kernel,user;
	int64_t idleT,kernelT,userT;
	double cpuUtilization=0.0;
	//获取系统时间
	if(!GetSystemTimes(&idle,&kernel,&user))
	{

		return -1;
	}
	idleT = FileTimeToDouble(idle);
	kernelT=FileTimeToDouble(kernel);
	userT=FileTimeToDouble(user);
	
	if( (last_sys_user==0) ||(last_sys_kernel==0) ||(last_sys_idle==0) )
	{
		last_sys_user = userT;
		last_sys_kernel = kernelT;
		last_sys_idle = idleT;
		return -1;
	} 
	cpuUtilization = (double)(1-(double)(idleT-last_sys_idle)/(double)(kernelT-last_sys_kernel+userT-last_sys_user))*100;
	
	last_sys_user = userT;
	last_sys_kernel = kernelT;
	last_sys_idle = idleT;

	return cpuUtilization;	//返回CPU利用率
}

double CpuWatch::GetProcessCpuUtilization(HANDLE process){
	FILETIME now, create, exit, kernel, user;
	int64_t sys_time, time, time_delay;
	double pcpuUtilization = 0.0;

	if (!process){
		return -1;

	}
	//获取当前系统时间
	GetSystemTimeAsFileTime(&now);
	if (!GetProcessTimes(process, &create, &exit, &kernel, &user))
	{
		return -1;
	}
	//系统时间
	sys_time = (FileTimeToDouble(kernel) + FileTimeToDouble(user)) / processor_num;
	//当前时间
	time = FileTimeToDouble(now);

	if ((last_time == 0) || (last_sys_time == 0))
	{
		last_time = time;
		last_sys_time = sys_time;
		return -1;
	}

	time_delay = time - last_time;
	if (time_delay <= 0)
		return -1;
	pcpuUtilization = (double)((double)(sys_time - last_sys_time) / time_delay) * 100;

	last_sys_time = sys_time;
	last_time = time;

	return pcpuUtilization;
}

int CpuWatch::getCpuUtilization(HANDLE hProcess, double &processCpu, double & systemCpu){
	processCpu = -1;
	systemCpu = -1;
	int ret = 0;
	if (!hProcess){
		ret = 1;
		processCpu = this->GetProcessCpuUtilization(hProcess);
	}
	else{
		ret = 2;
	}
	systemCpu = this->GetSysCpuUtilization();
	return ret;
}

//获取进程CPU利用率
double CpuWatch::GetProcessCpuUtilization()
{
	FILETIME now,create,exit,kernel,user;
	int64_t sys_time,time,time_delay;
	double pcpuUtilization = 0.0;
	HANDLE hProcess = GetProcH();
	//没有设置进程名
	if(!hProcess)
			return -1;
	if(processor_num == 0)
	{
		processor_num = GetProcessorNum();	//获取CPU核数
	}
	//获取当前系统时间
	GetSystemTimeAsFileTime(&now);
	if(!GetProcessTimes(hProcess,&create,&exit,&kernel,&user))
	{
		return -1;
	}
	//系统时间
	sys_time = (FileTimeToDouble(kernel)+FileTimeToDouble(user))/processor_num;
	//当前时间
	time = FileTimeToDouble(now);

	if( (last_time == 0) || ( last_sys_time == 0) )
	{
		last_time = time;
		last_sys_time =sys_time;
		return -1;
	}

	time_delay = time -last_time;
	if(time_delay<=0)
		return -1;
	pcpuUtilization = (double)((double)(sys_time - last_sys_time)/time_delay)*100;
	
	last_sys_time = sys_time;
	last_time = time;

	return pcpuUtilization;
}

//根据进程名获取进程句柄，使用已经设置的进程名
HANDLE CpuWatch::GetProcH()
{
	if(strcmp("",processName))
		return getProcH(processName);
	return NULL;
}

//根据进程名获取进程ID，普适函数
HANDLE CpuWatch::getProcH(char *procName)
{
	HANDLE hsnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 processInfo;
	if(!hsnapshot)
		return NULL;
	if(!Process32First(hsnapshot,&processInfo))
		return NULL;
	do
	{
		//找到进程
		if(!strcmp(processInfo.szExeFile,procName))
		{
			CloseHandle(hsnapshot);
			return OpenProcess(PROCESS_ALL_ACCESS,false,processInfo.th32ProcessID);	//获取进程句柄
		}
	}while(Process32Next(hsnapshot,&processInfo));
	
	CloseHandle(hsnapshot);
	return NULL;
}


//设置进程名
void CpuWatch::SetProcName(char *input)
{
	memcpy(processName,input,strlen(input));
	processName[strlen(input)]='\0';
}






