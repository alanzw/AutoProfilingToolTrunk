
#include <stdio.h>
#include <assert.h>

#include "hook-function.h"

int frame_cnt = 0;
double elapse_time = 0.0f;
double last_time = 0.0f;

extern InfoRecorder * infoRecorder;
extern bool rateControl;

//Log * logger = NULL;

// --- DirectX 9 ---
TDirect3DCreate9 pD3d = Direct3DCreate9;
TD3D9CreateDevice pD3D9CreateDevice = NULL;
TD3D9GetSwapChain pD3D9GetSwapChain = NULL;
TD3D9DevicePresent pD3D9DevicePresent = NULL;
TSwapChainPresent pSwapChainPresent = NULL;

D3DFORMAT pD3DFORMAT = D3DFMT_UNKNOWN;
//DXGI_FORMAT pDXGI_FORMAT = DXGI_FORMAT_UNKNOWN;
// ------ directx 10 / 10.1
TD3D10CreateDeviceAndSwapChain pD3D10CreateDeviceAndSwapChain = NULL;
TD3D10CreateDeviceAndSwapChain1 pD3D10CreateDeviceAndSwapChain1 = NULL;

// ------ directx 11
TD3D11CreateDeviceAndSwapChain pD3D11CreateDeviceAndSwapChain = NULL;

// ------ DXGI -----
TDXGISwapChainPresent pDXGISwapChainPresent = NULL;
DXGI_FORMAT pDXGI_FORMAT = DXGI_FORMAT_UNKNOWN;
TCreateDXGIFactory pCreateDXGIFactory = NULL;
TDXGICreateSwapChain pDXGICreateSwapChain = NULL;

//////// internal functions

static IDirect3DSurface9 *resolvedSurface = NULL;
static IDirect3DSurface9 *offscreenSurface = NULL;

//////// hook functions

// Detour function that replaces the Direct3DCreate9() API
DllExport IDirect3D9* WINAPI
hook_d3d(UINT SDKVersion)
{
	static int hooked_d3d9 = 0;
	//create device
	IDirect3D9 *pDirect3D9 = pD3d(SDKVersion);

	if (hooked_d3d9 > 0)
		return pDirect3D9;

	hooked_d3d9 = 1;

	if (pD3D9CreateDevice == NULL) {
		//Log::slog("[Direct3DCreate9]\n");
#if 0
		infoRecorder->logFrame("\t\tcpu_utilization\t\tgpu_utilization\t\t fps\n");
		infoRecorder->logSecond("\t\tcpu_utilization\t\tgpu_utilization\t\t fps\n");
#endif
		//logger->log("\t\tcpu_utilization\t\tgpu_utilization\t\t fps\n");
		uintptr_t* pInterfaceVTable = (uintptr_t*)*(uintptr_t*)pDirect3D9;
		pD3D9CreateDevice = (TD3D9CreateDevice) pInterfaceVTable[16];   // IDirect3D9::CreateDevice()

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pD3D9CreateDevice, hook_D3D9CreateDevice);
		if(DetourTransactionCommit()==NO_ERROR)
		{
			//Log::slog("hook IDirect3D9::CreateDevice() succeed!\n");
		}
	}
	return pDirect3D9;
}

// Detour function that replaces the IDirect3D9::CreateDevice() API
DllExport HRESULT __stdcall
hook_D3D9CreateDevice(
		IDirect3DDevice9 * This,
		UINT Adapter,
		D3DDEVTYPE DeviceType,
		HWND hFocusWindow,
		DWORD BehaviorFlags,
		D3DPRESENT_PARAMETERS *pPresentationParameters,
		IDirect3DDevice9 **ppReturnedDeviceInterface
	)
{
	static int createdevice_hooked = 0;

	HRESULT hr = pD3D9CreateDevice(This, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	
	if(createdevice_hooked > 0)
		return hr;

	if(FAILED(hr))
		return hr;

	if (pD3D9DevicePresent == NULL) {
		uintptr_t* pInterfaceVTable = (uintptr_t*)*(uintptr_t*)*ppReturnedDeviceInterface;

		// 14: IDirect3DDevice9::GetSwapChain,  17: IDirect3DDevice9::Present
		// 41: IDirect3DDevice9::BeginScene,    42: IDirect3DDevice9::EndScene
		pD3D9GetSwapChain = (TD3D9GetSwapChain)pInterfaceVTable[14];
		pD3D9DevicePresent = (TD3D9DevicePresent)pInterfaceVTable[17];  
		/*pD3D9BeginScene =(TD3D9BeginScene)pInterfaceVTable[41];*/
		/*pD3D9EndScene =(TD3D9EndScene)pInterfaceVTable[42];*/
		
#if 0
		pRelease = (TRelease) pInterfaceVTable[2];	// IDirect3DDevice9::Release();
#endif

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pD3D9GetSwapChain, hook_D3D9GetSwapChain);
		DetourAttach(&(PVOID&)pD3D9DevicePresent, hook_D3D9DevicePresent);
		/*DetourAttach(&(PVOID&)pD3D9BeginScene, hook_D3D9BeginScene);*/
		if(DetourTransactionCommit()==NO_ERROR)
		{
			//Log::slog("hook IDirect3DDevice9::GetSwapChain IDirect3DDevice9::Present IDirect3DDevice9::BeginScene succeed!\n");
		}
	}

	createdevice_hooked = 1;

	return hr;
}

// Detour function that replaces the IDirect3dDevice9::GetSwapChain() API
DllExport HRESULT __stdcall hook_D3D9GetSwapChain(
		IDirect3DDevice9 *This,
		UINT iSwapChain,
		IDirect3DSwapChain9 **ppSwapChain
	)
{
	static int getswapchain_hooked = 0;

	HRESULT hr = pD3D9GetSwapChain(This, iSwapChain, ppSwapChain);
	
	if (getswapchain_hooked > 0)
		return hr;

	getswapchain_hooked = 1;

	if (ppSwapChain != NULL && pSwapChainPresent == NULL) {
		OutputDebugString("[IDirect3dDevice9::GetSwapChain]\n");

		IDirect3DSwapChain9 *pIDirect3DSwapChain9 = *ppSwapChain;
		uintptr_t* pInterfaceVTable = (uintptr_t*)*(uintptr_t*)pIDirect3DSwapChain9;  // IDirect3dSwapChain9
		uintptr_t* ppSwapChainPresent = (uintptr_t*)pInterfaceVTable[3];   // IDirect3DSwapChain9::Present
		pSwapChainPresent = (TSwapChainPresent) ppSwapChainPresent;

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pSwapChainPresent, hook_D3D9SwapChainPresent);
		DetourTransactionCommit();
	}
	return hr;
}


void onPresent(){
	frame_cnt++;
	//frame_cnt++;
	//double tmp_render_time = cal_run_time(begin_t,end_t,Frequency);
	//render_time_log.log("\t\t%.1f\n",tmp_render_time);	//per frame render time
	//sum_render_time +=tmp_render_time;
	//if( frame_num == STATISTIC_FRAMES )
	//{
	//	render_time_log.log("sum_render_time:\t\t%.1f\n",sum_render_time);
	//	sum_render_time = 0;
	//}
	/////////////////caculate fps

	/////////////////////////////////////////////////////////////////////
	//limit it to max_fps
	double frame_time = 0.0f;
	if (last_time)
	{
		double cur_time = (float)timeGetTime();
		frame_time = cur_time - last_time;
		elapse_time += frame_time;
		last_time = cur_time;
	}
	else
	{
		last_time = (float)timeGetTime();
	}

	////limit it to max_fps
	double to_sleep = 0.0f;
	if (rateControl){
		to_sleep = 1000.0 / maxFps * frame_cnt - elapse_time;
		if (to_sleep > 0) {
			Sleep((DWORD)to_sleep);
		}
	}

	float fps = 0.0f;

	if (elapse_time >= TIME_INTERVAL)
	{
		fps = frame_cnt * 1000.0 / elapse_time;
		frame_cnt = 0;
		elapse_time = 0;
		//logger->log("\t\t%8f\t\t%8d\t\t%8f\n", observe_cpu.GetProcessCpuUtilization(GetCurrentProcess()), observe_gpu.GetGpuUsage(), fps);
	}
	infoRecorder->onFrameEnd();
}


// Detour function that replaces the IDirect3dSwapChain9::Present() API
DllExport HRESULT __stdcall hook_D3D9SwapChainPresent(
		IDirect3DSwapChain9 * This,
		CONST RECT* pSourceRect,
		CONST RECT* pDestRect,
		HWND hDestWindowOverride,
		CONST RGNDATA* pDirtyRegion,
		DWORD dwFlags
	)
{
	static int present_hooked = 0;
	IDirect3DDevice9 *pDevice;

	if (present_hooked == 0) {
		//Log::slog("[IDirect3dSwapChain9::Present()]");
		present_hooked = 1;
	}

	HRESULT hr = pSwapChainPresent(This, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);

	onPresent();

	This->GetDevice(&pDevice);
	pDevice->Release();
	return hr;
}


// Detour function that replaces the IDirect3dDevice9::Present() API
DllExport HRESULT __stdcall hook_D3D9DevicePresent(
		IDirect3DDevice9 * This,
		CONST RECT* pSourceRect,
		CONST RECT* pDestRect,
		HWND hDestWindowOverride,
		CONST RGNDATA* pDirtyRegion
	)
{
	/////////////////////////////////////////
	//if(!freq_inited)
	//{
	//	QueryPerformanceFrequency(&Frequency);
	//	freq_inited = 1;
	//}
	//if(frame_num!=0)
	//{
	//	QueryPerformanceCounter(&cur_present_time);
	//	double tmp_respond_time = cal_run_time(frame_end,cur_present_time,Frequency);
	//	if( tmp_respond_time>0 )
	//	{
	//		present_response_log.log("\t\t%.1f\n",tmp_respond_time);
	//		sum_response_time +=tmp_respond_time;
	//	}

	//	if( frame_num == STATISTIC_FRAMES )
	//	{
	//		present_response_log.log("sum_present_response_time:\t\t%.1f\n",sum_response_time);
	//		sum_response_time = 0;
	//	}
	//}
	//////////////////////////
	static int present_hooked = 0;

	if (present_hooked == 0) {
		//Log::slog("[IDirect3dDevice9::Present()]\n");
		present_hooked = 1;
	}
	/////////////////////////////////////////////////////
	HRESULT hr = pD3D9DevicePresent(This, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	
	/*QueryPerformanceCounter(&end_t);*/
	//infoRecorder->onFrameEnd();
	onPresent();
	////////////////////////////////////////////////////
	//QueryPerformanceCounter(&frame_end);
	return hr;
}

#ifdef HOOKALL

enum DX_VERSION{
	dx_none = 0,
	dx_9,
	dx_10,
	dx_10_1,
	dx_11
};

static enum DX_VERSION dx_version = dx_none;

void proc_hook_IDXGISwapChain_Present(IDXGISwapChain * ppSwapChain){
	uintptr_t * pInterfaceVTable = (uintptr_t *)*(uintptr_t *)ppSwapChain;
	pDXGISwapChainPresent = (TDXGISwapChainPresent)pInterfaceVTable[8];

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)pDXGISwapChainPresent, hook_DXGISwapChainPresent);
	DetourTransactionCommit();
}

// detour function that replace the CreateDXGIFactorh() API
DllExport HRESULT __stdcall hook_CreateDXGIFactory(REFIID riid, void **ppFactory){
	HRESULT hr = pCreateDXGIFactory(riid, ppFactory);
	if (pDXGICreateSwapChain == NULL && riid == IID_IDXGIFactory && ppFactory != NULL){

		uintptr_t * pInterfaceVTable = (uintptr_t *)*(uintptr_t *)*ppFactory;
		pDXGICreateSwapChain = (TDXGICreateSwapChain)pInterfaceVTable[10];
		// 10: IDXGIFactory::CreateSwapChain
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(LPVOID&)pDXGICreateSwapChain, hook_DXGICreateSwapChain);
		DetourTransactionCommit();
	}
	return hr;
}

// detour function that replaces the IDXGIFactory::CreateSwapChain API
DllExport HRESULT __stdcall hook_DXGICreateSwapChain(IDXGIFactory * This, IUnknown *pDevice, DXGI_SWAP_CHAIN_DESC * pDesc, IDXGISwapChain ** ppSwapChain){
	HRESULT hr = pDXGICreateSwapChain(This, pDevice, pDesc, ppSwapChain);
	if (pDXGISwapChainPresent == NULL && pDevice != NULL && ppSwapChain != NULL){
		proc_hook_IDXGISwapChain_Present(*ppSwapChain);
	}
	return hr;
}

// detour function that replaces the D3D10CreateDeviceAndSwapChain() API
DllExport HRESULT __stdcall hook_D3D10CreateDeviceAndSwapChain(IDXGIAdapter * pAdapter, D3D10_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, UINT SDKVersion, DXGI_SWAP_CHAIN_DESC * pSwapChainDesc, IDXGISwapChain ** ppSwapChain, ID3D10Device ** ppDevice){
	HRESULT hr = pD3D10CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice);
	if (pDXGISwapChainPresent == NULL && pAdapter != NULL && ppSwapChain != NULL && ppDevice != NULL){
		proc_hook_IDXGISwapChain_Present(*ppSwapChain);
	}
	return hr;
}

// detour function that replaces the D3D10CreateDeviceSwapChain1() API
DllExport HRESULT __stdcall hook_D3D10CreateDeviceAndSwapChain1(IDXGIAdapter * pAdapter, D3D10_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, D3D10_FEATURE_LEVEL1 HardwareLevel, UINT SDKVersion, DXGI_SWAP_CHAIN_DESC * pSwapChainDesc, IDXGISwapChain ** ppSwapChain, ID3D10Device1 ** ppDevice){
	HRESULT hr = pD3D10CreateDeviceAndSwapChain1(pAdapter, DriverType, Software, Flags, HardwareLevel, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice);

	if (pDXGISwapChainPresent == NULL && pAdapter != NULL && ppSwapChain != NULL && ppDevice != NULL){
		proc_hook_IDXGISwapChain_Present(*ppSwapChain);
	}
	return hr;

}

// detour function that replaces the D3D11CreateDeviceAndSwapChain() API
DllExport HRESULT __stdcall hook_D3D11CreateDeviceAndSwapChain(IDXGIAdapter *pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL * pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc, IDXGISwapChain** ppSwapChain, ID3D11Device ** ppDevice, D3D_FEATURE_LEVEL * pFeatureLevel, ID3D11DeviceContext ** ppImmediateContext){
	HRESULT hr = pD3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
	if (pDXGISwapChainPresent == NULL && pAdapter != NULL && ppSwapChain != NULL && ppDevice != NULL){
		proc_hook_IDXGISwapChain_Present(*ppSwapChain);

	}
	return hr;
}

bool check_dx_device_version(IDXGISwapChain * This, const GUID IID_target){
	IUnknown * pDevice = NULL;
	HRESULT hr;

	if (dx_version != dx_none){
		return false;
	}

	hr = This->GetDevice(IID_target, (void **)&pDevice);
	if (FAILED(hr) || pDevice == NULL){
		// failed to get the device
		pDevice->Release();
		return false;
	}

	pDevice->Release();
	return true;
}


// detour function that replaces the IDXGISwapChain::Present() API
DllExport HRESULT __stdcall hook_DXGISwapChainPresent(IDXGISwapChain * This, UINT SyncInterval, UINT Flags){
	static int frame_interval;
	static LARGE_INTEGER initialTv, captureTv, freq;
	static int capture_initialized = 0;

	int i;
	

	DXGI_SWAP_CHAIN_DESC pDESC;
	HRESULT hr = pDXGISwapChainPresent(This, SyncInterval, Flags);


	This->GetDesc(&pDESC);
	pDXGI_FORMAT = pDESC.BufferDesc.Format; 

	if (dx_version == dx_none){
		if (check_dx_device_version(This, IID_ID3D10Device)){
			dx_version = dx_10;
		}
		else if (check_dx_device_version(This, IID_ID3D10Device1)){
			dx_version = dx_10_1;
		}
		else if (check_dx_device_version(This, IID_ID3D11Device)){
			dx_version = dx_11;
		}
	}
	hr = 0;

	onPresent();

	// d3d10 / d3d10.1
	if (dx_version == dx_10 || dx_version == dx_10_1){

	}

	return S_OK;
}


#endif

static double cal_run_time(
	LARGE_INTEGER begin,
	LARGE_INTEGER end,LARGE_INTEGER freq)
{
	return (double)((double)( end.QuadPart - begin.QuadPart )*1000/(double)freq.QuadPart);
}
#if 0
void get_proc_name()
{
	char tmp[255];
	memset(tmp,0,sizeof(tmp));
	int pos=0;
	::GetModuleFileNameA(NULL,static_cast<LPTSTR>(process_name),sizeof(process_name));
	process_name[strlen(process_name)]='\0';
	for(int i = strlen(process_name)-1;i>0;i--)
	{
		if(process_name[i]=='\\')
			break;
		pos++;
	}
	
	memcpy(tmp,process_name+strlen(process_name)-pos,pos);
	observe_cpu.SetProcName(tmp);
	proc_name_fetched = 1;
}
#endif