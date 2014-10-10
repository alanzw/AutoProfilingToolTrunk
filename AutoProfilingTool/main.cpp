// the main entry of the tool

#include <iostream>
#include "gamecharactormaker.h"
#include "schedulewindow.h"
#if 1

#define DEFAULT_GAME_FOLDER "\\Games\\"
#else
#define DEFAULT_GAME_FOLDER "\\"
#endif
using namespace std;
// para: argv0, the tool name
//

int usage(int argc){
	cout << "usage:\n\tAutoProfilingTool [-U <unitType>] [[-S <profileInputSet>] or [-I <inputFile>]] [-D <dllName> -P <saveDirectory> [-O <setName> [-F <fps>] -G <gameName> ...]." << endl;
	cout << "\t-U: the <unitType> specific the unit to recoder, can be UNIT_FPS or UNIT_SECONDS." << endl;
	cout << "\t-I: the <profileInputSet> file contains the names of all the games' charactor file." << endl;
	cout << "\t-D: the <dllName> specified the dll to use. if dll name is 'hookd3dall.dll', may need to use -u <unit> to specific the record unit for game." << endl;
	cout << "\t-F: the <fps> is to limit the games FPS." << endl;
	cout << "\t-G: the <gameName>... contains all the games to run and log the charactor to files." << endl;
	cout << "\t-P: the <saveDirectory> to save the ouputfile." << endl;
	cout << "\t-O: the <setName> to specfic the output file name." << endl;

	if (argc <= 2){
		cout << "usage: AutoProfilingTool -I <profileInputSet>, or AutoProfileTool -D <dllName> -G <gameName> ...." << endl;
		return -1;
	}
	else if (argc > 3){

	}

}


// the arg list, the argv is valid
void dealArgList(int argc, char ** argv){
	for (int i = 0; i < argc; i++){
		if (!strcmp(argv[i], "-I")){
			// schedule window

		}
		else if (!strcmp(argv[i], "-D") || !strcmp(argv[i], "-F") || !strcmp(argv[i], "-G")){
			// charactor maker
		}
	}
}

int main(int argc, char ** argv){
	if (argc <= 2){
		usage(argc);
		return -1;
	}

	char * inputSet = NULL, *inputFile = NULL, * dllName = NULL, * gameName = NULL, * log = NULL;
	char * saveDirectory = NULL, * outputFileName = NULL;

	int maxFps = 0 ;
	bool limitFps = false, enableLogFrame = false;
	UNIT unitType = UNIT::UNIT_FPS;
	
	bool getWindow = false;
	// deal the args
	for (int i = 0; i < argc; i++){
		if (!strcmp(argv[i], "-U") || !strcmp(argv[i], "-u")){
			if (!strcmp(argv[i + 1], "UNIT_SECONDS")){
				unitType = UNIT_SECONDS;
			}
		}
		else if (!strcmp(argv[i], "-I") || !strcmp(argv[i], "-i")){
			// schedule window
			inputSet = _strdup(argv[i + 1]);
			ScheduleWindow<float> * scheduleWindowForSet = new ScheduleWindow<float>(inputSet, unitType);
			scheduleWindowForSet->processInputSet(inputSet);
			getWindow = true;
			break;
		}
		else if (!strcmp(argv[i], "-S") || !strcmp(argv[i], "-s")){
			inputFile = _strdup(argv[i + 1]);

			ScheduleWindow<float> * scheduleWindowForSingle = new ScheduleWindow<float>(inputFile, 0, unitType);

			scheduleWindowForSingle->getScheduleWindow(inputFile);
			getWindow = true;
			break;
		}
		else if (!strcmp(argv[i], "-D") || !strcmp(argv[i], "-d")){
			// charactor maker
			dllName = _strdup(argv[i + 1]);
		}
		else if (!strcmp(argv[i], "-F") || !strcmp(argv[i], "-f")){
			// charactor maker
			limitFps = true;
			maxFps = atoi(argv[i + 1]);

		}else if(!strcmp(argv[i], "-G") || !strcmp(argv[i], "-f")){
			// charactor maker
			gameName = _strdup(argv[i + 1]);

		}
		else if(!strcmp(argv[i], "-L") || !strcmp(argv[i], "-l")){
			log = _strdup(argv[i+1]);
			enableLogFrame = true;	
		}
		else if(!strcmp(argv[i], "-P") || !strcmp(argv[i], "-p")){
			saveDirectory = _strdup(argv[i+1]);
		}
		else if(!strcmp(argv[i], "-O") || !strcmp(argv[i], "-o")){
			outputFileName = _strdup(argv[i+1]);
		}
	}
	// here to create charactor maker
	if (getWindow){

	}
	else{
		CharactorMaker * cmaker = new CharactorMaker(gameName, dllName, DEFAULT_GAME_FOLDER, 1, UNIT_FPS);

		if (limitFps){
			printf("[main]: limitFps true?\n");
			cmaker->setMaxFps(maxFps);
		}
		if(enableLogFrame){
			printf("[main]: allow to log frame data.\n");
			cmaker->setEnableFrameLog(true);
		}

		if(saveDirectory != NULL){
			cmaker->setSaveDirectory(saveDirectory);
		}
		if(outputFileName != NULL){
			cmaker->setOutputFileName(outputFileName);
		}

		cmaker->loadGame();
	}
	return 0;
}