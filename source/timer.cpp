#include "timer.hpp"

//Ping Pong by Andrew Vieira

Timer::Timer()
{
	start_ticks = 0;
	paused_ticks = 0;

	paused = false;
	started = false;
}
void Timer::Start()
{
	started = true;

	paused = false;

	start_ticks = SDL_GetTicks();
	paused_ticks = 0;
}
void Timer::Stop()
{
	started = false;

	paused = false;

	start_ticks = 0;
	paused_ticks = 0;
}
void Timer::Pause()
{
	if (started && !paused)
	{
		paused = true;

		paused_ticks = SDL_GetTicks() - start_ticks;
		start_ticks = 0;
	}
}
void Timer::Unpause()
{
	if (started && paused)
	{
		paused = false;

		start_ticks = SDL_GetTicks() - paused_ticks;

		paused_ticks = 0;
	}
}
Uint32 Timer::GetTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = paused_ticks;
		}
		else
		{
			time = SDL_GetTicks() - start_ticks;
		}
	}

	return time;
}
bool Timer::IsStarted()
{
	return started;
}
bool Timer::IsPaused()
{
	return paused && started;
}