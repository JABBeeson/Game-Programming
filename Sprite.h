#pragma once
#include "Position.h"
#include "SDL.h"

class Sprite
{
	//needs to contain the texture (it only needs to contain the emeny type,
	//can then use it to allocate when rendering), position, sprite type(ememy).
public:

	Position pos;
	SDL_Rect destinationRenderTarget;
	SDL_Rect Source;
	SDL_Texture* texture;

	Sprite();
	Sprite(Position, SDL_Rect, SDL_Texture*);

	void UpdateRect();
	~Sprite();

private:
	SDL_Rect nullRect = { 0, 0, -1, -1 };
};
