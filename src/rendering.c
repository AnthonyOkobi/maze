#include <SDL2/SDL.h>
#include <math.h>
#include <limits.h>
#include "../inc/header.h"
#include "../inc/constants.h"

/**
 * normalizeAngle - normalizing the angle
 * @angle: the angle
 * Return: the normal angle
 */
float normalizeAngle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

/**
 * distanceBetweenPoints - measures distance between points
 * @x1: first x point
 * @y1: first y point
 * @x2: second x point
 * @y2: second y point
 * Return: the distance
 */
float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * castRay - casts rays
 * @rayAngle: the ray angle
 * @stripld: counter
 */
void castRay(float rayAngle, int stripId)
{
	rayAngle = normalizeAngle(rayAngle);
    
    int isRayFacingDown = rayAngle > 0 && rayAngle < PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;
    
    float xintercept, yintercept;
    float xstep, ystep;

    /* Horizontal ray-grid intersection code */
    int foundHorzWallHit = FALSE;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    /* Finding the y-coordinate of the closest horizontal grid intersection */
    yintercept = floor(p.y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    /* Finding the x-coordinate of the closest horizontal grid intersection */
    xintercept = p.x + (yintercept - p.y) / tan(rayAngle);

    /* Calculate the increment xstep and ystep */
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    /* Incrementing xstep and ystep until finding a wall */
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        
        if (mapHasWallAt(xToCheck, yToCheck)) {
            /* found a wall hit */
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = TRUE;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    
    /* Vertical ray-grid intersection code */
    int foundVertWallHit = FALSE;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    /* Finding the x-coordinate of the closest horizontal grid intersection */
    xintercept = floor(p.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    /* Finding the y-coordinate of the closest horizontal grid intersection */
    yintercept = p.y + (xintercept - p.x) * tan(rayAngle);

    /* Calculating the increment xstep and ystep */
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    /* Incrementing xstep and ystep until finding a wall */
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        
        if (mapHasWallAt(xToCheck, yToCheck)) {
            /* found a wall hit */
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = TRUE;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    /* Calculate both horizontal and vertical hit distances and choose the smallest one */
    float horzHitDistance = foundHorzWallHit
        ? distanceBetweenPoints(p.x, p.y, horzWallHitX, horzWallHitY)
        : INT_MAX;
    float vertHitDistance = foundVertWallHit
        ? distanceBetweenPoints(p.x, p.y, vertWallHitX, vertWallHitY)
        : INT_MAX;

    if (vertHitDistance < horzHitDistance) {
        rays[stripId].distance = vertHitDistance;
        rays[stripId].wallHitX = vertWallHitX;
        rays[stripId].wallHitY = vertWallHitY;
        rays[stripId].wallHitContent = vertWallContent;
        rays[stripId].wasHitVertical = TRUE;
    } else {
        rays[stripId].distance = horzHitDistance;
        rays[stripId].wallHitX = horzWallHitX;
        rays[stripId].wallHitY = horzWallHitY;
        rays[stripId].wallHitContent = horzWallContent;
        rays[stripId].wasHitVertical = FALSE;
    }
    rays[stripId].rayAngle = rayAngle;
    rays[stripId].isRayFacingDown = isRayFacingDown;
    rays[stripId].isRayFacingUp = isRayFacingUp;
    rays[stripId].isRayFacingLeft = isRayFacingLeft;
    rays[stripId].isRayFacingRight = isRayFacingRight;
}

/**
 * renderMap - rendering rays
 */
void castAllRays(void)
{
	int stripld;
	float rayAngle;

	rayAngle = p.rotationAngle - (FOV_ANGLE / 2);

	for (stripld = 0; stripld < NUM_RAYS; stripld++)
	{
		castRay(rayAngle, stripld);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

/**
* renderMap - rendering the map
* @instance: sdl instance
*/
void renderMap(SDL_Instance instance)
{
	int i, j;
	int tileX, tileY, tileColor;

	for (i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (j = 0; j < MAP_NUM_COLS; j++)
		{
			tileX = j * TILE_SIZE;
			tileY = i * TILE_SIZE;
			tileColor = map[i][j] != 0 ? 255 : 0;

			SDL_SetRenderDrawColor(instance.renderer, tileColor, tileColor, tileColor, 255);
			SDL_Rect mapTileRect = {
				tileX * MINIMAP_SCALE_FACTOR,
				tileY * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR
			};
			SDL_RenderFillRect(instance.renderer, &mapTileRect);
		}
	}
}

/**
 * renderRays - renders rays
 * Return: nothing
 */
void renderRays(SDL_Instance instance)
{
	int i;

	SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 255);
    for (i = 0; i < NUM_RAYS; i++)
	{
        SDL_RenderDrawLine(
            instance.renderer,
            MINIMAP_SCALE_FACTOR * p.x,
            MINIMAP_SCALE_FACTOR * p.y,
            MINIMAP_SCALE_FACTOR * rays[i].wallHitX,
            MINIMAP_SCALE_FACTOR * rays[i].wallHitY
        );
    }
}
