#ifndef __LIGHTWEIGHTRECORDER_H__
#define __LIGHTWEIGHTRECORDER_H__
// this is for the high performance logger
#include <Windows.h>
#include <stdio.h>

#define MAX_LOG_BUFFER_SIZE 8388608



class LightWeightRecorder{
	int bufferSize;

	int curLogSize;
	char * curPoint;
	char * logBuffer;
	char * temBuffer;
	FILE * file;


public:
	LightWeightRecorder(char * prefix, int bufferSize = MAX_LOG_BUFFER_SIZE);
	~LightWeightRecorder();

	void log(char * format, ...);
	bool init(char * prefix);
	bool close();
	bool flush(bool force);
};

#endif