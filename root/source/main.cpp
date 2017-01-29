#include <iostream>
#include <chrono>
#include <vector>
#include <iterator>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "headers/globals.h"
#include "headers/Position.h"
#include "headers/GameWorld.h"
#include "headers/Sprite.h"
#include "headers/Input.h"

using namespace std;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

//render text
//set title
GameWorld gameWorld;
Input userInput;

bool fulScrTog = false, twoPlayer = false;
double playerSpeed = 100;
double animationFrameTime;

void tFullScr(SDL_Window* window) {
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	bool fulScrTog = SDL_GetWindowFlags(window) & FullscreenFlag;														
	SDL_SetWindowFullscreen(window, fulScrTog ? 0 : FullscreenFlag); 
}

chrono::high_resolution_clock::time_point getCurrentTime(){
	return chrono::high_resolution_clock::now();
}

Position getMapSpriteStartingPosition(int& spriteElementNumber) {
	int columnOffset = (spriteElementNumber%GAMEWORLDSIZE_X);
	int rowOffset = (spriteElementNumber / GAMEWORLDSIZE_X);
	columnOffset *= GRIDELESIZE_X;
	rowOffset *= GRIDELESIZE_Y;
	return Position(columnOffset, rowOffset);
}

int importTextures()
{
	//	**** IMPORT PLAYER SPRITES ****
	for (int i = 0; i < gameWorld.characterTextureAddresses.size(); i++) {
		SDL_Surface *PlayerSur = IMG_Load(gameWorld.getFullPath(gameWorld.characterTextureAddresses.at(i)));
		if (PlayerSur == NULL) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", SDL_GetError());
			return 1;
		}
		else {
			SDL_Texture *PlayerTex = SDL_CreateTextureFromSurface(renderer, PlayerSur);// convert surface to texture
			if (PlayerTex == NULL) {
				SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
				return 1;
			}

			else {
				gameWorld.characterTextureList.push_back(PlayerTex);
			}
		}
	}

	for (int i = 0; i < gameWorld.staticTextureAddresses.size(); i++) {

		SDL_Surface *StaticSur = IMG_Load(gameWorld.getFullPath(gameWorld.staticTextureAddresses.at(i)));
		if (StaticSur == NULL) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", SDL_GetError());
			return 1;
		}
		else {
			SDL_Texture* StaticTex = SDL_CreateTextureFromSurface(renderer, StaticSur);// convert surface to texture
			if (StaticTex == NULL) {
				SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
				return 1;
			}

			else {
				gameWorld.staticTextureList.push_back(StaticTex);
			}
		}
	}

	for (int i = 0; i < gameWorld.HUDTextureAddresses.size(); i++) {
		SDL_Surface *HudSur = IMG_Load(gameWorld.getFullPath(gameWorld.HUDTextureAddresses.at(i)));
		if (HudSur == NULL) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", SDL_GetError());
			return 1;
		}
		else {
			SDL_Texture* HudTex = SDL_CreateTextureFromSurface(renderer, HudSur);// convert surface to texture
			if (HudTex == NULL) {
				SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
				return 1;
			}

			else {
				gameWorld.HudTextureList.push_back(HudTex);
				gameWorld.HudTextureDimentions.push_back({ (double)HudSur->w, (double)HudSur->h });
			}
		}
	}
}

void setupAllSprites()
{	
	for (int i = 1; i < gameWorld.HUDTextureAddresses.size()-1; i++) {
		SDL_Rect HudEleRect = { 0,0,gameWorld.HudTextureDimentions.at(i).x,gameWorld.HudTextureDimentions.at(i).y };
		Sprite* h = new Sprite({ 0,0 }, HudEleRect, gameWorld.HudTextureList.at(i), 0);
		gameWorld.HudSprites.push_back(*h);
		delete h;
	}

	for (int i = 0; i < gameWorld.map.size(); i++)	{
		SDL_Rect mapTileRect = { 0, 0, 50,50 };
		Position startingCoordenates = getMapSpriteStartingPosition(i);
		Sprite* s = new Sprite(startingCoordenates, mapTileRect, gameWorld.returnMapTextureValue(gameWorld.map.at(i).x), gameWorld.map.at(i).y);
		s->source = { (int)(((int)gameWorld.map.at(i).x <= 9) ? ((int)gameWorld.map.at(i).x - 1) : ((int)gameWorld.map.at(i).x - 10)) * 50,0,50,50 };
		gameWorld.staticSprites.push_back(*s);
		delete s;
	}
	for (int i = 0; i < gameWorld.enemyStart.size(); i++) {
		SDL_Rect eRect1 = { 0, 0, 50, 50 };
		SDL_Rect eRect2 = { 50, 0, 50, 50 };
		SDL_Rect eRect3 = { 100, 0, 50, 50 };
		Sprite* enemy = new Sprite(gameWorld.enemyStart.at(i), eRect1, gameWorld.characterTextureList.at(2), 0);
		enemy->doAnimate = false;
		enemy->animationFrames.push_back(eRect2);
		enemy->animationFrames.push_back(eRect3);
		enemy->source = eRect1;
		gameWorld.enemySprites.push_back(*enemy);
		delete enemy;
	}

	int playerNum;
	if (twoPlayer == true) { playerNum = 2; }
	else playerNum = 1;

	for (int i = 0; i < playerNum; i++) {
		SDL_Rect pRect1 = { 0,0, 50, 50 };
		SDL_Rect pRect2 = { 50, 0, 50, 50 };
		SDL_Rect pRect3 = { 100, 0, 50, 50 };
		SDL_Rect pRect4 = { 150, 0, 50, 50 };
		SDL_Rect pRect5 = { 200, 0, 50, 50 };

		Sprite* player = new Sprite(gameWorld.playerStart, pRect1, gameWorld.characterTextureList.at(i), 0);
		player->doAnimate = true;
		player->animationTime = 0.25;	//time perframe
		player->animationFrames.push_back(pRect1);
		player->animationFrames.push_back(pRect2);
		player->animationFrames.push_back(pRect3);
		player->animationFrames.push_back(pRect4);
		player->animationFrames.push_back(pRect5);
		player->UpdateSource();
		gameWorld.characterSprites.push_back(*player);
		//cout << player->ExactSpriteLocation(gameWorld) << endl;
		delete player;
	}
}

void processInput(bool &running)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				cout << "W pressed" << endl;
				userInput.W = true;
				break;
			case SDLK_a:
				userInput.A = true;
				break;
			case SDLK_s:
				userInput.S = true;
				break;
			case SDLK_d:
				userInput.D = true;
				break;
			case SDLK_p:
				tFullScr(window);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				userInput.W = false;
				break;
			case SDLK_a:
				userInput.A = false;
				break;
			case SDLK_s:
				userInput.S = false;
				break;
			case SDLK_d:
				userInput.D = false;
				break;
			}

			break;
		case SDL_QUIT:
			running = false;
			break;
		}
	}

	userInput.Process();
}

void enemyAutoMove(double frameTime) {
	
	for (Sprite e : gameWorld.enemySprites) {
		

		if (e.CanMove(gameWorld, 3)) {
			e.MoveSprite(gameWorld, playerSpeed, frameTime, 3);
		}
		else if (e.CanMove(gameWorld, 2)) {
			e.MoveSprite(gameWorld, playerSpeed, frameTime, 2);
		}
		else if (e.CanMove(gameWorld, 3)) {
			e.MoveSprite(gameWorld, playerSpeed, frameTime, 0);
		}
		else e.MoveSprite(gameWorld, playerSpeed, frameTime, 1);
		e.DoTimers(gameWorld, frameTime);
	}
}

void update(double frameTime) {
	if (userInput.W) {
		if (gameWorld.characterSprites.at(0).CanMove(gameWorld, 3)) {
			gameWorld.characterSprites.at(0).MoveSprite(gameWorld, playerSpeed, frameTime, 3);
		}
	}
	else if (userInput.A) {
		if (gameWorld.characterSprites.at(0).CanMove(gameWorld, 2)) {
			gameWorld.characterSprites.at(0).MoveSprite(gameWorld, playerSpeed, frameTime, 2);
		}
	}
	else if (userInput.S) {
		if (gameWorld.characterSprites.at(0).CanMove(gameWorld, 1)) {
			gameWorld.characterSprites.at(0).MoveSprite(gameWorld, playerSpeed, frameTime, 1);
		}
	}
	else if (userInput.D) {
		if (gameWorld.characterSprites.at(0).CanMove(gameWorld, 0)) {
			gameWorld.characterSprites.at(0).MoveSprite(gameWorld, playerSpeed, frameTime, 0);
		}
	}
	else {
		// keep going 
	}

	enemyAutoMove(frameTime);

	for (Sprite c : gameWorld.characterSprites) {
		c.DoTimers(gameWorld, frameTime);
	}

	if (!Mix_PlayingMusic()) Mix_PlayMusic(gameWorld.Music, -1);
}

void doRender(Sprite& s)
{
	SDL_RenderCopyEx(renderer, s.texture, (s.source.w == -1) ? NULL : &s.source, &s.destinationRenderTarget, s.orientation * 90, NULL, SDL_FLIP_NONE);
	//SDL_RenderDrawRect(renderer, &s.destinationRenderTarget);
}

void render(bool running)
{
	int spriteFrame;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);

	if (running) {
		for (Sprite s : gameWorld.staticSprites) {
			doRender(s);
		}
		for (Sprite e : gameWorld.enemySprites) {
			doRender(e);
		}
		for (Sprite c : gameWorld.characterSprites) {
			doRender(c);
		}
	}
	else {
		for (Sprite h : gameWorld.HudSprites) {
			doRender(h);
		}
	}
	SDL_RenderPresent(renderer);
}

int startUp() {
	SDL_Surface *HudSur = IMG_Load(gameWorld.getFullPath(gameWorld.HUDTextureAddresses.at(0)));
	if (HudSur == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", SDL_GetError());
		return 1;
	}
	else {
		SDL_Texture* HudTex = SDL_CreateTextureFromSurface(renderer, HudSur);// convert surface to texture
		if (HudTex == NULL) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
			return 1;
		}
		else {
			gameWorld.HudTextureList.push_back(HudTex);
			gameWorld.HudTextureDimentions.push_back({ (double)HudSur->w, (double)HudSur->h });
		}
	}
	SDL_Rect HudEleRect = { 0,0,gameWorld.HudTextureDimentions.at(0).x,gameWorld.HudTextureDimentions.at(0).y };
	Sprite* h = new Sprite(Position{0,0}, HudEleRect, gameWorld.HudTextureList.at(0), 0);
	h->source = HudEleRect;
	gameWorld.HudSprites.push_back(*h);
	delete h;
	render(false);
	return 0;
	
}

int main(int argc, char *argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { //copys header into file
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialised OK!\n");

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_image init error: %s\n", IMG_GetError());
		return 1;
	}
	SDL_Log("SDL_image initialised OK!\n");
	if (SDL_CreateWindowAndRenderer(WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE, &window, &renderer)){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 1;
	}
	SDL_RenderSetLogicalSize(renderer, WINDOW_W, WINDOW_H);
	

	SDL_SetWindowTitle(window, "Games Programming | Joe Beeson | 15564479 ");


	startUp();

	// SDL_mixer initialise
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_mixer init error: %s\n   PERHAPS NO HEADPHONES/SPEAKERS CONNECTED\n", Mix_GetError());
		return 1;
	}
	SDL_Log("SDL_mixer initialised OK!\n");
	
	gameWorld.loadAudio();
	
	importTextures();
	setupAllSprites();
		
	bool running = true;
	double timeDiff = 0;														
	chrono::high_resolution_clock::time_point previous = getCurrentTime();
	chrono::high_resolution_clock::time_point previous2 = getCurrentTime();
	chrono::high_resolution_clock::time_point previous3 = getCurrentTime();


	while (running)
	{	
		//system("cls");
		timeDiff = (chrono::duration_cast<chrono::microseconds>(getCurrentTime() - previous).count());
		timeDiff = timeDiff / 1000000;
		previous = getCurrentTime();
		cout << "Time per game tick: " << timeDiff << endl;

		processInput(running); 
		previous2 = getCurrentTime();
		update(timeDiff);
		timeDiff = (chrono::duration_cast<chrono::microseconds>(getCurrentTime() - previous2).count());
		timeDiff = timeDiff / 1000000;
		cout << "Time per update tick: " << timeDiff << endl;
		previous3 = getCurrentTime();
		render(true);
		timeDiff = (chrono::duration_cast<chrono::microseconds>(getCurrentTime() - previous3).count());
		timeDiff = timeDiff / 1000000;
		cout << "Time per render tick: " << timeDiff << endl;
		cout << "Player Score : " << gameWorld.PLayerScores.at(0) << endl;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}