#include "gamecharactormaker.h"
#include "detours\detours.h"
// this is for the game charactor maker

CharactorMaker::CharactorMaker(char * _gameName, char * _gameFolder, int _runtime, UNIT _unit){

	this->unit = _unit;
	this->runTime = _runtime;
	this->gameName = _strdup(_gameName);
	this->dllName = _strdup(DEFAULT_DLL_NAME);
	this->gameFolder = _strdup(_gameFolder);

	this->limitFps = false;
	this->toLogFrame = false;
	this->saveDirectory = NULL;
	this->outputFileName = NULL;
}

CharactorMaker::CharactorMaker(char * _gameName, char *_dllName, char * _gameFolder, int _runtime, UNIT _unit){

	this->unit = _unit;
	this->runTime = _runtime;
	this->gameName = _strdup(_gameName);
	this->dllName = _strdup(_dllName);
	this->gameFolder = _strdup(_gameFolder);
	this->limitFps = false;
	this->toLogFrame = false;
	this->saveDirectory = NULL;
	this->outputFileName = NULL;
}

CharactorMaker::~CharactorMaker(){
	if (this->gameName){
		free(gameName);
		gameName = NULL;
	}
	if (this->dllName){
		free(dllName);
		dllName = NULL;
	}
	if (gameFolder){
		free(gameFolder);
		gameFolder = NULL;
	}	
	if (charactorLogger){
		delete charactorLogger;
		charactorLogger = NULL;
	}
}

// read the loader's arguments and form the hookd3d.dll arglist
void CharactorMaker::dealArgv(int argc, char ** argv, int startIndex, int stopIndex){
	char * p = argList;
	for (int i = startIndex; i < stopIndex; i++){

		//
		sprintf("%s ", argv[i]);
		if (!strncmp("-t", argv[i], 2))
		{
			// the time to run
			this->runTime = atoi(argv[i + 1]);
			//i += 2;
		}
		else if (!strncmp("-u", argv[i], 2)){
			// the unit
			// valid in hookd3dall.dll
			int u = atoi(argv[i + 1]);
			if (u == UNIT_FPS)
				this->unit = UNIT_FPS;
			else if (u == UNIT_SECONDS)
				this->unit = UNIT_SECONDS;
			
			//i += 2;
		}
		else{
			//i++;
		}
	}
}

void CharactorMaker::loadGame(){
	if (gameName == NULL){
		return;
	}
	if (dllName == NULL){
		return;
	}

	loadGame(gameName, dllName);
}

// start the game with a named dll
// the game name is full path with a game name or just the current path and the name
void CharactorMaker::loadGame(char * _gameName, char * _dllName){
	// define the variables
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	LPSECURITY_ATTRIBUTES lpAttributes;
	LPSECURITY_ATTRIBUTES lpThreadAttributes;
	STARTUPINFO startupInfo = { sizeof(startupInfo) };
	PROCESS_INFORMATION processInformation;
	char cmdLine[100], tem[100] = {0};
	HANDLE curProcessHandle = NULL;

	si.cb = sizeof(si);

#if 0
	// first set the work directory
	if (!GetCurrentDirectory(MAX_PATH, path)){
		// get the directory failed
	}
	strcat(path, gameFolder);

	char * endPoint = path;
	while (*endPoint){
		endPoint++;
	}


	

	// get the folder in game name
	char * p = gameName;
	char * newGameName = gameName;
	while (*p){
		if (*p == '\\' || *p == '/'){
			strncpy(endPoint, gameName, p - gameName + 1);
			newGameName = p + 1;
			break;
		}
		p++;
	}

#endif
	bool relativePath = true;
	printf("Game Name: %s\n", _gameName);
	char * p = _gameName, * lastSlash = NULL;
	while(*p != 0){
		if(*p == ':' || *p == '\\' || *p == '/'){
			// the game name contains the path
			relativePath = false;
		}
		p++;
	}

	p = _gameName;
	// use the relative path or the full path
	if(relativePath == true){
		strcpy(path, ".\\");   // set the path to the current path
	}else{
		// get the path
		while(*p != 0){
			if(*p == '\\' || *p=='/'){
				lastSlash = p;
			}
			p++;
		}

		strncpy(path, _gameName, lastSlash - _gameName);
		printf("Path: %s.\n", path);
	}
	

#if 0
	if (!SetCurrentDirectory(path)){
		// set the directory failed.
		printf("[error]: set current path to '%s' failed.\n", path);
	}
#endif
	// load the game with cmdline
	memset(&startupInfo, 0, sizeof(STARTUPINFO));
	curProcessHandle = GetCurrentProcess();
	startupInfo.cb = sizeof(STARTUPINFO);
	startupInfo.dwFlags = 0;
	startupInfo.wShowWindow = SW_HIDE;

	// prepare the cmd line, the optional parameter is just -F or -f, to limit the fps
	// the game name is the full path?
	if (this->limitFps){
		printf("[INFO]: enable limit fps?\n");
		sprintf(tem, "%s -F %d", _gameName, this->maxFps);
	}
	else{
#if 1
		sprintf(tem, "%s", _gameName);
#else

		sprintf(tem, "%s", newGameName);

#endif
	}

	///write the save directory and the output file name
	if(this->saveDirectory != NULL){
		strcat(tem, " -S ");
		strcat(tem, saveDirectory);
	}
	// the output set file name
	if(this->outputFileName != NULL){
		strcat(tem, " -O ");
		strcat(tem, outputFileName);
	}

	if(this->toLogFrame){
		printf("[INFO]: enable frame Log.\n");
		sprintf(cmdLine, "%s -L %s", tem, "frame");

	}else{
		sprintf(cmdLine, "%s", tem);
	}

	printf("[INFO in Tool]: game cmdline:%s, dll name:%s.\n", cmdLine, _dllName);
#if 0
	bool ret = DetourCreateProcessWithDll(NULL, cmdLine, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE, NULL, path, &startupInfo, &processInformation, _dllName, NULL);
#else
	bool ret = DetourCreateProcessWithDll(NULL, cmdLine, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE, NULL, path, &si, &pi, _dllName, NULL);

#endif
	if (!ret){
		printf("[error]: create game '%s' with dll '%s' failed.\n", cmdLine, _dllName);
	}
}

// start the game with hookd3d.dll
void CharactorMaker::loadGame(char * _gameName){
	loadGame(_gameName, "HookD3D.dll");
}
