#include "display.hpp"

//Ping Pong by Andrew Vieira

bool Display::StartUp()
{
	bool success = true;

	MyWindow = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 450, SDL_WINDOW_SHOWN /*|| SDL_WINDOW_FULLSCREEN*/);

	if (MyWindow == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (MyRenderer == nullptr)
		{
			std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
	}

	Center();

	return success;
}
void Display::ShutDown()
{
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	MyRenderer = nullptr;
	MyWindow = nullptr;
}
void Display::Center()
{
	SDL_SetWindowPosition(MyWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
void Display::Fill(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_SetRenderDrawColor(MyRenderer, red, green, blue, alpha);
	SDL_RenderClear(MyRenderer);
}
void Display::Render()
{
	SDL_RenderPresent(MyRenderer);
}
SDL_Window* Display::GetWindow()
{
	return MyWindow;
}
SDL_Renderer* Display::GetRenderer()
{
	return MyRenderer;
}