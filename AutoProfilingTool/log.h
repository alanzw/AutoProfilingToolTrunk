#ifndef __LOG_H__
#define __LOG_H__
// this for the log system for the project
#include <fstream>
#include <sstream>
#include <ostream>
#include <iostream>
#include <time.h>

using namespace std;


class Log {
	time_t tv;
public:
	void init(const char* fname);
	void log(const char* text, ...);
	void slog(const char* text, ...);
	void logscreen(const char * text, ...);
	void close();

	Log(const char * filename);
	~Log();

private:
	char fname_[100];
	ofstream fs_;
};

#endif