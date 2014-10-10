#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3d9.h"
#include "wrap_direct3ddevice9.h"

IDirect3DDevice9 * cur_d3ddevice = NULL;
D3DCAPS9 d3d_caps;
bool GetDeviceCapsCalled = false;

int WrapperDirect3D9::ins_count = 0;
HashSet WrapperDirect3D9::m_list;

WrapperDirect3D9::WrapperDirect3D9(IDirect3D9* ptr, int _id): m_d3d(ptr), id(_id) {

	m_list.AddMember(ptr, this);
}

inline int WrapperDirect3D9::GetID() {
	return this->id;
}

inline void WrapperDirect3D9::SetID(int id) {
	this->id = id;
}
#ifdef GETWRAPPERDEVICE
WrapperDirect3D9* WrapperDirect3D9::GetWrapperD3D9(IDirect3D9* ptr) {
	gRecoder->logTrace("[INFO]: Direct call GetWrapperD3D9.\n");
#if 1
	WrapperDirect3D9* ret = (WrapperDirect3D9*)( m_list.GetDataPtr((PVOID)ptr) );
	if(ret == NULL) {
		ret = new WrapperDirect3D9(ptr, ins_count++);
		gRecoder->logTrace("[INFO]: create new Direct3D? id:%d\n", WrapperDirect3D9::ins_count);
		m_list.AddMember(ptr, ret);
	}
#else
	WrapperDirect3D9 * ret = (WrapperDirect3D9 *);
#endif
	gRecoder->logTrace("[INFO]: Direct edn GetWrapperD3D9.\n");
	return ret;
}
#endif

STDMETHODIMP WrapperDirect3D9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: Direct call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_d3d->QueryInterface(riid,ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: Direct end QueryInterface.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3D9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: Direct AddRef.\n");
	gRecoder->cmdCalled(0);
	HRESULT hr = m_d3d->AddRef();
	gRecoder->logTrace("[INFO]: Direct end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3D9::Release(THIS) {
	gRecoder->logTrace("[INFO]: Direct call Release.\n");
	gRecoder->cmdCalled(0);
	HRESULT hr = m_d3d->Release();
	gRecoder->logTrace("[INFO]: Direct end Release.\n");
	return hr;
}

/*** IDirect3D9 methods ***/
STDMETHODIMP WrapperDirect3D9::RegisterSoftwareDevice(THIS_ void* pInitializeFunction) {
	gRecoder->logTrace("[INFO]: Direct call RegisterSoftwareDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr = m_d3d->RegisterSoftwareDevice(pInitializeFunction);
	gRecoder->logTrace("[INFO]: Direct end RegisterSoftwareDevice.\n");
	return hr;
}
STDMETHODIMP_(UINT) WrapperDirect3D9::GetAdapterCount(THIS) {
	gRecoder->logTrace("[INFO]: Direct call GetAdaperCount.\n");
	gRecoder->cmdCalled(sizeof(UINT));
	UINT ret = m_d3d->GetAdapterCount();
	gRecoder->logTrace("[INFO]: Direct end GetAdapterCount.\n");
	return ret;
}

STDMETHODIMP WrapperDirect3D9::GetAdapterIdentifier(THIS_ UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier) {
	gRecoder->logTrace("[INFO]: Direct call GetAdapterIdentifier.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(DWORD)+sizeof(D3DADAPTER_IDENTIFIER9));
	HRESULT hr = m_d3d->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
	gRecoder->logTrace("[INFO]: Direct end GetAdapterIdentifier.\n");
	return hr;
}

STDMETHODIMP_(UINT) WrapperDirect3D9::GetAdapterModeCount(THIS_ UINT Adapter,D3DFORMAT Format) {
	gRecoder->logTrace("[INFO]: Direct call GetAdapterModeCount.\n");
	gRecoder->cmdCalled(sizeof(UINT) * 2 + sizeof(D3DFORMAT));
	UINT ret= m_d3d->GetAdapterModeCount(Adapter, Format);
	gRecoder->logTrace("[INFO]: Direct end GetAdapterModeCount.\n");
	return ret;
}

STDMETHODIMP WrapperDirect3D9::EnumAdapterModes(THIS_ UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) {
	gRecoder->logTrace("[INFO]: Direct call EnumAdapterModes.\n");
	gRecoder->cmdCalled(sizeof(UINT) * 2 + sizeof(D3DDISPLAYMODE));
	HRESULT hr = m_d3d->EnumAdapterModes(Adapter, Format, Mode, pMode);
	gRecoder->logTrace("[INFO]: Direct end EnumAdapterModes.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::GetAdapterDisplayMode(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) {
	gRecoder->logTrace("[INFO]: Direct call GetAdapterDisplayMode.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DDISPLAYMODE));
	HRESULT hr = m_d3d->GetAdapterDisplayMode(Adapter, pMode);
	gRecoder->logTrace("[INFO]: Direct end GetAdapterDisaplayMode.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::CheckDeviceType(THIS_ UINT Adapter,D3DDEVTYPE DevType,D3DFORMAT AdapterFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) {
	gRecoder->logTrace("[INFO]: Direct call CheckDeviceType.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DDEVTYPE) + sizeof(D3DFORMAT) * 2 + sizeof(BOOL));
	HRESULT hr = m_d3d->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
	gRecoder->logTrace("[INFO]: Direct end CheckDeviceType.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::CheckDeviceFormat(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) {
	gRecoder->logTrace("[INFO]: Direct call CheckDeviceFormat.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DDEVTYPE) + sizeof(D3DFORMAT) * 2 + sizeof(DWORD) + sizeof(D3DRESOURCETYPE));
	HRESULT hr = m_d3d->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
	static int checkCount = 0;
	if(CheckFormat == 827611204){
		checkCount++;
		if(checkCount >= 7){
			//DebugBreak();
		}
	}

	gRecoder->logTrace("[INFO]: check device foramt(%d, %d, %d, %d, %d, %d).\n", Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
	gRecoder->logTrace("[INFO]: Direct end CheckDeviceFormat.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::CheckDeviceMultiSampleType(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) {
	gRecoder->logTrace("[INFO]: Direct call CheckDeviceMultiSampleType.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DDEVTYPE) + sizeof(D3DFORMAT) + sizeof(BOOL) + sizeof(D3DMULTISAMPLE_TYPE) + sizeof(DWORD) + sizeof(void *));
	HRESULT hr = m_d3d->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
	gRecoder->logTrace("[INFO]: Direct end CheckDeviceMultiSampleType.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::CheckDepthStencilMatch(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) {
	gRecoder->logTrace("[INFO]: Direct call CheckDepthStencilMatch.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DDEVTYPE) + sizeof(D3DFORMAT) * 3);
	HRESULT hr = m_d3d->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
	gRecoder->logTrace("[INFO]: Direct end CheckDepthStencilMatch.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::CheckDeviceFormatConversion(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat) {
	gRecoder->logTrace("[INFO]: Direct call CheckDeviceFormatConversion.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DDEVTYPE) + sizeof(D3DFORMAT) * 2);
	HRESULT hr = m_d3d->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
	gRecoder->logTrace("[INFO]: Direct end CheckDeviceFormatConversion.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::GetDeviceCaps(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) {
	gRecoder->logTrace("[INFO]: Direct call GetDevideCaps.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DDEVTYPE) + sizeof(D3DCAPS9) + sizeof(void *));
	HRESULT hr =m_d3d->GetDeviceCaps(Adapter, DeviceType, pCaps);
	gRecoder->logTrace("[INFO]: Direct end GetDeviceCaps.\n");
	return hr;
}

STDMETHODIMP_(HMONITOR) WrapperDirect3D9::GetAdapterMonitor(THIS_ UINT Adapter) {
	gRecoder->logTrace("[INFO]: Direct call GetAdapterMonitor.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(HMONITOR));
	HMONITOR hr = m_d3d->GetAdapterMonitor(Adapter);
	gRecoder->logTrace("[INFO]: Direct end GetAdapterMonitor.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3D9::CreateDevice(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) {
	gRecoder->logTrace("[INFO]: Direct call CreateDevice.\n");
	gRecoder->cmdSendAndCalled(sizeof(UINT) + sizeof(D3DDEVTYPE) + sizeof(HWND) + sizeof(DWORD) + sizeof(D3DPRESENT_PARAMETERS));

	IDirect3DDevice9* base_device = NULL;
	
	HRESULT hr = m_d3d->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, &base_device);
	cur_d3ddevice = base_device;

	WrapperDirect3DDevice9 * wdd = NULL;
	if(SUCCEEDED(hr)) {
		//MessageBox(NULL, "success", NULL, MB_OK);
		wdd = new WrapperDirect3DDevice9(base_device, WrapperDirect3DDevice9::ins_count++);
		*ppReturnedDeviceInterface = static_cast<IDirect3DDevice9*>(wdd);
	}
	else {
		gRecoder->logTrace("[ERROR]: D3D create device failed.\n");
	}

	//WrapperDirect3DDevice9::ins_count++;
	// get the window handle
	HWND hd = pPresentationParameters->hDeviceWindow;
	RECT winRect;
	BOOL ret = GetWindowRect(hd, &winRect);
	if (ret == TRUE){
	}
	else{
	}
	gRecoder->logTrace("[INFO]: Direct end CreateDevice.\n");
	return hr;
}