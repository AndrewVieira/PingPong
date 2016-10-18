#pragma once

//Ping Pong by Andrew Vieira

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class SubSystem
{
public:

	bool StartUp();
	void ShutDown();
};