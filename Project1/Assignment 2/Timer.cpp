#include "Timer.h"

Timer::Timer()
{
	m_countsPerSecond = 0.0;
	m_counterStart = 0;

	m_frameCount = 0;
	m_fps = 0;

	m_frameTimeOld = 0;
	m_frameTime;
}

Timer::~Timer()
{

}

void Timer::StartTime()
{
	LARGE_INTEGER _frequencyCount;
	QueryPerformanceFrequency(&_frequencyCount);

	//Stores the frequency of counts per second
	m_countsPerSecond = double(_frequencyCount.QuadPart);

	QueryPerformanceCounter(&_frequencyCount);
	//stores the current time in counts
	m_counterStart = _frequencyCount.QuadPart;
}

double Timer::GetTime()
{
	LARGE_INTEGER _currentTime;
	QueryPerformanceCounter(&_currentTime);
	//me returns the time in seconds that StartTime (with m_counterstart) was called last
	return double(_currentTime.QuadPart - m_counterStart) / m_countsPerSecond;
}

double Timer::GetFrameTime()
{
	LARGE_INTEGER _currentTime;
	__int64 _tickCount;
	QueryPerformanceCounter(&_currentTime);

	_tickCount = _currentTime.QuadPart - m_frameTimeOld;
	m_frameTimeOld = _currentTime.QuadPart;

	if (_tickCount < 0.0f)
		_tickCount = 0.0f;
	//returns the last time that GetFrameTime() was called to realize how many seconds each fram takes to process
	return float(_tickCount) / m_countsPerSecond;
}

double Timer::TimeCheck()
{
	//checks the fps of the system, and returns the current frametime
	m_frameCount++;
	if (GetTime() > 1.0f)
	{
		m_fps = m_frameCount;
		m_frameCount = 0;
		StartTime();
	}

	return m_frameTime = GetFrameTime();
}