#include "GameWorld.h"
#include <iostream>

void GameWorld::setCanKill(bool i) {
	this->canKill = i;
	if (i) {
		for (Sprite e : enemySprites) {
			e.doAnimate = true;
		}
	}
	else for (Sprite e : enemySprites) {
		e.doAnimate = false;
		e.source = { 0, 0, 50, 50 };
	}
}

SDL_Texture* GameWorld::returnMapTextureValue(int i) {
	// NEED TO ACOMODATE FOR COLLECTABLES ALSO
	if (i < 9) {
		return staticTextureList.at(0);
	}
	else if (i == 11) {
		return staticTextureList.at(2);
	}
	else {
		return staticTextureList.at(1);
	}
}

char*  GameWorld::getFullPath(char* path) {
	char* fullPath = SDL_GetBasePath();
	strcat(fullPath, path);
	return fullPath;
}

void GameWorld::removeTexture(int _playerGridIndex){
	this->map.at(_playerGridIndex).x = 9;
	this->staticSprites.at(_playerGridIndex).source = { 9 * 50, 0, 50,50 };
}
void GameWorld::playAudio(int i) {
	switch (i)
	{
	case 1:
		Mix_PlayChannel(-1, Point, 1);
		break;
	case 2:
		Mix_PlayChannel(-1, Cherry, 1);
		break;
	default:
		break;
	}
}

int GameWorld::loadAudio() {
	// Load the music
	this->Music = Mix_LoadMUS(getFullPath("assets/audio/Music.wav"));
	if (!Music)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUS error: %s\n", Mix_GetError());
		return 1;
	}
	SDL_Log("SDL_mixer loaded music OK!\n");\

	// Load the sound effect
	Mix_Chunk *Point = Mix_LoadWAV(getFullPath("assets/audio/Point.mp3"));
	if (!Point)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadWAV error: %s\n", Mix_GetError());
		return 1;
	}
	SDL_Log("SDL_mixer loaded sound effect OK!\n");

	Cherry = Mix_LoadWAV(getFullPath("assets/audio/Cherry.wav"));
	if (!Cherry)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadWAV error: %s\n", Mix_GetError());
		return 1;
	}
	SDL_Log("SDL_mixer loaded sound effect OK!\n");

}

GameWorld::GameWorld() {
	//loadAudio();
}
GameWorld::~GameWorld() {}