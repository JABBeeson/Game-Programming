#include "Globals.h"
#include <iostream>
#include <chrono>
#include "SDL.h"
#include "Position.h"	// importing class headers
#include "Inputs.h"
#include "Window.h"
#include <string>

using namespace std;

// **** WINDOW AND RENDERER POINTER DECLARATION ****
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

//int picPosX = 0, picPosY = 0;
bool fulScrTog = false;
double playerSpeed = 100;

Position pos;
Inputs userInput;

void TFullScr(SDL_Window* window)
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;//unidentified 32 bit number
	bool fulScrTog = SDL_GetWindowFlags(window) & FullscreenFlag;	// determins wearther or no the window is toggled to full screen.
	cout << FullscreenFlag;
	SDL_SetWindowFullscreen(window, fulScrTog ? 0 : FullscreenFlag); // '?' condional notaion
	// get native res
	// if fullscreen, set to native
	// else set to windowed
}

chrono::high_resolution_clock::time_point getCurrentTime() //everything must be multipied by the frame time!!
{
	return chrono::high_resolution_clock::now();
}

char* getFullPath(char* path) {
	char* fullPath = SDL_GetBasePath();
	strcat(fullPath, path);
	return fullPath;
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

	//in this case, the player movement. moveXY, is a value thats added to the plaer position, giving the illusion of movement. 
		pos.moveXY(userInput.horizontal * playerSpeed * frameTime, userInput.vertical * playerSpeed * frameTime);

		/*if (userInput.P == true && fulScrTog == false);
		{

			//window = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 0, SDL_SWSURFACE | SDL_RESIZABLE | SDL_WINDOW_FULLSCREEN);
			//SDL_SetWindowDisplayMode();
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			fulScrTog = true;
		}
		if(userInput.P == true && fulScrTog == true )
		{
			fulScrTog = false;
		}
			*/

	//SDL_Log("Update");
}

void render(SDL_Texture *texture)
{
	// render

	//Clear the entire renderer
	SDL_RenderClear(renderer);
	
	//  image rendering
	SDL_Rect destRect = { pos.getX(),pos.getY(),201,160 };	//XYWH
	SDL_RenderCopy(
		renderer,		// rendereing context
		texture,		//source texture
		NULL,			//SDL_Rect source, Null for all
		&destRect);		//rendering target

	//	SDL_RenderCopy();


	//updates the screen
	SDL_RenderPresent(renderer);

	//SDL_Log("Render");
}

int main(int argc, char* argv[])
{
	// **** VARIABLE DECLARATION ****
	

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
	SDL_Delay(1000);
		
	SDL_Surface *BeeSur = SDL_LoadBMP(getFullPath("Assets/Bee.bmp"));
	if (BeeSur == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Texture *BeeTex = SDL_CreateTextureFromSurface(renderer, BeeSur);
	if (BeeTex == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		return 1;
	}

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
		render(BeeTex); // render
	}
	
	//Window is closed and destroyed
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	

	//Clean up
	SDL_Quit();
	return 0;
}