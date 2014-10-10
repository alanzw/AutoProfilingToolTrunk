#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3d9.h"
#include "wrap_direct3ddevice9.h"
#include "wrap_direct3dvertexbuffer9.h"
#include "wrap_direct3dindexbuffer9.h"
#include "wrap_direct3dvertexdeclaration9.h"
#include "wrap_direct3dvertexshader9.h"
#include "wrap_direct3dpixelshader9.h"
#include "wrap_direct3dtexture9.h"
#include "wrap_direct3dstateblock9.h"
#include "wrap_direct3dcubetexture9.h"
#include "wrap_direct3dswapchain9.h"
#include "wrap_direct3dsurface9.h"
#include "wrap_direct3dvolumetexture9.h"

bool tex_send[4024] = { 0 };

double time_total = 0.0f;
int frame_all_count = 0;

WrapperDirect3DDevice9::WrapperDirect3DDevice9(IDirect3DDevice9* device, int _id) : m_device(device), id(_id) {
	m_list.AddMember(device, this);
}

inline int WrapperDirect3DDevice9::GetID() {
	return this->id;
}

inline void WrapperDirect3DDevice9::SetID(int id) {
	this->id = id;
}
#ifdef GETWRAPPERDEVICE
WrapperDirect3DDevice9* WrapperDirect3DDevice9::GetWrapperDevice9(IDirect3DDevice9* ptr) {

	gRecoder->logTrace("[INFO]: Device call GetWrapperDevice9.\n");

	WrapperDirect3DDevice9* ret = (WrapperDirect3DDevice9*)( m_list.GetDataPtr(ptr) );
	if(ret == NULL) {
		ret = new WrapperDirect3DDevice9(ptr, ins_count++);
		gRecoder->logTrace("[INFO]: Device Create new Device, total: %d.\n", WrapperDirect3DDevice9::ins_count);
	}
	gRecoder->logTrace("[INFO]: Device end GetWrapperDevice9.\n");
	return ret;
}
#endif

STDMETHODIMP WrapperDirect3DDevice9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: Device call QueryInterface.\n");
	void * ret = NULL;
	HRESULT hr = m_device->QueryInterface(riid, &ret);
	if (ppvObj)
		*ppvObj = this;
	if (hr == E_NOINTERFACE){
		gRecoder->logTrace("[ERROR]: Device QueryInterface failed, riid: ");
		gRecoder->logGuid(riid);
		gRecoder->logTrace(" , 0x%p ----> 0x%p.\n", ret, ppvObj);
	}
	else{
		gRecoder->logTrace("[INFO]: Device QueryInterface return non e_nointerface, riid: ");
		gRecoder->logGuid(riid);
		gRecoder->logTrace(" , 0x%p ----> 0x%p.\n", ret, ppvObj);
	}
	gRecoder->cmdCalled(sizeof(riid)+sizeof(void *));
	gRecoder->logTrace("[INFO]: Device end QueryInterface.\n");
	return hr;
	//return S_OK;
}
STDMETHODIMP_(ULONG) WrapperDirect3DDevice9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: Device call AddRef.\n");
	gRecoder->cmdCalled(sizeof(int));
	gRecoder->logTrace("[INFO]: Device end AddRef.\n");
	return m_device->AddRef();
}
STDMETHODIMP_(ULONG) WrapperDirect3DDevice9::Release(THIS) {
	gRecoder->logTrace("[INFO]: Device call Release.\n");
	gRecoder->cmdCalled(sizeof(int));
	gRecoder->logTrace("[INFO]: Device end Release.\n");
	return m_device->Release();
}

/*** IDirect3DDevice9 methods ***/

STDMETHODIMP WrapperDirect3DDevice9::TestCooperativeLevel(THIS){
	gRecoder->logTrace("[INFO]: Device call TestCooperativeLevel.\n");
	gRecoder->cmdCalled(sizeof(int));

	HRESULT hr = m_device->TestCooperativeLevel();
	gRecoder->logTrace("[INFO]: Device end TestCooperativeLevel.\n");
	return hr; // m_device->TestCooperativeLevel();
}

STDMETHODIMP_(UINT) WrapperDirect3DDevice9::GetAvailableTextureMem(THIS) {
	gRecoder->logTrace("[INFO]: Device call GetAvailableTextureMem.\n");
	gRecoder->cmdCalled(sizeof(int));
	UINT hr = m_device->GetAvailableTextureMem();
	gRecoder->logTrace("[INFO]: Device end GetAvailableTextureMem.\n");
	return hr;//  m_device->GetAvailableTextureMem();
}

STDMETHODIMP WrapperDirect3DDevice9::EvictManagedResources(THIS) {
	gRecoder->logTrace("[INFO]: Device call EvictManagedResources.\n");
	gRecoder->cmdCalled(sizeof(int));
	HRESULT hr = m_device->EvictManagedResources();
	gRecoder->logTrace("[INFO]: Device end EvictManagedResources.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetDirect3D(THIS_ IDirect3D9** ppD3D9) {
	gRecoder->logTrace("[INFO]: Device call GetDirect3D.\n");
	gRecoder->cmdCalled(sizeof(int));
	LPDIRECT3D9 base_d3d9;
	HRESULT hr = m_device->GetDirect3D(&base_d3d9);

#ifndef GETWRAPPERDEVICE
	if (typeid(*base_d3d9) == typeid(IDirect3D9)){
		gRecoder->logError("[INFO]: Device GetDirect3D got a IDirect3D.\n");
		//TODO : return the global WrapperDirect3D, should be only one
		*ppD3D9 = new WrapperDirect3D9(base_d3d9, WrapperDirect3D9::ins_count++);
	}
	else if (typeid(*base_d3d9) == typeid(WrapperDirect3D9)){
		*ppD3D9 = base_d3d9;
	}
	else{
		gRecoder->logError("[ERROR]: Device GetDirect3D got an unkown type.\n");
		*ppD3D9 = base_d3d9;
	}
#else
#if 1

#if 0 
	*ppD3D9 = dynamic_cast<IDirect3D9 *>(WrapperDirect3D9::GetWrapperD3D9(base_d3d9));
#else
	*ppD3D9 = WrapperDirect3D9::GetWrapperD3D9(base_d3d9);
#endif
#else
	*ppD3D9 = dynamic_cast<IDirect3D9 *>(base_d3d9);
#endif
#endif
	gRecoder->logTrace("[INFO]: Device end GetDirect3D.\n");

	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::GetDeviceCaps(THIS_ D3DCAPS9* pCaps) {
	gRecoder->logTrace("[INFO]: Device call GetDeviceCaps.\n");
	gRecoder->cmdCalled(sizeof(D3DCAPS9));
	HRESULT hr = m_device->GetDeviceCaps(pCaps);
	gRecoder->logTrace("[INFO]: Device end GetDeviceCaps.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetDisplayMode(THIS_ UINT iSwapChain, D3DDISPLAYMODE* pMode) {
	gRecoder->logTrace("[INFO]: Device call GetDisplayMode.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(D3DDISPLAYMODE));
	HRESULT hr = m_device->GetDisplayMode(iSwapChain, pMode);
	gRecoder->logTrace("[INFO]: Device end GetDisplayMode.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetCreationParameters(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) {
	gRecoder->logTrace("[INFO]: Device call GetCreationParameters.\n");
	gRecoder->cmdCalled(sizeof(D3DDEVICE_CREATION_PARAMETERS));
	HRESULT hr = m_device->GetCreationParameters(pParameters);
	gRecoder->logTrace("[INFO]: Device end GetCreationParameters.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetCursorProperties(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap) {
	gRecoder->logTrace("[INFO]: Device call SetSursorProperties.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + ((WrapperDirect3DSurface9*)pCursorBitmap)->getSurfaceSize());
	HRESULT hr = m_device->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
	gRecoder->logTrace("[INFO]: Device end SetsCursorProperties.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DDevice9::SetCursorPosition(THIS_ int X, int Y, DWORD Flags) {
	gRecoder->logTrace("[INFO]: Device call SetCursorPosition.\n");
	gRecoder->cmdCalled(sizeof(int)* 2 + sizeof(DWORD));
	m_device->SetCursorPosition(X, Y, Flags);
	gRecoder->logTrace("[INFO]: Device end SetCursorPosition.\n");
}

STDMETHODIMP_(BOOL) WrapperDirect3DDevice9::ShowCursor(THIS_ BOOL bShow) {
	gRecoder->logTrace("[INFO]: Device call ShowCursor.\n");
	gRecoder->cmdCalled(sizeof(BOOL));
	BOOL ret = m_device->ShowCursor(bShow);
	gRecoder->logTrace("[INFO]: Device end ShowCursor.\n");
	return ret;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateAdditionalSwapChain(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain) {
	gRecoder->logTrace("[INFO]: Device call CreateAdditionalSwapChain.\n");
	gRecoder->cmdCalled(sizeof(D3DPRESENT_PARAMETERS)+sizeof(void *));
	HRESULT hr = m_device->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
	gRecoder->logTrace("[INFO]: Device end CreateAdditionalSwapChain.\n");
	return hr;
}

// this function is to create a new swap chain ? (yes, confirmed)
STDMETHODIMP WrapperDirect3DDevice9::GetSwapChain(THIS_ UINT iSwapChain, IDirect3DSwapChain9** pSwapChain) {
	gRecoder->logTrace("[INFO]: Device call GetSwapChain.\n");
	IDirect3DSwapChain9* base_chain = NULL;
	HRESULT hr = m_device->GetSwapChain(iSwapChain, &base_chain);
	WrapperDirect3DSwapChain9* chain = NULL;

	gRecoder->cmdSendAndCalled(sizeof(UINT)+sizeof(void *));
	
#ifndef GETWRAPPERDEVICE
	if (typeid(*base_chain) == typeid(IDirect3DSwapChain9)){
		chain = new WrapperDirect3DSwapChain9(base_chain, WrapperDirect3DSwapChain9::ins_count++);
		*pSwapChain = chain;
	}
	else if (typeid(*base_chain) == typeid(WrapperDirect3DSwapChain9)){
		*pSwapChain = base_chain;
	}
	else{
		gRecoder->logError("[ERROR]: Device GetSwapChain got an unknown type.\n");
		*pSwapChain = base_chain;
	}
#else
	chain = WrapperDirect3DSwapChain9::GetWrapperSwapChain9(base_chain);

#if 0
	*pSwapChain = dynamic_cast<IDirect3DSwapChain9 *>(chain);
#else
	*pSwapChain = chain;
#endif
#endif
	gRecoder->logTrace("[INFO]: Device end GetSwapChain.\n");
	return hr;
}

STDMETHODIMP_(UINT) WrapperDirect3DDevice9::GetNumberOfSwapChains(THIS){
	gRecoder->logTrace("[INFO]: Device call GetNumberOfSwapChain.\n");
	gRecoder->cmdCalled(0);
	UINT hr =m_device->GetNumberOfSwapChains();
	gRecoder->logTrace("[INFO]: Device end GetNumberOfSwapChian.\n");
	return hr;
}

// reset is an importtant function in multi-windowed games, be careful the window handle in D3DPRESENT_PARAMETERS
STDMETHODIMP WrapperDirect3DDevice9::Reset(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) {
	gRecoder->logTrace("[INFO]: Device call Reset.\n");
	gRecoder->cmdSendAndCalled(sizeof(D3DPRESENT_PARAMETERS));
	HRESULT hr = m_device->Reset(pPresentationParameters);
	gRecoder->logTrace("[INFO]: Device end Reset.\n");
	return hr;
}

int presented = 0;
extern CRITICAL_SECTION f9;
extern int serverInputArrive;
DWORD tick_start = 0, tick_end = 0;

STDMETHODIMP WrapperDirect3DDevice9::Present(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) {
	gRecoder->logTrace("[INFO]: Device call Present.\n");
	bool tm = false, tm1 = false;

	char flag = 0;

	gRecoder->presentCalled(sizeof(RECT)* 2 + sizeof(HWND)+sizeof(RGNDATA));

	/////////////////////////////////////////////////////////////////////
	//limit it to max_fps
#if 1
	static double last_time = timeGetTime();
	static double elapse_time = 0.0;
	static double frame_cnt = 0.0;
	static double fps = 0.0;

	double frame_time = 0.0f;

	double cur_time = (float)timeGetTime();
	elapse_time += (cur_time - last_time);
	frame_time = cur_time - last_time;

	last_time = cur_time;
	frame_cnt++;

	//limit it to max_fps
	double to_sleep = 0.0f;
	if (gRecoder->toLimitFps()){
		to_sleep = 1000.0 / gRecoder->getMaxFps() * frame_cnt - elapse_time;
		if (to_sleep > 0){
			Sleep((DWORD)to_sleep);
		}
	}

	if (elapse_time >= 1000.0) {
		fps = frame_cnt * 1000.0 / elapse_time;
		frame_cnt = 0;
		elapse_time = 0;
	}
#endif
	/////////////////////////////////////////////////

	HRESULT hh = m_device->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	gRecoder->logTrace("[INFO]: Device end Present.\n");
	return hh;
}

// create a new IDirect3DSurface9
STDMETHODIMP WrapperDirect3DDevice9::GetBackBuffer(THIS_ UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer){
	gRecoder->logTrace("[INFO]: Device call GetBackBuffer.\n");
	gRecoder->cmdSendAndCalled(sizeof(UINT)* 2 + sizeof(D3DBACKBUFFER_TYPE)+sizeof(void *));

	IDirect3DSurface9* base_surface = NULL;
	HRESULT hr = m_device->GetBackBuffer(iSwapChain, iBackBuffer, Type, &base_surface);

	if (hr == D3D_OK){
#if 1
		WrapperDirect3DSurface9* ret = new WrapperDirect3DSurface9(base_surface, WrapperDirect3DSurface9::ins_count++);
#else
		WrapperDirect3DSurface9 * ret = WrapperDirect3DSurface9::GetWrapperSurface9(base_surface);
#endif
		// return the surface
#if 0
		*ppBackBuffer = dynamic_cast<IDirect3DSurface9*>(ret);
#else
		*ppBackBuffer = ret;
#endif
	}
	else{

	}
	gRecoder->logTrace("[INFO]: Device end GetBackBuffer.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::GetRasterStatus(THIS_ UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus) {
	gRecoder->logTrace("[INFO]: Device call GetRasterStatus.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(D3DRASTER_STATUS));

	HRESULT hr = m_device->GetRasterStatus(iSwapChain, pRasterStatus);
	gRecoder->logTrace("[INFO]: Device end GetRasterStatus.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetDialogBoxMode(THIS_ BOOL bEnableDialogs) {
	gRecoder->logTrace("[INFO]: Device call SetDialogBoxMode.\n");
	gRecoder->cmdCalled(sizeof(BOOL));
	HRESULT hr = m_device->SetDialogBoxMode(bEnableDialogs);
	gRecoder->logTrace("[INFO]: Device end SetDialogBoxMode.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DDevice9::SetGammaRamp(THIS_ UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp) {
	gRecoder->logTrace("[INFO]: Device call SetGammaRamp.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(DWORD)+sizeof(D3DGAMMARAMP));

	m_device->SetGammaRamp(iSwapChain, Flags, pRamp);
	gRecoder->logTrace("[INFO]: Device end SetGammaRamp.\n");
}
STDMETHODIMP_(void) WrapperDirect3DDevice9::GetGammaRamp(THIS_ UINT iSwapChain, D3DGAMMARAMP* pRamp) {
	gRecoder->logTrace("[INFO]: Device call GetGammaRamp.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(D3DGAMMARAMP));
	m_device->GetGammaRamp(iSwapChain, pRamp);
	gRecoder->logTrace("[INFO]: Device end GetGammaRamp.\n");
}

STDMETHODIMP WrapperDirect3DDevice9::CreateTexture(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle) {
	gRecoder->logTrace("[INFO]: Device call CreateTexture.\n");
	LPDIRECT3DTEXTURE9 base_tex = NULL;

	gRecoder->cmdSendAndCalled(sizeof(UINT)* 3 + sizeof(DWORD)+sizeof(D3DFORMAT)+sizeof(D3DPOOL)+sizeof(HANDLE)+sizeof(void *));

	HRESULT hr = m_device->CreateTexture(Width, Height, Levels, Usage, Format, Pool, &base_tex, pSharedHandle);

	WrapperDirect3DTexture9 * wt = NULL;
	if (SUCCEEDED(hr)) {
		// store the texture creation information
#if 1
		wt = new WrapperDirect3DTexture9(base_tex, WrapperDirect3DTexture9::ins_count++);
#else
		wt = WrapperDirect3DTexture9::GetWrapperTexture9(base_tex);
#endif
#if 1
		*ppTexture = dynamic_cast<IDirect3DTexture9*>(wt);
#else
		*ppTexture = wt;
#endif
		wt->height = Height;
		wt->width = Width;
		wt->foramt = Format;
	}
	else {
		gRecoder->logTrace("[ERROR]: Device create texture failed.\n");
	}
	gRecoder->logTrace("[INFO]: Device end CreateTexture.\n");
	return hr;
}

//TODO
// why volume texture did not send to clients ?
STDMETHODIMP WrapperDirect3DDevice9::CreateVolumeTexture(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle) {
	gRecoder->logTrace("[INFO]: Device call CreateVolumeTexture.\n");
	gRecoder->logError("[INFO]: Device call CreateVolumeTexture.\n");

	gRecoder->cmdSendAndCalled(sizeof(UINT)* 3 + sizeof(DWORD)+sizeof(D3DFORMAT)+sizeof(D3DPOOL)+sizeof(void *)+sizeof(HANDLE));

	IDirect3DVolumeTexture9 * base_tex = NULL;
	HRESULT hr = m_device->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, &base_tex, pSharedHandle);
	if (SUCCEEDED(hr)){

#if 1
		WrapperDirect3DVolumeTexture9 * w_v_t = new WrapperDirect3DVolumeTexture9(base_tex, WrapperDirect3DVolumeTexture9::ins_count++);
#else
		WrapperDirect3DVolumeTexture9 * w_v_t = WrapperDirect3DVolumeTexture9::GetWrapperTexture9(base_tex);
#endif
		*ppVolumeTexture = dynamic_cast<IDirect3DVolumeTexture9*>(w_v_t);

		w_v_t->height = Height;
		w_v_t->width = Width;
		w_v_t->depth = Depth;
		w_v_t->level = Levels;
		w_v_t->format = Format;

	}
	else{
	}
	gRecoder->logTrace("[INFO]: Device end CreateVolumeTexture.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateCubeTexture(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle) {
	IDirect3DCubeTexture9* base_cube_tex = NULL;
	gRecoder->logTrace("[INFO]: Device call CreateCubeTexture.\n");
	gRecoder->logError("[INFO]: Device call CreateCubeTexture.\n");

	gRecoder->cmdSendAndCalled(sizeof(UINT)* 2 + sizeof(DWORD)+sizeof(D3DFORMAT)+sizeof(D3DPOOL)+sizeof(HANDLE)+sizeof(void *));

	HRESULT hr = m_device->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, &base_cube_tex, pSharedHandle);

	WrapperDirect3DCubeTexture9 * wct = NULL;

	if (SUCCEEDED(hr)) {
#if 1
		wct = new WrapperDirect3DCubeTexture9(base_cube_tex, WrapperDirect3DCubeTexture9::ins_count++);
#else 
		wct = WrapperDirect3DCubeTexture9::GetWrapperCubeTexture9(base_cube_tex);
#endif

		wct->edgeLength = EdgeLength;
		wct->level = Levels;
		wct->format = Format;

		*ppCubeTexture = dynamic_cast<IDirect3DCubeTexture9*>(wct);
	}
	else {
	}
	gRecoder->logTrace("[INFO]: Device end CreateCubeTexture.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle) {
	gRecoder->logTrace("[INFO]: Device call CreateVertexBuffer.\n");
	gRecoder->cmdSendAndCalled(sizeof(UINT)+sizeof(DWORD)* 2 + sizeof(D3DPOOL)+sizeof(void *)+sizeof(HANDLE));

	LPDIRECT3DVERTEXBUFFER9 base_vb = NULL;

	HRESULT hr = m_device->CreateVertexBuffer(Length, Usage, FVF, Pool, &base_vb, pSharedHandle);

	WrapperDirect3DVertexBuffer9 * wvb = NULL;

	if (SUCCEEDED(hr)) {
#if 1
		wvb = new WrapperDirect3DVertexBuffer9(base_vb, WrapperDirect3DVertexBuffer9::ins_count++);
#else
		wvb = WrapperDirect3DVertexBuffer9::GetWrapperVertexBuffer9(base_vb);
#endif

		wvb->vb_size = Length;

		if (wvb)
			*ppVertexBuffer = dynamic_cast<IDirect3DVertexBuffer9*>(wvb);
		else{
			gRecoder->logTrace("[ERROR]: Device new wrapper texture failed.\n");
		}
	}
	else {
		gRecoder->logTrace("[ERROR]: Device create vertex buffer failed.\n");
	}

	gRecoder->logTrace("[INFO]: Device end CreateVertexBuffer.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle) {
	gRecoder->logTrace("[INFO]: Device call CreateIndexBuffer.\n");
	gRecoder->cmdSendAndCalled(sizeof(UINT)+sizeof(DWORD)+sizeof(D3DFORMAT)+sizeof(D3DPOOL)+sizeof(void *)+sizeof(HANDLE));

	LPDIRECT3DINDEXBUFFER9 base_ib = NULL;

	HRESULT hr = m_device->CreateIndexBuffer(Length, Usage, Format, Pool, &base_ib, pSharedHandle);
	WrapperDirect3DIndexBuffer9 * wib = NULL;

	if (SUCCEEDED(hr)) {
		wib = new WrapperDirect3DIndexBuffer9(base_ib, WrapperDirect3DIndexBuffer9::ins_count++);
		wib->ib_size = Length;

		*ppIndexBuffer = dynamic_cast<IDirect3DIndexBuffer9*>(wib);

		if (*ppIndexBuffer == NULL) {
			gRecoder->logTrace("[ERROR]: Device new Wraper index buffer failed.\n");
		}
		else {
		}

	}
	else {
		gRecoder->logTrace("[ERROR]: Device create index buffer failed.\n");
	}
	gRecoder->logTrace("[INFO]: Device end CreateIndexBuffer.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateRenderTarget(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) {
	gRecoder->logTrace("[INFO]: Device call CreateRenderTarget.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + sizeof(D3DFORMAT)+sizeof(D3DMULTISAMPLE_TYPE)+sizeof(DWORD)+sizeof(BOOL)+sizeof(void *));

	gRecoder->logError("[ERROR]: Device CreateRenderTarget is called. need to add to sending list\n");

	// TODO : is the render target is created by other method?
	HRESULT hr = m_device->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
	gRecoder->logTrace("[INFO]: Device end CreateRenderTarget.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateDepthStencilSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) {
	/*TODO*/

	gRecoder->logTrace("[INFO]: Device call CreateDepthStencilSurface.\n");
	gRecoder->cmdSendAndCalled(sizeof(UINT)* 2 + sizeof(D3DFORMAT)+sizeof(D3DMULTISAMPLE_TYPE)+sizeof(DWORD)+sizeof(BOOL)+sizeof(void *)+sizeof(HANDLE));

	IDirect3DSurface9* base_surface = NULL;

	HRESULT hr = m_device->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, &base_surface, pSharedHandle);
	if (SUCCEEDED(hr)){
		WrapperDirect3DSurface9 * ws = NULL;
		ws = new WrapperDirect3DSurface9(base_surface, WrapperDirect3DSurface9::ins_count++);
		ws->width = Width;
		ws->height = Height;
		ws->format = Format;
#if 0
		*ppSurface = dynamic_cast<IDirect3DSurface9*>(ws);
#else
		*ppSurface = ws;
#endif
	}
	else{
		gRecoder->logTrace("[ERROR]: Device create depth stencil surface failed.\n");
	}
	gRecoder->logTrace("[INFO]: Device end CreateDepthStencilSurface.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::UpdateSurface(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint) {
	gRecoder->logTrace("[INFO]: Device call UpdateSurface.\n");
	WrapperDirect3DSurface9 * src = (WrapperDirect3DSurface9 *)pSourceRect;
	WrapperDirect3DSurface9 * dst = (WrapperDirect3DSurface9 *)pDestinationSurface;

	gRecoder->cmdCalled(sizeof(void *)* 2 + sizeof(RECT)+sizeof(POINT)+src->getSurfaceSize() * 2);

	IDirect3DSurface9* psrc = pDestinationSurface ? ((WrapperDirect3DSurface9*)pSourceSurface)->GetSurface9() : NULL;
	IDirect3DSurface9* pdst = pDestinationSurface ? ((WrapperDirect3DSurface9*)pSourceSurface)->GetSurface9() : NULL;
	HRESULT hr =m_device->UpdateSurface(psrc, pSourceRect, pdst, pDestPoint);
	gRecoder->logTrace("[INFO]: Device end UpdateSurface.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::UpdateTexture(THIS_ IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture) {
	gRecoder->logTrace("[INFO]: Device call UpdateTexture.\n");
	gRecoder->cmdCalled(sizeof(void *)* 2);

	HRESULT hr = m_device->UpdateTexture(pSourceTexture, pDestinationTexture);
	gRecoder->logTrace("[INFO]: Device end UpdateTexture.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::GetRenderTargetData(THIS_ IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface) {
	// check the surface's right

	gRecoder->logTrace("[INFO]: Device call GetRenderTargetData.\n");
	if (pRenderTarget == NULL || pDestSurface == NULL) {

	}

	WrapperDirect3DSurface9 * src = NULL, *dst = NULL;
	src = (WrapperDirect3DSurface9 *)pRenderTarget;
	dst = (WrapperDirect3DSurface9 *)pDestSurface;

	gRecoder->cmdCalled(sizeof(void *)* 2 + src->getSurfaceSize() * 2);

	HRESULT hr =m_device->GetRenderTargetData(src->GetSurface9(), dst->GetSurface9());
	gRecoder->logTrace("[INFO]: Device end GetRenderTargetData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::GetFrontBufferData(THIS_ UINT iSwapChain, IDirect3DSurface9* pDestSurface) {
	gRecoder->logTrace("[INFO]: Device call GetFrontBufferData.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(void *));

	HRESULT hr = m_device->GetFrontBufferData(iSwapChain, pDestSurface);
	gRecoder->logTrace("[INFO]: Device end GetFrontBufferData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::StretchRect(THIS_ IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter) {
	gRecoder->logTrace("[INFO]: Device call StretchRect.\n");
	gRecoder->cmdCalled(sizeof(void *)* 2 + sizeof(RECT)* 2 + sizeof(D3DTEXTUREFILTERTYPE));

	HRESULT hr =m_device->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
	gRecoder->logTrace("[INFO]: Device end StretchRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::ColorFill(THIS_ IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color) {
	gRecoder->logTrace("[INFO]: Device call ColorFill.\n");
	gRecoder->cmdCalled(sizeof(void *)+sizeof(RECT)+sizeof(D3DCOLOR));
	HRESULT hr =m_device->ColorFill(pSurface, pRect, color);
	gRecoder->logTrace("[INFO]: Device end ColorFill.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateOffscreenPlainSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle) {
	gRecoder->logTrace("[INFO]: Device call CreateOffscreenPlainSurface.\n");
	gRecoder->logError("[ERROR]: called CreateOffscreenPlainSurface inside games.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + sizeof(D3DFORMAT)+sizeof(D3DPOOL)+sizeof(void *)+sizeof(HANDLE));


	HRESULT hr = m_device->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
	gRecoder->logTrace("[INFO]: Device end CreateOffscreenPlainSurface.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget) {
	gRecoder->logTrace("[INFO]: Device call SetRenderTarget.\n");
	WrapperDirect3DSurface9 * sur = (WrapperDirect3DSurface9*)pRenderTarget;
	if (pRenderTarget == NULL) {

		gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(void *));

		HRESULT hh = m_device->SetRenderTarget(RenderTargetIndex, pRenderTarget);
		gRecoder->logTrace("[INFO]: Device end SetRenderTarget.\n");
		return hh;
	}

	gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(void *)+sur->getSurfaceSize());

	HRESULT hr = m_device->SetRenderTarget(RenderTargetIndex, ((WrapperDirect3DSurface9*)pRenderTarget)->GetSurface9());
	gRecoder->logTrace("[INFO]: Device end SetRenderTarget.\n");
	return hr;
}

// create new surface ?
STDMETHODIMP WrapperDirect3DDevice9::GetRenderTarget(THIS_ DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget) {
	gRecoder->logTrace("[INFO]: Device call GetRenderTarget.\n");
	HRESULT hr;
	WrapperDirect3DSurface9 * ws = NULL;

	IDirect3DSurface9 * ret = NULL;
	hr = m_device->GetRenderTarget(RenderTargetIndex, &ret);
	if (SUCCEEDED(hr)){
		ws = new WrapperDirect3DSurface9(ret, WrapperDirect3DSurface9::ins_count++);
		(*ppRenderTarget) = dynamic_cast<IDirect3DSurface9*>(ws);

		gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(void *)+ws->getSurfaceSize());

	}
	else{
		gRecoder->logTrace("[ERROR]: Device get render target failed.\n");
	}
	gRecoder->logTrace("[INFO]: Device end GetRenderTarget.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetDepthStencilSurface(THIS_ IDirect3DSurface9* pNewZStencil) {
	gRecoder->logTrace("[INFO]: Device call SetDepthStencilSurface.\n");
	HRESULT hh;
	if (pNewZStencil == NULL) {

		gRecoder->cmdSendAndCalled(sizeof(void*));
		hh = m_device->SetDepthStencilSurface(NULL);
		gRecoder->logTrace("[INFO]: Device end SetDepthStencilSurface.\n");
		return hh;
	}

	gRecoder->cmdSendAndCalled(sizeof(void *)+((WrapperDirect3DSurface9 *)pNewZStencil)->getSurfaceSize());

	hh = m_device->SetDepthStencilSurface(((WrapperDirect3DSurface9*)pNewZStencil)->GetSurface9());
	gRecoder->logTrace("[INFO]: Device end SetDepthStencilSurface.\n");
	return hh;
}


// create new depth stencil surface
STDMETHODIMP WrapperDirect3DDevice9::GetDepthStencilSurface(THIS_ IDirect3DSurface9** ppZStencilSurface) {
	gRecoder->logTrace("[INFO]: Device call GetDepthStencilSurface.\n");
	IDirect3DSurface9* base_surface = NULL;
	HRESULT hr = m_device->GetDepthStencilSurface(&base_surface);

	WrapperDirect3DSurface9* surface = NULL;
#ifndef GETWRAPPERDEVICE
	MessageBox(NULL, typeid(*base_surface).name(), "type", MB_OK);

	gRecoder->logError("[error addr]: base surface:%p, type id:%s.\n", base_surface, typeid(*base_surface).name());

	if (typeid(*base_surface) == typeid(IDirect3DSurface9)) {
		surface = new WrapperDirect3DSurface9(base_surface, WrapperDirect3DSurface9::ins_count++);

		gRecoder->cmdSendAndCalled(sizeof(void *)+surface->getSurfaceSize());

		*ppZStencilSurface = dynamic_cast<IDirect3DSurface9*>(surface);
	}
	else if (typeid(*base_surface) == typeid(WrapperDirect3DSurface9)){
		*ppZStencilSurface = dynamic_cast<IDirect3DSurface9*>(base_surface);
		gRecoder->cmdSendAndCalled(sizeof(void *)+((WrapperDirect3DSurface9 *)base_surface)->getSurfaceSize());
	}
	else{
		gRecoder->logError("[ERROR]: device GetDepthStencilSurface got an unknown type.\n");
		*ppZStencilSurface = dynamic_cast<IDirect3DSurface9*>(base_surface);
	}
#else
	surface = WrapperDirect3DSurface9::GetWrapperSurface9(base_surface);
	gRecoder->cmdSendAndCalled(surface->getSurfaceSize());

	*ppZStencilSurface = dynamic_cast<IDirect3DSurface9 *>(surface);
#endif
	gRecoder->logTrace("[INFO]: Device end GetStencilSurface.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::BeginScene(THIS) {
	gRecoder->logTrace("[INFO]: Device call BeginScene.\n");
	gRecoder->sceneOperationCalled();
	HRESULT h = m_device->BeginScene();
	gRecoder->logTrace("[INFO]: Device end BeginScene.\n");
	return h;
}
STDMETHODIMP WrapperDirect3DDevice9::EndScene(THIS) {
	gRecoder->logTrace("[INFO]: Device call EndScene.\n");
	gRecoder->sceneOperationCalled();
	HRESULT hh = m_device->EndScene();
	gRecoder->logTrace("[INFO]: Device end EndScene.\n");
	return hh;
}
STDMETHODIMP WrapperDirect3DDevice9::Clear(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) {
	gRecoder->logTrace("[INFO]: Device call Clear.\n");
	gRecoder->cmdSendAndCalled(sizeof(DWORD)* 3 + sizeof(D3DRECT)+sizeof(D3DCOLOR)+sizeof(float));
	HRESULT hh = m_device->Clear(Count, pRects, Flags, Color, Z, Stencil);
	gRecoder->logTrace("[INFO]: Device end Clear.\n");
	return hh;
}
STDMETHODIMP WrapperDirect3DDevice9::SetTransform(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix) {
	gRecoder->logTrace("[INFO]: Device call SetTransform.\n");
	if (pMatrix == NULL) {
	}

	gRecoder->cmdSendAndCalled(sizeof(D3DTRANSFORMSTATETYPE)+sizeof(D3DMATRIX));

	HRESULT hh = m_device->SetTransform(State, pMatrix);
	gRecoder->logTrace("[INFO]: Device end SetTransform.\n");
	return hh;

}
STDMETHODIMP WrapperDirect3DDevice9::GetTransform(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix) {
	gRecoder->logTrace("[INFO]: Device call GetTransform.\n");
	gRecoder->cmdCalled(sizeof(D3DTRANSFORMSTATETYPE)+sizeof(D3DMATRIX));

	HRESULT hr =m_device->GetTransform(State, pMatrix);
	gRecoder->logTrace("[INFO]: Device end GetTransform.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE Type, CONST D3DMATRIX* pD3DMatrix) {
	gRecoder->logTrace("[INFO]: Device call MultiplyTransform.\n");
	HRESULT hr =m_device->MultiplyTransform(Type, pD3DMatrix);
	gRecoder->logTrace("[INFO]: Device end MuliplyTransform.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetViewport(THIS_ CONST D3DVIEWPORT9* pViewport) {
	gRecoder->logTrace("[INFO]: Device call SetViewport.\n");
	if (pViewport == NULL) {
		gRecoder->logTrace("[ERROR]: Device set NULL viewport.\n");
	}
	gRecoder->cmdSendAndCalled(sizeof(D3DVIEWPORT9));
	HRESULT hh = m_device->SetViewport(pViewport);
	gRecoder->logTrace("[INFO]: Device end SetViewport.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetViewport(THIS_ D3DVIEWPORT9* pViewport) {
	gRecoder->logTrace("[INFO]: Device call GetViewport.\n");
	gRecoder->cmdCalled(sizeof(D3DVIEWPORT9));

	HRESULT hr = m_device->GetViewport(pViewport);
	gRecoder->logTrace("[INFO]: Device end GetViewport.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetMaterial(THIS_ CONST D3DMATERIAL9* pMaterial) {
	gRecoder->logTrace("[INFO]: Device call SetMaterial.\n");
	gRecoder->cmdSendAndCalled(sizeof(D3DMATERIAL9));

	HRESULT hh = m_device->SetMaterial(pMaterial);
	gRecoder->logTrace("[INFO]: Device end SetMaterial.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetMaterial(THIS_ D3DMATERIAL9* pMaterial) {
	gRecoder->logTrace("[INFO]: Device call GetMaterial.\n");
	gRecoder->cmdCalled(sizeof(D3DMATERIAL9));
	HRESULT hr = m_device->GetMaterial(pMaterial);
	gRecoder->logTrace("[INFO]: Device end GetMaterial.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetLight(THIS_ DWORD Index, CONST D3DLIGHT9* pD3DLight9) {
	gRecoder->logTrace("[INFO]: Device call SetLight.\n");
	HRESULT hh = m_device->SetLight(Index, pD3DLight9);

	gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(D3DLIGHT9));
	gRecoder->logTrace("[INFO]: Device end SetLight.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetLight(THIS_ DWORD Index, D3DLIGHT9* pD3DLight9) {
	gRecoder->logTrace("[INFO]: Device call GetLight.\n");
	gRecoder->cmdCalled(sizeof(DWORD)+sizeof(D3DLIGHT9));
	HRESULT hr = m_device->GetLight(Index, pD3DLight9);
	gRecoder->logTrace("[INFO]: Device end Light.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::LightEnable(THIS_ DWORD Index, BOOL Enable) {
	gRecoder->logTrace("[INFO]: Device call LightEnable.\n");
	gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(BOOL));
	HRESULT hh = m_device->LightEnable(Index, Enable);

	gRecoder->logTrace("[INFO]: Device end LightEnable.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetLightEnable(THIS_ DWORD Index, BOOL* pEnable) {
	gRecoder->logTrace("[INFO]: Device call GetLightEnable.\n");
	gRecoder->cmdCalled(sizeof(DWORD)+sizeof(BOOL));
	HRESULT hr = m_device->GetLightEnable(Index, pEnable);
	gRecoder->logTrace("[INFO]: Device end GetLightEnable.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetClipPlane(THIS_ DWORD Index, CONST float* pPlane) {
	gRecoder->logTrace("[INFO]: Device call SetClipPlane.\n");
	gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(float));
	HRESULT hr =m_device->SetClipPlane(Index, pPlane);
	gRecoder->logTrace("[INFO]: Device end SetClipPlane.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetClipPlane(THIS_ DWORD Index, float* pPlane) {
	gRecoder->logTrace("[INFO]: Device call GetClipPlane.\n");
	gRecoder->cmdCalled(sizeof(DWORD)+sizeof(float));
	HRESULT hr = m_device->GetClipPlane(Index, pPlane);
	gRecoder->logTrace("[INFO]: Device end GetClipPlane.\n");
	return hr;
}


STDMETHODIMP WrapperDirect3DDevice9::SetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD Value) {
	gRecoder->logTrace("[INFO]: Device call SetRenderState.\n");
	gRecoder->cmdSendAndCalled(sizeof(D3DRENDERSTATETYPE)+sizeof(DWORD));
	HRESULT hh = m_device->SetRenderState(State, Value);

	gRecoder->logTrace("[INFO]: Device end SetRenderState.\n");
	return hh;
}
STDMETHODIMP WrapperDirect3DDevice9::GetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue) {
	gRecoder->logTrace("[INFO]: Device call GetRenderState.\n");
	gRecoder->cmdCalled(sizeof(D3DRENDERSTATETYPE)+sizeof(DWORD));
	HRESULT hr = m_device->GetRenderState(State, pValue);
	gRecoder->logTrace("[INFO]: Device end GetRenderState.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB) {
	gRecoder->logTrace("[INFO]: Device call CreateStateBlock.\n");
	IDirect3DStateBlock9* sb_base = NULL;
	HRESULT hr = m_device->CreateStateBlock(Type, &sb_base);
	WrapperDirect3DStateBlock9 * wsb = NULL;

	if (SUCCEEDED(hr)) {
		wsb = new WrapperDirect3DStateBlock9(sb_base, WrapperDirect3DStateBlock9::ins_count++);
		*ppSB = dynamic_cast<IDirect3DStateBlock9*>(wsb);
	}
	else {
		gRecoder->logTrace("[ERROR]: Device create state block failed.\n");
	}

	gRecoder->cmdSendAndCalled(sizeof(D3DSTATEBLOCKTYPE)+sizeof(void*));
	gRecoder->logTrace("[INFO]: Device end CreateStateBlock.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::BeginStateBlock(THIS) {

	gRecoder->logTrace("[INFO]: Device call BeginStateBlock.\n");
	gRecoder->stateBlockCalled();
	HRESULT hh = m_device->BeginStateBlock();
	gRecoder->logTrace("[INFO]: Device end BeginStateBlock.\n");
	return hh;
}

//TODO
// check whether this function is to use a state block or create a new state block
STDMETHODIMP WrapperDirect3DDevice9::EndStateBlock(THIS_ IDirect3DStateBlock9** ppSB) {
	gRecoder->logTrace("[INFO]: Device call EndStateBlock.\n");
	WrapperDirect3DStateBlock9 * wsb = NULL;

	IDirect3DStateBlock9* sb_base = NULL;
	HRESULT hr = m_device->EndStateBlock(&sb_base);

	if (SUCCEEDED(hr)) {
		wsb = new WrapperDirect3DStateBlock9(sb_base, WrapperDirect3DStateBlock9::ins_count++);
		*ppSB = dynamic_cast<IDirect3DStateBlock9*>(wsb);
	}
	else {
		gRecoder->logTrace("[ERROR]: Device end state block create new state block failed.\n");
	}

	gRecoder->stateBlockCalled();
	gRecoder->logTrace("[INFO]: Device end EndStateBlock.\n");
	return hr;
}


STDMETHODIMP WrapperDirect3DDevice9::SetClipStatus(THIS_ CONST D3DCLIPSTATUS9* pClipStatus) {
	gRecoder->logTrace("[INFO]: Device call SetClipStatus.\n");
	gRecoder->cmdSendAndCalled(sizeof(D3DCLIPSTATUS9));
	HRESULT hr = m_device->SetClipStatus(pClipStatus);
	gRecoder->logTrace("[INFO]: Device end SetClipStatus.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetClipStatus(THIS_ D3DCLIPSTATUS9* pClipStatus) {
	gRecoder->logTrace("[INFO]: Device call GetClipStatus.\n");
	gRecoder->cmdCalled(sizeof(D3DCLIPSTATUS9));
	HRESULT hr = m_device->GetClipStatus(pClipStatus);
	gRecoder->logTrace("[INFO]: Device end GetClipStatus.\n");
	return hr;
}


STDMETHODIMP WrapperDirect3DDevice9::GetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture9** ppTexture) {
	gRecoder->logTrace("[INFO]: Device call GetTexture.\n");
	gRecoder->cmdCalled(sizeof(DWORD)+sizeof(void *));

	HRESULT hr = m_device->GetTexture(Stage, ppTexture);
	gRecoder->logTrace("[INFO]: Device end GetTexture.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture9* pTexture) {
	gRecoder->logTrace("[INFO]: Device call SetTexture.\n");

	if (pTexture == NULL) {

		gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(void *));
		return m_device->SetTexture(Stage, pTexture);
	}

	D3DRESOURCETYPE Type = pTexture->GetType();
	

	if (Type == D3DRTYPE_TEXTURE) {
		gRecoder->logTrace("[INFO]: Device set texture9.\n");
		int id = ((WrapperDirect3DTexture9*)pTexture)->GetID();
		//check device's creation
		WrapperDirect3DTexture9 * wt = (WrapperDirect3DTexture9 *)pTexture;

		gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(void *)+wt->getTextureSize());

		HRESULT hh = m_device->SetTexture(Stage, ((WrapperDirect3DTexture9*)pTexture)->GetTex9());
		gRecoder->logTrace("[INFO]: Device end SetTexture.\n");
		return hh;
	}
	else if (Type == D3DRTYPE_CUBETEXTURE) {
		gRecoder->logTrace("[INFO]: Device set cube texture9.\n");
		int id = ((WrapperDirect3DCubeTexture9*)pTexture)->GetID();
		WrapperDirect3DCubeTexture9 * wt = (WrapperDirect3DCubeTexture9 *)pTexture;

		gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(void *)+wt->getTextureSize());

		HRESULT hh = m_device->SetTexture(Stage, ((WrapperDirect3DCubeTexture9*)pTexture)->GetCubeTex9());
		gRecoder->logTrace("[INFO]: Device end SetTexture.\n");
		return hh;
	}
	else {
		gRecoder->logTrace("[ERROR]: Device set texture get an nuknown type.\n");
		gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(void *));
		HRESULT hr = m_device->SetTexture(Stage, pTexture);
		gRecoder->logTrace("[INFO]: Device end SetTexture.\n");
		return hr;
	}
}


STDMETHODIMP WrapperDirect3DDevice9::GetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue) {
	gRecoder->logTrace("[INFO]: Device call GetTextureStagetState.\n");
	gRecoder->cmdCalled(sizeof(DWORD)+sizeof(D3DTEXTURESTAGESTATETYPE)+sizeof(void *));

	HRESULT hr = m_device->GetTextureStageState(Stage, Type, pValue);
	gRecoder->logTrace("[INFO]: Device end GetTextureStageState.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetTextureStageState(THIS_ DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) {
	gRecoder->logTrace("[INFO]: Device call SetTextureStageState.\n");

	gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(D3DTEXTURESTAGESTATETYPE)+sizeof(DWORD));

	HRESULT hh = m_device->SetTextureStageState(Stage, Type, Value);
	gRecoder->logTrace("[INFO]: Device end SetTextureStagetState.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue) {
	gRecoder->logTrace("[INFO]: Device call GetSampleState.\n");
	gRecoder->cmdCalled(sizeof(DWORD)+sizeof(D3DSAMPLERSTATETYPE)+sizeof(DWORD *));

	HRESULT hr = m_device->GetSamplerState(Sampler, Type, pValue);
	gRecoder->logTrace("[INFO]: Device end GetSampleState.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::SetSamplerState(THIS_ DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value) {
	gRecoder->logTrace("[INFO]: Device call SetSampleState.\n");
	gRecoder->cmdSendAndCalled(sizeof(DWORD)+sizeof(D3DSAMPLERSTATETYPE)+sizeof(DWORD));

	HRESULT hh = m_device->SetSamplerState(Sampler, Type, Value);
	gRecoder->logTrace("[INFO]: Device end SetSampleSate.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::ValidateDevice(THIS_ DWORD* pNumPasses) {
	gRecoder->logTrace("[INFO]: Device call ValidateDevice.\n");
	gRecoder->cmdCalled(sizeof(DWORD *));
	HRESULT hr = m_device->ValidateDevice(pNumPasses);
	gRecoder->logTrace("[INFO]: Device end ValidateDevice.\n");
	return hr;
}


STDMETHODIMP WrapperDirect3DDevice9::SetPaletteEntries(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries) {
	gRecoder->logTrace("[INFO]: Device call SetPaletteEntries.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(PALETTEENTRY));
	HRESULT hr = m_device->SetPaletteEntries(PaletteNumber, pEntries);
	gRecoder->logTrace("[INFO]: Device end SetPaletteEntries.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetPaletteEntries(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries) {
	gRecoder->logTrace("[INFO]: Device call GetPaletteEntries.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(PALETTEENTRY));

	HRESULT hr = m_device->GetPaletteEntries(PaletteNumber, pEntries);
	gRecoder->logTrace("[INFO]: Device end GetPaletteEntries.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::SetCurrentTexturePalette(THIS_ UINT PaletteNumber) {
	gRecoder->logTrace("[INFO]: Device call SetCurrentTexturePalette.\n");
	gRecoder->logError("[INFO]: Device alled SetCurrentTexturePalette.\n");

	gRecoder->cmdCalled(sizeof(UINT));

	HRESULT hr =m_device->SetCurrentTexturePalette(PaletteNumber);
	gRecoder->logTrace("[INFO]: Device end SetCurrentTexturePalette.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::GetCurrentTexturePalette(THIS_ UINT *PaletteNumber) {
	gRecoder->logTrace("[INFO]: Device call GetCurrentTexturePalette.\n");
	gRecoder->cmdCalled(sizeof(UINT *));

	HRESULT hr = m_device->GetCurrentTexturePalette(PaletteNumber);
	gRecoder->logTrace("[INFO]: Device end GetCurrentTexturePalette.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetScissorRect(THIS_ CONST RECT* pRect) {
	gRecoder->logTrace("[INFO]: Device call SetScissorRect.\n");
	gRecoder->cmdSendAndCalled(sizeof(RECT));
	HRESULT hr = m_device->SetScissorRect(pRect);
	gRecoder->logTrace("[INFO]: Device end SetScissorRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetScissorRect(THIS_ RECT* pRect) {
	gRecoder->logTrace("[INFO]: Device call GetScissorRect.\n");
	gRecoder->cmdCalled(sizeof(RECT));

	HRESULT hr = m_device->GetScissorRect(pRect);
	gRecoder->logTrace("[INFO]: Device end GetScissorRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetSoftwareVertexProcessing(THIS_ BOOL bSoftware) {
	gRecoder->logTrace("[INFO]: Device call SetSoftwareVertexProcessing.\n");
	gRecoder->cmdCalled(sizeof(BOOL));
	HRESULT hh = m_device->SetSoftwareVertexProcessing(bSoftware);
	gRecoder->logTrace("[INFO]: Device end SetSoftwareVertexProcessing.\n");
	return hh;
}

STDMETHODIMP_(BOOL) WrapperDirect3DDevice9::GetSoftwareVertexProcessing(THIS) {
	gRecoder->logTrace("[INFO]: Device call GetSoftwareVertexProcessing.\n");
	gRecoder->cmdCalled(sizeof(BOOL));
	HRESULT hr =m_device->GetSoftwareVertexProcessing();
	gRecoder->logTrace("[INFO]: Device end GetSoftwareVertexProcessing.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetNPatchMode(THIS_ float nSegments) {
	gRecoder->logTrace("[INFO]: Device call SetNPatchMode.\n");
	gRecoder->logError("[INFO]: Device called SetNPatchMode.\n");

	gRecoder->cmdCalled(sizeof(float));
	HRESULT hh = m_device->SetNPatchMode(nSegments);
	gRecoder->logTrace("[INFO]: Device end SetNPatchMode.\n");
	return hh;
}

STDMETHODIMP_(float) WrapperDirect3DDevice9::GetNPatchMode(THIS) {
	gRecoder->logTrace("[INFO]: Device call GetNPatchMode.\n");
	gRecoder->cmdCalled(sizeof(float));

	float hr =m_device->GetNPatchMode();
	gRecoder->logTrace("[INFO]: Device end GetNPatchMode.\n");
	return hr;
}

/*
	place for DrawPrimitive functions
	*/

STDMETHODIMP WrapperDirect3DDevice9::ProcessVertices(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags) {
	gRecoder->logTrace("[INFO]: Device call ProcessVertices.\n");
	gRecoder->logError("[INFO]: Device called ProcessVertices.\n");

	int paramSize = sizeof(UINT)* 3 + sizeof(void *)* 2 + sizeof(DWORD);
#ifndef GETWRAPPERDEVICE
	if (typeid(*pVertexDecl) == typeid(WrapperDirect3DVertexDeclaration9)){
		paramSize += ((WrapperDirect3DVertexDeclaration9*)pVertexDecl)->getDeclarationSize();
	}
	else if (typeid(*pVertexDecl) == typeid(IDirect3DVertexDeclaration9)){
		gRecoder->logError("[ERROR]: Device call ProcessVertices use IDirect3DVertexDeclaration9.\n");
	}
	else{
		// unknown type
		gRecoder->logError("[ERROR]: Device call ProcessVertices use unknown type of declaration.\n");
	}
#else
	WrapperDirect3DVertexDeclaration9 * wvd = WrapperDirect3DVertexDeclaration9::GetWrapperDirect3DVertexDeclaration(pVertexDecl);
	paramSize += wvd->getDeclarationSize();
#endif

	gRecoder->cmdSendAndCalled(paramSize);

	HRESULT hr = m_device->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
	gRecoder->logTrace("[INFO]: Device end ProcessVertices.\n");
	return hr;
}

/*
	place for CreateVertexDeclaration
	*/

STDMETHODIMP WrapperDirect3DDevice9::GetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9** ppDecl) {
	gRecoder->logTrace("[INFO]: Device call GetVertexDeclaration.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr =  m_device->GetVertexDeclaration(ppDecl);
	gRecoder->logTrace("[INFO]: Device end GetVertexDeclaration.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetFVF(THIS_ DWORD FVF) {
	gRecoder->logTrace("[INFO]: Device call SetFVF.\n");
	gRecoder->cmdSendAndCalled(sizeof(DWORD));
	HRESULT hr = m_device->SetFVF(FVF);
	gRecoder->logTrace("[INFO]: Device end SetFVF.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DDevice9::GetFVF(THIS_ DWORD* pFVF) {
	gRecoder->logTrace("[INFO]: Device call GetFVF.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	HRESULT hr = m_device->GetFVF(pFVF);
	gRecoder->logTrace("[INFO]: Device end GetFVF.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateVertexShader(THIS_ CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader) {
	gRecoder->logTrace("[INFO]: Device call CreateVertexShader.\n");
	int cnt = 0;
	while (true) {
		if (pFunction[cnt++] == D3DVS_END()) break;
	}

	LPDIRECT3DVERTEXSHADER9 base_vs = NULL;
	HRESULT hr = m_device->CreateVertexShader(pFunction, &base_vs);
	WrapperDirect3DVertexShader9 * wvs = NULL;

	if (SUCCEEDED(hr)) {
		wvs = new WrapperDirect3DVertexShader9(base_vs, WrapperDirect3DVertexShader9::ins_count++);
		*ppShader = dynamic_cast<IDirect3DVertexShader9*>(wvs);
		wvs->funcCount = cnt;

		gRecoder->logTrace("[INFO]: Wrapper Vertex shader new with id:%d.\n", ins_count - 1);

		gRecoder->cmdSendAndCalled(sizeof(void *)* 2 + wvs->getShaderSize());
	}
	else {
		gRecoder->logTrace("[ERROR]: Device create vertex shader failed.\n");
	}
	gRecoder->logTrace("[INFO]: Device end CreateVertexShader.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetVertexShader(THIS_ IDirect3DVertexShader9* pShader) {
	gRecoder->logTrace("[INFO]: Device call SetVertexShader.\n");
	HRESULT hh;
	if (pShader == NULL) {

		gRecoder->cmdSendAndCalled(sizeof(void *));
		hh = m_device->SetVertexShader(NULL);
		gRecoder->logTrace("[INFO]: Device end SetVertexShader.\n");
		return hh;
	}

	hh = m_device->SetVertexShader(((WrapperDirect3DVertexShader9*)pShader)->GetVS9());
	gRecoder->cmdSendAndCalled(((WrapperDirect3DVertexShader9*)pShader)->getShaderSize() + sizeof(void *));
	gRecoder->logTrace("[INFO]: Device end SetVertexShader.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetVertexShader(THIS_ IDirect3DVertexShader9** ppShader) {
	gRecoder->logTrace("[INFO]: Device call GetVertexShader.\n"); 
	LPDIRECT3DVERTEXSHADER9 base_vertex_shader = NULL;
	HRESULT hr = m_device->GetVertexShader(&base_vertex_shader);
#ifndef GETWRAPPERDEVICE
	if (typeid(*base_vertex_shader) == typeid(IDirect3DVertexShader9)){

		gRecoder->logError("[INFO]: Device GetVertexShader get a IDirect3DVertexShader9.\n");
		gRecoder->cmdCalled(sizeof(void *));
	}
	else if (typeid(*base_vertex_shader) == typeid(WrapperDirect3DVertexShader9)){
		gRecoder->cmdCalled(sizeof(void *)+((WrapperDirect3DVertexShader9*)base_vertex_shader)->getShaderSize());
	}
	else{
		// unknown type
		gRecoder->logError("[ERROR]: Device GetVertexShader got an unknown type shader.\n");
	}
#else
	WrapperDirect3DVertexShader9 * wvs = WrapperDirect3DVertexShader9::GetWrapperVertexShader(base_vertex_shader);

	gRecoder->cmdCalled(sizeof(void *)+ wvs->getShaderSize());
#if 0
	*ppShader = dynamic_cast<IDirect3DVertexShader9 *>(wvs);
#else
	*ppShader = wvs;
#endif
#endif
	gRecoder->logTrace("[INFO]: Device end GetVertexShader.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetVertexShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount) {
	gRecoder->logTrace("[INFO]: Device call SetVertexShaderConstantF.\n");
	gRecoder->logTrace("[INFO]: SetVertexShaderConstantF(%d, 0x%p, %d).\n", StartRegister, pConstantData, Vector4fCount);

	gRecoder->vertexShaderConstantCalled(sizeof(UINT)* 2 + sizeof(void *), sizeof(float)* 4 * Vector4fCount);

	HRESULT hh = m_device->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	gRecoder->logTrace("[INFO]: Device end SetVertexShaderConstantF.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetVertexShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount) {
	gRecoder->logTrace("[INFO]: Device call GetVertexShaderConstantF.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + sizeof(float*)+sizeof(float)* 4 * Vector4fCount);

	HRESULT hr = m_device->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	gRecoder->logTrace("[INFO]: Device end GetVertexShaderConstantF.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetVertexShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount) {
	gRecoder->logTrace("[INFO]: Device call SetVertexShaderConstantI.\n");
	HRESULT hh = m_device->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);

	gRecoder->vertexShaderConstantCalled(sizeof(UINT)* 2 + sizeof(int *), 4 * sizeof(int)* Vector4iCount);
	gRecoder->logTrace("[INFO]: Device end SetVertexShaderConstantI.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetVertexShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount) {
	gRecoder->logTrace("[INFO]: Device call GetVertexShaderConstantI.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + sizeof(int*)+sizeof(int)* Vector4iCount * 4);
	HRESULT hr = m_device->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
	gRecoder->logTrace("[INFO]: Device end GetVertexShaderConstantI.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetVertexShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount) {
	gRecoder->logTrace("[INFO]: Device call SetVertexShaderConstantB.\n");
	HRESULT hh = m_device->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);

	gRecoder->vertexShaderConstantCalled(sizeof(UINT)* 2 + sizeof(BOOL *), sizeof(BOOL)* BoolCount);
	gRecoder->logTrace("[INFO]: Device end SetVertexShaderConstantB.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetVertexShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount) {
	gRecoder->logTrace("[INFO]: Device call GetVertexShaderConstantB.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + sizeof(BOOL *)+sizeof(BOOL)* BoolCount);

	HRESULT hr = m_device->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
	gRecoder->logTrace("[INFO]: Device end GetVertexShaderConstantB.\n");
	return hr;
}

/*
	place for SetVertexDeclaration
	*/

/*
	place for SetStreamSource
	*/

STDMETHODIMP WrapperDirect3DDevice9::GetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride) {
	gRecoder->logTrace("[INFO]: Device call GetStreamSource.\n");
	gRecoder->logError("[INFO]: Device Called GetStreamSource.\n");

	LPDIRECT3DVERTEXBUFFER9 base_vertex_buffer = NULL;
	HRESULT hr = m_device->GetStreamSource(StreamNumber, &base_vertex_buffer, pOffsetInBytes, pStride);

#ifndef GETWRAPPERDEVICE
	if (typeid(*base_vertex_buffer) == typeid(IDirect3DVertexBuffer9)){
		// get the vb size
		D3DVERTEXBUFFER_DESC vd;
		base_vertex_buffer->GetDesc(&vd);
		gRecoder->cmdCalled(sizeof(UINT)* 3 + sizeof(void *)* 3 + vd.Size);
		// 
		*ppStreamData = base_vertex_buffer;
	}
	else if (typeid(*base_vertex_buffer) == typeid(WrapperDirect3DVertexBuffer9)){
		gRecoder->logError("[INFO]: Device Called GetStreamSource, get a WrapperDirectVertexBuffer.\n");
		gRecoder->cmdCalled(sizeof(UINT)* 3 + sizeof(void *)* 3 + ((WrapperDirect3DVertexBuffer9*)base_vertex_buffer)->vb_size);

		*ppStreamData = ((WrapperDirect3DVertexBuffer9*)base_vertex_buffer)->GetVB9();
	}
	else{
		// unknown type
		gRecoder->logError("[ERROR]: GetStreamSource got an unknown type vertex buffer.\n");
		*ppStreamData = base_vertex_buffer;
	}
#else

	gRecoder->logError("[INFO]: Device Called GetStreamSource, get a WrapperDirectVertexBuffer.\n");
	WrapperDirect3DVertexBuffer9 * wvb = WrapperDirect3DVertexBuffer9::GetWrapperVertexBuffer9(base_vertex_buffer);
#if 0
	*ppStreamData = ((WrapperDirect3DVertexBuffer9*)base_vertex_buffer)->GetVB9();
#else
#if 0
	*ppStreamData = dynamic_cast<IDirect3DVertexBuffer9 *>(wvb);
#else
	*ppStreamData = wvb;
#endif
#endif
#endif
	gRecoder->cmdCalled(sizeof(UINT)* 3 + sizeof(void *)* 3 + wvb->vb_size);
	gRecoder->logTrace("[INFO]: Device end GetStreamSource.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetStreamSourceFreq(THIS_ UINT StreamNumber, UINT Setting) {
	gRecoder->logTrace("[INFO]: Device call SetStreamSourceFreq.\n");
	gRecoder->logError("[INFO]: Device called SetStreamSourceFreq.\n");

	gRecoder->cmdCalled(sizeof(UINT)* 2);

	HRESULT hr = m_device->SetStreamSourceFreq(StreamNumber, Setting);
	gRecoder->logTrace("[INFO]: Device end SetStreamSourceReq.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetStreamSourceFreq(THIS_ UINT StreamNumber, UINT* pSetting) {
	gRecoder->logTrace("[INFO]: Device call GetStreamSourceFreq.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2);
	HRESULT hr = m_device->GetStreamSourceFreq(StreamNumber, pSetting);
	gRecoder->logTrace("[INFO]: Device end GetStreamSourceFreq.\n");
	return hr;
}

/*
	place for SetIndices
	*/

STDMETHODIMP WrapperDirect3DDevice9::GetIndices(THIS_ IDirect3DIndexBuffer9** ppIndexData) {
	gRecoder->logTrace("[INFO]: Device call GetIndices.\n");
	LPDIRECT3DINDEXBUFFER9 base_indexed_buffer = NULL;
	HRESULT hr = m_device->GetIndices(&base_indexed_buffer);
#ifndef GETWRAPPERDEVICE
	if (typeid(*base_indexed_buffer) == typeid(IDirect3DIndexBuffer9)){
		D3DINDEXBUFFER_DESC idec;
		base_indexed_buffer->GetDesc(&idec);

		gRecoder->cmdCalled(sizeof(void*)+idec.Size);
		*ppIndexData = base_indexed_buffer;
	}
	else if (typeid(*base_indexed_buffer) == typeid(WrapperDirect3DIndexBuffer9)){
		gRecoder->cmdCalled(sizeof(void *)+((WrapperDirect3DIndexBuffer9*)base_indexed_buffer)->ib_size);

		*ppIndexData = ((WrapperDirect3DIndexBuffer9 *)base_indexed_buffer)->GetIB9();
	}
	else{
		// unknown type
		gRecoder->logError("[ERROR]: Device GetIndices called.\n");
		*ppIndexData = base_indexed_buffer;
	}
#else
	WrapperDirect3DIndexBuffer9 * wib = WrapperDirect3DIndexBuffer9::GetWrapperIndexedBuffer9(base_indexed_buffer);
	gRecoder->cmdCalled(sizeof(void *)+wib->ib_size);
#if 0
	*ppIndexData = ((WrapperDirect3DIndexBuffer9 *)base_indexed_buffer)->GetIB9();

#else

#if 0

	*ppIndexData = dynamic_cast<IDirect3DIndexBuffer9 *>(wib);
#else
	*ppIndexData = wib;
#endif
#endif
#endif
	gRecoder->logTrace("[INFO]: Device end GetIndices.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreatePixelShader(THIS_ CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader) {
	gRecoder->logTrace("[INFO]: Device call CreatePixelShader.\n");
	int cnt = 0;
	while (true) {
		if (pFunction[cnt++] == D3DPS_END()) break;
		//cnt++;
	}
	//WrapperDirect3DPixelShader9::ins_count++;
	LPDIRECT3DPIXELSHADER9 base_ps = NULL;

	HRESULT hr = m_device->CreatePixelShader(pFunction, &base_ps);

	WrapperDirect3DPixelShader9 * wps = NULL;
	if (SUCCEEDED(hr)) {
#if 1
		wps = new WrapperDirect3DPixelShader9(base_ps, WrapperDirect3DPixelShader9::ins_count++);
#else
		wps = WrapperDirect3DPixelShader9::GetWrapperPixelShader(base_ps);
#endif
		*ppShader = dynamic_cast<IDirect3DPixelShader9*>(wps);

		gRecoder->cmdSendAndCalled(sizeof(void *)* 2 + sizeof(DWORD)* cnt);
		wps->funcCount = cnt;
	}
	else {
		gRecoder->logError("[Device]: create pixel shader failed.\n");
	}
	gRecoder->logTrace("[INFO]: Device end CreatPixelShader.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetPixelShader(THIS_ IDirect3DPixelShader9* pShader) {
	gRecoder->logTrace("[INFO]: Device call SetPixelShader.\n");
	if (pShader == NULL) {
		gRecoder->setPixelShaderCalled(sizeof(void *), 0);
		return m_device->SetPixelShader(pShader);
	}
	WrapperDirect3DPixelShader9 * wps = (WrapperDirect3DPixelShader9*)pShader;
	gRecoder->setPixelShaderCalled(sizeof(void*), wps->funcCount * sizeof(DWORD));
	HRESULT hr = m_device->SetPixelShader(((WrapperDirect3DPixelShader9*)pShader)->GetPS9());
	gRecoder->logTrace("[INFO]: Device end SetPixelShader.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::GetPixelShader(THIS_ IDirect3DPixelShader9** ppShader) {
	gRecoder->logTrace("[INFO]: Device call GetPixelShader.\n"); 
	LPDIRECT3DPIXELSHADER9 base_pixel_shader = NULL;
	HRESULT hr = m_device->GetPixelShader(&base_pixel_shader);

#ifndef GETWRAPPERDEVICE
	if (typeid(*base_pixel_shader) == typeid(IDirect3DPixelShader9)){
		UINT dataSize = 0;
		base_pixel_shader->GetFunction(NULL, &dataSize);
		gRecoder->cmdCalled(sizeof(void *)+dataSize);

		*ppShader = base_pixel_shader;
	}
	else if (typeid(*base_pixel_shader) == typeid(WrapperDirect3DPixelShader9)){
		WrapperDirect3DPixelShader9 * wps = (WrapperDirect3DPixelShader9 *)base_pixel_shader;
		gRecoder->cmdCalled(sizeof(void *)+wps->funcCount * sizeof(DWORD));
	}
	else{
		gRecoder->logError("[ERROR]: Device GetPixelShader got an unknown type pixel shader.\n");
		gRecoder->cmdCalled(sizeof(void *));
		*ppShader = base_pixel_shader;
	}
#else
	WrapperDirect3DPixelShader9 * wps = WrapperDirect3DPixelShader9::GetWrapperPixelShader(base_pixel_shader);
	gRecoder->cmdCalled(sizeof(void *)+wps->funcCount * sizeof(DWORD));
#if 0
	*ppShader = dynamic_cast<IDirect3DPixelShader9*>(wps);
#else
	*ppShader = wps;
#endif
#endif

	gRecoder->logTrace("[INFO]: Device end GetPixelShader.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetPixelShaderConstantF(THIS_ UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount) {
	gRecoder->logTrace("[INFO]: Device call SetPixelShaderConstantF.\n");
	gRecoder->pixelShaderConstantCalled(sizeof(UINT)* 2 + sizeof(void *), sizeof(float)* 4 * Vector4fCount);

	HRESULT hh = m_device->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	gRecoder->logTrace("[INFO]: Device end SetPixelShaderConstantF.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetPixelShaderConstantF(THIS_ UINT StartRegister, float* pConstantData, UINT Vector4fCount) {
	gRecoder->logTrace("[INFO]: Device call GetPixelShaderConstantF.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + sizeof(void *)+sizeof(float)* 4 * Vector4fCount);

	HRESULT hr = m_device->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
	gRecoder->logTrace("[INFO]: Device end GetPixelShaderConstantF.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetPixelShaderConstantI(THIS_ UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount) {
	gRecoder->logTrace("[INFO]: Device call SetPixelShaderConstantI.\n");
	gRecoder->pixelShaderConstantCalled(sizeof(UINT)* 2 + sizeof(int *), sizeof(int)* 4 * Vector4iCount);

	HRESULT hh = m_device->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
	gRecoder->logTrace("[INFO]: Device end SetPixelConstantI.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetPixelShaderConstantI(THIS_ UINT StartRegister, int* pConstantData, UINT Vector4iCount) {

	gRecoder->logTrace("[INFO]: Device call GetPixelShaderConstantI.\n");
	gRecoder->cmdCalled(sizeof(UINT)* +sizeof(int *)+sizeof(int)* 4 * Vector4iCount);

	HRESULT hr = m_device->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
	gRecoder->logTrace("[INFO]: Device end GetPixelShaderConstantI.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetPixelShaderConstantB(THIS_ UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount) {
	gRecoder->logTrace("[INFO]: Device call SetPixelShaderConstantB.\n");

	gRecoder->pixelShaderConstantCalled(sizeof(UINT)* 2 + sizeof(BOOL *), sizeof(BOOL)* BoolCount);

	HRESULT hh = m_device->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
	gRecoder->logTrace("[INFO]: Device end SetPixelShaderConsatntB.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::GetPixelShaderConstantB(THIS_ UINT StartRegister, BOOL* pConstantData, UINT BoolCount) {
	gRecoder->logTrace("[INFO]: Device call GetPixelShaderConstantB.\n");
	gRecoder->cmdCalled(sizeof(UINT)* 2 + sizeof(BOOL *)+sizeof(BOOL)* BoolCount);

	HRESULT hr = m_device->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
	gRecoder->logTrace("[INFO]: Device end GetPixelShaderConstantB.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::DrawRectPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo) {
	gRecoder->logTrace("[INFO]: Device call DrawRectPatch.\n");
	gRecoder->logError("[INFO]: Device called DrawRectPath.\n");

	gRecoder->cmdCalled(sizeof(sizeof(UINT)+sizeof(float *)+sizeof(D3DRECTPATCH_INFO)));

	HRESULT hr = m_device->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
	gRecoder->logTrace("[INFO]: Device end DrawRectPatch.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::DrawTriPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo) {
	gRecoder->logTrace("[INFO]: Device call DrawTriPatch.\n");
	gRecoder->logError("[INFO]: Device called DrawTriPatch.\n");
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(void *)+sizeof(D3DTRIPATCH_INFO));

	HRESULT hr = m_device->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
	gRecoder->logTrace("[INFO]: Device end DrawTriPatch.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::DeletePatch(THIS_ UINT Handle) {
	gRecoder->logTrace("[INFO]: Device call DeletePatch.\n");
	gRecoder->logError("[INFO]: Device called DeletePatch.\n");
	gRecoder->cmdCalled(sizeof(UINT));
	HRESULT hr =m_device->DeletePatch(Handle);
	gRecoder->logTrace("[INFO]: Device end DeletePatch.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateQuery(THIS_ D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery) {
	gRecoder->logTrace("[INFO]: Device call CreateQuery.\n");
	gRecoder->cmdCalled(sizeof(D3DQUERYTYPE)+sizeof(void *));
	HRESULT hr = m_device->CreateQuery(Type, ppQuery);
	gRecoder->logTrace("[INFO]: Device end CreateQury.\n");
	return hr;
}