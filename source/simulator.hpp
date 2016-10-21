#pragma once

//Ping Pong by Andrew Vieira

#include <SDL_ttf.h>

#include "display.hpp"
#include "handle.hpp"
extern Display GameDisplay;
extern Handle GameHandle;
extern TTF_Font* GameFont;

#include "timer.hpp"
#include "game_object.hpp"

class Simulator
{
public:
	void StartUp();
	void ShutDown();

	void MainLoop();

	void Input();
	void Logic();
	void Output();
private:
	bool running = true;

	Timer StepTimer;

	Paddle PlayerPaddle;
	AI GameAI;
	Paddle AIPaddle;
	Ball GameBall;
	Score PlayerScore;
	Score AIScore;
};