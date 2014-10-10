#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3dvertexdeclaration9.h"

int WrapperDirect3DVertexDeclaration9::ins_count = 0;
HashSet WrapperDirect3DVertexDeclaration9::m_list;\


WrapperDirect3DVertexDeclaration9 * WrapperDirect3DVertexDeclaration9::GetWrapperDirect3DVertexDeclaration(IDirect3DVertexDeclaration9 * ptr){
	gRecoder->logTrace("[INFO]: VertexDeclaration9 call GetWrapperVertexDeclaration9.\n");
	WrapperDirect3DVertexDeclaration9 * ret = (WrapperDirect3DVertexDeclaration9 *)(m_list.GetDataPtr(ptr));
	if (ret == NULL){
		ret = new WrapperDirect3DVertexDeclaration9(ptr, ins_count++);
	}
	gRecoder->logTrace("[INFO]: VertexDeclaration9 end GetWrapperVertexDeclaration9.\n");
	return ret;
}


int WrapperDirect3DVertexDeclaration9::getDeclarationSize(){
	return sizeof(D3DVERTEXELEMENT9) * this->Count;
}


WrapperDirect3DVertexDeclaration9::WrapperDirect3DVertexDeclaration9(IDirect3DVertexDeclaration9* ptr, int _id): m_vd(ptr), id(_id) {
	m_list.AddMember(ptr, this);
}

void WrapperDirect3DVertexDeclaration9::SetID(int id) {
	this->id = id;
}

int WrapperDirect3DVertexDeclaration9::GetID() {
	return this->id;
}

IDirect3DVertexDeclaration9* WrapperDirect3DVertexDeclaration9::GetVD9() {
	return m_vd;
}

/*** IUnknown methods ***/
STDMETHODIMP WrapperDirect3DVertexDeclaration9::QueryInterface(THIS_ REFIID riid, void** ppvObj) {
	gRecoder->logTrace("[INFO]: VertexDeclaration9 call QueryInterface.\n");
	gRecoder->cmdCalled(sizeof(riid) + sizeof(void *));
	HRESULT hr = m_vd->QueryInterface(riid, ppvObj);
	*ppvObj = this;
	gRecoder->logTrace("[INFO]: VertexDeclaration9 end QueryInterface.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DVertexDeclaration9::AddRef(THIS) {
	gRecoder->logTrace("[INFO]: VertexDeclaration9 call AddRef.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_vd->AddRef();
	gRecoder->logTrace("[INFO]: VertexDeclaration9 end AddRef.\n");
	return hr;
}

STDMETHODIMP_(ULONG) WrapperDirect3DVertexDeclaration9::Release(THIS) {
	gRecoder->logTrace("[INFO]: VertexDeclaration9 call Release.\n");
	gRecoder->cmdCalled(sizeof(ULONG));
	ULONG hr = m_vd->Release();
	gRecoder->logTrace("[INFO]: VertexDeclaration9 end Release.\n");
	return hr;
}

/*** IDirect3DVertexDeclaration9 methods ***/
STDMETHODIMP WrapperDirect3DVertexDeclaration9::GetDevice(THIS_ IDirect3DDevice9** ppDevice) {
	gRecoder->logTrace("[INFO]: VertexDeclaration9 call GetDevice.\n");
	gRecoder->cmdCalled(sizeof(void *));
	HRESULT hr = m_vd->GetDevice(ppDevice);
	gRecoder->logTrace("[INFO]: VertexDeclaration9 end GetDevice.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DVertexDeclaration9::GetDeclaration(THIS_ D3DVERTEXELEMENT9* pElement,UINT* pNumElements) {
	gRecoder->logTrace("[INFO]: VertexDeclaration9 call GetDeclaration.\n");
	gRecoder->cmdCalled(sizeof(void *) * 2 + sizeof(D3DVERTEXELEMENT9) + sizeof(UINT));
	HRESULT hr = m_vd->GetDeclaration(pElement, pNumElements);
	gRecoder->logTrace("[INFO]: VertexDeclaration9 end GetDeclaration.\n");
	return hr;
}