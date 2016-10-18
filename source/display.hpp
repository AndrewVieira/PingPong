#pragma once

//Ping Pong by Andrew Vieira

#include <iostream>
#include <SDL.h>

class Display
{
public:
	bool StartUp();
	void ShutDown();
	void Center();
	void Fill(Uint8 red = 0x00, Uint8 green = 0x00, Uint8 blue = 0x00, Uint8 alpha = 0xFF);
	void Render();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

private:
	SDL_Window* MyWindow = nullptr;
	SDL_Renderer* MyRenderer = nullptr;
};