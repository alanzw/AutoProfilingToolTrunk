#include "hook_common.h"
#include <Windows.h>
#include "recorder.h"
#include "wrap_direct3d9.h"

Recoder * gRecoder = NULL;    // the global recoder

IDirect3D9* (WINAPI* Direct3DCreate9Next)(UINT SDKVersion) = Direct3DCreate9;
void (WINAPI* ExitProcessNext)(UINT uExitCode) = ExitProcess;

IDirect3D9 * WINAPI Direct3DCreate9Callback(UINT SDKVersion){
	gRecoder->logTrace("[INFO]: call the Direct3DCraete9.\n");
	IDirect3D9 * base_d3d9 = Direct3DCreate9Next(SDKVersion);
	IDirect3D9 * pv = NULL;

	if (base_d3d9){
		pv = dynamic_cast<IDirect3D9 *>(new WrapperDirect3D9(base_d3d9, WrapperDirect3D9::ins_count++));
	}

	return pv;
}


void WINAPI ExitProcessCallback(UINT uExitCode){
	gRecoder->logError("[INFO]: call exit process.\n");

	if (gRecoder){
		gRecoder->FlushLog(true);
		delete gRecoder;
		gRecoder = NULL;
	}
	
	ExitProcessNext(uExitCode);
}
void StartHook() {
	gRecoder->logTrace("[INFO]: to start hook d3d.\n");


	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach((PVOID*)&Direct3DCreate9Next, Direct3DCreate9Callback);
	DetourAttach(&(PVOID&)ExitProcessNext, ExitProcessCallback);
	LONG co = DetourTransactionCommit();
	if( co== NO_ERROR){
		gRecoder->logTrace("[INFO]: detour transaction commit succeeded.\n");
	}
	else{
		gRecoder->logTrace("[ERROR]: detour transaction commit failed with code:%d.\n", co);
	}
}


// read the cmdline to find whether to limit the fps
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


#if 0
char * getSavePath(char * cmdLine){
	char * p = cmdLine;
	char path[MAX_PATH] = {0};
	char * lastSlash  = NULL;
	while(*p){
		if(*p == '\\' || *p == '/'){
			lashSlash = p;
		}
		p++;
	}
	if(lastSlash - cmdLine >0){
		strncpy(path, cmdLine, lastSlash - cmdLine);
		return _strdup(path);
	}else{
		return _strdup(".\\");
	}
}
#endif

bool rateControl = false;
int maxFps = 30;
bool enableFrameLog = false;
char path[MAX_PATH] = {0};
char outputFileName[MAX_PATH] = {0};
bool useOutput = false;

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
				//return 1;
				p = pEnd;
			}
			else if(*p == 'L' || *p == 'l'){
				// the log option
				p++;
				while(*p == ' ' ){
					p++;
				}
				// the p is the start of the log option
				pEnd = p;
				while( *pEnd){
					if(!(*pEnd) || (*pEnd) == ' '){
						break;
					}
					pEnd++;
				}
				if(!strncmp("frame", p, pEnd - p)){
					// frame log enabled.
					enableFrameLog = true;
				}
				p = pEnd;

			}
			else if(*p == 'S' || *p == 's'){
				// the save directory
				p++;
				while(*p == ' '){
					p++;
				}
				// the p is the start of the save directory
				pEnd = p;
				while(*pEnd){
					if(!(*pEnd) || (*pEnd) == ' '){
						break;
					}
					pEnd++;
				}
				strncpy(path, p, pEnd - p);
				p=pEnd;
			}
			else if(*p == 'O' || *p == 'o'){
				// the output file name
				p++;
				while(*p == ' '){
					p++;
				}
				pEnd = p;
				while(*pEnd){
					if(!(*pEnd) || (*pEnd) == ' '){
						break;
					}
					pEnd++;
				}
				strncpy(outputFileName, p, pEnd - p);
				p = pEnd;
				useOutput = true;
			}

		}
		p++;
	}
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {

	char * cmdLine = GetCommandLine();
	char * gameName = NULL;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// deal with the command line, get all the parameters
		gameName = getGameName(cmdLine);
		if (gameName == NULL){
			MessageBox(NULL, "null game name", "ERROR", MB_OK);
		}

		getFps(cmdLine);

		// init the logger
		if (gRecoder == NULL){
			if(useOutput == false){
				gRecoder = new Recoder(path, gameName);
			}
			else{
				gRecoder = new Recoder(path, gameName, outputFileName);
			}
		}
		
		//getFps(cmdLine);

		if (rateControl){
			gRecoder->setLimitFps(true);
			gRecoder->setMaxFps(maxFps);
		}
		else{
			gRecoder->logTrace("[INFO]: no limit to fps.\n");
		}
		
		if(enableFrameLog){
			gRecoder->setEnableFrameLog(true);
		}
		else{
			gRecoder->logTrace("[INFO]: do not log frame.\n");
		}

		// start the hook
		DisableThreadLibraryCalls(hModule);

		StartHook();
		break;
	case DLL_THREAD_ATTACH: break;
	case DLL_THREAD_DETACH: break;
	case DLL_PROCESS_DETACH:

		//don't do anything here
		break;

		WM_ACTIVATE;
	}

	return TRUE;
}