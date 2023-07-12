#include <SDL2/SDL.h>
#include <stdio.h>
#include "../inc/constants.h"
#include "../inc/header.h"

/* Declaration of Global Variables */

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct Player p;
struct Ray rays[NUM_RAYS];
int ticksLastFrame;
uint32_t *colorBuffer = NULL;
SDL_Texture *colorBufferTexture;
Uint32 *wallTexture = NULL;
Uint32 *textures[NUM_TEXTURES];
/**
* main - main work
* Return: always 0.
*/
int main(void)
{
	SDL_Instance instance;

	/* Initializing the Window and Render */
	if (init_instance(&instance) != 0)
		return (1);

	/* Setting up Player */
	setupPlayer(instance);

	/* Main Game Loop */
	while ("game is running")
	{
		SDL_RenderClear(instance.renderer);

		/* Retrieving Input Events */
		if (poll_events() == 1)
			break;

		/* Game Update */
		update();

		/* Rendering */
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 255);
		SDL_RenderClear(instance.renderer);

		generate3DProjection();

		renderColorBuffer(instance);
		clearColorBuffer(0xFF000000);

		renderMap(instance);
		renderRays(instance);
		renderPlayer(instance);

		SDL_RenderPresent(instance.renderer);
	}
	free(wallTexture);
	free(colorBuffer);
	/* Render and Window destroy before quitting */
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();

	return (0);
}
