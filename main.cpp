#include "main.hpp"

//Ping Pong by Andrew Vieira

int main(int argc, char* argv[])
{
	//Start Up
	SDL_StartUp();
	Window_StartUp();
	Handle_StartUp();

	GameFont = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 30);

	//Game Loop
	Window_Center();

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
		Handle_Poll();

		float time_step = StepTimer.GetTicks() / 1000.f;

		if (MouseStates[BIND_WINDOW_QUIT] || KeyStates[BIND_QUIT] == true)
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

		if (KeyStates[BIND_UP] == true)
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

		if (KeyStates[BIND_DOWN] == true)
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

		Window_Fill();

		PlayerScore.Render();
		AIScore.Render();
		PlayerPaddle.Render();
		AIPaddle.Render();
		GameBall.Render();

		Window_Render();
	}

	AIScore.Destroy();
	PlayerScore.Destroy();
	GameBall.Destroy();
	AIPaddle.Destroy();
	PlayerPaddle.Destroy();

	//ShutDown
	TTF_CloseFont(GameFont);
	GameFont = nullptr;
	Handle_ShutDown();
	Window_ShutDown();
	SDL_ShutDown();

	return 0;
}

bool SDL_StartUp()
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
void SDL_ShutDown()
{
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Window_StartUp()
{
	bool success = true;

	GameWindow = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 450, SDL_WINDOW_SHOWN /*|| SDL_WINDOW_FULLSCREEN*/);

	if (GameWindow == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (GameRenderer == nullptr)
		{
			std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
	}

	return success;
}
void Window_ShutDown()
{
	SDL_DestroyRenderer(GameRenderer);
	SDL_DestroyWindow(GameWindow);
	GameRenderer = nullptr;
	GameWindow = nullptr;
}
void Window_Center()
{
	SDL_SetWindowPosition(GameWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
void Window_Fill(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	SDL_SetRenderDrawColor(GameRenderer, red, green, blue, alpha);
	SDL_RenderClear(GameRenderer);
}
void Window_Render()
{
	SDL_RenderPresent(GameRenderer);
}

bool Handle_StartUp()
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
void Handle_ShutDown()
{

}
void Handle_Poll()
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
			SDL_GetMouseState(&MouseX, &MouseY);
		else if (GameEvent.type == SDL_MOUSEBUTTONDOWN)
			MouseStates[BIND_PRESSED] = true;
		else if (GameEvent.type == SDL_MOUSEBUTTONUP)
			MouseStates[BIND_PRESSED] = false;
	}
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

		NewTexture = SDL_CreateTextureFromSurface(GameRenderer, LoadedSurface);
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
		MyTexture = SDL_CreateTextureFromSurface(GameRenderer, TextSurface);
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

	SDL_RenderCopyEx(GameRenderer, MyTexture, clip, &RenderQuad, angle, center, flip);
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