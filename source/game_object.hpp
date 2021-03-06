#pragma once
//Ping Pong by Andrew Vieira

#include <iostream>
#include <string>

#include "texture.hpp"

struct GameObject
{
	virtual void Create(int x = 0, int y = 0) = 0;
	virtual void Destroy() = 0;
	virtual void Logic() = 0;
	virtual void Render() = 0;
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