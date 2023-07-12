#include <SDL2/SDL.h>
#include "../inc/header.h"
#include "../inc/constants.h"

/**
 * clearColorBuffer - clears the color buffer
 * @color: the color
 * Return: nothing
 */
void clearColorBuffer(Uint32 color)
{
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        for (int y = 0; y < WINDOW_HEIGHT; y++)
            colorBuffer[(WINDOW_WIDTH * y) + x] = color;
    }
}

/**
 * renderColorBuffer - renders the color buffer
 * Return: nothing
 */
void renderColorBuffer(SDL_Instance instance)
{
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int)((Uint32)WINDOW_WIDTH * sizeof(Uint32))
    );
    SDL_RenderCopy(instance.renderer, colorBufferTexture, NULL, NULL);
}
