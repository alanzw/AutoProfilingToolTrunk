#ifndef __WRAP_DIRECT3DSURFACE9__
#define __WRAP_DIRECT3DSURFACE9__


class WrapperDirect3DSurface9 : public IDirect3DSurface9 
{
private:
	IDirect3DSurface9* m_surface;
	int size;
	int id;
public:
	UINT width, height;
	D3DFORMAT format;

	//int getSurfaceSize();

	static int ins_count;
	WrapperDirect3DSurface9(IDirect3DSurface9* ptr, int id);
#ifdef GETWRAPPERDEVICE
	static WrapperDirect3DSurface9* GetWrapperSurface9(IDirect3DSurface9* ptr);
	static HashSet m_list;
#endif
	inline int GetID();
	inline void SetID(int id);
	IDirect3DSurface9* GetSurface9();

	int getSurfaceSize();

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
	COM_METHOD(HRESULT,GetContainer)(THIS_ REFIID riid,void** ppContainer);
	COM_METHOD(HRESULT,GetDesc)(THIS_ D3DSURFACE_DESC *pDesc);
	COM_METHOD(HRESULT,LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
	COM_METHOD(HRESULT,UnlockRect)(THIS);
	COM_METHOD(HRESULT,GetDC)(THIS_ HDC *phdc);
	COM_METHOD(HRESULT,ReleaseDC)(THIS_ HDC hdc);
};

#endif