#include "hook_direct3D_API.h"

int hook_direct3D_API::d3d_device_present_hooked = 0;
int hook_direct3D_API::swap_chain_present_hooked = 0;
int hook_direct3D_API::resolution_inited		 = 0;

int hook_direct3D_API::resolution_inited = 0;
int hook_direct3D_API::capture_inited    = 0;
int hook_direct3D_API::vsource_inited	 = 0;

int hook_direct3D_API::game_width = 0;
int hook_direct3D_API::game_height= 0;
	
int hook_direct3D_API::encoder_width	 = 0;
int hook_direct3D_API::encoder_height	 = 0;
int hook_direct3D_API::video_rate_inited = 0;
int hook_direct3D_API::frame_interval	 = 0;

int hook_direct3D_API::enable_server_rate_control = 1;
int hook_direct3D_API::server_token_fill_interval = 41667;
int hook_direct3D_API::server_num_token_to_fill = 1;
int hook_direct3D_API::server_max_tokens = 2;
int hook_direct3D_API::video_fps = 24;

IDirect3DSurface9 *hook_direct3D_API::resolvedSurface = NULL;
IDirect3DSurface9 *hook_direct3D_API::offscreenSurface= NULL;

hook_direct3D_API::hook_direct3D_API(void)
{
}


hook_direct3D_API::~hook_direct3D_API(void)
{
}

//hook D3DDevice present 
DllExport HRESULT _stdcall hook_direct3D_API::hook_D3D9DevicePresent(
	IDirect3DDevice9 *p_d3d_device,
	CONST RECT		 * p_source_rect,
	CONST RECT		 * p_dest_rect,
	HWND			 hDestWindowOverride,
	CONST			 RGNDATA *p_dirty_region)
{
	if(!d3d_device_present_hooked)
	{
		Log::log("[IDirect3dDevice9::Present()]\n");
		d3d_device_present_hooked=1;
	}
	HRESULT hr = pD3D9DevicePresent ( p_d3d_device, p_source_rect, p_dest_rect, hDestWindowOverride, p_dirty_region );
	if( !resolution_inited )
	{
		if( !D3D9_get_resolution(p_d3d_device))
			return hr;
	}
	if(enable_server_rate_control)
	{
		if(ga_hook_video_rate_control()>0)

	}
	


}

//hook swap_chain present
DllExport HRESULT _stdcall hook_direct3D_API::hook_DXGI_swap_chain_present(
	IDXGISwapChain *p_swap_chain,
	UINT		   sync_interval,
	UINT		   flags)
{

}

//get resolution of render frames
int hook_direct3D_API::D3D9_get_resolution( 
	IDirect3DDevice9 *p_device)
{
	HRESULT hr;
	D3DSURFACE_DESC desc;
	IDirect3DSurface9 *render_surface;
	
	if( resolution_inited ==1 )
		return 0;
	hr = p_device->GetRenderTarget( 0, &render_surface );

	if( !render_surface || FAILED(hr) )
		return -1;
	render_surface->GetDesc(&desc);
	render_surface->Release();

	if( ga_hook_get_resolution(desc.Width,desc.Height) == -1 )
		return -1;
	resolution_inited = 1;
}


int hook_direct3D_API::ga_hook_get_resolution(int width,int height)
{
	int resolution[2];
	if( game_width <=0 ||game_height<=0 )
	{
		game_width  = width;
		game_height = height;
		if(ga_conf_readints("max-resolution",resolution,2) == 2)
		{
			encoder_width = resolution[0];
			encoder_height= resolution[1];
		}
		else
		{
			encoder_width  = (game_width / ENCODING_MOD_BASE) * ENCODING_MOD_BASE;
			encoder_height = (game_height / ENCODING_MOD_BASE) * ENCODING_MOD_BASE;
		}
		Log::log("resolution fitted: game %dx%d; encoder %dx%d\n",
			game_width, game_height, encoder_width, encoder_height);
		return 0;
	}
	else
		Log::log("resolution not fitted (%dx%d)\n", width, height);
	return -1;
}



long hook_direct3D_API::pcdiff_us(
	LARGE_INTEGER t1, LARGE_INTEGER t2, LARGE_INTEGER freq)
{
	return 1000000LL * (t1.QuadPart - t2.QuadPart) / freq.QuadPart;
}
//
int hook_direct3D_API::ga_hook_video_rate_control()
{
	
	static int max_tokens;
	static long long tokens = 0LL;
#ifdef WIN32
	static LARGE_INTEGER lastCounter, freq;
	LARGE_INTEGER currCounter;
#else
	static struct timeval lastCounter;
	struct timeval currCounter;
#endif
	long long delta;
	// init
	if(video_rate_inited == 0) {
		tokens = 0LL;
		max_tokens = server_max_tokens * server_token_fill_interval;
#ifdef WIN32
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&lastCounter);
#else
		gettimeofday(&lastCounter, NULL);
#endif
		Log::log("[token_bucket] interval=%d, fill=%d, max=%d (%d)\n",
			(int) server_token_fill_interval,
			(int) server_num_token_to_fill,
			(int) server_max_tokens,
			(int) max_tokens);
		video_rate_inited = 1;
		return -1;
	}
	//
#ifdef WIN32
	QueryPerformanceCounter(&currCounter);
	delta = pcdiff_us(currCounter, lastCounter, freq);
#else
	gettimeofday(&currCounter, NULL);
	delta = tvdiff_us(&currCounter, &lastCounter);
#endif
	if(delta >= server_token_fill_interval) {
		tokens += delta;
		lastCounter = currCounter;
	}
	if(tokens > max_tokens) {
		tokens = max_tokens;
	}
	if(tokens >= server_token_fill_interval) {
		tokens -= server_token_fill_interval;
		return 1;
	}
	return -1;
}

bool
	hook_direct3D_API::D3D9_screen_capture(IDirect3DDevice9 * pDevice)
{	
	
	static LARGE_INTEGER initialTv, captureTv, freq;
	//
	HRESULT hr;
	D3DSURFACE_DESC desc;
	IDirect3DSurface9 *renderSurface, *oldRenderSurface;
	D3DLOCKED_RECT lockedRect;
	int i;
	struct pooldata *data;
	struct vsource_frame *frame;
	//
	if(vsource_inited == 0)
		return false;
	//
	renderSurface = oldRenderSurface = NULL;
	//
	hr = pDevice->GetRenderTarget(0, &renderSurface);
	if (FAILED(hr)) {
		if (hr == D3DERR_INVALIDCALL) {
			Log::log("GetRenderTarget failed (INVALIDCALL)\n");
		} else if (hr == D3DERR_NOTFOUND) {
			Log::log("GetRenderTarget failed (D3DERR_NOTFOUND)\n");
		} else {
			Log::log("GetRenderTarget failed. (other)\n");
		}
	}
	if (renderSurface == NULL) {
		Log::log("renderSurface == NULL.\n");
		return false;
	}
	
	renderSurface->GetDesc(&desc);

	if(desc.Width != game_width
	|| desc.Height != game_height) {
		return false;
	}

	if (capture_inited == 0) {
		frame_interval = 1000000/video_fps; // in the unif of us
		frame_interval++;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&initialTv);
		capture_inited = 1;
	} else {
		QueryPerformanceCounter(&captureTv);
	}
	
	// check if the surface of local game enable multisampling,
	// multisampling enabled will avoid locking in the surface
	// if yes, create a no-multisampling surface and copy frame into it
	if (desc.MultiSampleType != D3DMULTISAMPLE_NONE) {
		if(resolvedSurface == NULL) {
			hr = pDevice->CreateRenderTarget(game_width, game_height,
					desc.Format,
					D3DMULTISAMPLE_NONE,
					0,			// non multisampleQuality
					FALSE,			// lockable
					&resolvedSurface, NULL);
			if (FAILED(hr)) {
				Log::log("CreateRenderTarget(resolvedSurface) failed.\n");
				return false;
			}
		}

		hr = pDevice->StretchRect(renderSurface, NULL,
					resolvedSurface, NULL, D3DTEXF_NONE);
		if (FAILED(hr)) {
			Log::log("StretchRect failed.\n");
			return false;
		}
		
		oldRenderSurface = renderSurface;
		renderSurface = resolvedSurface;
	}

	// create offline surface in system memory
	if(offscreenSurface == NULL) {
		hr = pDevice->CreateOffscreenPlainSurface(game_width, game_height, 
				desc.Format,
				D3DPOOL_SYSTEMMEM,
				&offscreenSurface, NULL);
		if (FAILED(hr)) {
			Log::log("Create offscreen surface failed.\n");
			return false;
		}
	}
	
	// copy the render-target data from device memory to system memory
	hr = pDevice->GetRenderTargetData(renderSurface, offscreenSurface);

	if (FAILED(hr)) {
		Log::log("GetRenderTargetData failed.\n");
		if(oldRenderSurface)
			oldRenderSurface->Release();
		else
			renderSurface->Release();
		return false;
	}	
	
	if(oldRenderSurface)
		oldRenderSurface->Release();
	else
		renderSurface->Release();

	// start to lock screen from offline surface
	hr = offscreenSurface->LockRect(&lockedRect, NULL, NULL);
	if (FAILED(hr)) {
		Log::log("LockRect failed.\n");
		return false;
	}

	// copy image 
	do {
		unsigned char *src, *dst;
		data = g_pipe[0]->allocate_data();
		frame = (struct vsource_frame*) data->ptr;
		frame->pixelformat = PIX_FMT_BGRA;
		frame->realwidth = desc.Width;
		frame->realheight = desc.Height;
		frame->realstride = desc.Width<<2;
		frame->realsize = frame->realwidth * frame->realstride;
		frame->linesize[0] = frame->realstride;//frame->stride;
		//
		src = (unsigned char*) lockedRect.pBits;
		dst = (unsigned char*) frame->imgbuf;
		for (i = 0; i < encoder_height; i++) {
			//memcpy(frame->imgbuf+i*encoder_width*sizeof(DWORD), (BYTE *)lockedRect.pBits+i*lockedRect.Pitch, 1*encoder_width*sizeof(DWORD));
			//CopyMemory(frame->imgbuf, lockedRect.pBits, lockedRect.Pitch * screenRect.bottom);
			CopyMemory(dst, src, frame->realstride/*frame->stride*/);
			src += lockedRect.Pitch;
			dst += frame->realstride;//frame->stride;
		}
		frame->imgpts = pcdiff_us(captureTv, initialTv, freq)/frame_interval;
	} while(0);

	// duplicate from channel 0 to other channels
	for(i = 1; i < SOURCES; i++) {
		int j;
		struct pooldata *dupdata;
		struct vsource_frame *dupframe;
		dupdata = g_pipe[i]->allocate_data();
		dupframe = (struct vsource_frame*) dupdata->ptr;
		//
		vsource_dup_frame(frame, dupframe);
		//
		g_pipe[i]->store_data(dupdata);
		g_pipe[i]->notify_all();
	}
	g_pipe[0]->store_data(data);
	g_pipe[0]->notify_all();
	
	offscreenSurface->UnlockRect();
#if 1	// XXX: disable until we have found a good place to safely Release()
	if(hook_boost == 0) {
		if(offscreenSurface != NULL) {
			offscreenSurface->Release();
			offscreenSurface = NULL;
		}
		if(resolvedSurface != NULL) {
			resolvedSurface->Release();
			resolvedSurface = NULL;
		}
	}
#endif
		
	return true;

}

void vsource_dup_frame(struct vsource_frame *src, struct vsource_frame *dst)
{
	int j;
	dst->imgpts = src->imgpts;
	dst->pixelformat = src->pixelformat;
	for(j = 0; j < MAX_STRIDE; j++) {
		dst->linesize[j] = src->linesize[j];
	}
	dst->realwidth = src->realwidth;
	dst->realheight = src->realheight;
	dst->realstride = src->realstride;
	dst->realsize = src->realsize;
	memcpy(src->imgbuf, dst->imgbuf, dst->imgbufsize);
	return;
}