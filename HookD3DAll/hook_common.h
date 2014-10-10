#ifndef __HOOK_COMMON_H__

#define __HOOK_COMMON_H__

#include <d3d9.h>
#include <d3dx9.h>
#include <typeinfo.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "comctl32.lib")

#define COM_METHOD(TYPE, METHOD) TYPE STDMETHODCALLTYPE METHOD

#include "detours\detours.h"
#pragma comment(lib, "detours/detours.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "nvapi.lib")

extern IDirect3D9* (WINAPI* Direct3DCreate9Next)(UINT SDKVersion);

IDirect3D9* WINAPI Direct3DCreate9Callback(UINT SDKVersion);
void WINAPI ExitProcessCallback(UINT uExitCode);

//#define GETWRAPPERDEVICE

#endif