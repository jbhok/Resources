#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#endif

//#if defined(__linux__)
//#include <unistd.h>
//#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h>

class Enemy{
	//boolean for state of enemy
	bool active;

	//enemy texture
	SDL_Texture *texture;

	//enemy rectanbel for position(x,y) and size(h,w)
	SDL_Rect posRect;

	//movement direction values
	float xDir, yDir;

	//enemy speed
	float speed;

	//enemy float posiitons to prevent precision loss
	float pos_X, pos_Y;

	//enemy angle
	float angle;

	//point for the center of you object, used for rotatoin
	SDL_Point center;

	//enemy creation method, requires the renderer, a path to the needed image
	Enemy(SDL_Renderer *renderer, string filePath);

	//enemy update
	void Update(float deltaTime);

	//enemy draw
	void Draw(SDL_Renderer *renderer);

	//enemy reset
	void Reset();

	//enemy descturion method
	~Enemy();

};
