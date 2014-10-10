#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dsurface9.h"
#include "wrap_direct3ddevice9.h"

int WrapperDirect3DSurface9::ins_count = 0;
HashSet WrapperDirect3DSurface9::m_list;

int WrapperDirect3DSurface9::getSurfaceSize(){
#if 0
	return width * height * 4;
#else
	D3DSURFACE_DESC desc;
	if(m_surface){
		m_surface->GetDesc(&desc);
		return desc.Height * desc.Width * 4;
	}
	else{
		return 0;
	}
#endif
}

WrapperDirect3DSurface9::WrapperDirect3DSurface9(IDirect3DSurface9* ptr, int _id): m_surface(ptr), id(_id) {
	m_list.AddMember(ptr, this);
}

inline int WrapperDirect3DSurface9::GetID() {
	return this->id;
}

inline void WrapperDirect3DSurface9::SetID(int id) {
	this->id = id;
}
#ifdef GETWRAPPERDEVICE
WrapperDirect3DSurface9* WrapperDirect3DSurface9::GetWrapperSurface9(IDirect3DSurface9* ptr) {
	gRecoder->logTrace("[INFO]: Surface9 call GetWrapperSurface9.\n");
	WrapperDirect3DSurface9* ret = (WrapperDirect3DSurface9*)(m_list.GetDataPtr(ptr));
	if(ret == NULL) {
		ret = new WrapperDirect3DSurface9(ptr, WrapperDirect3DSurface9::ins_count++);
	}
	gRecoder->logTrace("[INFO]: Surface9 end GetWrapperSurface9.\n");
	return ret;
}
#endif

IDirect3DSurface9* WrapperDirect3DSurface9::GetSurface9() {
	return this->m_surface;
}

/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DSurface9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: Surface9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_surface->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: Surface9 end QueryInterface.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DSurface9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: Surface9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_surface->AddRef();
	gRecoder->logTrace("[INFO]: Surface9 end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DSurface9::Release(THIS) {
	gRecoder->logTrace("[INFO]: Surface9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_surface->Release();
	gRecoder->logTrace("[INFO]: Surface9 end Release.\n");
	return hr;
}

/*** IDirect3DResource9 methods ***/
STDMETHODIMP WrapperDirect3DSurface9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: Surface9 call GetDevice.\n");
	IDirect3DDevice9* base_device = NULL;
	HRESULT hr = m_surface->GetDevice(&base_device);
#ifdef GETWRAPPERDEVICE
	WrapperDirect3DDevice9* device = WrapperDirect3DDevice9::GetWrapperDevice9(base_device);
	*ppDevice = device;
#else
	if (typeid(*base_device) == typeid(IDirect3DDevice9))
		*ppDevice = base_device;
	else if (typeid(*base_device) == typeid(WrapperDirect3DDevice9)){
		gRecoder->logError("[ERROR]: Surface get device got a WrapperDevice.\n");
		*ppDevice = ((WrapperDirect3DDevice9 *)base_device)->GetIDirect3DDevice9();
	}
	else{
		gRecoder->logError("[ERROR]: Surface GetDevice got an unknown type.\n");
		*ppDevice = base_device;
	}
#endif

	gRecoder->cmdCalled(sizeof(void *));
	gRecoder->logTrace("[INFO]: Surface9 end GetDevice.\n");
	return hr;
}


STDMETHODIMP WrapperDirect3DSurface9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags){
	gRecoder->logTrace("[INFO]: Surface9 call SetPrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) * 2 + SizeOfData);
	HRESULT hr = m_surface->SetPrivateData(refguid, pData, SizeOfData, Flags);
	gRecoder->logTrace("[INFO]: Surface9 end SetPrivateData.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSurface9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) {
	gRecoder->logTrace("[INFO]: Surface9 call GetPrivateData.\n");
	DWORD sizeOfData = 0;
	HRESULT hr = m_surface->GetPrivateData(refguid, pData, &sizeOfData);

	*pSizeOfData = sizeOfData;

	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) * 2 + sizeof(DWORD) + sizeOfData);
	gRecoder->logTrace("[INFO]: Surface9 end GetPrivateData.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSurface9::FreePrivateData(THIS_ REFGUID refguid) {
	gRecoder->logTrace("[INFO]: Surface9 call FreePrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid));
	HRESULT hr = m_surface->FreePrivateData(refguid);
	gRecoder->logTrace("[INFO]: Surface9 end FreePrivateData.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DSurface9::SetPriority(THIS_ DWORD PriorityNew) {
	gRecoder->logTrace("[INFO]: Surface9 call SetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = m_surface->SetPriority(PriorityNew);
	gRecoder->logTrace("[INFO]: Surface9 end SetPriority.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DSurface9::GetPriority(THIS) {
	gRecoder->logTrace("[INFO]: Surface9 call GetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_surface->GetPriority();
	gRecoder->logTrace("[INFO]: Surface9 end GetPriority.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DSurface9::PreLoad(THIS) {
	gRecoder->logTrace("[INFO]: Surface9 call PreLoad.\n");
	gRecoder->cmdCalled(0);
	m_surface->PreLoad();
	gRecoder->logTrace("[INFO]: Surface9 end PreLoad.\n");
	return;
}

STDMETHODIMP_(D3DRESOURCETYPE) WrapperDirect3DSurface9::GetType(THIS) {
	gRecoder->logTrace("[INFO]: Surface9 call GetType.\n");
	gRecoder->cmdCalled(sizeof(D3DRESOURCETYPE));
	D3DRESOURCETYPE hr = m_surface->GetType();
	gRecoder->logTrace("[INFO]: Surface9 end GetType.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSurface9::GetContainer(THIS_ REFIID riid,void** ppContainer) {
	gRecoder->logTrace("[INFO]: Surface9 call GetConteiner.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_surface->GetContainer(riid, ppContainer);
	gRecoder->logTrace("[INFO]: Surface9 end GetContainer.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSurface9::GetDesc(THIS_ D3DSURFACE_DESC *pDesc) {
	gRecoder->logTrace("[INFO]: Surface9 call GetDesc.\n");
	gRecoder->cmdCalled(sizeof(D3DSURFACE_DESC)+ sizeof(void *));
	HRESULT hr =m_surface->GetDesc(pDesc);
	gRecoder->logTrace("[INFO]: Surface9 end GetDesc.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSurface9::LockRect(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) {
	gRecoder->logTrace("[INFO]: Surface9 call LockRect.\n");
	gRecoder->cmdCalled(sizeof(D3DLOCKED_RECT) + sizeof(RECT) + sizeof(void *) * 2 + sizeof(DWORD));
	HRESULT hr = m_surface->LockRect(pLockedRect, pRect, Flags);
	gRecoder->logTrace("[INFO]: Surface9 end LockRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSurface9::UnlockRect(THIS) {
	gRecoder->logTrace("[INFO]: Surface9 call UnlockRect.\n");
	gRecoder->surfaceUnlockRectCalled(0, this->getSurfaceSize());
	HRESULT hr = m_surface->UnlockRect();
	gRecoder->logTrace("[INFO]: Surface9 end UnlockRect.\n");
	return hr;
}


STDMETHODIMP WrapperDirect3DSurface9::GetDC(THIS_ HDC *phdc) {
	gRecoder->logTrace("[INFO]: Surface9 call GetDC.\n");
	gRecoder->cmdCalled(sizeof(HDC) + sizeof(void *));
	HRESULT hr = m_surface->GetDC(phdc);
	gRecoder->logTrace("[INFO]: Surface9 end GetDC.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DSurface9::ReleaseDC(THIS_ HDC hdc) {
	gRecoder->logTrace("[INFO]: Surface9 call ReleaseDC.\n");
	gRecoder->cmdCalled(sizeof(HDC));
	HRESULT hr =m_surface->ReleaseDC(hdc);
	gRecoder->logTrace("[INFO]: Surface9 end ReleaseDC.\n");
	return hr;
}
