#include "bullet.h"
//bullet creation method
Bullet::Bullet(SDL_Renderer *renderer, string filePath, float x, float y){

	//set bullet initla state
	active=false;

	//set bullet speed
	speed = 800.0;

	//loat the rexture to a suraface

	SDL_Surface *surface = IMG_Load(filePath.c_str());

	//create the rexture from the passed renderer and created surfacess
	texture= SDL_CreateTextureFromSurface(renderer, surface);

	//free surface for later use;
	SDL_FreeSurface(surface);

	//set the width and height  of the bullet's rectangle
	//by querying the texture itself
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w=w;
	posRect.h=h;

	//set the x and y positions of the bullet recangle
	//finishing aligning to the player center using texutr width
	posRect.x =x - (posRect.w/2);
	posRect.y=y;

	//set the float posiiotn values of the texurre for precision loss
	pos_X=x;
	pos_Y=y;

	//initialize the direction vars for the bullet
	//no x Movement, only Y movement(up)
	xDir=0;
	yDir=-1;

}

//bullet update method
void Bullet::Update(float deltaTime){

	//check to see if the bullet is active
	if(active){

		//adjust position floats based on speed, direction(-1 for up), and deltaTime
	pos_Y += (speed * yDir) *deltaTime;

	//Update bullet posiiton with code to axount for precision loss
	posRect.y = (int) (pos_Y + 0.5f);

	//check to see if the bullet is off the top of the screen
	//and deactivate and move off screen
	if(posRect.y < (0-posRect.h)){

		posRect.x = -1000;
		pos_X=posRect.x;
		active=false;

	}

	}

}

//draw bullet method
void Bullet::Draw(SDL_Renderer * renderer)
{
SDL_RenderCopy(renderer, texture, NULL, &posRect);
}
//bullet destruction
Bullet::~Bullet(){
	SDL_DestroyTexture(texture);
}

