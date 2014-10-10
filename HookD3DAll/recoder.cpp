#include "recorder.h"

void Recoder::init(char * path, char * prefix, char * setName){

	FILE * setFile = NULL;
	char fullPathForSet[MAX_PATH] = {0};

	// get the prefix from the full path game name
	char name[100] = {0};
	char * p = prefix;
	char * lastSlash = NULL;
	while(*p){
		if(*p == '\\'|| *p == '/'){
			lastSlash = p;
		}
		p++;
	}
	strcpy(name, lastSlash+1);


	// create the set file
	if(setName != NULL){
		sprintf(fullPathForSet, "%s\\%s", path, setName);
		// the set name is the full path name
		setFile = fopen(fullPathForSet, "w");
	}
	char errorInfo[512];
	

	// ofstream open 
	char logFileName[128];
	sprintf(logFileName, "%s\\%s.frame.log", path, name);

	if(setName != NULL){
		fprintf(setFile, "%s", logFileName);
	}

#ifndef FILE_POINTER
	frameLogStream.open(logFileName, ios::out);
#else
	frameLogFile = fopen(logFileName, "w");

	if(frameLogFile == NULL){
		sprintf(errorInfo, "open frame log failed, name:%s", logFileName);
		MessageBox(NULL, errorInfo, "ERROR", MB_OK);
	}

#endif
	sprintf(logFileName, "%s\\%s.second.log", path, name);

	if(setName != NULL){
		fprintf(setFile, "%s", logFileName);
	}

#ifndef FILE_POINTER
	secondLogStream.open(logFileName, ios::out);
#else
	secondLogFile = fopen(logFileName, "w");
	if(secondLogFile == NULL){
		sprintf(errorInfo, "open second log failed, name:%s", logFileName);
		MessageBox(NULL, errorInfo, "ERROR", MB_OK);
	}
#endif
	sprintf(logFileName, "%s.error.log", name);
#ifndef FILE_POINTER
	errorLogStream.open(logFileName, ios::out);
#else
	errorLogFile = fopen(logFileName, "w");

	if(errorLogFile == NULL){
		sprintf(errorInfo, "open error log failed, name:%s", logFileName);
		MessageBox(NULL, errorInfo, "ERROR", MB_OK);
	}

	assert(frameLogFile);
	assert(secondLogFile);
	assert(errorLogFile);

	if (frameLogFile == NULL || secondLogFile == NULL || errorLogFile == NULL){
		printf("[INFO]: failed to open log files.\n");
		MessageBox(NULL,"open log files failed", "ERROR", MB_OK);
	}

#endif

#ifdef LOG_TRACE
	sprintf(logFileName, "%s.trace.log", prefix);
	traceLogFile = fopen(logFileName, "w");
	if (traceLogFile == NULL){
		printf("[INFO]: failed to open log files.\n");
	}
#endif

	frameLogBuffer = NULL;
	secondLogBuffer = NULL;
	errorLogBuffer = NULL;

	// allocate the buffers

	curFrameLogBufferPoint = NULL;
	curSecondLogBufferPoint = NULL;
	curErrorLogBufferPoint = NULL;

	// the temp buffer
	buffer1 = NULL;
	buffer2 = NULL;
	buffer3 = NULL;

	// allocate the buffers
	frameLogBuffer = (char *)malloc(sizeof(char)* MAX_LOG_BUFFER_SIZE);
	secondLogBuffer = (char *)malloc(sizeof(char)* MAX_LOG_BUFFER_SIZE);
	errorLogBuffer = (char *)malloc(sizeof(char)* MAX_LOG_BUFFER_SIZE);

	curFrameLogBufferPoint = frameLogBuffer;
	curSecondLogBufferPoint = secondLogBuffer;
	curErrorLogBufferPoint = errorLogBuffer;

	buffer1 = (char *)malloc(sizeof(char)* MAX_TEM_LOG_BUFFER_SIZE);
	buffer2 = (char *)malloc(sizeof(char)* MAX_TEM_LOG_BUFFER_SIZE);
	buffer3 = (char *)malloc(sizeof(char)*MAX_TEM_LOG_BUFFER_SIZE);

	assert(buffer1);
	assert(buffer2);
	assert(buffer3);

	memset(frameLogBuffer, 0, MAX_LOG_BUFFER_SIZE);
	memset(secondLogBuffer, 0, MAX_LOG_BUFFER_SIZE);
	memset(errorLogBuffer, 0, MAX_LOG_BUFFER_SIZE);

	memset(buffer1, 0, MAX_TEM_LOG_BUFFER_SIZE);
	memset(buffer2, 0, MAX_TEM_LOG_BUFFER_SIZE);
	memset(buffer3, 0, MAX_TEM_LOG_BUFFER_SIZE);

#ifdef LOG_TRACE
	buffer4 = NULL;
	traceLogBuffer = (char *)malloc(sizeof(char)* MAX_LOG_BUFFER_SIZE);
	buffer4 = (char *)malloc(sizeof(char)* MAX_TEM_LOG_BUFFER_SIZE);
	curTraceLogBufferPoint = traceLogBuffer;
	memset(traceLogBuffer, 0, MAX_LOG_BUFFER_SIZE);
	memset(buffer4, 0, MAX_TEM_LOG_BUFFER_SIZE);
#endif

	frameCpuWatcher = new CpuWatch();
	secondCpuWatcher = new CpuWatch();
	gpuWatcher = new GpuWatch();
	processHandle = GetCurrentProcess();  // get the game process handle

	frameLogSize = 0;
	secondLogSize = 0;
	errorLogSize = 0;

	// set all to zero

	cmdCountInFrame = 0;
	cmdCountInSecond = 0;
	objCountInFrame = 0;
	objCountInSecond = 0;
	dataSizeInFrame = 0;
	dataSizeInSecond = 0;

	triangleCountInFrame = 0;
	triangleCountInSecond = 0;
	ibLockCountInFrame = 0;
	ibLockCountInSecond = 0;
	vbLockCountInFrame = 0;
	vbLockCountInSecond = 0;

	surfaceLockCountInFrame = 0;
	surfaceLockCountInSecond = 0;
	textureLockCountInFrame = 0;
	textureLockCountInSecond = 0;
	stateBlockCountInFrame = 0;
	stateBlockCountInSecond = 0;

	drawTimesInFrame = 0;
	drawTimesInSecond = 0;
	setTextureInFrame = 0;
	setTextureInSecond = 0;
	fpsInSecond = 0.0f;

	parameterDataSizeInFrame = 0;
	parameterDataSizeInSecond = 0;
	parameterDataToRemoteInFrame = 0;
	parameterDataToRemoteInSecond = 0;
	vertexShaderConstInFrame = 0;
	vertexShaderConstInSecond = 0;

	pixelShaderConstInFrame = 0;
	pixelShaderConstInSecond = 0;
	vertexShaderCmdCountInFrame = 0;
	vertexShaderCmdCountInSecond = 0;
	pixelShaderCmdCountInFrame = 0;
	pixelShaderCmdCountInSecond = 0;

	QueryPerformanceFrequency(&freq);

	processHandle = GetCurrentProcess();
	frameIndex = 0;
	timeIndex  = 0;
}

void Recoder::init(char * path, char * prefix){
	char out[MAX_PATH] = {0};
	sprintf(out, "%s.single.set", prefix);
	init(path, prefix, NULL);
}

void Recoder::init(char * prefix){
	init(".\\", prefix);
}

// this is for recoder. do the counter's work
Recoder::Recoder(){
	this->limitFps = false;
	this->enableFrameLog = false;
	this->maxFps = 30;
	// use the default prefix
	init(DEFAULT_LOG_PREFIX);
}

Recoder::Recoder(char * name){
	this->limitFps = false;
	this->enableFrameLog = false;
	this->maxFps = 30;
	init(name);
}

Recoder::Recoder(char * name, int fps){
	this->limitFps = true;
	this->maxFps = fps;
	init(name);
}

Recoder::Recoder(char *path, char *name){
	this->limitFps = false;
	this->enableFrameLog = false;
	this->maxFps = 30;
	init(path, name);
}
Recoder::Recoder(char * path, char * name, int fps){
	this->limitFps = true;
	this->maxFps = fps;
	init(path, name);
}

Recoder::Recoder(char * path, char *name, char * setName){
	this->limitFps = false;
	this->enableFrameLog  = false;
	this->maxFps = 30;
	init(path, name, setName);
}

Recoder::~Recoder(){
	if (frameLogBuffer){
		free(frameLogBuffer);
		frameLogBuffer = NULL;
	}
	if (secondLogBuffer){
		free(secondLogBuffer);
		secondLogBuffer = NULL;
	}
	if (errorLogBuffer){
		free(errorLogBuffer);
		errorLogBuffer = NULL;
	}
#ifdef FILE_POINTER

	if (frameLogFile){
		fclose(frameLogFile);
		frameLogFile = NULL;
	}
	if (secondLogFile){
		fclose(secondLogFile);
		secondLogFile = NULL;
	}
	if (errorLogFile){
		fclose(errorLogFile);
		errorLogFile = NULL;
	}
#endif

#ifdef LOG_TRACE
	if (traceLogFile){
		fclose(traceLogFile);
		traceLogFile = NULL;
	}
#endif

}
// flush the logs from memory to files

void Recoder::flushErrorLog(bool forceToFlush){
	if (forceToFlush){
		// write to file anyway
		fprintf(errorLogFile, "%s", errorLogBuffer);
		memset(errorLogBuffer, 0, MAX_LOG_BUFFER_SIZE);
		// reset cur point
		this->curErrorLogBufferPoint = errorLogBuffer;
		errorLogSize = 0;
	}
	else{

	}
}
void Recoder::flushFrameLog(bool forceToFlush){
	if (forceToFlush){
		// write to file anyway
		fprintf(frameLogFile, "%s", frameLogBuffer);
		memset(frameLogBuffer, 0, MAX_LOG_BUFFER_SIZE);
		curFrameLogBufferPoint = frameLogBuffer;
		frameLogSize = 0;
	}
	else{

	}
}
void Recoder::flushSecondLog(bool forceToFlush){
	if (forceToFlush){
		// write to file anyway
		fprintf(secondLogFile, "%s", secondLogBuffer);
		memset(secondLogBuffer, 0, MAX_LOG_BUFFER_SIZE);
		curSecondLogBufferPoint = secondLogBuffer;
		secondLogSize = 0;
	}
	else{

	}
}

void Recoder::FlushLog(bool forceToFlush){
	if (forceToFlush){
		// write to file anyway
		flushFrameLog(true);
		flushSecondLog(true);
		flushErrorLog(true);
#ifdef LOG_TRACE
		flushTraceLog(true);
#endif
		return;
	}

	if (this->frameLogSize >= MAX_LOG_BUFFER_SIZE - 20){
		flushFrameLog(true);
	}
	else{
		flushFrameLog();
	}

	if (this->secondLogSize >= MAX_LOG_BUFFER_SIZE - 20){
		flushSecondLog(true);
	}
	else{
		flushSecondLog();
	}

	if (this->errorLogSize >= MAX_LOG_BUFFER_SIZE - 20){
		flushErrorLog(true);
	}
	else{
		flushErrorLog();
	}

#ifdef LOG_TRACE
	if (this->traceLogSize >= MAX_LOG_BUFFER_SIZE - 20){
		flushTraceLog(true);
	}
	else{
		flushTraceLog();
	}

#endif
}

void Recoder::onFrameEnd(){
	// compute the fps
	float curFps = 0.0f;
	double cpuUsage = 0.0f;
	double gpuUsage = 0.0f;
	// get the frame time
	QueryPerformanceCounter(&endTime);

	if (frameStarted){
		this->frameCountInSecond++;
		timeCount += (endTime.QuadPart - startTime.QuadPart);
		//logError("[INFO]: time count:%lld, freq:%lld.\n", timeCount,freq.QuadPart);
		if (timeCount >= this->freq.QuadPart){
			//logError("[INFO]: logSecond.\n");
			onSecondEnd();
			timeCount = 0;
		}

		//gpuUsage = this->gpuWatcher->gpuUtilization();

		// do the log for frame
		// log format should be: [index] [fps] [cpu] [gpu] [cmdCount] [paramSize] [paramSizeToRemote] [objcCount] [dataSize] [triangleCount] [drawTimes] [ibLockCount] [ibSize] [vbLockCount] [vbSize] [surfaceLockCount] [surfaceSize] [textureLockCount] [textureSize] [setTextureCount] [stateBlockCount] [vertexShaderCmdCount] [vertexShaderConstSize] [pixelShaderSize] [pixelShaderConstSize]
#ifdef ENABLE_LOG_FRAME
		if(this->enableFrameLog){
#if 1
			cpuUsage = frameCpuWatcher->GetProcessCpuUtilization(this->processHandle);
			gpuUsage = gpuWatcher->GetGpuUsage();

			curFps = this->freq.QuadPart / ((endTime.QuadPart - startTime.QuadPart));
#endif

			this->logFrame("%d %f %f %f %d %lld %lld %d %lld %d %d %d %d %d %d %d %lld %d %d %d %d %d %d %d %d\n", frameIndex, curFps, cpuUsage, gpuUsage, this->cmdCountInFrame, this->parameterDataSizeInFrame, this->parameterDataToRemoteInFrame, this->objCountInFrame, this->dataSizeInFrame, this->triangleCountInFrame, this->drawTimesInFrame, this->ibLockCountInFrame, this->ibSizeInFrame, this->vbLockCountInFrame, this->vbSizeInFrame, this->surfaceLockCountInFrame, this->surfaceSizeInFrame, this->textureLockCountInFrame, this->textureSizeInFrame, this->setTextureInFrame, this->stateBlockCountInFrame, this->vertexShaderCmdCountInFrame, this->vertexShaderConstInFrame, this->pixelShaderCmdCountInFrame, this->pixelShaderConstInFrame);

			frameIndex++;
#endif
			

			this->cmdCountInFrame = 0;
			this->objCountInFrame = 0;
			this->dataSizeInFrame = 0;
			this->triangleCountInFrame = 0;
			this->ibLockCountInFrame = 0;
			this->ibSizeInFrame = 0;
			this->vbLockCountInFrame = 0;
			this->vbSizeInFrame = 0;
			this->surfaceLockCountInFrame = 0;
			this->surfaceSizeInFrame = 0;
			this->textureLockCountInFrame = 0;
			this->textureSizeInFrame = 0;
			this->stateBlockCountInFrame = 0;
			this->drawTimesInFrame = 0;
			this->setTextureInFrame = 0;
			this->parameterDataSizeInFrame = 0;
			this->parameterDataToRemoteInFrame = 0;
			this->vertexShaderConstInFrame = 0;
			this->vertexShaderCmdCountInFrame = 0;
			this->pixelShaderCmdCountInFrame = 0;
			this->pixelShaderConstInFrame = 0;
		}

		QueryPerformanceCounter(&startTime);
	}
	else{
		frameStarted = true;
		QueryPerformanceCounter(&startTime);
	}

}
void Recoder::onFrameStart(){

	// get the start time
	QueryPerformanceCounter(&startTime);
	if (!secondStarted){
		onSecondStart();
		secondStarted = true;
	}

	this->cmdCountInFrame = 0;
	this->objCountInFrame = 0;
	this->dataSizeInFrame = 0;
	this->triangleCountInFrame = 0;
	this->ibLockCountInFrame = 0;
	this->vbLockCountInFrame = 0;
	this->surfaceLockCountInFrame = 0;
	this->textureLockCountInFrame = 0;
	this->stateBlockCountInFrame = 0;
	this->drawTimesInFrame = 0;
	this->setTextureInFrame = 0;
	this->parameterDataSizeInFrame = 0;
	this->parameterDataToRemoteInFrame = 0;
	this->vertexShaderConstInFrame = 0;
	this->vertexShaderCmdCountInFrame = 0;
	this->pixelShaderCmdCountInFrame = 0;
	this->pixelShaderConstInFrame = 0;
}

void Recoder::onSecondStart(){
	this->frameCountInSecond = 0;
	this->timeCount = 0;
	QueryPerformanceCounter(&secondStart);
}

// when 1 second is up, set all second counters to 0
void Recoder::onSecondEnd(){
	//secondStarted = false;
	QueryPerformanceCounter(&secondEnd);
	// log second's counter first
	// log format should be: [index] [fps] [cpu] [gpu] [cmdCount] [paramSize] [paramSizeToRemote] [objcCount] [dataSize] [triangleCount] [drawTimes] [ibLockCount] [ibSize] [vbLockCount] [vbSize] [surfaceLockCount] [surfaceSize] [textureLockCount] [textureSize] [setTextureCount] [stateBlockCount] [vertexShaderCmdCount] [vertexShaderConstSize] [pixelShaderSize] [pixelShaderConstSize]
	timeIndex++;
	float cpuUsage = 0.0f;
	float gpuUsage = 0.0f;

	if (secondStarted){
		this->fpsInSecond = frameCountInSecond * 1.0f * this->freq.QuadPart / (secondEnd.QuadPart - secondStart.QuadPart);

		this->frameCountInSecond = 0;
		this->processHandle = GetCurrentProcess();

		cpuUsage = secondCpuWatcher->GetProcessCpuUtilization(this->processHandle);
		gpuUsage = gpuWatcher->GetGpuUsage();

		this->logSecond("%d %f %f %f %d %lld %lld %d %lld %d %d %d %d %d %d %d %lld %d %d %d %d %d %d %d %d\n", timeIndex, fpsInSecond, cpuUsage, gpuUsage, this->cmdCountInSecond, this->parameterDataSizeInSecond, this->parameterDataToRemoteInSecond, this->objCountInSecond, this->dataSizeInSecond, this->triangleCountInSecond, this->drawTimesInSecond, this->ibLockCountInSecond, this->ibSizeInSecond, this->vbLockCountInSecond, this->vbSizeInSecond, this->surfaceLockCountInSecond, this->surfaceSizeInSecond, this->textureLockCountInSecond, this->textureSizeInSecond, this->setTextureInSecond, this->stateBlockCountInSecond, this->vertexShaderCmdCountInSecond, this->vertexShaderConstInSecond, this->pixelShaderCmdCountInSecond, this->pixelShaderConstInSecond);

		// set second's counter to 0
		this->cmdCountInSecond = 0;
		this->objCountInSecond = 0;
		this->dataSizeInSecond = 0;
		this->triangleCountInSecond = 0;
		this->ibLockCountInSecond = 0;
		this->ibSizeInSecond = 0;
		
		this->vbLockCountInSecond = 0;
		this->vbSizeInSecond = 0;
		this->surfaceLockCountInSecond = 0;
		this->surfaceSizeInSecond = 0;
		this->textureLockCountInSecond = 0;
		this->textureSizeInSecond = 0;

		this->stateBlockCountInSecond = 0;
		this->drawTimesInSecond = 0;
		this->setTextureInSecond = 0;
		this->parameterDataSizeInSecond = 0;
		this->parameterDataToRemoteInSecond = 0;
		this->vertexShaderCmdCountInSecond = 0;
		this->vertexShaderConstInSecond = 0;
		this->pixelShaderCmdCountInSecond = 0;
		this->pixelShaderConstInSecond = 0;
	}
	else{
		secondStarted = true;
	}

	QueryPerformanceCounter(&secondStart);
}

void Recoder::logFrame(const char * format, ...){
#ifdef ENABLE_LOG_FRAME
	va_list ap;
	va_start(ap, format);
	int n = vsprintf(this->buffer1, format, ap);
	va_end(ap);


#if 0
	if (this->frameLogSize + n >= MAX_LOG_BUFFER_SIZE){
		flushFrameLog(true);
	}
#else
	flushFrameLog(true);
#endif

	// copy the log
	strcpy(this->curFrameLogBufferPoint, buffer1);

	this->frameLogSize += n;
	this->curFrameLogBufferPoint += n;
#endif
}

void Recoder::logSecond(const char * format, ...){

#ifdef ENABLE_LOG_SECOND
	va_list ap;
	va_start(ap, format);
	int n = vsprintf(this->buffer2, format, ap);
	va_end(ap);
#if 0
	if (this->secondLogSize + n >= MAX_LOG_BUFFER_SIZE){
		flushSecondLog(true);
	}
#else
	flushSecondLog(true);
#endif

	// copy the log
	strcpy(this->curSecondLogBufferPoint, buffer2);

	this->secondLogSize += n;
	this->curSecondLogBufferPoint += n;
#endif
}

void Recoder::logError(const char * format, ...){

#ifdef ENABLE_LOG_ERROR
	va_list ap;
	va_start(ap, format);
	int n = vsprintf(this->buffer3, format, ap);
	va_end(ap);
#if 0
	if (this->errorLogSize + n >= MAX_LOG_BUFFER_SIZE){
		flushErrorLog(true);
	}
#else
	flushErrorLog(true);
#endif

	// copy the log
	strcpy(this->curErrorLogBufferPoint, buffer3);

	this->errorLogSize += n;
	this->curErrorLogBufferPoint += n;
#endif
}


void Recoder::logTrace(const char * format, ...){
#ifdef LOG_TRACE
	va_list ap;
	va_start(ap, format);
	int n = vsprintf(this->buffer4, format, ap);
	va_end(ap);

#if 0
	if (this->traceLogSize + n >= MAX_LOG_BUFFER_SIZE){
		flushTraceLog(true);

	}
#else
	flushTraceLog(true);

#endif

	//logError("trace len:%d, curTracePoint:0x%p, start:0x%p, start+ size:0x%p\n", n, curTraceLogBufferPoint, traceLogBuffer, traceLogBuffer + MAX_LOG_BUFFER_SIZE);

	// copy the log
	strcpy(this->curTraceLogBufferPoint, buffer4);

	memset(buffer4, 0, MAX_TEM_LOG_BUFFER_SIZE);
	this->traceLogSize += n;
	this->curTraceLogBufferPoint += n;
#else

#endif
}
#ifdef LOG_TRACE
void Recoder::flushTraceLog(bool forceToFlush){
	if (forceToFlush){
		// write to file anyway
		fprintf(traceLogFile, "%s", traceLogBuffer);
		memset(traceLogBuffer, 0, MAX_LOG_BUFFER_SIZE);
		// reset cur point
		this->curTraceLogBufferPoint = traceLogBuffer;
		traceLogSize = 0;
	}
	else{

	}
}
#endif

/// functions
// the cmd is not send to remote
void Recoder::cmdCalled(int paramSize){
	this->cmdCountInFrame++;
	this->cmdCountInSecond++;

	this->parameterDataSizeInFrame += paramSize;
	this->parameterDataSizeInSecond += paramSize;

	this->logError("[INFO]: cmd param size:%d.\n", paramSize);
}
// the cmd is sent to remote
void Recoder::cmdSendAndCalled(int paramSize){
	this->cmdCountInFrame++;
	this->cmdCountInSecond++;
	this->parameterDataSizeInFrame += paramSize;
	this->parameterDataSizeInSecond += paramSize;
	this->parameterDataToRemoteInFrame += paramSize;
	this->parameterDataToRemoteInSecond += paramSize;

	this->logError("[INFO]: send cmd size:%d.\n", paramSize);
	this->logTrace("[INFO]: send cmd size:%d.\n", paramSize);
}

// draw primitives, send to remote
void Recoder::drawCalled(int paramSize, int primCount){
#if 0
	this->cmdCountInFrame++;
	this->cmdCountInSecond++;
	this->parameterDataSizeInFrame += paramSize;
	this->parameterDataSizeInSecond += paramSize;
	this->parameterDataToRemoteInFrame += paramSize;
	this->parameterDataToRemoteInSecond += paramSize;
#else
	cmdSendAndCalled(paramSize);
#endif

	this->triangleCountInFrame += primCount;
	this->triangleCountInSecond += primCount;

	// each draw command represent an object

	this->objCountInFrame++;
	this->objCountInSecond++;

	this->drawTimesInFrame++;
	this->drawTimesInSecond++;

}
// set vertex buffer, send
void Recoder::setVertexBufferCalled(int paramSize, int dataSize){
	cmdSendAndCalled(paramSize);

	this->dataSizeInFrame += dataSize;
	this->dataSizeInSecond += dataSize;

	// equal to draw, because each draw will call set vb and set ib
}
// set index buffer, send
void Recoder::setIndexBufferCalled(int paramSize, int dataSize){
	cmdSendAndCalled(paramSize);

	this->dataSizeInFrame += dataSize;
	this->dataSizeInSecond += dataSize;

}
// scene operation, begin and end, send
void Recoder::sceneOperationCalled(){
	cmdSendAndCalled(0);
}
// stateBlock operation, begin and end, send

// set vertex shader, send
void Recoder::setVertexShaderCalled(int paramSize, int shaderSize){
	cmdSendAndCalled(paramSize);

	this->dataSizeInFrame += shaderSize;
	this->dataSizeInSecond += shaderSize;

	this->vertexShaderCmdCountInFrame += shaderSize;
	this->vertexShaderCmdCountInSecond += shaderSize;

	this->vertexShaderSizeInFrame += shaderSize;
	this->vertexShaderConstInSecond += shaderSize;

}
// vertex shader constant , send
void Recoder::vertexShaderConstantCalled(int paramSize, int dataSize){
	cmdSendAndCalled(paramSize);

	this->dataSizeInFrame += dataSize;
	this->dataSizeInSecond += dataSize;

	this->vertexShaderConstInFrame += dataSize;
	this->vertexShaderConstInSecond += dataSize;

}
// set pixel shader, send
void Recoder::setPixelShaderCalled(int paramSize, int shaderSize){
	this->cmdSendAndCalled(paramSize);

	this->dataSizeInFrame += shaderSize;
	this->dataSizeInSecond += shaderSize;

	this->pixelShaderCmdCountInFrame += shaderSize;
	this->pixelShaderCmdCountInSecond += shaderSize;

	this->pixelShaderSizeInFrame += shaderSize;
	this->pixelShaderSizeInSecond += shaderSize;
}
// pixel shader data, send
void Recoder::pixelShaderConstantCalled(int paramSize, int dataSize){
	this->cmdSendAndCalled(paramSize);

	this->dataSizeInFrame += dataSize;
	this->dataSizeInSecond += dataSize;
	this->pixelShaderConstInFrame += dataSize;
	this->pixelShaderConstInSecond += dataSize;
}
// texture unlock, not send
void Recoder::textureUnLockRectCalled(int paramSize, int texSize){
	this->cmdCalled(paramSize);

	this->dataSizeInFrame += texSize;
	this->dataSizeInSecond += texSize;
	this->textureSizeInFrame += texSize;
	this->textureSizeInSecond += texSize;

	this->textureLockCountInFrame++;
	this->textureLockCountInSecond++;
}
// surface unlock, not send
void Recoder::surfaceUnlockRectCalled(int paramSize, int surfaceSize){
	this->cmdCalled(paramSize);

	this->dataSizeInFrame += surfaceSize;
	this->dataSizeInSecond += surfaceSize;
	this->surfaceSizeInFrame += surfaceSize;
	this->surfaceSizeInSecond += surfaceSize;

	this->surfaceLockCountInFrame++;
	this->surfaceLockCountInSecond++;
}
// index buffer lock, send
void Recoder::indexBufferLockCalled(int paramSize, int ibSize){
	this->cmdSendAndCalled(paramSize);

	this->ibLockCountInFrame++;
	this->ibLockCountInSecond++;

	this->ibSizeInFrame += ibSize;
	this->ibSizeInSecond += ibSize;
	this->dataSizeInFrame += ibSize;
	this->dataSizeInSecond += ibSize;
}
void Recoder::vertexBufferLockCalled(int paramSize, int vbSize){
	this->cmdSendAndCalled(paramSize);

	this->vbLockCountInFrame++;
	this->vbLockCountInSecond++;

	this->vbSizeInFrame += vbSize;
	this->vbSizeInSecond += vbSize;
	this->dataSizeInFrame += vbSize;
	this->dataSizeInSecond += vbSize;
}
void Recoder::presentCalled(int paramSize){
	this->frameIndex++;
	this->cmdSendAndCalled(paramSize);

	// the last, call the onFrameEnd
	this->onFrameEnd();
}


void Recoder::stateBlockCalled(){
	this->cmdSendAndCalled(0);
	this->stateBlockCountInFrame++;
	this->stateBlockCountInSecond++;
}


void Recoder::logGuid(GUID riid){
	//sprintf(curTraceLogBufferPoint, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X} ", riid.Data1, riid.Data2, riid.Data3, riid.Data4[1], riid.Data4[0], riid.Data4[7], riid.Data4[6], riid.Data4[5], riid.Data4[4], riid.Data4[3], riid.Data4[2]);
	logTrace("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X} ", riid.Data1, riid.Data2, riid.Data3, riid.Data4[1], riid.Data4[0], riid.Data4[7], riid.Data4[6], riid.Data4[5], riid.Data4[4], riid.Data4[3], riid.Data4[2]);

}