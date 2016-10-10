#ifndef  TIMER_H
#define TIMER_H
#include <iostream>
#include <windows.h>
using namespace std;

class Timer
{
	//Functions
private:
	double GetTime();			//Returns the time in seconds since StartTime() was last called
	double GetFrameTime();		//Returns the time in seconds each frame takes to process
protected:
public:
	Timer();
	~Timer();
	void StartTime();			//Starts the timer and saves the time in counts in a variable
	double TimeCheck();			//Is the main time "check" that is made to calculate the fps and return the frametime

	//Variables
private:
	double m_countsPerSecond;
	__int64 m_counterStart;

	int m_frameCount;
	int m_fps;

	__int64 m_frameTimeOld;
	double m_frameTime;
protected:
public:
};
#endif // TIMER_H