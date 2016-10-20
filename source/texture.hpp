#pragma once

//Ping Pong by Andrew Vieira

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "display.hpp"
extern Display GameDisplay;
extern TTF_Font* GameFont;

class Texture
{
public:
	bool Create();
	void Destroy();

	bool LoadFromFile(std::string path);
	bool LoadFromRenderedText(std::string textureText, SDL_Color textColor);

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);

	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int GetWidth();
	int GetHeight();

private:
	SDL_Texture* MyTexture = nullptr;
	int width = 0;
	int height = 0;
};