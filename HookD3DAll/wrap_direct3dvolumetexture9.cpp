#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dvolumetexture9.h"
#include "wrap_direct3ddevice9.h"
#include "wrap_direct3dvolume9.h"

int WrapperDirect3DVolumeTexture9::ins_count = 0;
HashSet WrapperDirect3DVolumeTexture9::m_list;

inline int WrapperDirect3DVolumeTexture9::getTextureSize(){
	return this->depth * this->width * this->height * 4;
}

WrapperDirect3DVolumeTexture9::WrapperDirect3DVolumeTexture9(IDirect3DVolumeTexture9 * ptr, int _id): m_tex(ptr), id(_id){
	m_list.AddMember(ptr, this);
}

inline int WrapperDirect3DVolumeTexture9::GetID(){
	return this->id;
}

inline void WrapperDirect3DVolumeTexture9::SetID(int id){
	this->id = id;
}

#ifdef GETWRAPPERDEVICE
WrapperDirect3DVolumeTexture9 * WrapperDirect3DVolumeTexture9::GetWrapperTexture9(IDirect3DVolumeTexture9 * ptr){
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetWrapperTexture9.\n");
	WrapperDirect3DVolumeTexture9 * ret = NULL;
	ret = (WrapperDirect3DVolumeTexture9 *)m_list.GetDataPtr(ptr);
	if(ret == NULL){
		gRecoder->logTrace("[ERROR]: VolumeTexture9 create new VolumeTexture9.\n");
		ret = new WrapperDirect3DVolumeTexture9(ptr, ins_count++);
	}
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetWrapperTexture9.\n");
	return ret;
}
#endif

IDirect3DVolumeTexture9 * WrapperDirect3DVolumeTexture9::GetVolumeTex9(){
	return this->m_tex;
}

/******* IUnknown Mehtods ***********/
STDMETHODIMP WrapperDirect3DVolumeTexture9::QueryInterface(THIS_ REFIID riid, void **ppvObj){
	gRecoder->logTrace("[INFO]: VolumeTexture9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = this->m_tex->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: VolumeTexture9 end QueryInterface.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DVolumeTexture9::AddRef(THIS){
	gRecoder->logTrace("[INFO]: VolumeTexture9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr  = this->m_tex->AddRef();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end AddRef.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DVolumeTexture9::Release(THIS){
	gRecoder->logTrace("[INFO]: VolumeTexture9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = this->m_tex->Release();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end Release.\n");
	return hr;
}

/*************** Methods **************/
STDMETHODIMP WrapperDirect3DVolumeTexture9::GetDevice(THIS_ IDirect3DDevice9** ppDevice)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	IDirect3DDevice9 * base_device = NULL;
	HRESULT hr = this->m_tex->GetDevice(ppDevice);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetDevice.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call SetPrivateData.\n");

	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) * 2 + SizeOfData);
	HRESULT hr = this->m_tex->SetPrivateData(refguid, pData, SizeOfData, Flags);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end SetPrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetPrivateData.\n");
	DWORD sizeOfData = 0;
	HRESULT hr = this->m_tex->GetPrivateData(refguid, pData, &sizeOfData);
	*pSizeOfData = sizeOfData;
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) * 2 + sizeof(DWORD) + sizeOfData);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetPrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::FreePrivateData(THIS_ REFGUID refguid)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call FreePrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid));
	HRESULT hr = this->m_tex->FreePrivateData(refguid);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end FreePrivateData.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DVolumeTexture9::SetPriority(THIS_ DWORD PriorityNew)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call SetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = this->m_tex->SetPriority(PriorityNew);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end SetPriority.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DVolumeTexture9::GetPriority(THIS)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = this->m_tex->GetPriority();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetPriority.\n");
	return hr;
}
STDMETHODIMP_(void) WrapperDirect3DVolumeTexture9::PreLoad(THIS)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call PreLoad.\n");
	gRecoder->cmdCalled(0);
	this->m_tex->PreLoad();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end PreLoad.\n");
}
STDMETHODIMP_(D3DRESOURCETYPE) WrapperDirect3DVolumeTexture9::GetType(THIS)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetType.\n");
	gRecoder->cmdCalled(sizeof(D3DRESOURCETYPE));
	D3DRESOURCETYPE hr = this->m_tex->GetType();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetType.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DVolumeTexture9::SetLOD(THIS_ DWORD LODNew)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call SetLOD.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = this->m_tex->SetLOD(LODNew);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end SetLOD.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DVolumeTexture9::GetLOD(THIS)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetLOD.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = this->m_tex->GetLOD();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetLOD.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DVolumeTexture9::GetLevelCount(THIS)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetLevelCount.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = this->m_tex->GetLevelCount();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetLevelCount.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::SetAutoGenFilterType(THIS_ D3DTEXTUREFILTERTYPE FilterType)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call SetAutoGenFilterType.\n");
	gRecoder->cmdCalled(sizeof(D3DTEXTUREFILTERTYPE));
	HRESULT hr = this->m_tex->SetAutoGenFilterType(FilterType);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end SetAutoGenFilterType.\n");
	return hr;
}
STDMETHODIMP_(D3DTEXTUREFILTERTYPE) WrapperDirect3DVolumeTexture9::GetAutoGenFilterType(THIS)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetAutoGenFilterType.\n");
	gRecoder->cmdCalled(sizeof(D3DTEXTUREFILTERTYPE));
	D3DTEXTUREFILTERTYPE hr = this->m_tex->GetAutoGenFilterType();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetAutoGenFilterType.\n");
	return hr;
}
STDMETHODIMP_(void) WrapperDirect3DVolumeTexture9::GenerateMipSubLevels(THIS)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GenerateMipSubLevel.\n");
	gRecoder->cmdCalled(0);
	this->m_tex->GenerateMipSubLevels();
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GenerateMipSubLevels.\n");
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::GetLevelDesc(THIS_ UINT Level,D3DVOLUME_DESC *pDesc)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetLevelDesc.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DVOLUME_DESC) + sizeof(void *));
	HRESULT hr = this->m_tex->GetLevelDesc(Level, pDesc);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetLevelDesc.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::GetVolumeLevel(THIS_ UINT Level,IDirect3DVolume9** ppVolumeLevel)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call GetVolumeLevel.\n");
	IDirect3DVolume9 * tpVolumeLevel = NULL;
	HRESULT hr = this->m_tex->GetVolumeLevel(Level, &tpVolumeLevel);
	
#ifndef GETWRAPPERDEVICE
	if (typeid(*tpVolumeLevel) == typeid(IDirect3DVolume9)){
		D3DVOLUME_DESC vdesc;
		tpVolumeLevel->GetDesc(&vdesc);


		// TODO : how to calculate the volume size
		gRecoder->cmdCalled(sizeof(UINT) + sizeof(void *) + vdesc.Height * vdesc.Width * vdesc.Depth);

		*ppVolumeLevel = tpVolumeLevel;
	}
	else if (typeid(*tpVolumeLevel) == typeid(WrapperDirect3DVolume9)){

		WrapperDirect3DVolume9 * wv = (WrapperDirect3DVolume9 *)tpVolumeLevel;
		gRecoder->cmdCalled(sizeof(UINT) + sizeof(void *) + wv->getVolumeSize());

		*ppVolumeLevel = wv->GetIDirect3DVolume9();
	}
	else{
		// error type

		gRecoder->logError("[ERROR]: VolumeTexture GetVolumeLevel got an unknown type.\n");
		*ppVolumeLevel = tpVolumeLevel;
	}
#else
	WrapperDirect3DVolume9 * wv = WrapperDirect3DVolume9 ::GetWrapperDirect3DVolume9(tpVolumeLevel);
	gRecoder->cmdCalled(sizeof(UINT)+sizeof(void *)+wv->getVolumeSize());

	*ppVolumeLevel = dynamic_cast<IDirect3DVolume9 *>(wv);

#endif
	gRecoder->logTrace("[INFO]: VolumeTexture9 end GetVolumeLevel.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::LockBox(THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call LockBox.\n");
	gRecoder->cmdCalled(sizeof(UINT) + sizeof(D3DLOCKED_BOX) + sizeof(D3DBOX) + sizeof(DWORD));

	HRESULT hr = this->m_tex->LockBox(Level, pLockedVolume, pBox, Flags);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end LockBox.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::UnlockBox(THIS_ UINT Level)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call UnlockBox.\n");
	gRecoder->cmdCalled(sizeof(UINT));
	HRESULT hr = this->m_tex->UnlockBox(Level);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end UnlockBox.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolumeTexture9::AddDirtyBox(THIS_ CONST D3DBOX* pDirtyBox)
{
	gRecoder->logTrace("[INFO]: VolumeTexture9 call AddDirtyBox.\n");
	gRecoder->cmdCalled(sizeof(D3DBOX) + sizeof(void *));
	HRESULT hr = this->m_tex->AddDirtyBox(pDirtyBox);
	gRecoder->logTrace("[INFO]: VolumeTexture9 end AddDirtyBox.\n");
	return hr;
}