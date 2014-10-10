#include "inforecoder.h"

// constructor and destructor
InfoRecorder::InfoRecorder(char * prefix){
	char recorderName[100];

	// init he frame recorder
	sprintf(recorderName, "%s.frame.log", prefix);
	frameRecorder = new LightWeightRecorder(recorderName);
	memset(recorderName, 0, 100);
	sprintf(recorderName, "%s.second.log", prefix);
	secondRecorder = new LightWeightRecorder(recorderName);
	memset(recorderName, 0, 100);
	sprintf(recorderName, "%s.error.log", prefix);
	errorRecorder = new LightWeightRecorder(recorderName);

	// create all the watcher
	frameCpuWatcher = new CpuWatch();
	secondCpuWatcher = new CpuWatch();
	gpuWatcher = new GpuWatch();

	processHandle = GetCurrentProcess();
	if (processHandle == NULL){
		MessageBox(NULL, "null process handle, get current process failed.", "Error", MB_OK);
	}


	timeCount = 0;
	QueryPerformanceFrequency(&freq);

	frameIndex = 0;
	secondIndex = 0;
	frameCountInSecond = 0;

	frameStarted = false;
	secondStarted = false;

	logFrame("FrameIndex FPS cpu gpu\n");
	logSecond("SecondIndex FPS cpu gpu\n");
}

InfoRecorder::~InfoRecorder(){

	// flush first
	flush();

	if (frameRecorder){
		delete frameRecorder;
		frameRecorder = NULL;
	}
	if (secondRecorder){
		delete secondRecorder;
		secondRecorder = NULL;
	}
	if (errorRecorder){
		delete errorRecorder;
		errorRecorder = NULL;
	}

	if (frameCpuWatcher){
		delete frameCpuWatcher;
		frameCpuWatcher = NULL;
	}
	if (secondCpuWatcher){
		delete secondCpuWatcher;
		secondCpuWatcher = NULL;
	}
	if (gpuWatcher){
		delete gpuWatcher;
		gpuWatcher = NULL;
	}
}


// functions
void InfoRecorder::flush(){
	this->frameRecorder->flush(true);
	this->secondRecorder->flush(true);
	this->errorRecorder->flush(true);
}

// get the cpu usage and gpu usage and the fps
bool InfoRecorder::onFrameEnd(){
	// compute the fps
	float curFps = 0.0f;
	double cpuUsage = 0.0f;
	double gpuUsage = 0.0f;
	// get the frame time
	QueryPerformanceCounter(&frameEnd);

	if (frameStarted){
#if 1
		cpuUsage = frameCpuWatcher->GetProcessCpuUtilization(processHandle);

		gpuUsage = gpuWatcher->GetGpuUsage();

		curFps =  this->freq.QuadPart / ((frameEnd.QuadPart - frameStart.QuadPart));
#endif

		frameCountInSecond++;

		timeCount += (frameEnd.QuadPart - frameStart.QuadPart);
		if (timeCount >= this->freq.QuadPart){
			onSecondEnd();
			timeCount = 0;
		}
#if 1
		// do the log for frame.
		// the log format should be: [index] [fps] [cpuUsage] [gpuUsage]
		frameRecorder->log("%d %f %f %f\n", frameIndex, curFps, cpuUsage, gpuUsage);
#endif
	}
	else{
		frameStarted = true;
	}

	frameIndex++;
	QueryPerformanceCounter(&frameStart);
	return true;
}
// get the cpu and gpu usage and the fps
bool InfoRecorder::onSecondEnd(){
	QueryPerformanceCounter(&secondEnd);

	if (secondStarted){
		// log the second counter
		float cpuUsage = 0.0f;
		float gpuUsage = 0.0f;
		float fpsInSecond = frameCountInSecond * this->freq.QuadPart / (secondEnd.QuadPart - secondStart.QuadPart);

		frameCountInSecond = 0;

		cpuUsage = secondCpuWatcher->GetProcessCpuUtilization(processHandle);
		gpuUsage = gpuWatcher->GetGpuUsage();

		secondRecorder->log("%d %f %f %f\n", secondIndex, fpsInSecond, cpuUsage, gpuUsage);
	}
	else{
		secondStarted = true;
	}
	secondIndex++;
	QueryPerformanceCounter(&secondStart);
	return true;
}

// log the error
void InfoRecorder::logError(char * format, ...){
	va_list ap;
	va_start(ap, format);
	errorRecorder->log(format, ap);
	va_end(ap);
}

void InfoRecorder::logFrame(char * format, ...){
	va_list ap;
	va_start(ap, format);
	frameRecorder->log(format, ap);
	va_end(ap);
}
void InfoRecorder::logSecond(char * format, ...){
	va_list ap;
	va_start(ap, format);
	secondRecorder->log(format, ap);
	va_end(ap);
}