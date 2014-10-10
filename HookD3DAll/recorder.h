#ifndef __RECORDER_H__

#define __RECORDER_H__
//#include "..\Utility\log.h"
#include "..\Utility\CpuWatch.h"
#include "..\Utility\GpuWatch.h"
#include "..\Utility\hash_set.h"

#include <assert.h>

#define GETWRAPPERDEVICE

#define MAX_LOG_BUFFER_SIZE 819200//8388608   // 8MB
#define MAX_TEM_LOG_BUFFER_SIZE 1024
#define DEFAULT_LOG_PREFIX "default"

#define FILE_POINTER

//#define LOG_TRACE     // to log the trace for d3d
#define ENABLE_LOG_FRAME
#define ENABLE_LOG_SECOND
//#define ENABLE_LOG_ERROR

#include <iostream>
using namespace std;

// the recorder is to record all the performance data

class Recoder{

	unsigned int frameIndex, timeIndex;

	int cmdCountInFrame;             // instruction count
	int cmdCountInSecond;

	int objCountInFrame;             // the object count in a single frame
	int objCountInSecond;            // the object count in one second

	LONGLONG dataSizeInFrame;    // all object data ( vb, ib, texture, surface, constantF and so on, but no contains the parameters)
	LONGLONG dataSizeInSecond; 

	unsigned int triangleCountInFrame;       // triangles drawed
	unsigned int triangleCountInSecond;

	int ibLockCountInFrame;			 // index bufffer update times
	int ibLockCountInSecond;

	int ibSizeInFrame;
	int ibSizeInSecond;

	int vbLockCountInFrame;			 // vertex buffer update times
	int vbLockCountInSecond;

	int vbSizeInFrame;
	int vbSizeInSecond;

	int surfaceLockCountInFrame;    // surface update times
	int surfaceLockCountInSecond;

	LONGLONG surfaceSizeInFrame;
	LONGLONG surfaceSizeInSecond;

	int textureLockCountInFrame;    // texture update times
	int textureLockCountInSecond;    

	int textureSizeInFrame;
	int textureSizeInSecond;

	int stateBlockCountInFrame;		// the state block times
	int stateBlockCountInSecond;

	int drawTimesInFrame;           // call the draw function times
	int drawTimesInSecond;

	int setTextureInFrame;          // set texture times
	int setTextureInSecond;

	float fpsInSecond;              // fps in second

	LONGLONG parameterDataSizeInFrame;    // all the parameters' size
	LONGLONG parameterDataSizeInSecond;

	LONGLONG parameterDataToRemoteInFrame;    // the parameter data to send to remote
	LONGLONG parameterDataToRemoteInSecond;

	unsigned int vertexShaderConstInFrame;  // vertex shader constant F size
	unsigned int vertexShaderConstInSecond; 

	unsigned int pixelShaderConstInFrame;   // pixel shader constant F size
	unsigned int pixelShaderConstInSecond;

	// store the shader command lines
	unsigned int vertexShaderCmdCountInFrame;
	unsigned int pixelShaderCmdCountInFrame;
	unsigned int vertexShaderCmdCountInSecond;
	unsigned int pixelShaderCmdCountInSecond;

	unsigned int vertexShaderSizeInFrame;
	unsigned int vertexShaderSizeInSecond;
	unsigned int pixelShaderSizeInFrame;
	unsigned int pixelShaderSizeInSecond;

private:
	// the logger
#ifndef FILE_POINTER
	ofstream frameLogStream;
	ofstream secondLogStream;
	ofstream errorLogStream;
#else

	FILE * frameLogFile;
	FILE * secondLogFile;
	FILE * errorLogFile;
#endif
#if 0
	Log * frameLogger;    // log to memory in frame
	Log * secondLogger; // log in second
	Log * errorLogger;
#endif

	int frameLogSize;
	int secondLogSize;
	int errorLogSize;

	char * frameLogBuffer, *curFrameLogBufferPoint;
	char * secondLogBuffer, * curSecondLogBufferPoint;
	char * errorLogBuffer, * curErrorLogBufferPoint;

	char * buffer1, * buffer2, * buffer3;
#ifdef LOG_TRACE
	char * traceLogBuffer, *curTraceLogBufferPoint, *buffer4;
	int traceLogSize;
	FILE * traceLogFile;
#endif

	LARGE_INTEGER freq;
	LARGE_INTEGER startTime, secondStart;
	LARGE_INTEGER endTime, secondEnd;
	LONGLONG  timeCount;
	bool secondStarted;

	bool limitFps;
	bool enableFrameLog;
	int maxFps;

	CpuWatch * frameCpuWatcher;
	CpuWatch * secondCpuWatcher;
	GpuWatch * gpuWatcher;

	HANDLE processHandle;
	int frameCountInSecond;
	bool frameStarted;

	void init(char * prefix);
	void init(char * path, char * prefix);
	void init(char * path, char * prefix, char * setName);

public:

	//constructor and destructor
	Recoder();
	Recoder(char *path, char *name);
	Recoder(char * name);
	Recoder(char * name, int fps);
	Recoder(char * path, char * name, int fps);
	Recoder(char * path, char * name, char * setName);
	~Recoder();

	// tool
	void logGuid(GUID riid);

	inline bool isEnableFameLog(){ return enableFrameLog; }
	inline void setEnableFrameLog(bool val){ enableFrameLog = val; }
	inline bool toLimitFps(){ return limitFps; }
	inline void setLimitFps(bool v){ limitFps = v; }
	inline int getMaxFps(){ return this->maxFps; }
	inline void setMaxFps(int mfps){ maxFps = mfps; }

	void flushFrameLog(bool forceToFlush = false);
	void flushSecondLog(bool forceToFlush = false);
	void flushErrorLog(bool forceToFlush = false);
	void FlushLog(bool forceToFlush = false);
	void logTrace(const char * format, ...);
#ifdef LOG_TRACE
	void flushTraceLog(bool forceToFlush = false);
#endif

	void onFrameStart();
	void onFrameEnd();

	void onSecondEnd();
	void onSecondStart();

	// function to log
	void logFrame(const char * foramt, ...);
	void logSecond(const char * format, ...);
	// functions to collect data

	void logError(const char * format, ...);

	// function
	void cmdCalled(int paraSize);        // the command is not necessary for recontruction.
	void cmdSendAndCalled(int paraSize);   // the commad is used to remote reconstruct
	void drawCalled(int paramSize, int primCount);

	void setVertexBufferCalled(int paramSize, int dataSize);   // send
	void setIndexBufferCalled(int paramSize, int indexSize);   // send

	void sceneOperationCalled();   // send
	void stateBlockCalled();       // send

	void setVertexShaderCalled(int argSize, int shaderSize);
	void vertexShaderConstantCalled(int argSize, int dataSize); // send
	void setPixelShaderCalled(int argSize, int shaderSize);
	void pixelShaderConstantCalled(int argSize, int dataSize); // send

	void textureUnLockRectCalled(int argSize, int texSize);  //not send
	void surfaceUnlockRectCalled(int argSize, int surfaceSize);   //not send
	void indexBufferLockCalled(int argSize, int ibSzie);   //send
	void vertexBufferLockCalled(int argSize, int vbSize); // send
	void presentCalled(int argSize);//send
};

extern Recoder * gRecoder;

#endif