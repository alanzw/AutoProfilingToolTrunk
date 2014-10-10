#ifndef __SCHEDULEWINDOW_H__
#define __SCHEDULEWINDOW_H__
// this is for the schedule windows, compute all the charactor of a game and determine the window size

//
#include <iostream>

#include <fstream>
#include <sstream>
#include <ostream>

#include <stdio.h>

#include <vector>
#include <string>
#include "..\Utility\log.h"
#include "common.h"

using namespace std;

template <class Type> class ScheduleWindow{
	ofstream ofs;   // the file out stream
	ifstream ifs;   // the file in stream

	FILE * inputSet;
	FILE * input;

	vector<string> files;   // store the filenames read from inputset.

	Log * logger;
	char outputFileName[128];
	char inputFileName[128];
	char * inputSetFile;

	char curFileInput[128];
	FILE * curFile;

	UNIT unit;
	unsigned int lines;
	Type * cpuArray, *gpuArray;
	short * fpsArray;

	bool limitFps;
	int maxFps;

	//private function
	Type average(int step){

	}
	unsigned int getFileLines(char * fileName){
		unsigned int ret = 0;
		char line[1024];
#if 0
		while (!feof(input)){
			if (fgets(line, 1024, input) != NULL){
				ret++;
			}
		}

		fseek(input, 0, 0);   // reset the file
#else
		FILE * t = fopen(fileName, "r");
		while (!feof(t)){
			if (fgets(line, 1024, t) != NULL){
				ret++;
			}
		}
		fclose(t);
#endif
		return ret;
	}

	double getVarianceSum(int step, VARIANCE_TYPE  varType){
		double ret = 0.0f;

		int loopCount = lines / step;
		int remain = lines & step;
		Type ave = 0;

		Type * arr = NULL;
		double var = 0.0f;

		if (varType == CPU_VAR){
			arr = this->cpuArray;
		}
		else if (varType == GPU_VAR){
			arr = this->gpuArray;
		}
		else{
			// error
		}

		// for all steps, compute the average and variance
		for (int i = 0; i < loopCount; i++){
			ave = 0;
			for (int j = i * step; j < (i + 1) * step; j++){
				ave += arr[j];
			}
			ave = ave * 1.0 / step;
			for (int j = i * step; j < (i + 1) * step; j++){
				var += (arr[j] - ave) * (arr[j] - ave);
			}
			ave = 0;
		}
		// for remianing, get the variance
		for (int j = step * loopCount; j < lines; j++){
			ave += arr[j];
		}
		ave = ave * 1.0 / remain;

		for (int j = step * loopCount; j < lines; j++){
			var += (arr[j] - ave) *(arr[j] - ave);
			//ave += arr[j];
		}


		return var;
	}


	bool parseInputSet(char *filename) // read the input set file to get all the input files
	{
		return true;
	}

public:
	void dealArgv(int argc, char ** argv, int startIndex, int stopIndex);

	ScheduleWindow(char * fileName, UNIT unitType)   // the filename is the inpuset
	{
		strcpy(inputFileName, fileName);
		sprintf(outputFileName, "%s.out.txt", fileName);
		this->unit = unitType;

		//ofs.open(outputFileName);

		logger = new Log(outputFileName);

		cpuArray = NULL;
		gpuArray = NULL;

#if 0
		if (!ofs){
			cerr << "[error]: unable to open output file:" << ofs << endl;
		}
#endif
	}


	ScheduleWindow(char * inputFileName, int type, UNIT unitType){
		this->inputSetFile = _strdup(inputFileName);
		this->unit = unitType;
		cpuArray = NULL;
		gpuArray = NULL;
	}

	~ScheduleWindow(){

	}

	inline void setLimitFps(bool b){ this->limitFps = b; }
	inline void setMaxFps(int mfps){ setLimitFps(true); this->maxFps = mfps; }

	Type getScheduleWindow(char * inputFileName){
		Type ret = 0;
		char line[1024];
		Type tcpu, tgpu;
		short tfps = 0;
		unsigned int index = 0;

		Type * varArray = NULL;
		Type * gpuVarArray = NULL;

		short * intervalArray = NULL;
		short varCount = 0;

		if (unit == UNIT::UNIT_FPS){

			varCount = (FPS_MAX_STEP - FPS_INTERVAL_BASE) / FPS_INCREASE_SPEED;
			varCount += 5;
			varArray = (Type *)malloc(sizeof(Type)*varCount);
			gpuVarArray = (Type *)malloc(sizeof(Type)* varCount);

			intervalArray = (short *)malloc(sizeof(short)* varCount);
			if (!varArray || !intervalArray || !gpuVarArray){
				// error
				return -1;
			}

		}
		else if (unit == UNIT_SECONDS){
			varCount = (SECOND_MAX_STEP - SECOND_INTERVAL_BASE) / SECOND_INCREASE_SPEED;
			varCount += 5;
			varArray = (Type *)malloc(sizeof(Type)*varCount);
			gpuVarArray = (Type *)malloc(sizeof(Type)* varCount);


			intervalArray = (short *)malloc(sizeof(short)* varCount);
			if (!varArray || !intervalArray ||!gpuVarArray){
				// error
				return -1;
			}
		}
		else{
			// error
		}

		lines = this->getFileLines(inputFileName);

		cpuArray = (Type *)malloc(sizeof(Type)* lines + 100);
		gpuArray = (Type *)malloc(sizeof(Type)* lines + 100);

		fpsArray = (short *)malloc(sizeof(short)* lines + 100);

		if (cpuArray == NULL || gpuArray == NULL){
			// eror
			printf("[error]: alloc cpu arry or gpu array failed.\n");
		}

		FILE * theInput = fopen(inputFileName, "r");
		if (theInput == NULL){
			printf("[error]: open the input file '%s' failed.\n", inputFileName);
		}
		while (!feof(theInput)){
			if (fgets(line, 1024, theInput) != NULL){
				sscanf(line, "%f\t%f\%d", &tcpu, &tgpu, &tfps);

				cpuArray[index] = tcpu;
				gpuArray[index] = tgpu;
				fpsArray[index] = tfps;

				index++;   // increase the lines
			}
		}


		//
		//varCount = 0;   // set to 0?
		int varIndex = 0;

		// finish the input, then do the compute
		if (unit == UNIT::UNIT_FPS){

			for (int i = FPS_INTERVAL_BASE; i < FPS_MAX_STEP; i += FPS_INCREASE_SPEED){
				//compute the variance sum for this step
				intervalArray[varIndex] = i;
				varArray[varIndex] = getVarianceSum(i, CPU_VAR);
				gpuVarArray[varIndex++] = getVarianceSum(i, GPU_VAR);
			}
		}
		else if (unit == UNIT::UNIT_SECONDS){
			for (int i = SECOND_INTERVAL_BASE; i < SECOND_MAX_STEP; i += SECOND_INCREASE_SPEED){
				intervalArray[varIndex] = i;
				varArray[varIndex] = getVarianceSum(i, CPU_VAR);
				gpuVarArray[varIndex++] = getVarianceSum(i, GPU_VAR);
			}
		}
		else{
			// error
		}

		short cpuBestIndex = 0;
		short gpuBestIndex = 0;
		Type cpuBest = cpuArray[cpuBestIndex];
		Type gpuBest = gpuArray[gpuBestIndex];

		// get the best interval
		for (int i = 0; i < varIndex; i++){
			if (cpuBest > varArray[i]){
				cpuBest = varArray[i];
				cpuBestIndex = i;
			}
			if (gpuBest > gpuVarArray[i]){
				gpuBest = gpuVarArray[i];
				gpuBestIndex = i;
			}
		}
		// write to result
#if 0
		if (!curFile){
			curFile = fopen(outputFileName, "a");
		}
#endif
		//
		if (unit == UNIT::UNIT_FPS){
			logger->log("[%s]: UNIT_FPS best schedule window:\n", curFileInput);
			logger->log("[CPU window]:\t%d, variance sum:%f\n", intervalArray[cpuBestIndex], varArray[cpuBestIndex]);
			logger->log("[GPU window]:\t%d, variance sum:%f\n", intervalArray[gpuBestIndex], gpuVarArray[gpuBestIndex]);
		}
		else if (unit == UNIT::UNIT_SECONDS){
			logger->log("[%s]: UINT_SECONDS best schedule window:\n", curFileInput);
			logger->log("[CPU window]:\t%d, variance sum:%f\n", intervalArray[cpuBestIndex], varArray[cpuBestIndex]);
			logger->log("[GPU window]:\t%d, variance sum:%f\n", intervalArray[gpuBestIndex], gpuVarArray[gpuBestIndex]);
		}

		fclose(theInput);
		theInput = NULL;
		return 0;
	}
	bool processInputSet(char * filename){
		if (parseInputSet(filename) != false){
			return false;
		}

		// 
		vector<string>::const_iterator it = files.begin();

		// if the file is OK, read and process the input
		while (it != files.end()){
			Type result = this->getScheduleWindow((char *)it->c_str());
		}
	}

};


#if 0
// this is for the schedule window

// constructor and destructor
template<class Type> ScheduleWindow<Type>::ScheduleWindow<Type>(char * filename, UNIT unitType){
	strcpy(inputFileName, filename);
	sprintf(outputFileName, "%s.out.txt", filename);
	this->unit = unitType;

	//ofs.open(outputFileName);

	logger = new Log(outputFileName);

	cpuArray = NULL;
	gpuArray = NULL;

#if 0
	if (!ofs){
		cerr << "[error]: unable to open output file:" << ofs << endl;
	}
#endif
}
template<class Type> ScheduleWindow<Type>::ScheduleWindow<Type>(char * inputSet, int type, UNIT unitType){
	this->inputSetFile = _strdup(inputSet);
	this->unit = unitType;
	cpuArray = NULL;
	gpuArray = NULL;
}

template<class Type> ScheduleWindow<Type>::~ScheduleWindow<Type>(){

}

template<class Type> unsigned int ScheduleWindow<Type>::getFileLines(char * fileName){
	unsigned int ret = 0;
	char line[1024];
#if 0
	while (!feof(input)){
		if (fgets(line, 1024, input) != NULL){
			ret++;
		}
	}

	fseek(input, 0, 0);   // reset the file
#else
	FILE * t = fopen(fileName, "r");
	while (!feof(t)){
		if (fgets(line, 1024, t) != NULL){
			ret++;
		}
	}
	fclose(t);
#endif
	return ret;
}


// use the [input] pointer to compute the schedule window
template<class Type> Type ScheduleWindow<Type>::getScheduleWindow(char * inputFileName){
	Type ret = 0;
	char line[1024];
	Type tcpu, tgpu;
	short tfps = 0;
	unsigned int index = 0;

	double * varArray = NULL;
	short * intervalArrary = NULL;
	short varCount = 0;

	if (unit == UNIT::UNIT_FPS){

		varCount = (FPS_MAX_STEP - FPS_INTERVAL_BASE) / FPS_INCREASE_SPEED;
		varCount += 5;
		varArray = (double *)malloc(sizeof(double)*varCount);
		intervalArrary = (short *)malloc(sizeof(short)* varCount);
		if (!varArray || !intervalArray){
			// error
			return -1;
		}

	}
	else if (unit == UNIT::UINT_SECONDS){
		varCount = (SECOND_MAX_STEP - SECOND_INTERVAL_BASE) / SECOND_INCREASE_SPEED;
		varCount += 5;
		varArray = (double *)malloc(sizeof(double)*varCount);
		intervalArrary = (short *)malloc(sizeof(short)* varCount);
		if (!varArray || !intervalArrary){
			// error
			return -1;
		}
	}
	else{
		// error
	}

	lines = this->getFileLines(inputFileName);

	cpuArray = (Type *)malloc(sizeof(Type)* lines + 100);
	gpuArray = (Type *)malloc(sizeof(Type)* lines + 100);

	fpsArray = (short *)malloc(sizeof(short)* lines + 100);

	if (cpuArray == NULL || gpuArry == NULL){
		// eror
		printf("[error]: alloc cpu arry or gpu array failed.\n");
	}

	FILE * theInput = fopen(inputFileName, "r");
	if (theInput == NULL){
		printf("[error]: open the input file '%s' failed.\n", inputFileName);
	}
	while (!feof(theInput)){
		if (fgets(line, 1024, theInput) != NULL){
			sscanf(line, "%f\t%f\%d", &tcpu, &tgpu, &tfps);

			cpuArray[index] = tcpu;
			gpuArray[index] = tgpu;
			fpsArray[index] = tfps;

			index++;   // increase the lines
		}
	}

	// finish the input, then do the compute
	if (unit == UNIT::UNIT_FPS){

		for (int i = FPS_INTERVAL_BASE; i < FPS_MAX_STEP; i += FPS_INCREASE_SPEED){
			//compute the variance sum for this step
			intervalArrary[varCount] = i;
			varArray[varCount++] = getVarianceSum(i);
		}
	}
	else if (unit == UNIT::UINT_SECONDS){
		for (int i = SECOND_INTERVAL_BASE; i < SECOND_MAX_STEP; i += SECOND_INCREASE_SPEED){
			intervalArrary[varCount] = i;
			varArray[varCount++] = getVarianceSum(i);
		}
	}
	else{
		// error
	}

	short cpuBestIndex = 0;
	short gpuBestIndex = 0;
	Type cpuBest = cpuArray[cpuBestIndex];
	Type gpuBest = gpuArray[gpuBestIndex];

	// get the best interval
	for (int i = 0; i < varCount; i++){
		if (cpuBest > cpuArray[i]){
			cpuBest = cpuArray[i];
			cpuBestIndex = i;
		}
		if (gpuBest > gpuArray[i]){
			gpuBest = gpuArray[i];
			gpuBestIndex = i;
		}
	}
	// write to result
#if 0
	if (!curFile){
		curFile = fopen(outputFileName, "a");
	}
#endif
	//
	if (unit == UNIT::UNIT_FPS){
		logger->log("[%s]: UNIT_FPS best schedule window:\n", curFileInput);
		logger->log("[CPU window]:\t%d, variance sum:%f\n", intervalArrary[cpuBestIndex], cpuArray[cpuBestIndex]);
		logger->log("[GPU window]:\t%d, variance sum:%f\n", intervalArrary[gpuBestIndex], gpuArray[gpuBestIndex]);
	}
	else if (unit == UNIT::UINT_SECONDS){
		logger->log("[%s]: UINT_SECONDS best schedule window:\n", curFileInput);
		logger->log("[CPU window]:\t%d, variance sum:%f\n", intervalArrary[cpuBestIndex], cpuArray[cpuBestIndex]);
		logger->log("[GPU window]:\t%d, variance sum:%f\n", intervalArrary[gpuBestIndex], gpuArray[gpuBestIndex]);
	}

	fclose(theInput);
	theInput = NULL;
	return 0;
}

template<class Type> Type ScheduleWindow<Type>::average(int step){

}

// get the variance sum with step
template<class Type> double ScheduleWindow<Type>::getVarianceSum(int step, VARIANCE_TYPE varType){
	double ret = 0.0f;

	int loopCount = lines / step;
	int remain = lines & step;
	Type ave = 0;

	Type * arr = NULL;
	double var = 0.0f;

	if (varType == CPU_VAR){
		arr = this->cpuArray;
	}
	else if (varType == GPU_VAR){
		arr = this->gpuArray;
	}
	else{
		// error
	}

	// for all steps, compute the average and variance
	for (int i = 0; i < loopCount; i++){
		ave = 0;
		for (int j = i * step; j < (i + 1) * step; j++){
			ave += arr[j];
		}
		ave = ave * 1.0 / step;
		for (int j = i * step; j < (i + 1) * step; j++){
			var += (arr[j] - ave) * (arr[j] - ave);
		}
		ave = 0;
	}
	// for remianing, get the variance
	for (int j = step * loopCount; j < lines; j++){
		ave += arr[j];
	}
	ave = ave * 1.0 / remain;

	for (int j = step * loopCount; j < lines; j++){
		var += (arr[j] - ave) *(arr[j] - ave);
		//ave += arr[j];
	}

}


// compute all files
template<class Type> bool ScheduleWindow<Type>::processInputSet(char * filename){
	if (parseInputSet(filename) != false){
		return false;
	}

	// 
	vector<string>::const_iterator it = files.begin();

	// if the file is OK, read and process the input
	while (it != files.end()){
		Type result = this->getScheduleWindow(it->c_str());
	}
}


// the file name is the input set, contains all the input file names
template<class Type> bool ScheduleWindow<Type>::parseInputSet(char *filename){

}
#endif


#endif