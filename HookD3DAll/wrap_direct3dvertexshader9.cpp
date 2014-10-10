#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dvertexshader9.h"


int WrapperDirect3DVertexShader9::ins_count = 0;
HashSet WrapperDirect3DVertexShader9::m_list;

int WrapperDirect3DVertexShader9::getShaderSize(){
#ifdef TEST_VERTEX_SHADER_SIZE

	UINT size =0;
	this->m_vs->GetFunction(NULL, &size);
	gRecoder->logError("[INFO]: VertexShader get shader size:%d, funcCount * sizeof(DWORD) = %d.\n", size, sizeof(DWORD) * this->funcCount);

#endif
	return sizeof(DWORD) * this->funcCount;

}

WrapperDirect3DVertexShader9::WrapperDirect3DVertexShader9(IDirect3DVertexShader9* ptr, int _id): m_vs(ptr), id(_id) {
	m_list.AddMember(ptr, this);
}

inline int WrapperDirect3DVertexShader9::GetID() {
	return this->id;
}

inline void WrapperDirect3DVertexShader9::SetID(int id) {
	this->id = id;
}

IDirect3DVertexShader9* WrapperDirect3DVertexShader9::GetVS9() {
	return m_vs;
}

#ifdef GETWRAPPERDEVICE
WrapperDirect3DVertexShader9* WrapperDirect3DVertexShader9::GetWrapperVertexShader(IDirect3DVertexShader9* ptr) {
	gRecoder->logTrace("[INFO]: VertexShader9 call GetWrapperVertexShader.\n");
	WrapperDirect3DVertexShader9* ret = (WrapperDirect3DVertexShader9*)( m_list.GetDataPtr(ptr) );
	if(ret == NULL) {

		ret = new WrapperDirect3DVertexShader9(ptr, ins_count++);
	}
	gRecoder->logTrace("[INFO]: VertexShader9 end GetWrapperVertexShader.\n");
	return ret;
}
#endif
/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DVertexShader9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: VertexShader9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_vs->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: VertexShader9 end QueryInterface.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DVertexShader9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: VertexShader9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_vs->AddRef();
	gRecoder->logTrace("[INFO]: VertexShader9 end AddRef.\n");
	return hr;
}
STDMETHODIMP_(ULONG) WrapperDirect3DVertexShader9::Release(THIS) {
	gRecoder->logTrace("[INFO]: VertexShader9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_vs->Release();
	gRecoder->logTrace("[INFO]: VertexShader9 end Release.\n");
	return hr;
}

/*** IDirect3DVertexShader9 methods ***/
STDMETHODIMP WrapperDirect3DVertexShader9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: VertexShader9 call GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr = m_vs->GetDevice(ppDevice);
	gRecoder->logTrace("[INFO]: VertexShader9 end GetDevice.\n");
	return hr;
}
STDMETHODIMP WrapperDirect3DVertexShader9::GetFunction(THIS_ void* ptr,UINT* pSizeOfData) {
	gRecoder->logTrace("[INFO]: VertexShader9 call GetFunction.\n");
	UINT sizeOfData = 0;
	HRESULT hr = m_vs->GetFunction(ptr, &sizeOfData);
	gRecoder->cmdCalled(sizeof(void *) * 2 + sizeOfData);
	gRecoder->logTrace("[INFO]: VertexShader9 end GetFunction.\n");
	return hr;
}

