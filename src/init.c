#include <SDL2/SDL.h>
#include "../inc/header.h"

/**
* init_instance - initializing SDL2
* @instance: new instance
* Return: 0 if it fails, 1 if it's successful.
*/
int init_instance(SDL_Instance *instance)
{
	/* Initializing SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n",
			SDL_GetError());
		return (1);
	}
	/* Creating a new Window instance */
	instance->window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED,
					    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* Create a new Renderer instance linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
		    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}
