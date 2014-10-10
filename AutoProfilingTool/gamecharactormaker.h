#ifndef __GAMECHARACTORMAKER_H__
#define __GAMECHARACTORMAKER_H__
// this is for the charactor maker for any d3d game. record the cpu usage, gpu usage and the fps
#include <Windows.h>
#include "..\Utility\log.h"
#include "common.h"

#define DEFAULT_DLL_NAME "HookD3D.dll"

class CharactorMaker{
	char * gameName, *dllName, *gameFolder;
	char * saveDirectory, * outputFileName;

	char argList[128];
	char path[MAX_PATH];
	int runTime;    // the max time to run, in minutes

	UNIT unit;     // identify the recording time interval, in frame or in seconds
	Log * charactorLogger;   // write to file

	bool limitFps;
	bool toLogFrame;
	int maxFps;

public:
	inline void setEnableFrameLog(bool val){ toLogFrame = val; }
	inline void setMaxFps(int mfps){ limitFps = true; maxFps = mfps; }

	inline void setSaveDirectory(char * directory){
		this->saveDirectory = _strdup(directory);
	}
	inline void setOutputFileName(char * fileName){
		this->outputFileName = _strdup(fileName);
	}

	// load game accordingly
	void loadGame();

	// load game with hookd3d.dll
	void loadGame(char * _gameName);

	// load game with specified dll
	void loadGame(char * _gameName, char * _dllName);

	void dealArgv(int argc, char ** argv, int startIndex, int stopIndex);   // read the arg list for the loader and format the argList 

	// the runtime indicate the time to run

	CharactorMaker(char * _gameName, char * _gameFolder, int _runtime, UNIT _unit);

	CharactorMaker(char * _gameName, char *_dllName, char * _gameFolder, int _runtime, UNIT _unit);
	~CharactorMaker();
};


#endif