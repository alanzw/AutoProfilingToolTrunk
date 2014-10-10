#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dindexbuffer9.h"
#include "wrap_direct3ddevice9.h"
static int max_ib = 0;
int WrapperDirect3DIndexBuffer9::ins_count = 0;
HashSet WrapperDirect3DIndexBuffer9::m_list;

WrapperDirect3DIndexBuffer9::WrapperDirect3DIndexBuffer9(IDirect3DIndexBuffer9* ptr, int _id): m_ib(ptr), id(_id) {
	m_list.AddMember(ptr, this);
}

int mesh_arr[4];


IDirect3DIndexBuffer9* WrapperDirect3DIndexBuffer9::GetIB9() {
	return m_ib;
}

inline void WrapperDirect3DIndexBuffer9::SetID(int id) {
	this->id = id;
}

inline int WrapperDirect3DIndexBuffer9::GetID() {
	return id;
}
#ifdef GETWRAPPERDEVICE

WrapperDirect3DIndexBuffer9* WrapperDirect3DIndexBuffer9::GetWrapperIndexedBuffer9(IDirect3DIndexBuffer9* base_indexed_buffer) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call GetWrapperIndexedBuffer9.\n");
	WrapperDirect3DIndexBuffer9* ret = (WrapperDirect3DIndexBuffer9*)( m_list.GetDataPtr( (PVOID)base_indexed_buffer ) );

	if(ret == NULL) {
		gRecoder->logTrace("[INFO]: new WrapperIndexBuffer, id:%d.\n", ins_count);
		ret = new WrapperDirect3DIndexBuffer9(base_indexed_buffer, ins_count++);
	}
	gRecoder->logTrace("[INFO]: IndexBuffer9 end GetWrapperIndexedBuffer9.\n");
	return ret;
}
#endif

/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DIndexBuffer9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_ib->QueryInterface(riid, ppvObj);
	*ppvObj  = this;
	gRecoder->logTrace("[INFO]: IndexBuffer9 end QueryInterface.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DIndexBuffer9::AddRef(THIS) { 
	gRecoder->logTrace("[INFO]: IndexBuffer9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_ib->AddRef();
	gRecoder->logTrace("[INFO]: IndexBuffer9 end AddRef.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DIndexBuffer9::Release(THIS) { 
	gRecoder->logTrace("[INFO]: IndexBuffer9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_ib->Release();
	gRecoder->logTrace("[INFO]: IndexBuffer9 end Release.\n");
	return hr;

}

/*** IDirect3DResource9 methods ***/
STDMETHODIMP WrapperDirect3DIndexBuffer9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) { 
	gRecoder->logTrace("[INFO]: IndexBuffer9 call GetDevice.\n");
	IDirect3DDevice9* base = NULL;
	HRESULT hr = this->m_ib->GetDevice(&base);
	WrapperDirect3DDevice9 * ret = NULL;
#ifndef GETWRAPPERDEVICE	
	if (typeid(*base) == typeid(IDirect3DDevice9)){
		*ppDevice = base;
	}
	else if (typeid(*base) == typeid(WrapperDirect3DDevice9)){
		gRecoder->logError("[ERROR]: Index Buffer GetDevice got a WrapperDevice.\n");
		*ppDevice = ((WrapperDirect3DDevice9 *)base)->GetIDirect3DDevice9();
	}
	else{
		gRecoder->logError("[ERROR]: Index Buffer GetDevice got a Unknow type.\n");
		*ppDevice = base;
	}
#else
	ret = WrapperDirect3DDevice9::GetWrapperDevice9(base);

#if 0
	*ppDevice = dynamic_cast<IDirect3DDevice9 *>(ret);
#else
	*ppDevice = ret;
#endif
#endif

	gRecoder->cmdCalled(sizeof(void *));

	gRecoder->logTrace("[INFO]: IndexBuffer9 end GetDevice.\n");
	return hr;
	//return m_ib->GetDevice(ppDevice); 
}

STDMETHODIMP WrapperDirect3DIndexBuffer9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call SetPrivateData.\n");
	HRESULT hr = m_ib->SetPrivateData(refguid, pData, SizeOfData, Flags);

	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) * 2 + SizeOfData);
	gRecoder->logTrace("[INFO]: IndexBuffer9 end SetPrivateData.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DIndexBuffer9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) { 
	gRecoder->logTrace("[INFO]: IndexBuffer9 call GetPrivateData.\n");
	DWORD sizeOfData = 0;
	HRESULT hr = m_ib->GetPrivateData(refguid, pData, &sizeOfData);

	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) * 2 + sizeOfData);
	gRecoder->logTrace("[INFO]: IndexBuffer9 end GetPrivateData.\n");
	return hr;

}
STDMETHODIMP WrapperDirect3DIndexBuffer9::FreePrivateData(THIS_ REFGUID refguid) { 
	gRecoder->logTrace("[INFO]: IndexBuffer9 call FreePrivateData.\n"); 
	gRecoder->cmdCalled(sizeof(refguid));

	HRESULT hr = m_ib->FreePrivateData(refguid); 
	gRecoder->logTrace("[INFO]: IndexBuffer9 end FreePrivateData.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DIndexBuffer9::SetPriority(THIS_ DWORD PriorityNew) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call SetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);
	DWORD hr = m_ib->SetPriority(PriorityNew);
	gRecoder->logTrace("[INFO]: IndexBuffer9 end SetPriority.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DIndexBuffer9::GetPriority(THIS) { 
	gRecoder->logTrace("[INFO]: IndexBuffer9 call GetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_ib->GetPriority(); 
	gRecoder->logTrace("[INFO]: IndexBuffer9 end GetPriority.\n");
	return hr;
}

STDMETHODIMP_(void) WrapperDirect3DIndexBuffer9::PreLoad(THIS) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call PreLoad.\n");
	gRecoder->cmdCalled(0);
	m_ib->PreLoad();
	gRecoder->logTrace("[INFO]: IndexBuffer9 end PreLoad.\n");
	return;
}

STDMETHODIMP_(D3DRESOURCETYPE) WrapperDirect3DIndexBuffer9::GetType(THIS) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call PreLoad.\n");
	gRecoder->cmdCalled(sizeof(D3DRESOURCETYPE));
	D3DRESOURCETYPE hr = m_ib->GetType();
	gRecoder->logTrace("[INFO]: IndexBuffer9 end PreLoad.\n");
	return hr;

}

STDMETHODIMP WrapperDirect3DIndexBuffer9::Lock(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call Lock.\n");
	void * tmp = NULL;
	gRecoder->indexBufferLockCalled(sizeof(UINT) * 2 + sizeof(void *) + sizeof(DWORD), SizeToLock);
	HRESULT hr = m_ib->Lock(OffsetToLock, SizeToLock, ppbData, Flags);
	gRecoder->logTrace("[INFO]: IndexBuffer9 end Lock.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DIndexBuffer9::Unlock(THIS) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call Unlock.\n");
	gRecoder->cmdSendAndCalled(0);

	HRESULT hr = m_ib->Unlock();
	gRecoder->logTrace("[INFO]: IndexBuffer9 end Unlock.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DIndexBuffer9::GetDesc(THIS_ D3DINDEXBUFFER_DESC *pDesc) {
	gRecoder->logTrace("[INFO]: IndexBuffer9 call GetDesc.\n");
	gRecoder->cmdCalled(sizeof(void *)+sizeof(D3DINDEXBUFFER_DESC));
	HRESULT hr = m_ib->GetDesc(pDesc);

	gRecoder->logTrace("[INFO]: IndexBuffer9 end GetDesc.\n");
	return hr;
}
