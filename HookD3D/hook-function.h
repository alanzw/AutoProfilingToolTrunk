#ifndef __HOOK_FUNCTION_H__
#define __HOOK_FUNCTION_H__

#pragma once
#include "../utility/log.h"
#include "hookcommon.h"
#include "lightweightreocder.h"
#include "inforecoder.h"

#define HOOKALL

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3d10_1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "nvapi.lib")
#pragma comment(lib, "winmm.lib")

//extern Log * logger;
extern InfoRecorder * infoRecorder;
//
extern TDirect3DCreate9		pD3d;
extern TD3D9CreateDevice	pD3D9CreateDevice;
extern TD3D9GetSwapChain	pD3D9GetSwapChain;
extern TD3D9DevicePresent	pD3D9DevicePresent;
extern TSwapChainPresent	pSwapChainPresent;

extern TD3D10CreateDeviceAndSwapChain pD3D10CreateDeviceAndSwapChain;
extern TD3D10CreateDeviceAndSwapChain1 pD3D10CreateDeviceAndSwapChain1;
extern TD3D11CreateDeviceAndSwapChain pD3D11CreateDeviceAndSwapChain;
extern TCreateDXGIFactory pCreateDXGIFactory;

extern void release_hook_resources();

// --- DirectX 9 ---
DllExport IDirect3D9* WINAPI hook_d3d(UINT SDKVersion);

DllExport HRESULT __stdcall hook_D3D9CreateDevice(
	IDirect3DDevice9 * This,
	UINT Adapter,
	D3DDEVTYPE DeviceType,
	HWND hFocusWindow,
	DWORD BehaviorFlags,
	D3DPRESENT_PARAMETERS *pPresentationParameters,
	IDirect3DDevice9 **ppReturnedDeviceInterface
);

DllExport HRESULT __stdcall hook_D3D9GetSwapChain(
	IDirect3DDevice9 *This,
	UINT iSwapChain,
	IDirect3DSwapChain9 **ppSwapChain
);

DllExport HRESULT __stdcall hook_D3D9SwapChainPresent(
	IDirect3DSwapChain9 * This,
	CONST RECT* pSourceRect,
	CONST RECT* pDestRect,
	HWND hDestWindowOverride,
	CONST RGNDATA* pDirtyRegion,
	DWORD dwFlags
);

DllExport HRESULT __stdcall hook_D3D9DevicePresent(
	IDirect3DDevice9 * This,
	CONST RECT* pSourceRect,
	CONST RECT* pDestRect,
	HWND hDestWindowOverride,
	CONST RGNDATA* pDirtyRegion
);

#ifdef HOOKALL

// ---- DXGI -----
DllExport HRESULT __stdcall hook_CreateDXGIFactory(REFIID riid, void ** ppFactory);

DllExport HRESULT __stdcall hook_DXGICreateSwapChain(IDXGIFactory * This, IUnknown * pDevice, DXGI_SWAP_CHAIN_DESC * pDesc, IDXGISwapChain ** ppSwapChain);

// --- directx 10 / 10.1 / 11 -----
DllExport HRESULT __stdcall hook_D3D10CreateDeviceAndSwapChain(IDXGIAdapter * pAdapter, D3D10_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, UINT SDKVersion, DXGI_SWAP_CHAIN_DESC * pSwapChainDesc, IDXGISwapChain ** ppSwapChain, ID3D10Device ** ppDevice);

DllExport HRESULT __stdcall hook_D3D10CreateDeviceAndSwapChain1(IDXGIAdapter * pAdapter, D3D10_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, D3D10_FEATURE_LEVEL1 HardwareLevel, UINT SDKVersion, DXGI_SWAP_CHAIN_DESC * pSwapChainDesc, IDXGISwapChain ** ppSwapChain, ID3D10Device1 ** ppDevice);

DllExport HRESULT __stdcall hook_D3D11CreateDeviceAndSwapChain(IDXGIAdapter * pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL * pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC * pSwapChainDesc, IDXGISwapChain ** ppSwapChain, ID3D11Device ** ppDevice, D3D_FEATURE_LEVEL * pFeatureLevel, ID3D11DeviceContext **ppImmediateContext);

// ----

DllExport HRESULT __stdcall hook_DXGISwapChainPresent(IDXGISwapChain * This, UINT SyncInterval, UINT Flags);

#endif


void get_proc_name();

extern CpuWatch observe_cpu;
extern GpuWatch observe_gpu;
#if 0
IDirect3D9* (WINAPI* Direct3DCreate9Next)(UINT SDKVersion);

IDirect3D9* WINAPI Direct3DCreate9Callback(UINT SDKVersion);
#endif

void WINAPI ExitProcessCallback(UINT uExitCode);


/// global varibles  

extern bool rateControl;
extern int maxFps;


#endif
