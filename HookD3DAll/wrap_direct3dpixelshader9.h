#ifndef __WRAP_DIRECT3DPIXELSHADER9__
#define __WRAP_DIRECT3DPIXELSHADER9__


class WrapperDirect3DPixelShader9: public IDirect3DPixelShader9 
{
private:
	IDirect3DPixelShader9* m_ps;
	int id;
public:

	int funcCount;   // store the command count in the shader

	static int ins_count;
	WrapperDirect3DPixelShader9(IDirect3DPixelShader9* ptr, int _id);
	inline int GetID();
	inline void SetID(int id);
	IDirect3DPixelShader9* GetPS9();
#ifdef GETWRAPPERDEVICE
	static WrapperDirect3DPixelShader9* GetWrapperPixelShader(IDirect3DPixelShader9* ptr);
	static HashSet m_list;
#endif

	/*** IUnknown methods ***/
	COM_METHOD(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	COM_METHOD(ULONG,AddRef)(THIS);
	COM_METHOD(ULONG,Release)(THIS);

	/*** IDirect3DPixelShader9 methods ***/
	COM_METHOD(HRESULT,GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
	COM_METHOD(HRESULT,GetFunction)(THIS_ void*,UINT* pSizeOfData);

};

#endif