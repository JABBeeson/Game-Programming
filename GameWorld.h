#pragma once
#include <vector>
#include "SDL.h"
#include "Sprite.h"


class GameWorld
{
public:
	Sprite playerSprite;	//need constructor, even though no parameters
	std::vector<Sprite> staticSprites;
	std::vector<Sprite> enemySprites;
	std::vector<SDL_Texture> textureList;
};
