#pragma once

//Ping Pong by Andrew Vieira

#include "subsystem.hpp"
#include "display.hpp"
#include "handle.hpp"

#include "timer.hpp"
#include "texture.hpp"

#include "game_object.hpp"

SubSystem GameSubSystem;
Display GameDisplay;
Handle GameHandle;

TTF_Font* GameFont;

int main(int argc, char* argv[]);

