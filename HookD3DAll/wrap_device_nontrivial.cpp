#include "hook_common.h"
#include "recorder.h"

#include "wrap_direct3d9.h"
#include "wrap_direct3ddevice9.h"
#include "wrap_direct3dvertexbuffer9.h"
#include "wrap_direct3dindexbuffer9.h"
#include "wrap_direct3dvertexdeclaration9.h"
#include "wrap_direct3dvertexshader9.h"
#include "wrap_direct3dpixelshader9.h"
#include "wrap_direct3dtexture9.h"
#include "wrap_direct3dstateblock9.h"
#include "wrap_direct3dcubetexture9.h"
#include "wrap_direct3dswapchain9.h"
#include "wrap_direct3dsurface9.h"
#include "wrap_direct3dvolumetexture9.h"

int WrapperDirect3DDevice9::ins_count = 0;
HashSet WrapperDirect3DDevice9::m_list;

STDMETHODIMP WrapperDirect3DDevice9::DrawPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) {
	gRecoder->logTrace("[INFO]: Device Call DrawPrimtive.\n");
	gRecoder->drawCalled(sizeof(D3DPRIMITIVETYPE) + sizeof(UINT) * 2, PrimitiveCount);
	HRESULT hr = m_device->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
	gRecoder->logTrace("[INFO]: Device End DrawPrimitive.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE Type,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount) {
	gRecoder->logTrace("[INFO]: Device DrawIndexedPrimitive.\n");
	gRecoder->drawCalled(sizeof(D3DPRIMITIVETYPE) + sizeof(UINT) * 5, primCount);

	HRESULT hr = m_device->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);

	gRecoder->logTrace("[INFO]: Device End DrawIndexedPrimitive.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::DrawPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) {
	
	gRecoder->logTrace("[INFO]: Device call drawPrimitiveUP.\n");
	gRecoder->logTrace("[INFO]: DrawPrimitiveUP(");
	int VertexCount = 0;
#if 0
	switch(PrimitiveType) {
		gRecoder->logTrace("[INFO]: enter switch.\n");
	case D3DPT_POINTLIST:
		VertexCount = PrimitiveCount;
		gRecoder->logTrace("D3DPT_POINTLIST, ");
		break;
	case D3DPT_LINELIST:
		VertexCount = PrimitiveCount * 2;
		gRecoder->logTrace("D3DPT_LINELIST, ");
		break;
	case D3DPT_LINESTRIP:
		VertexCount = PrimitiveCount + 1;
		gRecoder->logTrace("D3DPT_LINESTRIP, ");
		break;
	case D3DPT_TRIANGLELIST:
		VertexCount = PrimitiveCount * 3;
		gRecoder->logTrace("D3DPT_TRIANGLELIST, ");
		break;
	case D3DPT_TRIANGLESTRIP:
		gRecoder->logTrace("D3DPT_TRIANGLESTRIP, ");
	case D3DPT_TRIANGLEFAN:
		VertexCount = PrimitiveCount + 2;
		gRecoder->logTrace("D3DPT_TRIANGLEFAN, ");
		break;
	default:
		VertexCount = 0;
		break;
	}
	gRecoder->logTrace("%d, 0x%p, %d).\n", PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
#else
	gRecoder->logTrace("%d, %d, 0x%p, %d).\n", PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
#endif
	gRecoder->drawCalled(sizeof(D3DPRIMITIVETYPE) + sizeof(UINT) * 2 + sizeof(void *), PrimitiveCount);
	gRecoder->logTrace("[INFO]: to draw.\n");
	HRESULT hr = m_device->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);

	gRecoder->logTrace("[INFO]: Device end drawPrimitiveUP.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::DrawIndexedPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) {
	gRecoder->logTrace("[INFO]: Device call DrawIndexedPrimitiveUP.\n");

	gRecoder->drawCalled(sizeof(D3DPRIMITIVETYPE) + sizeof(UINT) * 4 + sizeof(void *) * 2, PrimitiveCount);
	HRESULT hr = m_device->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);

	gRecoder->logTrace("[INFO]: Device end DrawIndexedPrimitiveUP.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::CreateVertexDeclaration(THIS_ CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) {
	gRecoder->logTrace("[INFO]: Device call CreateVertexDeclaration.\n");

	int ve_cnt = 0;
	D3DVERTEXELEMENT9 end = D3DDECL_END();

	// create the vertex declaration
	//WrapperDirect3DVertexDeclaration9::ins_count++;
	LPDIRECT3DVERTEXDECLARATION9 base_vd = NULL;
	HRESULT hr = m_device->CreateVertexDeclaration(pVertexElements, &base_vd);
	WrapperDirect3DVertexDeclaration9 * vd = NULL;
	if(SUCCEEDED(hr)) {
		vd = new WrapperDirect3DVertexDeclaration9(base_vd, WrapperDirect3DVertexDeclaration9::ins_count++);
		*ppDecl = dynamic_cast<IDirect3DVertexDeclaration9*>(vd);
	}
	else {
		gRecoder->logTrace("[ERROR]: Device Create ver5tex declaration failed.\n");
	}

	while(true) {
		ve_cnt++;
		if(pVertexElements[ve_cnt].Type == end.Type && pVertexElements[ve_cnt].Method == end.Method && pVertexElements[ve_cnt].Offset == end.Offset && pVertexElements[ve_cnt].Stream == end.Stream && pVertexElements[ve_cnt].Usage == end.Usage && pVertexElements[ve_cnt].UsageIndex == end.UsageIndex) break;
	}

	vd->Count = ve_cnt;
	// the parameters' size should be the actual data size
	gRecoder->cmdCalled(sizeof(D3DVERTEXELEMENT9) * ve_cnt);
	gRecoder->logTrace("[INFO]: Device end CreateVertexDeclaration.\n");
	return hr;
}

STDMETHODIMP WrapperDirect3DDevice9::SetVertexDeclaration(THIS_ IDirect3DVertexDeclaration9* pDecl) {
	//cur_decl_ = (WrapperDirect3DVertexDeclaration9*)pDecl;
	gRecoder->logTrace("[INFO]: Device call SetVertexDeclaration.\n");
	if(pDecl == NULL) {
		return m_device->SetVertexDeclaration(pDecl);
	}

	HRESULT hh= m_device->SetVertexDeclaration(((WrapperDirect3DVertexDeclaration9*)pDecl)->GetVD9());

	gRecoder->cmdCalled(sizeof(D3DVERTEXELEMENT9) * ((WrapperDirect3DVertexDeclaration9 *)pDecl)->Count);
	gRecoder->logTrace("[INFO]: Device end SetVertexDeclaration.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::SetStreamSource(THIS_ UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) {
	gRecoder->logTrace("[INFO]: Device call SetStreamSource.\n");
	if(pStreamData == NULL) {
		gRecoder->setVertexBufferCalled(sizeof(UINT) * 3 + sizeof(void*), 0);
		return m_device->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
	}

	WrapperDirect3DVertexBuffer9* wvb = (WrapperDirect3DVertexBuffer9*)pStreamData;

	HRESULT hh = m_device->SetStreamSource(StreamNumber, ((WrapperDirect3DVertexBuffer9*)pStreamData)->GetVB9(), OffsetInBytes, Stride);
	
	//TODO : SetStreamSource, what is the parameter's size and does it need to calculate the vertex buffer size ?
	//gRecoder->cmdCalled(sizeof(UINT) * 3 + sizeof(void *));
	gRecoder->setVertexBufferCalled(sizeof(UINT) * 3 + sizeof(void*), ((WrapperDirect3DVertexBuffer9*)pStreamData)->vb_size);
	gRecoder->logTrace("[INFO]: Device end SetStreamSource.\n");
	return hh;
}

STDMETHODIMP WrapperDirect3DDevice9::SetIndices(THIS_ IDirect3DIndexBuffer9* pIndexData) {
	gRecoder->logTrace("[INFO]: Device call SetIndices.\n");
	if(pIndexData == NULL) {
		//cur_ib_ = NULL;
		gRecoder->setIndexBufferCalled(sizeof(void *), 0);
		return m_device->SetIndices(pIndexData);
	}

	WrapperDirect3DIndexBuffer9* wib = (WrapperDirect3DIndexBuffer9*)pIndexData;
	gRecoder->setIndexBufferCalled(sizeof(void *), ((WrapperDirect3DIndexBuffer9*)pIndexData)->ib_size);

	HRESULT hh = m_device->SetIndices(((WrapperDirect3DIndexBuffer9*)pIndexData)->GetIB9());
	gRecoder->logTrace("[INFO]: Device end SetIndices.\n");
	return hh;
}