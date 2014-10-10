#ifndef __WRAP_DIRECT3DINDEXBUFFER9__
#define __WRAP_DIRECT3DINDEXBUFFER9__

#include <map>
#include <iostream>
using namespace std;

class WrapperDirect3DIndexBuffer9: public IDirect3DIndexBuffer9
{
private:
	int id;
public:
	int ib_size;
	IDirect3DIndexBuffer9* m_ib;
	static int ins_count;

	WrapperDirect3DIndexBuffer9(IDirect3DIndexBuffer9* ptr, int _id);
	LPDIRECT3DINDEXBUFFER9 GetIB9();
	inline void SetID(int id);
	inline int GetID();
#ifdef GETWRAPPERDEVICE
	static WrapperDirect3DIndexBuffer9* GetWrapperIndexedBuffer9(IDirect3DIndexBuffer9* base_indexed_buffer);
	static HashSet m_list;
#endif

public:
	/*** IUnknown methods ***/
	COM_METHOD(HRESULT, QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	COM_METHOD(ULONG,AddRef)(THIS);
	COM_METHOD(ULONG,Release)(THIS);

	/*** IDirect3DResource9 methods ***/
	COM_METHOD(HRESULT, GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
	COM_METHOD(HRESULT, SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
	COM_METHOD(HRESULT, GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData);
	COM_METHOD(HRESULT, FreePrivateData)(THIS_ REFGUID refguid);
	COM_METHOD(DWORD, SetPriority)(THIS_ DWORD PriorityNew);
	COM_METHOD(DWORD, GetPriority)(THIS);
	COM_METHOD(void, PreLoad)(THIS);
	COM_METHOD(D3DRESOURCETYPE, GetType)(THIS);
	COM_METHOD(HRESULT, Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
	COM_METHOD(HRESULT, Unlock)(THIS);
	COM_METHOD(HRESULT, GetDesc)(THIS_ D3DINDEXBUFFER_DESC *pDesc);
};

#endif
