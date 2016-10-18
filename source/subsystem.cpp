#include "subsystem.hpp"

//Ping Pong by Andrew Vieira

bool SubSystem::StartUp()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
			success = false;
		}

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags)&imgFlags))
		{
			std::cout << "SDL_Image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
			success = false;
		}

		if (TTF_Init() == -1)
		{
			std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError << std::endl;
			success = false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
			success = false;
		}
	}

	return success;
}

void SubSystem::ShutDown()
{
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}