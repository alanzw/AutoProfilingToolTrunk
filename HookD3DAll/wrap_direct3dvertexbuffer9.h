#ifndef __WRAP_DIRECT3DVERTEXBUFFER9__
#define __WRAP_DIRECT3DVERTEXBUFFER9__

class WrapperDirect3DVertexBuffer9: public IDirect3DVertexBuffer9 
{
private:
	IDirect3DVertexBuffer9* m_vb;
	int id;
public:

	int vb_size;

	static int ins_count;
	WrapperDirect3DVertexBuffer9(IDirect3DVertexBuffer9* ptr, int _id);
	LPDIRECT3DVERTEXBUFFER9 GetVB9();

	inline void SetId(int id);
	inline int GetId();
#ifdef GETWRAPPERDEVICE
	static WrapperDirect3DVertexBuffer9* GetWrapperVertexBuffer9(IDirect3DVertexBuffer9* ptr);
	static HashSet m_list;
#endif
public:
	/*** IUnknown methods ***/
	COM_METHOD(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	COM_METHOD(ULONG,AddRef)(THIS);
	COM_METHOD(ULONG,Release)(THIS);

	/*** IDirect3DResource9 methods ***/

	COM_METHOD(HRESULT,GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
	COM_METHOD(HRESULT,SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
	COM_METHOD(HRESULT,GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData);
	COM_METHOD(HRESULT,FreePrivateData)(THIS_ REFGUID refguid);
	COM_METHOD(DWORD, SetPriority)(THIS_ DWORD PriorityNew);
	COM_METHOD(DWORD, GetPriority)(THIS);
	COM_METHOD(void, PreLoad)(THIS);
	COM_METHOD(D3DRESOURCETYPE, GetType)(THIS);

	COM_METHOD(HRESULT,Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags);
	COM_METHOD(HRESULT,Unlock)(THIS);
	COM_METHOD(HRESULT,GetDesc)(THIS_ D3DVERTEXBUFFER_DESC *pDesc);
};

#endif
