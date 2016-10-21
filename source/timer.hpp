#pragma once

//Ping Pong by Andrew Vieira

#include <SDL.h>

class Timer
{
public:
	Timer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();

	Uint32 GetTicks();

	bool IsStarted();
	bool IsPaused();

private:
	Uint32 start_ticks;
	Uint32 paused_ticks;

	bool paused;
	bool started;
};