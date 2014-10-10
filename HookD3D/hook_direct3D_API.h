#pragma once
#include <d3d9.h>
#include <windows.h>
#include <d3dx9.h>
#include "d3d10_1.h"
#include "d3dx9tex.h"
#include "dxerr.h"
#include "../utility/log.h"
#include "detours\detours.h"
#include "../utility/utility.h"
#include "../utility/ga_confvar.h"
#include <map>
#include "../utility/ga_win32.h"

#define BITSPERPIXEL     32
#define ENCODING_MOD_BASE 2
#define	MAX_STRIDE		  4
using namespace std;


typedef  HRESULT (STDMETHODCALLTYPE *TD3D9DevicePresent)( 
	IDirect3DDevice9 * This,
	CONST RECT* pSourceRect,
	CONST RECT* pDestRect,
	HWND hDestWindowOverride,
	CONST RGNDATA* pDirtyRegion
);

typedef  HRESULT (STDMETHODCALLTYPE *TSwapChainPresent)( 
	IDirect3DSwapChain9 * This,
	CONST RECT* pSourceRect,
	CONST RECT* pDestRect,
	HWND hDestWindowOverride,
	CONST RGNDATA* pDirtyRegion,
	DWORD dwFlags
);

struct vsource_frame {
	long long imgpts;		// presentation timestamp
	//enum vsource_format pixelformat; // rgba or yuv420p
	PixelFormat pixelformat;
	int linesize[MAX_STRIDE];	// strides for YUV
	int realwidth;
	int realheight;
	int realstride;
	int realsize;
	// internal data - should not change after initialized
	int maxstride;
	int imgbufsize;
	unsigned char *imgbuf;
	unsigned char *imgbuf_internal;
	int alignment;
};

#pragma comment(lib,"detours\detours.lib")

#define DllImport _declspec( dllimport )
#define DllExport _declspec( dllexport )

class hook_direct3D_API
{
public:
	hook_direct3D_API(void);
	~hook_direct3D_API(void);
	
	
	static bool D3D9_screen_capture(IDirect3DDevice9 * pDevice);
	
	int ga_hook_video_rate_control();
	long pcdiff_us(LARGE_INTEGER t1, LARGE_INTEGER t2, LARGE_INTEGER freq);

	//hook D3DDevice present
	DllExport HRESULT _stdcall 
	hook_D3D9DevicePresent(IDirect3DDevice9 *p_d3d_device,CONST RECT* p_source_rect,CONST RECT* p_dest_rect,HWND hDestWindowOverride,CONST RGNDATA *p_dirty_region);
	//hook D3D9 swap chain present
	DllExport HRESULT _stdcall 
		hook_DXGI_swap_chain_present(IDXGISwapChain *p_swap_chain,UINT sync_interval,UINT flags);

public:
	TD3D9DevicePresent pD3D9DevicePresent;
    TSwapChainPresent pSwapChainPresent;

	static int d3d_device_present_hooked;
	static int swap_chain_present_hooked;
	
	static int resolution_inited;
	static int video_rate_inited;
	static int vsource_inited;
	static int capture_inited;
	static int game_width;
	static int game_height;
	
	static int encoder_width;
	static int encoder_height;
	static map<string,gaConfVar> ga_vars;
	static map<string,gaConfVar>::iterator ga_vmi = ga_vars.begin();
	

	static int enable_server_rate_control;
	static int server_token_fill_interval;
	static int server_num_token_to_fill;
	static int server_max_tokens;
	static int video_fps;
	static int frame_interval;
	static IDirect3DSurface9 *resolvedSurface;
	static IDirect3DSurface9 *offscreenSurface;
};

