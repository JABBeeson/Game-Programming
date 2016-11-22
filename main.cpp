#include <iostream>
#include <chrono>
#include <vector>
#include <iterator>
#include <string>

#include "Globals.h"	// importing class headers
#include "SDL.h"
#include "Position.h"
#include "Inputs.h"
#include "Sprite.h"
#include "GameWorld.h"

using namespace std;

// **** WINDOW AND RENDERER POINTER DECLARATION ****

//global is instantiated at load time - before main starts

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
GameWorld gameWorld;
Inputs userInput;

bool fulScrTog = false;
double playerSpeed = 100;


// toggle fullscreen routine
void TFullScr(SDL_Window* window)
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;//unidentified 32 bit number
	bool fulScrTog = SDL_GetWindowFlags(window) & FullscreenFlag;	// determins wearther or no the window is toggled to full screen.
	cout << FullscreenFlag;

	SDL_SetWindowFullscreen(window, fulScrTog ? 0 : FullscreenFlag); // '?' condional notaion
																	
	// if fullscreen, set to native
	// else set to windowed
}

//clock
chrono::high_resolution_clock::time_point getCurrentTime() //everything must be multipied by the frame time!!
{
	return chrono::high_resolution_clock::now();
}

//aquired the correct path
char* getFullPath(char* path) {
	char* fullPath = SDL_GetBasePath();
	strcat(fullPath, path);
	return fullPath;
}

void SetupSprite()
{
	SDL_Rect pRect = { PLAYERSTART.getX(),PLAYERSTART.getY(), 201, 160 };
	Sprite* p = new Sprite(PLAYERSTART, pRect, gameWorld.textureList.at(0));
	gameWorld.playerSprite = *p;
	delete p;

	for (int i = 0; i > ENEMYNUM; i++)
	{
		SDL_Rect eRect = { ENEMYSTART.getX(),ENEMYSTART.getY(), 201, 160 };	// cannot initialise an SDL_Rect in line.
		Sprite* e = new Sprite(ENEMYSTART, eRect, gameWorld.textureList.at(i));
		gameWorld.enemySprites.push_back(*e);
		delete e;
	}

}

int ImportTextures()
{
	SDL_Surface *PlayerSur = SDL_LoadBMP(getFullPath("Assets/Bee.bmp"));
	if (PlayerSur == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Texture *PlayerTex = SDL_CreateTextureFromSurface(renderer, PlayerSur);// convert surface to texture
		if (PlayerTex == NULL) {
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
			return 1;
		}

		else
		{
			gameWorld.textureList.push_back(PlayerTex); // add texture to list
		}
	}

}

void processInput(bool &running)
{
	// get input, SLD POLL EVENT, SDL QUIT EVENT -
	SDL_Event event;
	while (SDL_PollEvent(&event))	// key events
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				SDL_Log("W");
				userInput.W = true;
				break;
			case SDLK_a:
				SDL_Log("A");
				userInput.A = true;
				break;
			case SDLK_s:
				SDL_Log("S");
				userInput.S = true;
				break;
			case SDLK_d:
				SDL_Log("D");
				userInput.D = true;
				break;
			case SDLK_p:
				SDL_Log("p");
				TFullScr(window);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				SDL_Log("W up");
				userInput.W = false;
				break;
			case SDLK_a:
				SDL_Log("A up");
				userInput.A = false;
				break;
			case SDLK_s:
				SDL_Log("S up");
				userInput.S = false;
				break;
			case SDLK_d:
				SDL_Log("D up");
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

void update(double frameTime)		//everything must be multipied by the frame time!!
{
	// change the state
	gameWorld.playerSprite.pos.moveXY(userInput.horizontal * playerSpeed * frameTime, userInput.vertical * playerSpeed * frameTime);
	//in this case, the player movement. moveXY, is a value thats added to the plaer position, giving the illusion of movement.
	//SDL_Log("Update");
}

void DoRender(Sprite& s)
{
	SDL_RenderCopy(renderer, s.texture, (s.Source.w == -1) ? NULL : &s.Source, &s.destinationRenderTarget);
}

void render()
{
	// render

	//Clear the entire renderer
	SDL_RenderClear(renderer);

	//  image rendering

	for (auto Sprite : gameWorld.staticSprites)
		DoRender(Sprite);
	for (auto Sprite : gameWorld.enemySprites)
		DoRender(Sprite);

	/*vector<Sprite>::iterator staticIT;
	for (staticIT = gameWorld.staticSprites.begin(); staticIT < gameWorld.staticSprites.end(); staticIT++) {
		Sprite currentStatic = *staticIT;
		DoRender(currentStatic);
	}

	vector<Sprite>::iterator enemyIT;
	for (enemyIT = gameWorld.enemySprites.begin(); enemyIT < gameWorld.enemySprites.end(); enemyIT++) {
		Sprite currentEnemy = *enemyIT;
		DoRender(currentEnemy);
	}
	*/

	Sprite &playerSprite = gameWorld.playerSprite;
	DoRender(playerSprite);


	//updates the screen
	SDL_RenderPresent(renderer);

	//SDL_Log("Render");
}

int main(int argc, char* argv[])
{
	// **** LOAD IN SLD LIBRARY ****
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { //copys header into file
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_INit Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialised OK!\n");

	// **** WINDOW, SURFACE AND TEXTURE DECLARATION ****

	if (SDL_CreateWindowAndRenderer(WINDOW_W,WINDOW_H,SDL_WINDOW_RESIZABLE,&window,&renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 1;
	}

	SDL_RenderSetLogicalSize(renderer, WINDOW_W, WINDOW_H);

	ImportTextures();
	SetupSprite();	// set up sprites and fills in sprite textures
	
	// **** GAME LOOP ***

	bool running = true;
	double timeDiff = 0;														//Time related
	chrono::high_resolution_clock::time_point previous = getCurrentTime();


	while (running)
	{
		timeDiff = (chrono::duration_cast<chrono::microseconds>(getCurrentTime() - previous).count());
		timeDiff = timeDiff / 1000000; // CONVERSION TO SECONDS
		previous = getCurrentTime();


		processInput(running); // process input
		update(timeDiff); // update
		render(); // render
	}

	//Window is closed and destroyed
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);


	//Clean up
	SDL_Quit();
	return 0;
}
