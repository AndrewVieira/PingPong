#include "main.hpp"

//Ping Pong by Andrew Vieira

int main(int argc, char* argv[])
{
	//Start Up
	GameSubSystem.StartUp();
	GameDisplay.StartUp();
	GameHandle.StartUp();

	GameFont = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 30);

	//Game Loop
	Timer StepTimer;

	Paddle PlayerPaddle;
	PlayerPaddle.Create(10, 180);

	AI GameAI;

	Paddle AIPaddle;
	AIPaddle.Create(760, 180);

	Ball GameBall;
	GameBall.Create(385, 210);

	Score PlayerScore;
	PlayerScore.Create(10, 0);

	Score AIScore;
	AIScore.Create(760, 0);

	bool running = true;
	while (running)
	{
		GameHandle.Poll();

		float time_step = StepTimer.GetTicks() / 1000.f;

		if (GameHandle.GetMouseState(BIND_WINDOW_QUIT) || GameHandle.GetKeyState(BIND_QUIT) == true)
			running = false;

		int ai_choice = GameAI.Think(GameBall.MyRect.y+15, AIPaddle.MyRect.y+45);

		if (ai_choice == 0)
		{
			AIPaddle.velocity -= int(100 * time_step);
		}
		else
		{
			if (AIPaddle.velocity < 0)
			{
				AIPaddle.velocity = 0;
			}
		}

		if (ai_choice == 1)
		{
			AIPaddle.velocity += int(100 * time_step);
		}
		else
		{
			if (AIPaddle.velocity > 0)
			{
				AIPaddle.velocity = 0;
			}
		}

		if (GameHandle.GetKeyState(BIND_UP) == true)
		{
			PlayerPaddle.velocity -= int(100 * time_step);
		}
		else
		{
			if (PlayerPaddle.velocity < 0)
			{
				PlayerPaddle.velocity = 0;
			}
		}

		if (GameHandle.GetKeyState(BIND_DOWN) == true)
		{
			PlayerPaddle.velocity += int(100 * time_step);
		}
		else
		{
			if (PlayerPaddle.velocity > 0)
			{
				PlayerPaddle.velocity = 0;
			}
		}

		PlayerPaddle.Logic();
		AIPaddle.Logic();
		GameBall.Collision(&PlayerPaddle.MyRect);
		GameBall.Collision(&AIPaddle.MyRect);
		GameBall.Logic(time_step, &PlayerScore, &AIScore);
		PlayerScore.Logic();
		AIScore.Logic();

		StepTimer.Start();

		GameDisplay.Fill();

		PlayerScore.Render();
		AIScore.Render();
		PlayerPaddle.Render();
		AIPaddle.Render();
		GameBall.Render();

		GameDisplay.Render();
	}

	AIScore.Destroy();
	PlayerScore.Destroy();
	GameBall.Destroy();
	AIPaddle.Destroy();
	PlayerPaddle.Destroy();

	//ShutDown
	TTF_CloseFont(GameFont);
	GameFont = nullptr;
	GameHandle.ShutDown();
	GameDisplay.ShutDown();
	GameSubSystem.ShutDown();

	return 0;
}



bool Texture::Create() 
{
	return true; 
}
void Texture::Destroy()
{
	if (MyTexture != nullptr)
	{
		SDL_DestroyTexture(MyTexture);
		MyTexture = nullptr;
		width = 0;
		height = 0;
	}
}
bool Texture::LoadFromFile(std::string path)
{
	Destroy();

	SDL_Texture* NewTexture = nullptr;

	SDL_Surface* LoadedSurface = IMG_Load(path.c_str());
	if (LoadedSurface == nullptr)
	{
		std::cout << "Unable to load image "  << path.c_str() << "! SDL_image Error: "  << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(LoadedSurface, SDL_TRUE, SDL_MapRGB(LoadedSurface->format, 0x00, 0xFF, 0xFF));

		NewTexture = SDL_CreateTextureFromSurface(GameDisplay.GetRenderer(), LoadedSurface);
		if (NewTexture == nullptr)
		{
			std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError << std::endl;
		}
		else
		{
			width = LoadedSurface->w;
			height = LoadedSurface->h;
		}

		SDL_FreeSurface(LoadedSurface);
	}

	MyTexture = NewTexture;
	return MyTexture != nullptr;
}
bool Texture::LoadFromRenderedText(std::string texture_text, SDL_Color text_color)
{
	Destroy();

	SDL_Surface* TextSurface = TTF_RenderText_Solid(GameFont, texture_text.c_str(), text_color);
	if (TextSurface == nullptr)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		MyTexture = SDL_CreateTextureFromSurface(GameDisplay.GetRenderer(), TextSurface);
		if (MyTexture == nullptr)
		{
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			width = TextSurface->w;
			height = TextSurface->h;
		}

		SDL_FreeSurface(TextSurface);
	}

	return MyTexture != nullptr;
}
void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(MyTexture, red, green, blue);
}
void Texture::SetBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(MyTexture, blending);
}
void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(MyTexture, alpha);
}
void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect RenderQuad = { x, y, width, height };

	if (clip != nullptr)
	{
		RenderQuad.w = clip->w;
		RenderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(GameDisplay.GetRenderer(), MyTexture, clip, &RenderQuad, angle, center, flip);
}

Timer::Timer()
{
	start_ticks = 0;
	paused_ticks = 0;

	paused = false;
	started = false;
}
void Timer::Start()
{
	started = true;

	paused = false;

	start_ticks = SDL_GetTicks();
	paused_ticks = 0;
}
void Timer::Stop()
{
	started = false;

	paused = false;

	start_ticks = 0;
	paused_ticks = 0;
}
void Timer::Pause()
{
	if (started && !paused)
	{
		paused = true;

		paused_ticks = SDL_GetTicks() - start_ticks;
		start_ticks = 0;
	}
}
void Timer::Unpause()
{
	if (started && paused)
	{
		paused = false;

		start_ticks = SDL_GetTicks() - paused_ticks;

		paused_ticks = 0;
	}
}
Uint32 Timer::GetTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = paused_ticks;
		}
		else
		{
			time = SDL_GetTicks() - start_ticks;
		}
	}

	return time;
}
bool Timer::IsStarted()
{
	return started;
}
bool Timer::IsPaused()
{
	return paused && started;
}

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