#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dvolume9.h"
#include "wrap_direct3ddevice9.h"
int WrapperDirect3DVolume9::ins_count = 0;
HashSet WrapperDirect3DVolume9::m_list;

int WrapperDirect3DVolume9::getVolumeSize(){
	
	D3DVOLUME_DESC vdesc;
	this->m_d3dvolume->GetDesc(&vdesc);
	return vdesc.Width * vdesc.Height * vdesc.Depth * 4;

}

WrapperDirect3DVolume9::WrapperDirect3DVolume9(IDirect3DVolume9 *ptr, int _id):m_d3dvolume(ptr),id(_id){
	m_list.AddMember(ptr, this);
}

inline int WrapperDirect3DVolume9::GetID(){
	return this->id;
}
inline void WrapperDirect3DVolume9::SetID(int id){
	this->id =id;
}
#ifdef GETWRAPPERDEVICE
WrapperDirect3DVolume9 * WrapperDirect3DVolume9::GetWrapperDirect3DVolume9(IDirect3DVolume9 *ptr){
	gRecoder->logTrace("[INFO]: Volume9 call GetWrapperDirect3DVolume9.\n");
	WrapperDirect3DVolume9 * ret = NULL;
	ret = (WrapperDirect3DVolume9 *)m_list.GetDataPtr(ptr);
	if(ret == NULL){
	}
	gRecoder->logTrace("[INFO]: Volume9 end GetWrapperDirect3DVolume9.\n");
	return ret;
}
#endif
IDirect3DVolume9 * WrapperDirect3DVolume9::GetIDirect3DVolume9(){
	return this->m_d3dvolume;
}

/********************** IUnknown Methods *************/
STDMETHODIMP WrapperDirect3DVolume9::QueryInterface(THIS_ REFIID riid, void **ppvObj){
	gRecoder->logTrace("[INFO]: Volume9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr =this->m_d3dvolume->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: Volume9 end QueryInterface.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DVolume9::AddRef(THIS){
	gRecoder->logTrace("[INFO]: Volume9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = this->m_d3dvolume->AddRef();
	gRecoder->logTrace("[INFO]: Volume9 end AddRef.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DVolume9::Release(THIS){
	gRecoder->logTrace("[INFO]: Volume9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = this->m_d3dvolume->Release();
	gRecoder->logTrace("[INFO]: Volume9 end Release.\n");
	return hr;
}

/*************** Methods *************************/
STDMETHODIMP WrapperDirect3DVolume9::GetDevice(THIS_ IDirect3DDevice9** ppDevice)
{
	gRecoder->logTrace("[INFO]: Volume9 call GetDevice.\n"); 
	gRecoder->cmdCalled(sizeof(void *));
	IDirect3DDevice9* base_device = NULL;
	HRESULT hr = this->m_d3dvolume->GetDevice(&base_device);
#ifndef GETWRAPPERDEVICE
	if (typeid(*base_device) == typeid(IDirect3DDevice9)){
		*ppDevice = base_device;
	}
	else if (typeid(*base_device) == typeid(WrapperDirect3DDevice9)){
		*ppDevice = ((WrapperDirect3DDevice9*)base_device)->GetIDirect3DDevice9();
	}
	else{
		// error type
		*ppDevice = base_device;
	}
#else
#if 1
	*ppDevice = dynamic_cast<IDirect3DDevice9 *>(WrapperDirect3DDevice9::GetWrapperDevice9(base_device));
#else
	*ppDevice = ((WrapperDirect3DDevice9*)base_device)->GetIDirect3DDevice9();
#endif
	gRecoder->cmdCalled(sizeof(void *));
#endif
	gRecoder->logTrace("[INFO]: Volume9 end GetDevice.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolume9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	gRecoder->logTrace("[INFO]: Volume9 call SetPrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) * 2 + SizeOfData);
	HRESULT hr =this->m_d3dvolume->SetPrivateData(refguid, pData, SizeOfData, Flags);
	gRecoder->logTrace("[INFO]: Volume9 end SetPrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolume9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	gRecoder->logTrace("[INFO]: Volume9 call GetPrivateData.\n");
	DWORD sizeOfData = 0;
	HRESULT hr =this->m_d3dvolume->GetPrivateData(refguid, pData, &sizeOfData);
	*pSizeOfData = sizeOfData;
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) * 2 + sizeof(DWORD) + sizeOfData);
	gRecoder->logTrace("[INFO]: Volume9 end GetPrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolume9::FreePrivateData(THIS_ REFGUID refguid)
{
	gRecoder->logTrace("[INFO]: Volume9 call FreePrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid));

	HRESULT hr =this->m_d3dvolume->FreePrivateData(refguid);
	gRecoder->logTrace("[INFO]: Volume9 end FreePrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolume9::GetContainer(THIS_ REFIID riid,void** ppContainer)
{
	gRecoder->logTrace("[INFO]: Volume9 call GetContainer.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr =this->m_d3dvolume->GetContainer(riid, ppContainer);
	gRecoder->logTrace("[INFO]: Volume9 end GetContainer.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolume9::GetDesc(THIS_ D3DVOLUME_DESC *pDesc)
{
	gRecoder->logTrace("[INFO]: Volume9 call GetDesc.\n");
	gRecoder->cmdCalled(sizeof(void *) + sizeof(D3DVOLUME_DESC));
	HRESULT hr =this->m_d3dvolume->GetDesc(pDesc);
	gRecoder->logTrace("[INFO]: Volume9 end GetDesc.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolume9::LockBox(THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags)
{
	gRecoder->logTrace("[INFO]: Volume9 call LockBox.\n");
	gRecoder->cmdCalled(sizeof(D3DLOCKED_BOX) + sizeof(D3DBOX) + sizeof(DWORD) + sizeof(void *) * 2);
	HRESULT hr =this->m_d3dvolume->LockBox(pLockedVolume, pBox, Flags);
	gRecoder->logTrace("[INFO]: Volume9 end LockBox.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVolume9::UnlockBox(THIS)
{
	gRecoder->logTrace("[INFO]: Volume9 call UnlockBox.\n");
	gRecoder->cmdCalled(0);
	HRESULT hr =this->m_d3dvolume->UnlockBox();
	gRecoder->logTrace("[INFO]: Volume9 end UnlockBox.\n");
	return hr;
}
