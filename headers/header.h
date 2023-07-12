#ifndef _HEADER_
#define _HEADER_

#include <SDL2/SDL.h>
#include "../inc/constants.h"

extern const int map[MAP_NUM_ROWS][MAP_NUM_COLS];

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int isGameRunning;


typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

struct Player
{
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
};
extern struct Player p;

extern struct Ray {
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
} rays[NUM_RAYS];

// extern struct Ray rays[NUM_RAYS];
extern int ticksLastFrame;
extern Uint32 *colorBuffer;
extern SDL_Texture *colorBufferTexture;
extern Uint32 *wallTexture;
extern Uint32 *textures[NUM_TEXTURES];

/* Functions */
void render(SDL_Instance instance);
void close(SDL_Instance instance);
int init_instance(SDL_Instance *);
int poll_events(void);
void renderMap(SDL_Instance instance);
void setupPlayer(SDL_Instance instance);
void renderPlayer(SDL_Instance instance);
void movePlayer(float deltaTime);
int mapHasWallAt(float x, float y);
void update(void);
void castAllRays(void);
void castRay(float rayAngle, int strIpld);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
void renderRays(SDL_Instance instance);
void clearColorBuffer(Uint32 color);
void renderColorBuffer(SDL_Instance instance);
void generate3DProjection(void);

#endif /* _HEADER_ */
