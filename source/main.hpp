#pragma once

//Ping Pong by Andrew Vieira

#include "subsystem.hpp"
#include "display.hpp"
#include "handle.hpp"
#include "simulator.hpp"

TTF_Font* GameFont;
SubSystem GameSubSystem;
Display GameDisplay;
Handle GameHandle;
Simulator GameSimulator;

int main(int argc, char* argv[]);