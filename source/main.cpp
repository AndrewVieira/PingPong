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