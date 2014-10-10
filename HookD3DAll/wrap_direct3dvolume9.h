#ifndef __WRAP_DIRECT3DVOLUME9__
#define __WRAP_DIRECT3DVOLUME9__

class WrapperDirect3DVolume9 : public IDirect3DVolume9
{
private:
	IDirect3DVolume9 * m_d3dvolume;
	int id;

public:
	static int ins_count;
	int getVolumeSize();

	WrapperDirect3DVolume9(IDirect3DVolume9 *ptr, int _id);
	inline int GetID();
	inline void SetID(int id);
#ifdef GETWRAPPERDEVICE
	static WrapperDirect3DVolume9* GetWrapperDirect3DVolume9(IDirect3DVolume9 *ptr);
	static HashSet m_list;
#endif
	IDirect3DVolume9 * GetIDirect3DVolume9();

	/*** IUnknown methods ***/
    COM_METHOD(HRESULT, QueryInterface)(THIS_ REFIID riid, void** ppvObj);
    COM_METHOD(ULONG,AddRef)(THIS);
    COM_METHOD(ULONG,Release)(THIS);

    /*** IDirect3DVolume9 methods ***/
    COM_METHOD(HRESULT, GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
    COM_METHOD(HRESULT, SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    COM_METHOD(HRESULT, GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData);
    COM_METHOD(HRESULT, FreePrivateData)(THIS_ REFGUID refguid);
    COM_METHOD(HRESULT, GetContainer)(THIS_ REFIID riid,void** ppContainer);
    COM_METHOD(HRESULT, GetDesc)(THIS_ D3DVOLUME_DESC *pDesc);
    COM_METHOD(HRESULT, LockBox)(THIS_ D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags);
    COM_METHOD(HRESULT, UnlockBox)(THIS);

};

#endif