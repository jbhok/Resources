#include "player.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

Player::Player(SDL_Renderer *renderer, int pNum, string filePath, float x, float y)
{
	//set the plaer number 0 or 1
	playerNum=pNum;
	speed = 500.0f;

	if(playerNum == 0){

		playerPath = filePath + "p1.png";
	}else{

		playerPath=filePath+"p2.png";
	}
surface = IMG_Load(playerPath.c_str());

texture = SDL_CreateTextureFromSurface(renderer,surface);

SDL_FreeSurface(surface);

posRect.x=x;
posRect.y=y;

int w, h;

SDL_QueryTexture(texture, NULL, NULL, &w, &h);

posRect.w = w;
posRect.h=h;

pos_X = x;
pos_Y = y;

xDir=0;
yDir=0;

}

void Player::Update(float deltaTime){

	pos_X += (speed * xDir) * deltaTime;
	pos_Y += (speed * yDir) * deltaTime;

	posRect.x = (int)(pos_X + 0.5f);
	posRect.y = (int)(pos_Y + 0.5f);

	if(posRect.x<0){
		posRect.x = 0;
			pos_X = posRect.x;
		}
		if(posRect.x > 1024 - posRect.w){
			posRect.x = 1024 - posRect.w;
			pos_X = posRect.x;
		}
		if(posRect.y<0){
			posRect.y = 0;
			pos_Y=posRect.y;
		}
		if(posRect.y > 768 - posRect.h){
			posRect.y = 768 - posRect.h;
			pos_Y= posRect.y;
		}

}

void Player::Draw(SDL_Renderer *renderer){

	SDL_RenderCopy(renderer, texture, NULL, &posRect);
}

Player::~Player(){
	SDL_DestroyTexture(texture);
}
