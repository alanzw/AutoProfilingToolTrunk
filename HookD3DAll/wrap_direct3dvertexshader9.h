#ifndef __WRAP_DIRECT3DVERTEXSHADER9__
#define __WRAP_DIRECT3DVERTEXSHADER9__

//#define TEST_VERTEX_SHADER_SIZE 

class WrapperDirect3DVertexShader9: public IDirect3DVertexShader9 
{
private:
	IDirect3DVertexShader9* m_vs;
	int id;
public:

	int funcCount;    // stores the shader's command count
	int getShaderSize();
	static int ins_count;
	WrapperDirect3DVertexShader9(IDirect3DVertexShader9* ptr, int _id);
	inline int GetID();
	inline void SetID(int id);
	IDirect3DVertexShader9* GetVS9();
#ifdef GETWRAPPERDEVICE
	static WrapperDirect3DVertexShader9* GetWrapperVertexShader(IDirect3DVertexShader9* ptr);
	static HashSet m_list;
#endif
public:

	/*** IUnknown methods ***/
	COM_METHOD(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObj);
	COM_METHOD(ULONG,AddRef)(THIS);
	COM_METHOD(ULONG,Release)(THIS);

	/*** IDirect3DVertexShader9 methods ***/
	COM_METHOD(HRESULT,GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
	COM_METHOD(HRESULT,GetFunction)(THIS_ void*,UINT* pSizeOfData);
};

#endif
