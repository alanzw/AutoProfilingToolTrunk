#pragma once
//常用的头文件
#include "d3d9.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tchar.h"
#include "windows.h"
#include "fstream"
#include "ostream"
#include "vector"
#include "NtDDNdis.h"
#include "winioctl.h"
#include "adl_sdk\adl_sdk.h"
#include "nv_sdk\nvapi.h"


#define MAXSIZE 255
#define Freq_Interval 10
#define s_unit 1000

//设置AMD显卡相关的函数指针
typedef int (*ADL_MAIN_CONTROL_CREATE)(ADL_MAIN_MALLOC_CALLBACK callback,int iEnumConnectedAdapters);
typedef int (*ADL_MAIN_CONTROL_REFRESH)();
typedef int (*ADL_OVERDRIVE5_TEMPERATURE_GET)(int iAdapterIndex,int iThermalControllerIndex,ADLTemperature *lpTemperature);
typedef int (*ADL_OVERDRIVE5_CURRENTACTIVITY_GET)(int iAdapterIndex,ADLPMActivity *lpActivity);

typedef long long int64_t;



