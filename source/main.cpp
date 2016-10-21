#include "main.hpp"

//Ping Pong by Andrew Vieira

int main(int argc, char* argv[])
{
	//Start Up
	GameSubSystem.StartUp();
	GameDisplay.StartUp();
	GameHandle.StartUp();
	GameFont = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 30);
	GameSimulator.StartUp();

	//Game Loop
	GameSimulator.MainLoop();

	//ShutDown
	GameSimulator.ShutDown();
	TTF_CloseFont(GameFont);
	GameFont = nullptr;
	GameHandle.ShutDown();
	GameDisplay.ShutDown();
	GameSubSystem.ShutDown();

	return 0;
}