#include "hook-function.h"



InfoRecorder * infoRecorder = NULL;

void(WINAPI * ExitProcessNext)(UINT uExitCode) = ExitProcess;

void WINAPI ExitProcessCallback(UINT uExitCode){
	//infoRecorder->close();
	if (infoRecorder){
		delete infoRecorder;
		infoRecorder = NULL;
	}

	ExitProcessNext(uExitCode);
}

#if 0
void startHook(){
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID *)&Direct3DCreate9Next, Direct3DCreate9Callback);
	DetourAttach(&(PVOID&)ExitProcessNext, ExitProcessCallback);
	DetourTransactionCommit();
}
#endif

static int hook_d9(){
	HMODULE hMode;
	if ((hMode = GetModuleHandle("d3d9.dll")) == NULL){
		infoRecorder->logError("[hook d9]: d3d9.dll not load yet.\n");
		if ((hMode = LoadLibrary("d3d9.dll")) == NULL){
			infoRecorder->logError("[hook d9]: load d3d9.dll failed.\n");
			return -1;
		}
	}
	pD3d = (TDirect3DCreate9)GetProcAddress(hMode, "Direct3DCreate9");
	if (pD3d == NULL){
		infoRecorder->logError("[hook d9]: GetProcAddress(Direct3DCreate9) failed.\n");
		return -1;
	}
	//
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)pD3d, hook_d3d);
	DetourTransactionCommit();

	return 0;

}
static int hook_dxgi(){
	HMODULE hMod;
	if ((hMod = GetModuleHandle("dxgi.dll")) == NULL){
		infoRecorder->logError("[hook dxgi]: dxgi.dll not load yet.\n");
		return -1;
	}
	pCreateDXGIFactory = (TCreateDXGIFactory)GetProcAddress(hMod, "CreateDXGIFactory");
	if (pCreateDXGIFactory == NULL){
		infoRecorder->logError("[hook dxgi]: GetProcessAddress(CreateDXGIFactory] failed.\n");
		return -1;
	}
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID &)pCreateDXGIFactory, hook_CreateDXGIFactory);
	DetourTransactionCommit();
	return 0;
}
static int hook_d10_1(){
	HMODULE hMod;
	if ((hMod = GetModuleHandle("d3d10_1.dll")) == NULL){
		infoRecorder->logError("[hook d10_1]: d3d10_1.dll not load yet.\n");
		if ((hMod = LoadLibrary("d3d10_1.dll")) == NULL){
			infoRecorder->logError("[hook d10_1]: load d3d10_1.dll failed.\n");
			return -1;
		}

	}
	pD3D10CreateDeviceAndSwapChain1 = (TD3D10CreateDeviceAndSwapChain1)GetProcAddress(hMod, "D3D10CreateDeviceAndSwapChain1");
	if (pD3D10CreateDeviceAndSwapChain1 == NULL){
		infoRecorder->logError("GetProcAddress(D3D10CreateDeviceAndSwapChain1) failed.\n");
		return -1;
	}
	// 
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID &)pD3D10CreateDeviceAndSwapChain1, hook_D3D10CreateDeviceAndSwapChain1);
	DetourTransactionCommit();
	return 0;
}
static int hook_d10(){
	HMODULE hMod;
	if ((hMod = GetModuleHandle("d3d10.dll")) == NULL){
		infoRecorder->logError("[hook d10]: d3d10.dll not load yet.\n");
		if ((hMod = LoadLibrary("d3d10.dll")) == NULL){
			infoRecorder->logError("[hook d10]: load d3d10.dll failed.\n");
			return -1;
		}

	}
	pD3D10CreateDeviceAndSwapChain = (TD3D10CreateDeviceAndSwapChain)GetProcAddress(hMod, "D3D10CreateDeviceAndSwapChain");
	if (pD3D10CreateDeviceAndSwapChain == NULL){
		infoRecorder->logError("GetProcAddress(D3D10CreateDeviceAndSwapChain) failed.\n");
		return -1;
	}
	//
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)pD3D10CreateDeviceAndSwapChain, hook_D3D10CreateDeviceAndSwapChain);
	DetourTransactionCommit();
	return 0;
}
static int hook_d11(){
	HMODULE hMod;
	if ((hMod = GetModuleHandle("d3d11.dll")) == NULL){
		infoRecorder->logError("[hook d11]: d3d11.dll not load yet.\n");
		if ((hMod = LoadLibrary("d3dll.dll")) == NULL){
			infoRecorder->logError("[hook d11]: load d3d11.dll failed.\n");
			return -1;
		}
	}
	pD3D11CreateDeviceAndSwapChain = (TD3D11CreateDeviceAndSwapChain)GetProcAddress(hMod, "D3D11CreateDeviceAndSwapChain");
	if (pD3D11CreateDeviceAndSwapChain == NULL){
		infoRecorder->logError("[hook d11]: GetProcAddress(D3D11CreateDeviceAndSwapChain) failed.\n");
		return -1;
	}
	//
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID &)pD3D11CreateDeviceAndSwapChain, hook_D3D11CreateDeviceAndSwapChain);
	DetourTransactionCommit();
	return 0;
}

int do_hook(){
#if 0
	if (CoInitializeEx(NULL, COINITBASE_MULTITHREADED) != S_OK){

	}
#endif

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)ExitProcessNext, ExitProcessCallback);
	DetourTransactionCommit();

	if (!hook_d9() || !hook_d10() || !hook_d10_1() || !hook_d11()){

	}
	else{
		return -1;
	}
}

char * getGameName(char * cmdline){
	char * p = cmdline;
	char gameName[100] = { 0 };
	while (*p){
		if (*p == ' '){
			// the white space is the seperator
			break;
		}
		p++;
	}
	if (p - cmdline > 0){
		strncpy(gameName, cmdline, p - cmdline);
		return _strdup(gameName);
	}
	else{
		return NULL;
	}

}
bool rateControl = false;
int maxFps = 30;

int getFps(char * cmdline){
	char * p = cmdline;
	char * pEnd = NULL;
	char fps[10] = { 0 };

	while (*p){
		if (*p == '-'){
			p++;
			if (*p == 'f' || *p == 'F'){
				// specific a FPS
				rateControl = true;
				p++;
				while (*p == ' '){
					p++;
				}
				// the p is the start of fps
				pEnd = p;
				while (*pEnd){
					if (!(*pEnd) || (*pEnd) == ' '){
						break;
					}
					pEnd++;
				}
				strncpy(fps, p, pEnd - p);
				maxFps = atoi(fps);
				return 1;
			}
		}
		p++;
	}
	return 0;
}


// record the data in fps and in second, two infoRecorders
//


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){


	char recorderName[100] = { 0 };
	char * cmdLine = GetCommandLine();
	char * gameName = NULL;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		gameName = getGameName(cmdLine);

		if (gameName == NULL){
			// error to get the name
			MessageBox(NULL, "null game name", "ERROR", MB_OK);
		}
		// the cmdline format is : <gameName> [-F fps]

		// init the infoRecorder
		
		
		if (infoRecorder == NULL)
		{
			infoRecorder = new InfoRecorder(gameName);
		}

		// start the hook
		do_hook();
		if (gameName){
			free(gameName);
			gameName = NULL;
		}
		break;

	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH:

		//don't do anything here
		break;

		WM_ACTIVATE;
	}
	return TRUE;
	//return TRUE;
}