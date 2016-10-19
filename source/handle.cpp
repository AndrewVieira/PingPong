#include "handle.hpp"

bool Handle::StartUp()
{
	for (int i = 0; i < BIND_KEY_TOTAL; i++)
		KeyStates[i] = false;

	for (int i = 0; i < BIND_MOUSE_TOTAL; i++)
		MouseStates[i] = false;

	bool success = true;

	KeyBindings[BIND_QUIT] = SDLK_ESCAPE;
	KeyBindings[BIND_UP] = SDLK_UP;
	KeyBindings[BIND_DOWN] = SDLK_DOWN;
	KeyBindings[BIND_SELECT] = SDLK_SPACE;

	//MouseBindings[BIND_WINDOW_QUIT];
	//MouseBindings[BIND_PRESSED];

	return success;
}
void Handle::ShutDown()
{

}
void Handle::Poll()
{
	while (SDL_PollEvent(&GameEvent))
	{
		if (GameEvent.type == SDL_QUIT)
			MouseStates[BIND_WINDOW_QUIT] = true;

		else if (GameEvent.type == SDL_KEYDOWN)
		{
			for (int i = 0; i < BIND_KEY_TOTAL; i++)
			{
				if (GameEvent.key.keysym.sym == KeyBindings[i])
					KeyStates[i] = true;
			}
		}

		else if (GameEvent.type == SDL_KEYUP)
		{
			for (int i = 0; i < BIND_KEY_TOTAL; i++)
			{
				if (GameEvent.key.keysym.sym == KeyBindings[i])
					KeyStates[i] = false;
			}
		}

		else if (GameEvent.type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&mouse_x, &mouse_y);
		else if (GameEvent.type == SDL_MOUSEBUTTONDOWN)
			MouseStates[BIND_PRESSED] = true;
		else if (GameEvent.type == SDL_MOUSEBUTTONUP)
			MouseStates[BIND_PRESSED] = false;
	}
}
bool Handle::GetKeyState(KEY_BINDINGS binding)
{
	return KeyStates[binding];
}
bool Handle::GetMouseState(MOUSE_BINDINGS binding)
{
	return MouseStates[binding];
}
int Handle::GetMouseX()
{
	return mouse_x;
}
int Handle::GetMouseY()
{
	return mouse_y;
}