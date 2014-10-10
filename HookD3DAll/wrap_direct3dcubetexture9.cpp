#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dcubetexture9.h"
#include "wrap_direct3dsurface9.h"
#include "wrap_direct3ddevice9.h"

int WrapperDirect3DCubeTexture9::ins_count = 0;
HashSet WrapperDirect3DCubeTexture9::m_list;

int WrapperDirect3DCubeTexture9::getTextureSize(){
	return edgeLength;
}

WrapperDirect3DCubeTexture9::WrapperDirect3DCubeTexture9(IDirect3DCubeTexture9* ptr, int _id): m_cube_tex(ptr), id(_id) {
	m_list.AddMember(ptr, this);
}

IDirect3DCubeTexture9* WrapperDirect3DCubeTexture9::GetCubeTex9(){
	return this->m_cube_tex;
}

int WrapperDirect3DCubeTexture9::GetID(){
	return this->id;
}

inline void WrapperDirect3DCubeTexture9::SetID(int id){
	this->id = id;
}
#ifdef GETWRAPPERDEVICE
WrapperDirect3DCubeTexture9* WrapperDirect3DCubeTexture9::GetWrapperCubeTexture9(IDirect3DCubeTexture9* ptr){
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetWrapperCubeTexture9.\n");
	WrapperDirect3DCubeTexture9* ret = (WrapperDirect3DCubeTexture9*)(m_list.GetDataPtr(ptr));
	//ret = WrapperDirect3DCubeTexture9::GetWrapperCubeTexture9(ptr);
	if(ret == NULL) {
		ret = new WrapperDirect3DCubeTexture9(ptr, ins_count++);
		gRecoder->logTrace("[INFO]: create new CubeTexture, total:%d.\n", ins_count);
	}

	gRecoder->logTrace("[INFO]: CubeTexture9 end GetWrapperCubeTexture9.\n");
	return ret;
}
#endif

/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DCubeTexture9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_cube_tex->QueryInterface(riid, ppvObj);
	*ppvObj = this;	
	if (hr == E_NOINTERFACE){
		gRecoder->logTrace("[ERROR]: CubeTexture QueryInterface failed. riid: 0x%p\n", riid);
	}
	gRecoder->logTrace("[INFO]: CubeTexture9 end QueryInterface.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DCubeTexture9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_cube_tex->AddRef();
	gRecoder->logTrace("[INFO]: CubeTexture9 end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DCubeTexture9::Release(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	HRESULT hr = m_cube_tex->Release();
	gRecoder->logTrace("[INFO]: CubeTexture9 end Release.\n");
	return hr;
}

/*** IDirect3DBaseTexture9 methods ***/
STDMETHODIMP WrapperDirect3DCubeTexture9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	IDirect3DDevice9* base = NULL;
	HRESULT hr = this->m_cube_tex->GetDevice(&base);

	WrapperDirect3DDevice9 * ret = NULL; 
	//WrapperDirect3DDevice9::GetWrapperDevice9(base);
#ifndef GETWRAPPERDEVICE	
	if (typeid(*base) == typeid(IDirect3DDevice9)){
		*ppDevice = base;
	}
	else if (typeid(*base) == typeid(WrapperDirect3DDevice9)){
		gRecoder->logError("[ERROR]: Cube Texture GetDevice got a WrapperDevice.\n");
		*ppDevice = ((WrapperDirect3DDevice9 *)base)->GetIDirect3DDevice9();
	}
	else{
		gRecoder->logError("[ERROR]: Cube Texture GetDevice got a Unknow type.\n");
		*ppDevice = base;
	}
#else
	gRecoder->logError("[ERROR]: Cube Texture GetDevice got a WrapperDevice.\n");
#if 0
	*ppDevice = ((WrapperDirect3DDevice9 *)base)->GetIDirect3DDevice9();
#else
	*ppDevice = base;
#endif
	gRecoder->cmdCalled(sizeof(void*));
#endif
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetDevice.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DCubeTexture9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call SetPrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) * 2 + SizeOfData);
	HRESULT hr = m_cube_tex->SetPrivateData(refguid, pData, SizeOfData, Flags);
	gRecoder->logTrace("[INFO]: CubeTexture9 end SetPrivateData.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DCubeTexture9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetPrivateData.\n");
	DWORD sizeOfData = 0;
	HRESULT hr = m_cube_tex->GetPrivateData(refguid, pData, &sizeOfData);

	*pSizeOfData = sizeOfData;
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) + sizeOfData);
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetPrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DCubeTexture9::FreePrivateData(THIS_ REFGUID refguid) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call FreePrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid));
	HRESULT hr =m_cube_tex->FreePrivateData(refguid);
	gRecoder->logTrace("[INFO]: CubeTexture9 end FreePrivateData.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DCubeTexture9::SetPriority(THIS_ DWORD PriorityNew) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call SetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = m_cube_tex->SetPriority(PriorityNew);
	gRecoder->logTrace("[INFO]: CubeTexture9 end SetPrioriry.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DCubeTexture9::GetPriority(THIS) {
	gRecoder->cmdCalled(sizeof(DWORD));
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetPriority.\n");
	DWORD hr = m_cube_tex->GetPriority();
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetPriority.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DCubeTexture9::PreLoad(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call PreLoad.\n");
	gRecoder->cmdCalled(0);
	m_cube_tex->PreLoad();
	gRecoder->logTrace("[INFO]: CubeTexture9 end PreLoad.\n");
	return;
}

STDMETHODIMP_(D3DRESOURCETYPE) WrapperDirect3DCubeTexture9::GetType(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetType.\n");
	gRecoder->cmdCalled(sizeof(D3DRESOURCETYPE));
	D3DRESOURCETYPE hr = m_cube_tex->GetType();
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetType.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DCubeTexture9::SetLOD(THIS_ DWORD LODNew) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call SetLOD.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = m_cube_tex->SetLOD(LODNew);
	gRecoder->logTrace("[INFO]: CubeTexture9 end SetLOD.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DCubeTexture9::GetLOD(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetLOD.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_cube_tex->GetLOD();
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetLOD.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DCubeTexture9::GetLevelCount(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetLevelCount.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_cube_tex->GetLevelCount();
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetLevelCount.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DCubeTexture9::SetAutoGenFilterType(THIS_ D3DTEXTUREFILTERTYPE FilterType) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call SetAutoGenFilterTypes.\n");
	gRecoder->cmdCalled(sizeof(D3DTEXTUREFILTERTYPE));

	HRESULT hr =m_cube_tex->SetAutoGenFilterType(FilterType);
	gRecoder->logTrace("[INFO]: CubeTexture9 end SetAutoGenFilterType.\n");
	return hr;
}

STDMETHODIMP_(D3DTEXTUREFILTERTYPE) WrapperDirect3DCubeTexture9::GetAutoGenFilterType(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetAutoGenFilterType.\n");
	gRecoder->cmdCalled(sizeof(D3DTEXTUREFILTERTYPE));
	D3DTEXTUREFILTERTYPE hr = m_cube_tex->GetAutoGenFilterType();
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetAutoGenFilterType.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DCubeTexture9::GenerateMipSubLevels(THIS) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GenerateMipSubLevel.\n");
	gRecoder->cmdCalled(0);
	m_cube_tex->GenerateMipSubLevels();
	gRecoder->logTrace("[INFO]: CubeTexture9 end GenerateMipSubLevel.\n");
	return;
}

STDMETHODIMP WrapperDirect3DCubeTexture9::GetLevelDesc(THIS_ UINT Level,D3DSURFACE_DESC *pDesc) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call GetLevelDesc.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(void *) + sizeof(D3DSURFACE_DESC));

	HRESULT hr = m_cube_tex->GetLevelDesc(Level, pDesc);
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetLevelDesc.\n");
	return hr;
}

#ifndef GETWRAPPDERDEVICE
// the get surface is to create a new surface
STDMETHODIMP WrapperDirect3DCubeTexture9::GetCubeMapSurface(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface) {
	gRecoder->logTrace("[INFO]: CubeTexture9 cal GetCubMapSurface.\n");
	IDirect3DSurface9* base_surface = NULL;
	HRESULT hr = m_cube_tex->GetCubeMapSurface(FaceType, Level, &base_surface);

	WrapperDirect3DSurface9* surface = NULL;
	surface = WrapperDirect3DSurface9::GetWrapperSurface9(base_surface);
#if 0
	if(surface == NULL) {

		surface = new WrapperDirect3DSurface9(base_surface, WrapperDirect3DSurface9::ins_count++);
	}
#endif
	*ppCubeMapSurface = surface;
	gRecoder->logTrace("[INFO]: CubeTexture9 end GetCubeMapSurface.\n");
	return hr;
}
#endif

STDMETHODIMP WrapperDirect3DCubeTexture9::LockRect(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call LockRect.\n");
	if(pRect == NULL) {
		gRecoder->logTrace("[ERROR]: texture9 lock texture reture to NULL?\n");
	}
	gRecoder->cmdCalled(sizeof(D3DCUBEMAP_FACES) + sizeof(UINT) + sizeof(D3DLOCKED_RECT) + sizeof(RECT) + sizeof(DWORD) + sizeof(void *) * 2);
	HRESULT hr = m_cube_tex->LockRect(FaceType, Level, pLockedRect, pRect, Flags);
	gRecoder->logTrace("[INFO]: CubeTexture9 end LockRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DCubeTexture9::UnlockRect(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call UnlockRect.\n");
	gRecoder->textureUnLockRectCalled(sizeof(D3DCUBEMAP_FACES) + sizeof(UINT), this->getTextureSize());

	HRESULT hr = m_cube_tex->UnlockRect(FaceType, Level);
	gRecoder->logTrace("[INFO]: CubeTexture9 end UnlockRect.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DCubeTexture9::AddDirtyRect(THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect) {
	gRecoder->logTrace("[INFO]: CubeTexture9 call AddDirtyRect.\n");
	gRecoder->cmdCalled(sizeof(D3DCUBEMAP_FACES) + sizeof(RECT) + sizeof(void *));
	HRESULT hr = m_cube_tex->AddDirtyRect(FaceType, pDirtyRect);
	gRecoder->logTrace("[INFO]: CubeTexture9 end AddDirtyRect.\n");
	return hr;
}