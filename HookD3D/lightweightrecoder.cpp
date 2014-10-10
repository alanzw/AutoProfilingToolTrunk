#include "lightweightreocder.h"
// this is for the high performance logger.

// constructor and destructor

LightWeightRecorder::LightWeightRecorder(char * prefix, int bufferSize){
	this->bufferSize = bufferSize;
	logBuffer = NULL;
	curPoint = NULL;
	file = NULL;
	curLogSize = 0;

	temBuffer = NULL;

	if (!init(prefix)){
		// error
	}
}

LightWeightRecorder::~LightWeightRecorder(){
	if (file){
		flush(true);
		close();
		file = NULL;
	}
	if (logBuffer){
		
		free(logBuffer);
		logBuffer = NULL;
		bufferSize = 0;
		curPoint = NULL;
		curLogSize = 0;
	}

	if (temBuffer){
		free(temBuffer);
		temBuffer = NULL;
	}

}

bool LightWeightRecorder::init(char * prefix){
	logBuffer = (char *)malloc(sizeof(char)* bufferSize);
	curPoint = logBuffer;

	temBuffer = (char *)malloc(sizeof(char)* 512);

	// format the log name
	char filename[128];
	sprintf(filename, "%s.log", prefix);
	file = fopen(filename, "w");
	if (file == NULL){
		// error
		return false;
	}
	
	return true;

}
void LightWeightRecorder::log(char * format, ...){
	va_list ap;
	va_start(ap, format);
	int n = vsprintf(temBuffer, format, ap);
	va_end(ap);

	if (this->curLogSize + n >= MAX_LOG_BUFFER_SIZE){
		flush(true);
	}
	// copy the log
	strcpy(this->curPoint, temBuffer);

	this->curLogSize += n;
	this->curPoint += n;
}
bool LightWeightRecorder::close(){
	if (file){
		fclose(file);
		file = NULL;
	}
	return true;
}
bool LightWeightRecorder::flush(bool force){
	if (force && curLogSize > 0){
		fprintf(file, "%s", this->logBuffer);
		memset(logBuffer, 0, MAX_LOG_BUFFER_SIZE);
		curLogSize = 0;
		curPoint = logBuffer;
	}
	return true;
}

