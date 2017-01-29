#pragma once 
#include <vector>
#include "SDL.h"
#include "Position.h"
#include <iostream>

class GameWorld;
class Sprite {
public:
	Position pos;
	Position spriteDimenions;
	Position playerGridCo;
	SDL_Rect destinationRenderTarget;
	SDL_Rect source;
	SDL_Texture* texture;
	int orientation, frame;
	std::vector<SDL_Rect> animationFrames;
	bool doAnimate = false;
	int currentAnimation;
	//double animationGap = 0.25;
	double animationTime = 0.25;
	double animationTimer = 0.0;	
	double canKillTimer = 0.0;
	double canKillTime = 5.0;
	void UpdateRect();
	//void UpdateSource(int frame);
	void UpdateSource();
	void DoTimers(GameWorld& world, double& frameTime);
	//void pDoTimers(GameWorld& world, double& frameTime);
	int ExactSpriteLocation(GameWorld& gameWorld, int , int);

	void MoveSprite(GameWorld& gameworld, double playerSpeed, double frameTime, int orientation);
	bool CanMove(GameWorld& gameWorld, int orientation);

	Sprite(Position pos, SDL_Rect destination, SDL_Texture* tex, double newOrientation);
	~Sprite();

private:
	SDL_Rect nullRect = { 0, 0, -1, -1 };
};