#include "enemy.h"

//enemy creation method
Enemy::Enemy(SDL_Renderer *renderer, string filePath)
{
	//get the path to enemts texture
	string enemyPath = filePath + "enemy.png";

	//load the texture into a surface
	SDL_Surface *surface = IMG_Load(enemyPath.c_str());

	//Create the texture form the passed Renderer and created surface
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	//free the surface for later use
	SDL_FreeSurface(surface);

	//set the width and height of the enemy's rectangle
	//by querying the texture itself
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w=w;
	posRect.h=h;

	//reset the nenemy
	Reset();

	//initialize the firextion vars for enemy
	//no x movement only y movment
	xDir=0;
	yDir=1;

	//start with a random angle
	angle = rand()%(360);

	//caclutlate venter pos by setting
	//_> pos to half of width
	//->y pos to half height
	center.x = posRect.w/2;
	center.y = posRect.h/2;

}

//enemy reset method
void Enemy::Reset(){

	//set random enem speed
	speed = rand() % (5) + 1;
	speed *= 100;

	//genderate random x position and set y back to the top of the screen
	posRect.x = rand() % (1024-posRect.w) + 1;
	posRect.y =0 - posRect.h;

	//set the float posiiotn balues of the tecture for preceision loss
	pos_X = posRect.x;
	pos_Y = posRect.y;

}

//enemy update method
void Enemy::Update(float deltaTime){

	//adjust posiition floats based on speed direction and deltatime
	pos_Y += (speed * yDir) * deltaTime;

	//Upate enemy position with code to account for precision loss
	posRect.y = (int)(pos_Y + 0.5f);

	//check to see if the enemy is off the bottom of the screen
	// and reset if it is
	if(posRect.y > 768){

		//reset the enemy
		Reset();
	}

	//update angle
	angle += .1;

}

//enemy draw method
 void Enemy::Draw(SDL_Renderer *renderer){

	 SDL_RenderCopyEx(renderer, texture, NULL, &posRect, angle, &center, SDL_FLIP_NONE);
 }

//enemy destruction
Enemy::~Enemy(){

	//SDL_DestroyTextuer(tecture);
}
