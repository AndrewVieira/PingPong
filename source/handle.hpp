#pragma once

#include <SDL.h>

enum KEY_BINDINGS
{
	BIND_QUIT,
	BIND_UP,
	BIND_DOWN,
	BIND_SELECT,
	BIND_KEY_TOTAL
};
enum MOUSE_BINDINGS
{
	BIND_WINDOW_QUIT,
	BIND_PRESSED,
	BIND_MOUSE_TOTAL
};

class Handle
{
public:
	bool StartUp();
	void ShutDown();
	void Poll();

	bool GetKeyState(KEY_BINDINGS binding);
	bool GetMouseState(MOUSE_BINDINGS binding);
	int GetMouseX();
	int GetMouseY();
private:
	SDL_Event GameEvent;
	bool KeyStates[BIND_KEY_TOTAL];
	SDL_Keycode KeyBindings[BIND_KEY_TOTAL];
	bool MouseStates[BIND_MOUSE_TOTAL];
	int mouse_x = 0;
	int mouse_y = 0;
};