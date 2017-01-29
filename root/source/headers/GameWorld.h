#pragma once
#include <array>
#include <vector>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Position.h"
#include "Sprite.h"

class GameWorld {
public:

	Mix_Music *Music = nullptr;
	Mix_Chunk *Point = nullptr;
	Mix_Chunk *Cherry = nullptr;

	char* getFullPath(char* path);

	void setCanKill(bool);
	bool canKill = false;
	std::array<int, 2> PLayerScores{ 0,0 };
	Position playerStart{ 300, 200 };
	std::vector<Sprite> characterSprites;	//need constructor, even though no parameters
	std::vector<Sprite> enemySprites;
	std::vector<Sprite> staticSprites;
	std::vector<Sprite> HudSprites;
	std::vector<SDL_Texture*> characterTextureList;
	std::vector<SDL_Texture*> enemyTextureList;
	std::vector<SDL_Texture*> staticTextureList;
	std::vector<SDL_Texture*> HudTextureList;
	std::vector<SDL_Texture*> collectablesTextureList;
	std::vector<Position> HudTextureDimentions;
	std::array<Position, 3> enemyStart{ Position(250,300),Position(300,300),Position(350,300) };
	std::array<char*, 4> HUDTextureAddresses = {
		"Assets/HUD/Loading.png",
		"Assets/HUD/Splash.png",
		"Assets/HUD/Start.png",
		"Assets/HUD/Numbers.png" 
	};
	std::array<char*, 3> characterTextureAddresses = {
		"Assets/Character/playerOne.png",
		"Assets/Character/playerTwo.png",
		"Assets/Enemy/enemy.png"
	};
	std::array<char*, 3> staticTextureAddresses = {
		"Assets/Walls/Walls.png",
		"Assets/Collectables/collectable.png",
		"Assets/Collectables/collectableTwo.png"
	};
	
	std::array<Position, 182> map =	{	//(map peice, orentation degrees )

		Position(2,0),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(1,1),Position(2,1),
		Position(1,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(11,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(6,0),Position(3,1),Position(10,0),Position(3,3),Position(6,0),Position(3,1),Position(10,0),Position(3,3),Position(6,1),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(4,0),Position(10,0),Position(10,0),Position(9,0),Position(3,2),Position(9,0),Position(10,0),Position(10,0),Position(4,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(4,0),Position(10,0),Position(3,0),Position(9,0),Position(9,0),Position(9,0),Position(3,0),Position(10,0),Position(4,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(4,0),Position(10,0),Position(6,3),Position(3,1),Position(9,0),Position(3,3),Position(6,1),Position(10,0),Position(4,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(4,0),Position(10,0),Position(4,0),Position(9,0),Position(9,0),Position(9,0),Position(4,0),Position(10,0),Position(4,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(4,0),Position(10,0),Position(7,3),Position(4,1),Position(4,1),Position(4,1),Position(7,2),Position(10,0),Position(4,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(4,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(4,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(7,3),Position(4,1),Position(6,0),Position(3,1),Position(10,0),Position(3,3),Position(6,0),Position(4,1),Position(7,2),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(10,0),Position(11,0),Position(4,0),Position(10,0),Position(11,0),Position(10,0),Position(4,0),Position(11,0),Position(10,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(5,0),Position(10,0),Position(3,2),Position(10,0),Position(5,0),Position(10,0),Position(3,2),Position(10,0),Position(5,0),Position(10,0),Position(1,2),
		Position(1,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(10,0),Position(1,2),
		Position(2,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(1,3),Position(2,2)
	};

	SDL_Texture* returnMapTextureValue(int i);
	void removeTexture(int);
	void playAudio(int);
	int loadAudio();
	~GameWorld();

	GameWorld();
};