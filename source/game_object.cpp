#include "game_object.hpp"

//Ping Pong by Andrew Vieira

void Paddle::Create(int x, int y)
{
	MyRect.x = x;
	MyRect.y = y;
	MyRect.h = 90;
	MyRect.w = 30;

	MyTexture.Create();
	MyTexture.LoadFromFile("assets/images/paddle.png");
}
void Paddle::Destroy()
{
	MyTexture.Destroy();
}
void Paddle::Render()
{
	MyTexture.Render(MyRect.x, MyRect.y);
}
void Paddle::Logic()
{
	if (velocity > 400)
	{
		velocity = 400;
	}
	else if (velocity < -400)
	{
		velocity = -400;
	}

	MyRect.y += velocity;

	if (MyRect.y < 0)
	{
		MyRect.y = 0;
	}
	else if (MyRect.y > 450 - MyRect.h)
	{
		MyRect.y = 450 - MyRect.h;
	}
}

void Ball::Create(int x, int y)
{
	MyRect.x = x;
	MyRect.y = y;
	MyRect.w = 30;
	MyRect.h = 30;

	MyTexture.Create();
	MyTexture.LoadFromFile("assets/images/ball.png");
}
void Ball::Destroy()
{
	MyTexture.Destroy();
}
void Ball::Render()
{
	MyTexture.Render(MyRect.x, MyRect.y);
}
void Ball::Logic()
{}
void Ball::Logic(float ts, Score* p1, Score* p2)
{
	MyRect.x += int(velocity_x * ts);
	MyRect.y += int(velocity_y * ts);

	if (MyRect.y < 0)
	{
		velocity_y = -velocity_y;
		MyRect.y = 0;
	}
	else if (MyRect.y > 450 - MyRect.h)
	{
		velocity_y = -velocity_y;
		MyRect.y = 450 - MyRect.h;
	}

	if (MyRect.x < 0)
	{
		Reset();
		p2->score++;
	}
	else if (MyRect.x > 800 - MyRect.w)
	{
		Reset();
		p1->score++;
	}
}
void Ball::Collision(SDL_Rect* PaddleRect)
{
	if (MyRect.x > PaddleRect->x && MyRect.x < PaddleRect->x + PaddleRect->w)
		if (MyRect.y > PaddleRect->y && MyRect.y < PaddleRect->y + PaddleRect->h)
		{
			velocity_x = -velocity_x;
		}
}
void Ball::Reset()
{
	MyRect.x = 385;
	MyRect.y = 210;

	velocity_x = -velocity_x;
	velocity_y = -velocity_y;
}

void Score::Create(int x, int y)
{
	MyRect.x = x;
	MyRect.y = y;

	SDL_Color TextColor = { 0xFF, 0xFF, 0xFF };
	MyTexture.LoadFromRenderedText(std::to_string(score), TextColor);
}
void Score::Destroy()
{
	MyTexture.Destroy();
}
void Score::Logic()
{
	SDL_Color TextColor = { 0xFF, 0xFF, 0xFF };
	MyTexture.LoadFromRenderedText(std::to_string(score), TextColor);
}
void Score::Render()
{
	MyTexture.Render(MyRect.x, MyRect.y);
}

int AI::Think(int ball_y, int paddle_y)
{
	if (ball_y < paddle_y)
		return GO_UP;

	if (ball_y > paddle_y)
		return GO_DOWN;

	return STAY;
}