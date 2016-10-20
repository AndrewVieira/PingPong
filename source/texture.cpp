#include "texture.hpp"

//Ping Pong by Andrew Vieira

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
		std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
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
int Texture::GetWidth()
{
	return width;
}
int Texture::GetHeight()
{
	return height;
}