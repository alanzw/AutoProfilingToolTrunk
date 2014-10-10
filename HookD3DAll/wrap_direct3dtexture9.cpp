#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dtexture9.h"
#include "wrap_direct3dsurface9.h"

int WrapperDirect3DTexture9::ins_count = 0;
HashSet WrapperDirect3DTexture9::m_list;

inline int WrapperDirect3DTexture9::getTextureSize(){
	if (level > 1){
		return width * height * 4 * 2;
	}
	else{
		return width * height * 4;
	}
}

int D3DXTexture = 0;
WrapperDirect3DTexture9::WrapperDirect3DTexture9(IDirect3DTexture9* ptr, int _id): m_tex(ptr), id(_id) {
	if(ptr == NULL) {
	}
	m_list.AddMember(ptr, this);
}

inline void WrapperDirect3DTexture9::SetID(int id) {
	this->id = id;
}

int WrapperDirect3DTexture9::GetID() {
	return this->id;
}

IDirect3DTexture9* WrapperDirect3DTexture9::GetTex9() {
	return this->m_tex;
}

#ifdef GETWRAPPERDEVICE

WrapperDirect3DTexture9* WrapperDirect3DTexture9::GetWrapperTexture9(IDirect3DTexture9* ptr) {
	gRecoder->logTrace("[INFO]: Texture9 call GetWrapperTexture9.\n");
	//Log::slog("WrapperDirect3DTexture9::GetWrapperTexture9(), ptr=%u\n", ptr);
	WrapperDirect3DTexture9* ret = (WrapperDirect3DTexture9*)( m_list.GetDataPtr(ptr) );
	if(ret == NULL) {
		ret = new WrapperDirect3DTexture9(ptr, ins_count++);
	}
	gRecoder->logTrace("[INFO]: Texture9 end GetWrapperTexture9.\n");
	return ret;
}
#endif

/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DTexture9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: Texture9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_tex->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: Texture9 end QueryInterface.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DTexture9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_tex->AddRef();
	gRecoder->logTrace("[INFO]: Texture9 end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DTexture9::Release(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_tex->Release();
	gRecoder->logTrace("[INFO]: Texture9 end Release.\n");
	return hr;
}

/*** IDirect3DBaseTexture9 methods ***/
STDMETHODIMP WrapperDirect3DTexture9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: Texture9 cal GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr = m_tex->GetDevice(ppDevice);
	gRecoder->logTrace("[INFO]: Texture9 end GetDevice.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DTexture9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) {
	gRecoder->logTrace("[INFO]: Texture9 call SetPrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) * 2 + SizeOfData);
	HRESULT hr = m_tex->SetPrivateData(refguid, pData, SizeOfData, Flags);
	gRecoder->logTrace("[INFO]: Texture9 end SetPrivateData.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DTexture9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) {
	gRecoder->logTrace("[INFO]: Texture9 call GetPrivateData.\n");
	DWORD sizeOfData = 0;
	HRESULT hr = m_tex->GetPrivateData(refguid, pData, &sizeOfData);
	*pSizeOfData = sizeOfData;
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) * 2 + sizeof(DWORD) + sizeOfData);
	gRecoder->logTrace("[INFO]: Texture9 end GetPrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DTexture9::FreePrivateData(THIS_ REFGUID refguid) {
	gRecoder->logTrace("[INFO]: Texture9 call FreePrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid));
	HRESULT hr = m_tex->FreePrivateData(refguid);
	gRecoder->logTrace("[INFO]: Texture9 end FreePrivateData.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DTexture9::SetPriority(THIS_ DWORD PriorityNew) {
	gRecoder->logTrace("[INFO]: Texture9 call SetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = m_tex->SetPriority(PriorityNew);
	gRecoder->logTrace("[INFO]: Texture9 end SetPriority.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DTexture9::GetPriority(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call GetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_tex->GetPriority();
	gRecoder->logTrace("[INFO]: Texture9 end GetPriority.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DTexture9::PreLoad(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call PreLoad.\n");
	gRecoder->cmdCalled(0);
	m_tex->PreLoad();
	gRecoder->logTrace("[INFO]: Texture9 end PreLoad.\n");
	return;
}

STDMETHODIMP_(D3DRESOURCETYPE) WrapperDirect3DTexture9::GetType(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call GetType.\n");
	gRecoder->cmdCalled(sizeof(D3DRESOURCETYPE));
	D3DRESOURCETYPE hr = m_tex->GetType();
	gRecoder->logTrace("[INFO]: Texture9 end GetType.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DTexture9::SetLOD(THIS_ DWORD LODNew) {
	gRecoder->logTrace("[INFO]: Texture9 call SetLOD.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = m_tex->SetLOD(LODNew);
	gRecoder->logTrace("[INFO]: Texture9 end SetLOD.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DTexture9::GetLOD(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call GetLOD.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_tex->GetLOD();
	gRecoder->logTrace("[INFO]: Texture9 end GetLOD.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DTexture9::GetLevelCount(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call GetLevelCount.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_tex->GetLevelCount();
	gRecoder->logTrace("[INFO]: Texture9 end GetLevelCount.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DTexture9::SetAutoGenFilterType(THIS_ D3DTEXTUREFILTERTYPE FilterType) {
	gRecoder->logTrace("[INFO]: Texture9 call SetAutoGenFilterType.\n");
	
	gRecoder->cmdCalled(sizeof(D3DTEXTUREFILTERTYPE));
	DWORD hr = m_tex->SetAutoGenFilterType(FilterType);
	gRecoder->logTrace("[INFO]: Texture9 end SetAutoGenFilterType.\n");
	return hr;
}

STDMETHODIMP_(D3DTEXTUREFILTERTYPE) WrapperDirect3DTexture9::GetAutoGenFilterType(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call GetAutoGenFilterType.\n");
	gRecoder->cmdCalled(sizeof(D3DTEXTUREFILTERTYPE));
	D3DTEXTUREFILTERTYPE hr = m_tex->GetAutoGenFilterType();
	gRecoder->logTrace("[INFO]: Texture9 end GetAutoGenFilterType.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DTexture9::GenerateMipSubLevels(THIS) {
	gRecoder->logTrace("[INFO]: Texture9 call GenerateMipSubLevels.\n");
	gRecoder->cmdCalled(0);
	m_tex->GenerateMipSubLevels();
	gRecoder->logTrace("[INFO]: Texture9 end GenerateMipSubLevels.\n");
	return;
}

STDMETHODIMP WrapperDirect3DTexture9::GetLevelDesc(THIS_ UINT Level,D3DSURFACE_DESC *pDesc) {
	gRecoder->logTrace("[INFO]: Texture9 call GetLevelDesc.\n");
	HRESULT hr = m_tex->GetLevelDesc(Level, pDesc);
	gRecoder->logTrace("[INFO]: Texture9 end GetLevelDesc.\n");
	return hr;
}


// how to deal with texture operation?
STDMETHODIMP WrapperDirect3DTexture9::GetSurfaceLevel(THIS_ UINT Level,IDirect3DSurface9** ppSurfaceLevel) {

	gRecoder->logTrace("[INFO]: Texture9 call GetSurfaceLevel.\n");
	IDirect3DSurface9* base_surface = NULL;
	HRESULT hr = m_tex->GetSurfaceLevel(Level, &base_surface);//ppSurfaceLevel);
#ifndef GETWRAPPERDEVICE
	if (typeid(*base_surface) == typeid(IDirect3DSurface9)){
		// get the surface size
		D3DSURFACE_DESC sdesc;
		base_surface->GetDesc(&sdesc);
		gRecoder->cmdCalled(sizeof(UINT) + sizeof(void *) + sdesc.Width * sdesc.Height * 4);
	}
	else if (typeid(*base_surface) == typeid(WrapperDirect3DSurface9)){

		gRecoder->cmdCalled(sizeof(UINT) + sizeof(void *) + ((WrapperDirect3DSurface9 *)base_surface)->getSurfaceSize());
		*ppSurfaceLevel = ((WrapperDirect3DSurface9 *)base_surface)->GetSurface9();
	}
	else{
		// error type
		gRecoder->logError("[ERROR]: Textrue GetSurfaceLevel got an nuknown surface type.\n");
		*ppSurfaceLevel = base_surface;
	}
#else
	// create new wrapper surface.
	WrapperDirect3DSurface9 * wsur = WrapperDirect3DSurface9::GetWrapperSurface9(base_surface);
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(void *)+wsur->getSurfaceSize());
#if 1
#if 0
	* ppSurfaceLevel = dynamic_cast<IDirect3DSurface9 *>(wsur);
#else
	*ppSurfaceLevel = wsur;
#endif
#else
	*ppSurfaceLevel = ((WrapperDirect3DSurface9 *)base_surface)->GetSurface9();

#endif
#endif
	gRecoder->logTrace("[INFO]: Texture9 end GetSurfaceLevel.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DTexture9::LockRect(THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) {
	gRecoder->logTrace("[INFO]: Texture9 call LockRect.\n");
	if(pRect == NULL) {
		gRecoder->logTrace("[ERROR]: texture9 lock rect return to NULL?\n");
	}

	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DLOCKED_RECT) + sizeof(RECT) + sizeof(DWORD) + sizeof(void *) * 2);
	HRESULT hr = m_tex->LockRect(Level, pLockedRect, pRect, Flags);
	gRecoder->logTrace("[INFO]: Texture9 end LockRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DTexture9::UnlockRect(THIS_ UINT Level) {
	gRecoder->logTrace("[INFO]: Texture9 call UnlockRect.\n");
	gRecoder->textureUnLockRectCalled(sizeof(UINT), this->getTextureSize());
	HRESULT hr = m_tex->UnlockRect(Level);
	gRecoder->logTrace("[INFO]: Texture9 end UnlockRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DTexture9::AddDirtyRect(THIS_ CONST RECT* pDirtyRect) {
	gRecoder->logTrace("[INFO]: Texture9 call AddDirtyRect.\n");
	gRecoder->cmdCalled(sizeof(RECT) * sizeof(void *));
	HRESULT hr = m_tex->AddDirtyRect(pDirtyRect);
	gRecoder->logTrace("[INFO]: Texture9 end AddDirtyRect.\n");
	return hr;
}