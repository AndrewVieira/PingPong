#pragma once

//Ping Pong by Andrew Vieira

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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

SDL_Window* GameWindow = nullptr;
SDL_Renderer* GameRenderer = nullptr;

SDL_Event GameEvent;
bool KeyStates[BIND_KEY_TOTAL];
SDL_Keycode KeyBindings[BIND_KEY_TOTAL];
bool MouseStates[BIND_MOUSE_TOTAL];
int MouseX = 0;
int MouseY = 0;

TTF_Font* GameFont;

int main(int argc, char* argv[]);

bool SDL_StartUp();
void SDL_ShutDown();

bool Window_StartUp();
void Window_ShutDown();
void Window_Center();
void Window_Fill(Uint8 red = 0x00, Uint8 green = 0x00, Uint8 blue = 0x00, Uint8 alpha = 0xFF);
void Window_Render();

bool Handle_StartUp();
void Handle_ShutDown();
void Handle_Poll();

struct Texture
{
	bool Create();
	void Destroy();

	bool LoadFromFile(std::string path);
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor);

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);

	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Texture* MyTexture = nullptr;

	int width = 0;
	int height = 0;
};

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

struct GameObject 
{
	virtual void Create(int x = 0, int y = 0)=0;
	virtual void Destroy()=0;
	virtual void Logic() = 0;
	virtual void Render()=0;
	SDL_Rect MyRect;
	Texture MyTexture;
};

struct Paddle : GameObject 
{
	void Create(int x = 0, int y = 0);
	void Destroy();
	void Logic();
	void Render();

	int velocity = 0;
};

struct Score : GameObject
{
	void Create(int x = 0, int y = 0);
	void Destroy();
	void Logic();
	void Render();

	TTF_Font* MyFont;
	int score = 0;
};

struct Ball : GameObject 
{
	void Create(int x = 0, int y = 0);
	void Destroy();
	void Logic();
	void Logic(float ts, Score* p1, Score* p2);
	void Render();
	void Reset();
	void Collision(SDL_Rect* PaddleRect);

	int velocity_x = 250;
	int velocity_y = 250;
};

struct AI
{
	enum choice
	{
		GO_UP,
		GO_DOWN,
		STAY
	};

	int Think(int ball_center_y, int paddle_center_y);
};