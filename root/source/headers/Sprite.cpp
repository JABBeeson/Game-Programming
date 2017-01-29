#include <iostream>
#include <math.h>
#include "GameWorld.h"
#include "Sprite.h"
#include "Globals.h"

using namespace std;

void Sprite::UpdateRect() {
	SDL_Rect d = { pos.x, pos.y, destinationRenderTarget.w, destinationRenderTarget.h };
	destinationRenderTarget = d;
}

void Sprite::UpdateSource() {
	this->source = animationFrames.at(currentAnimation);
}

/*void Sprite::UpdateSource(int frame) {

	this->source = { frame * 50, 0, 50, 50 };
	this->frame = frame;
	}*/
/*void Sprite::pDoTimers(GameWorld& world, double& frameTime) {
	animationTime = animationTime + frameTime;
	cout << animationTime << endl;
	if (animationTime >= animationGap) {
		UpdateSource(this->frame == 1 ? this->frame = 5 : this->frame = 1);
		animationTime = 0;
	}
}*/

void Sprite::DoTimers(GameWorld& world, double& frameTime) {
	/*
	if (world.canKill) {
		animationTime = animationTime + frameTime;
		if (animationTime > animationGap) {
			UpdateSource(this->frame != 2 ? this->frame = 2 : this->frame = 3);
			animationTime = 0;
		}		
	}
	if (!world.canKill) {
		UpdateSource(1);
	}*/
	
	if (world.canKill) {
		this->canKillTimer += frameTime;
	}
	
	if (doAnimate) {
		this->animationTimer += frameTime;
		if (this->animationTimer >= this->animationTime) {
			this->currentAnimation++;

			
			if (currentAnimation >= animationFrames.size()) {
			
				this->currentAnimation = 0;
			}
			this->animationTimer = 0.0;
			UpdateSource();
		}
	}

	if (this->canKillTimer >= canKillTime) {
		world.canKill = false;
		this->canKillTimer = 0.0;
	}
}

void Sprite::MoveSprite(GameWorld& world, double playerSpeed, double frameTime, int orientation) {
	switch (orientation)
	{
	case 0: // facing right;
		pos.moveXY(playerSpeed * frameTime, 0);
		break;
	case 2:	// facing left
		pos.moveXY(-playerSpeed * frameTime, 0);
		break;
	case 3:	// facing up
		pos.moveXY(0, -playerSpeed * frameTime);
		break;
	case 1:	// facing down
		pos.moveXY(0, playerSpeed * frameTime);
		break;
	default:
		break;
	}

	UpdateRect();
}
int Sprite::ExactSpriteLocation(GameWorld& gameWorld,int x, int y) {
	int a = (pos.x + x) / 50;
	int b = (pos.y + y) / 50;
	playerGridCo = { (double)a, (double)b};
	//std::cout << playerGridCo.x << " " << playerGridCo.y << std::endl;
	int playerGridIndex = playerGridCo.x + (playerGridCo.y* (GAMEWORLDSIZE_X));
	//std::cout << "playerGridIndex: " << playerGridIndex << std::endl;
	return playerGridIndex;
}
bool Sprite::CanMove(GameWorld& gameWorld, int newOrientation) {
	this->orientation = newOrientation;
	int playerGridIndex;
	int newIndex = -1;
	switch (newOrientation) {
	case 0: // facing right;
		playerGridIndex = ExactSpriteLocation(gameWorld, 0, 0);
		//std::cout << "facing right " << newIndex << std::endl;
		newIndex = playerGridIndex + 1;
		break;
	case 2:	// facing left
		playerGridIndex = ExactSpriteLocation(gameWorld, 49, 0);
		//std::cout << "facing left " << newIndex << std::endl;
		newIndex = playerGridIndex - 1;
		break;
	case 3:	// facing up
		playerGridIndex = ExactSpriteLocation(gameWorld, 0, 49);
		//std::cout << "facing up " << newIndex << std::endl;
		newIndex = playerGridIndex - GAMEWORLDSIZE_X;
		break;
	case 1:	// facing down
		playerGridIndex = ExactSpriteLocation(gameWorld, 0, 0);
		//std::cout << "facing down " << newIndex << std::endl;
		newIndex = playerGridIndex + GAMEWORLDSIZE_X;
		break;
	default:
		newIndex = -1;
		std::cout << "default" << std::endl;
		break;
	}
	//std::cout << "element index: " << newIndex << std::endl;
	if (newIndex == -1 || newIndex < 0 || newIndex > gameWorld.map.size()) { return false; std::cout << "broken" << std::endl; }
	if (gameWorld.map.at(newIndex).x > 8) {
		switch ((int)gameWorld.map.at(newIndex).x)
		{
		case 10:
			//std::cout << "point collision" << std::endl;
			gameWorld.PLayerScores.at(0) += 10;
			gameWorld.removeTexture(playerGridIndex);
			gameWorld.playAudio(1);
			break;
		case 11:
			//std::cout << "cherry collision" << std::endl;
			gameWorld.canKill = true;
			gameWorld.removeTexture(playerGridIndex);
			gameWorld.playAudio(2);
			break;
		default:
			break;
		}
		return true;
	}
	//std::cout << "collision" << std::endl;
		return false;
}
Sprite::Sprite(Position pos, SDL_Rect destination, SDL_Texture* tex, double _orientation) {
	this->pos = pos;
	orientation = _orientation;
	destinationRenderTarget = destination;
	destinationRenderTarget.x = pos.x;
	destinationRenderTarget.y = pos.y;
	//UpdateSource();
	texture = tex;
	this->currentAnimation = 0;
}
Sprite::~Sprite() {}
