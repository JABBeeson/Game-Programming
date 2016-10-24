#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[])
{
	// **** POINTER DECLARATION ****
	SDL_Window *window;		
	SDL_Renderer *renderer;

	

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
	
	//Clear the entire screen to our selected color.
	SDL_RenderClear(renderer);
		//updates the screen
	
		// Select the color for drawing. It is set to red here. 	
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	
	
	SDL_RenderPresent(renderer);


	SDL_Delay(5000); //two second pause

	//Window is closed and destroyed
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Clean up
	SDL_Quit();
	return 0;
}