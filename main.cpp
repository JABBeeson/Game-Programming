#include <iostream>
#include <chrono>
#include "SDL.h"

using namespace std;

// **** POINTER DECLARATION ****
SDL_Window *window;
SDL_Renderer *renderer;

chrono::high_resolution_clock::time_point getCurrentTime() //everything must be multipied by the frame time!!
{
	return chrono::high_resolution_clock::now();
}

void processInput(bool &running)
{
	// get input, SLD POLL EVENT, SDL QUIT EVENT - 

	SDL_Log("ProcessInput");
}



void update(double frameTime)		//everything must be multipied by the frame time!!
{
	// change the state
	
	//double position = playerSpeed * frameTime;	//regulation ensure that the player moves a constant speed

	SDL_Log("Update");
}

void render()
{
	// render

	//Clear the entire screen to our selected color.
	SDL_RenderClear(renderer);
	
	// Select the color for drawing. It is set to red here. 	
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	//updates the screen
	SDL_RenderPresent(renderer);

	SDL_Log("Render");
}

int main(int argc, char* argv[])
{
	//**** VARIABLE DECLARATION ****
	bool running = true;
	
	double timeDiff = 0;														//Time related
	chrono::high_resolution_clock::time_point previous = getCurrentTime();		//Time related
	
	

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { //copys header into file
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_INit Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialised OK!\n");

	// **** WINDOW SETTINGS ****

	if (SDL_CreateWindowAndRenderer(320,240,SDL_WINDOW_RESIZABLE,&window,&renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return 1;
	}
		
	// **** GAME LOOP ****

	while (running)
	{
		timeDiff = (chrono::duration_cast<chrono::microseconds>(getCurrentTime() - previous).count()) / (1000 * 1000);
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