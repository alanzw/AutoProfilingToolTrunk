#include "hook_common.h"
#include "recorder.h"
#include "wrap_direct3dpixelshader9.h"

int WrapperDirect3DPixelShader9::ins_count = 0;
HashSet WrapperDirect3DPixelShader9::m_list;

WrapperDirect3DPixelShader9::WrapperDirect3DPixelShader9(IDirect3DPixelShader9* ptr, int _id): m_ps(ptr), id(_id) {

	m_list.AddMember(ptr, this);
}

inline void WrapperDirect3DPixelShader9::SetID(int id) {
	this->id = id;
}

inline int WrapperDirect3DPixelShader9::GetID() {
	return this->id;
}

IDirect3DPixelShader9* WrapperDirect3DPixelShader9::GetPS9() {
	return m_ps;
}

#ifdef GETWRAPPERDEVICE
WrapperDirect3DPixelShader9* WrapperDirect3DPixelShader9::GetWrapperPixelShader(IDirect3DPixelShader9* ptr) {

	gRecoder->logTrace("[INFO]: PixelShader9 call GetWrapperPixelShader.\n");
	WrapperDirect3DPixelShader9* ret = (WrapperDirect3DPixelShader9*)( m_list.GetDataPtr(ptr) );
	if(ret == NULL) {
		ret = new WrapperDirect3DPixelShader9(ptr, ins_count++);
	}
	gRecoder->logTrace("[INFO]: PixelShader9 end GetWapperPixelShader.\n");
	return ret;
}
#endif

/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DPixelShader9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: PixelShader9 call QueryInterface.\n");
	HRESULT hr = m_ps->QueryInterface(riid, ppvObj);

	gRecoder->cmdCalled(sizeof(riid)+sizeof(void *));

	*ppvObj = this;
	gRecoder->logTrace("[INFO]: PixelShader9 end QueryInterface.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DPixelShader9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: PixelShader9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_ps->AddRef();
	gRecoder->logTrace("[INFO]: PixelShader9 end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DPixelShader9::Release(THIS) {
	gRecoder->logTrace("[INFO]: PixelShader9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_ps->Release();
	gRecoder->logTrace("[INFO]: PixelShader9 end Release.\n");
	return hr;
}

/*** IDirect3DPixelShader9 methods ***/
STDMETHODIMP WrapperDirect3DPixelShader9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: PixelShader9 call GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void*));
	HRESULT hr = m_ps->GetDevice(ppDevice);
	gRecoder->logTrace("[INFO]: PixelShader9 end GetDevice.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DPixelShader9::GetFunction(THIS_ void* ptr,UINT* pSizeOfData) {
	gRecoder->logTrace("[INFO]: PixelShader9 call GetFunction.\n");
	UINT sizeOfData = 0;
	HRESULT hr = m_ps->GetFunction(ptr, &sizeOfData);
	*pSizeOfData = sizeOfData;
	gRecoder->cmdCalled(sizeof(void *) * 2 + sizeOfData);
	gRecoder->logTrace("[INFO]: PixelShader9 end GetFunction.\n");
	return hr;
}