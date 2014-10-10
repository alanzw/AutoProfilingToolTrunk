#include "hook_common.h"
#include "recorder.h"
#include "wrap_direct3dvertexbuffer9.h"


int WrapperDirect3DVertexBuffer9::ins_count = 0;

HashSet WrapperDirect3DVertexBuffer9::m_list;

WrapperDirect3DVertexBuffer9::WrapperDirect3DVertexBuffer9(IDirect3DVertexBuffer9* ptr, int _id): m_vb(ptr), id(_id) {
	m_list.AddMember(ptr, this);
}


WrapperDirect3DVertexBuffer9 * WrapperDirect3DVertexBuffer9::GetWrapperVertexBuffer9(IDirect3DVertexBuffer9 * ptr){
	gRecoder->logTrace("[INFO]: VertexBuffer9 Call GetWraperVertexBuffer9.\n"); 
	WrapperDirect3DVertexBuffer9 * ret = (WrapperDirect3DVertexBuffer9 *)(m_list.GetDataPtr(ptr));
	if (ret == NULL){
		ret = new WrapperDirect3DVertexBuffer9(ptr, ins_count++);
	}
	gRecoder->logTrace("[INFO]: VertexBuffer9 end GetWrapperVertexBuffer9.\n");
	return ret;
}

LPDIRECT3DVERTEXBUFFER9 WrapperDirect3DVertexBuffer9::GetVB9() {
	return m_vb;
}

inline void WrapperDirect3DVertexBuffer9::SetId(int id) {
	this->id = id;
}

inline int WrapperDirect3DVertexBuffer9::GetId() {
	return this->id;
}
/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DVertexBuffer9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_vb->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: VertexBuffer9 end QueryInterface.\n");
	return hr;
};
STDMETHODIMP_(ULONG) WrapperDirect3DVertexBuffer9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_vb->AddRef();
	gRecoder->logTrace("[INFO]: VertexBuffer9 end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DVertexBuffer9::Release(THIS) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_vb->Release();
	gRecoder->logTrace("[INFO]: VertexBuffer9 end Release.\n");
	return hr;
}

/*** IDirect3DResource9 methods ***/
STDMETHODIMP WrapperDirect3DVertexBuffer9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr = m_vb->GetDevice(ppDevice);
	gRecoder->logTrace("[INFO]: VertexBuffer9 end GetDevice.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVertexBuffer9::SetPrivateData(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call SetPrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) + sizeof(DWORD) * 2 + SizeOfData);
	HRESULT hr = m_vb->SetPrivateData(refguid, pData, SizeOfData, Flags);
	gRecoder->logTrace("[INFO]: VertexBuffer9 end SetPrivateData.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVertexBuffer9::GetPrivateData(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call GetPrivateData.\n");
	DWORD sizeOfData = 0;
	HRESULT hr = m_vb->GetPrivateData(refguid, pData, &sizeOfData);
	*pSizeOfData = sizeOfData;
	gRecoder->cmdCalled(sizeof(refguid) + sizeof(void *) * 2 + sizeof(DWORD) + sizeOfData);
	gRecoder->logTrace("[INFO]: VertexBuffer9 end GetPrivateData.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DVertexBuffer9::FreePrivateData(THIS_ REFGUID refguid) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call FreePrivateData.\n");
	gRecoder->cmdCalled(sizeof(refguid));
	HRESULT hr = m_vb->FreePrivateData(refguid);
	gRecoder->logTrace("[INFO]: VertexBuffer9 end FreePrivateData.\n");
	return hr;
}
STDMETHODIMP_(DWORD) WrapperDirect3DVertexBuffer9::SetPriority(THIS_ DWORD PriorityNew) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call SetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD) * 2);

	DWORD hr = m_vb->SetPriority(PriorityNew);
	gRecoder->logTrace("[INFO]: VertexBuffer9 end SetPriority.\n");
	return hr;
}

STDMETHODIMP_(DWORD) WrapperDirect3DVertexBuffer9::GetPriority(THIS) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call GetPriority.\n");
	gRecoder->cmdCalled(sizeof(DWORD));
	DWORD hr = m_vb->GetPriority();
	gRecoder->logTrace("[INFO]: VertexBuffer9 end GetPriority.\n");
	return hr;
}
STDMETHODIMP_(void) WrapperDirect3DVertexBuffer9::PreLoad(THIS) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call PreLoad.\n");
	gRecoder->cmdCalled(0);
	m_vb->PreLoad();
	gRecoder->logTrace("[INFO]: VertexBuffer9 end PreLoad.\n");
	return;
}
STDMETHODIMP_(D3DRESOURCETYPE) WrapperDirect3DVertexBuffer9::GetType(THIS) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call GetType.\n");
	gRecoder->cmdCalled(sizeof(D3DRESOURCETYPE));
	D3DRESOURCETYPE hr = m_vb->GetType();
	gRecoder->logTrace("[INFO]: VertexBuffer9 end GetType.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DVertexBuffer9::Lock(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call Lock.\n");
	gRecoder->vertexBufferLockCalled(sizeof(UINT) * 2 + sizeof(void *) + sizeof(DWORD), SizeToLock);

	HRESULT hr = m_vb->Lock(OffsetToLock, SizeToLock, ppbData, Flags);
	gRecoder->logTrace("[INFO]: VertexBuffer9 end Lock.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DVertexBuffer9::Unlock(THIS) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call Unlock.\n");
	gRecoder->cmdCalled(0);
	HRESULT hr = m_vb->Unlock();
	gRecoder->logTrace("[INFO]: VertexBuffer9 end Unlock.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DVertexBuffer9::GetDesc(THIS_ D3DVERTEXBUFFER_DESC *pDesc) {
	gRecoder->logTrace("[INFO]: VertexBuffer9 call GetDesc.\n");
	gRecoder->cmdCalled(sizeof(D3DVERTEXBUFFER_DESC) + sizeof(void *));
	HRESULT hr =m_vb->GetDesc(pDesc);
	gRecoder->logTrace("[INFO]: VertexBuffer9 end GetDesc.\n");
	return hr;
}
