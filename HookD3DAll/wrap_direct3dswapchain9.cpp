#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dswapchain9.h"
#include "wrap_direct3dsurface9.h"

int WrapperDirect3DSwapChain9::ins_count = 0;
HashSet WrapperDirect3DSwapChain9::m_list;

WrapperDirect3DSwapChain9::WrapperDirect3DSwapChain9(IDirect3DSwapChain9* ptr, int _id): m_chain(ptr), id(_id) {
	m_list.AddMember(ptr, this);
}

inline int WrapperDirect3DSwapChain9::GetID() {
	return this->id;
}

inline void WrapperDirect3DSwapChain9::SetID(int id) {
	this->id = id;
}

#ifdef GETWRAPPERDEVICE

WrapperDirect3DSwapChain9* WrapperDirect3DSwapChain9::GetWrapperSwapChain9(IDirect3DSwapChain9* ptr) {
	gRecoder->logTrace("[INFO]: SwapChain9 call GetWrapperSwapChain9.\n");
	WrapperDirect3DSwapChain9* ret = (WrapperDirect3DSwapChain9*)( m_list.GetDataPtr(ptr) );

	if(ret == NULL) {
		gRecoder->logTrace("[INFO]: create new swap chain, id = %d.\n", ins_count);
		ret = new WrapperDirect3DSwapChain9(ptr, ins_count++);
	}
	gRecoder->logTrace("[INFO]: SwapChain9 end GetWrapperSwapChain9.\n");
	return ret;
}
#endif

/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DSwapChain9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: SwapChain9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_chain->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: SwapChain9 end QueryInterface.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DSwapChain9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: SwapChain9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_chain->AddRef();
	gRecoder->logTrace("[INFO]: SwapChain9 end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DSwapChain9::Release(THIS) {
	gRecoder->logTrace("[INFO]: SwapChain9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_chain->Release();
	gRecoder->logTrace("[INFO]: SwapChain9 end Release.\n");
	return hr;
}

/*** IDirect3DSwapChain9 methods ***/
STDMETHODIMP WrapperDirect3DSwapChain9::Present(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags) {

	gRecoder->logTrace("[INFO]: SwapChain9 call Present.\n");
	gRecoder->presentCalled(sizeof(void *) * 3 + sizeof(RECT) * 2 + sizeof(HWND) + sizeof(RGNDATA) + sizeof(DWORD));
	
	HRESULT hr = m_chain->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
	gRecoder->logTrace("[INFO]: SwapChain9 end Present.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSwapChain9::GetFrontBufferData(THIS_ IDirect3DSurface9* pDestSurface) {
	gRecoder->logTrace("[INFO]: SwapChain9 call GetFrontBufferData.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr = m_chain->GetFrontBufferData(pDestSurface);
	gRecoder->logTrace("[INFO]: SwapChain9 end GetFrontBufferData.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSwapChain9::GetBackBuffer(THIS_ UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) {
	gRecoder->logTrace("[INFO]: SwapChain9 call GetBackBuffer.\n"); 
	IDirect3DSurface9* base_surface = NULL;
	HRESULT hr = m_chain->GetBackBuffer(iBackBuffer, Type, &base_surface);
	WrapperDirect3DSurface9* surface = NULL;
#ifndef GETWRAPPERDEVICE
	if (typeid(*base_surface) == typeid(WrapperDirect3DSurface9)){
		*ppBackBuffer = surface;
	}
	else if (typeid(*base_surface) == typeid(IDirect3DSurface9)){
		gRecoder->logError("[ERROR]: GetBackBuffer got a IDirect3DSurface9. create new!");
		surface = new WrapperDirect3DSurface9(base_surface, WrapperDirect3DSurface9::ins_count++);
		*ppBackBuffer = surface;
	}
	else{

		// error
		gRecoder->logError("[ERROR]: GetBackBuffer got an unknown type.\n");
		*ppBackBuffer = NULL;
	}
	gRecoder->cmdSendAndCalled(sizeof(UINT) + sizeof(D3DBACKBUFFER_TYPE) + sizeof(void *));

#else
	surface = WrapperDirect3DSurface9::GetWrapperSurface9(base_surface);
	gRecoder->cmdSendAndCalled(sizeof(UINT)+sizeof(D3DBACKBUFFER_TYPE)+sizeof(void *));
	*ppBackBuffer = dynamic_cast<IDirect3DSurface9 *>(surface);
#endif
	gRecoder->logTrace("[INFO]: SwapChain9 end GetBackBuffer.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSwapChain9::GetRasterStatus(THIS_ D3DRASTER_STATUS* pRasterStatus) {
	gRecoder->logTrace("[INFO]: SwapChain9 call GetRasterStatus.\n");
	gRecoder->cmdCalled(sizeof(void *) + sizeof(D3DRASTER_STATUS));
	HRESULT hr = m_chain->GetRasterStatus(pRasterStatus);
	gRecoder->logTrace("[INFO]: SwapChain9 end GetRasterStatus.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSwapChain9::GetDisplayMode(THIS_ D3DDISPLAYMODE* pMode) {
	gRecoder->logTrace("[INFO]: SwapChain9 call GetDisplayMode.\n");
	gRecoder->cmdCalled(sizeof(D3DDISPLAYMODE));
	HRESULT hr =m_chain->GetDisplayMode(pMode);
	gRecoder->logTrace("[INFO]: SwapChain9 end GetDisplayMode.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSwapChain9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: SwapChain9 call GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr = m_chain->GetDevice(ppDevice);
	gRecoder->logTrace("[INFO]: SwapChain9 end GetDevice.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSwapChain9::GetPresentParameters(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) {
	gRecoder->logTrace("[INFO]: SwapChain9 call GetPresentParameters.\n");
	gRecoder->cmdCalled(sizeof(void *) + sizeof(D3DPRESENT_PARAMETERS));
	HRESULT hr = m_chain->GetPresentParameters(pPresentationParameters);
	gRecoder->logTrace("[INFO]: SwapChain9 end GetPresentParameters.\n");
	return hr;
}
