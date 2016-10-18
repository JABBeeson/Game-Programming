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

	window = SDL_CreateWindow(
		"Window1",					//Window Title
		SDL_WINDOWPOS_UNDEFINED,	//initial x position
		SDL_WINDOWPOS_UNDEFINED,	//initial y position
		640,						//width, in pixels
		480,						//height, in pixels
		SDL_WINDOW_OPENGL			//flags - window usable with OpenGL context
	); //creates window

	renderer = SDL_CreateRenderer(
		window,						//Parent window
		-1,							//Index
		SDL_RENDERER_ACCELERATED	//Flags - the renderer uses hardware acceleration
	);

	//Check if the window was successfuly created & warning
	if (window == NULL)
	{
		printf("Could not generate window %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(2000); //two second pause

	//Window is closed and destroyed
	SDL_DestroyWindow(window);

	//Clean up
	SDL_Quit();
	return 0;
}