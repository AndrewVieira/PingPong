#include "simulator.hpp"

//Ping Pong by Andrew Vieira

void Simulator::StartUp()
{
	PlayerPaddle.Create(10, 180);
	AIPaddle.Create(760, 180);
	GameBall.Create(385, 210);
	PlayerScore.Create(10, 0);
	AIScore.Create(760, 0);
}
void Simulator::ShutDown()
{
	AIScore.Destroy();
	PlayerScore.Destroy();
	GameBall.Destroy();
	AIPaddle.Destroy();
	PlayerPaddle.Destroy();
}
void Simulator::MainLoop()
{
	while (running)
	{
		Input();
		Logic();
		Output();
	}
}
void Simulator::Input() 
{
	GameHandle.Poll();
}
void Simulator::Logic() 
{
	float time_step = StepTimer.GetTicks() / 1000.f;

	if (GameHandle.GetMouseState(BIND_WINDOW_QUIT) || GameHandle.GetKeyState(BIND_QUIT) == true)
		running = false;

	int ai_choice = GameAI.Think(GameBall.MyRect.y + 15, AIPaddle.MyRect.y + 45);

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
}
void Simulator::Output() 
{
	GameDisplay.Fill();

	PlayerScore.Render();
	AIScore.Render();
	PlayerPaddle.Render();
	AIPaddle.Render();
	GameBall.Render();

	GameDisplay.Render();
}