#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dstateblock9.h"
#include "wrap_direct3ddevice9.h"
int WrapperDirect3DStateBlock9::ins_count = 0;

WrapperDirect3DStateBlock9::WrapperDirect3DStateBlock9(IDirect3DStateBlock9* _sb, int _id): m_sb(_sb), id(_id){

}

inline int WrapperDirect3DStateBlock9::GetID() {
	return this->id;
}

inline void WrapperDirect3DStateBlock9::SetID(int id) {
	this->id = id;
}

inline IDirect3DStateBlock9* WrapperDirect3DStateBlock9::GetSB9() {
	return this->m_sb;
}


/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DStateBlock9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: StateBlock9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid));
	HRESULT hr = m_sb->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: StateBlock9 end QueryInterface.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DStateBlock9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: StateBlock9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_sb->AddRef();
	gRecoder->logTrace("[INFO]: StateBlock9 end AddRef.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DStateBlock9::Release(THIS) {
	gRecoder->logTrace("[INFO]: StateBlock9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_sb->Release();
	gRecoder->logTrace("[INFO]: StateBlock9 end Release.\n");
	return hr;
}

/*** IDirect3DStateBlock9 methods ***/
STDMETHODIMP WrapperDirect3DStateBlock9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: StateBlock9 call GetDevice.\n");
	IDirect3DDevice9* base = NULL;
	HRESULT hr = this->m_sb->GetDevice(&base);

	gRecoder->cmdCalled(sizeof(void *));
	WrapperDirect3DDevice9 * ret = NULL;
	//WrapperDirect3DDevice9::GetWrapperDevice9(base);
#ifndef GETWRAPPERDEVICE
	if (
		(*base) == typeid(IDirect3DDevice9)){
		*ppDevice = base;
	}
	else if (typeid(*base) == typeid(WrapperDirect3DDevice9)){
		gRecoder->logError("[ERROR]: State Block GetDevice got a WrapperDevice.\n");
		*ppDevice = ((WrapperDirect3DDevice9 *)base)->GetIDirect3DDevice9();
	}
	else{
		gRecoder->logError("[ERROR]: State Block GetDevice got a Unknow type.\n");
		*ppDevice = base;
	}
#else
	ret = WrapperDirect3DDevice9::GetWrapperDevice9(base);
	gRecoder->cmdCalled(sizeof(void*));
	*ppDevice = dynamic_cast<IDirect3DDevice9 *>(ret);
#endif
	gRecoder->logTrace("[INFO]: StateBlock9 end GetDevice.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DStateBlock9::Capture(THIS) {

	gRecoder->logTrace("[INFO]: StateBlock9 call Capture.\n");
	gRecoder->cmdCalled(0);
	HRESULT hr = m_sb->Capture();
	gRecoder->logTrace("[INFO]: StateBlock9 end Capture.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DStateBlock9::Apply(THIS) {
	gRecoder->logTrace("[INFO]: StateBlock9 call Apply.\n");
	gRecoder->cmdCalled(0);
	HRESULT hr = m_sb->Apply();
	gRecoder->logTrace("[INFO]: StateBlock9 end Apply.\n");
	return hr;
}
