#ifndef __COMMON_H__
#define __COMMON_H__
// for common use in auto profiling tool

// the input data is in sencods or fps level
enum UNIT{
	UNIT_FPS,
	UNIT_SECONDS
};


// the inteval for each unit
enum IntervalBase{
	SECOND_INTERVAL_BASE = 10,
	FPS_INTERVAL_BASE = 300
	
};

// the increasing speed
enum IntervalIncreaseStep{
	SECOND_INCREASE_SPEED = 5,
	FPS_INCREASE_SPEED = 150
};

// the max step
enum MaxInterval{
	SECOND_MAX_STEP = 100,
	FPS_MAX_STEP = 3000
};

enum VARIANCE_TYPE{
	CPU_VAR,
	GPU_VAR
};


#pragma comment(lib, "detours\\detours.lib")

#endif