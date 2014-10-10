#include "log.h"
#include <Windows.h>
#include <stdlib.h>

#define MAX_CHAR 512

Log::Log(const char *filename){
	init(filename);

}
Log::~Log(){
	close();

}


// this is for the log component
void Log::init(const char * filename){
	strcpy(fname_, filename);
	fs_.open(fname_, ios::out);

	log("Log::init(), filename = %s.\n", fname_);

}

void Log::close(){
	log("Log::close() called.\n");
	fs_.close();
}

void Log::log(const char * text, ...){
	//if (!is_init_) init("fuck.log");
	char buffer[MAX_CHAR];
	char timestr[30];

	tv = time(0);
	tm* ltime = localtime(&tv);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);

	va_list ap;
	va_start(ap, text);
	vsprintf(buffer, text, ap);
	va_end(ap);
	DWORD thread = GetCurrentThreadId();
	fs_ << timestr << ": " << " [tid: " << thread << "]" << buffer;
	fs_.flush();
}

void Log::slog(const char* text, ...) {
	char buffer[MAX_CHAR];

	char timestr[30];

	tv = time(0);
	tm* ltime = localtime(&tv);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);

	va_list ap;
	va_start(ap, text);
	vsprintf(buffer, text, ap);
	va_end(ap);
	DWORD thread = GetCurrentThreadId();
	fs_ << timestr << ": " << " [tid: " << thread << "]" << buffer;
	fs_.flush();
}

void Log::logscreen(const char * text, ...){
	char buffer[MAX_CHAR];
	char timestr[30];

	tv = time(0);
	tm  * ltime = localtime(&tv);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);

	va_list ap;
	va_start(ap, text);
	vsprintf(buffer, text, ap);
	va_end(ap);

	cerr << timestr << ": " << buffer;
	cerr.flush();
}