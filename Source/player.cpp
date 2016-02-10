#include "player.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

Player::Player(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y)
{
	//set the plaer number 0 or 1
	playerNum=pNum;

	//set float for player speed
	speed = 500.0f;

	laser = Mix_LoadWAV((audioPath + "laser.wav").c_str());

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

	//set the movement floats to the players original x and y
	pos_X = x;
	pos_Y = y;

	//set the xdir and ydir for the joysticks
	xDir=0;
	yDir=0;

	//string to creat e the path of the players byllet image
	string bulletPath;
	//see if this is player 1, or player 2, and create the currect file path
	if(playerNum == 0){
		//create the bullet 1 texture
		bulletPath = filePath + "1bullet.png";
	}else{
		//create the bullet 2 texture
		bulletPath=filePath+"2bullet.png";
	}

	//create the players bullet pool
	for(int i=0; i < 10; i ++){
		//create the bullet and move off screen, out of the game play area
		Bullet tmpBullet(renderer, bulletPath, -1000, -1000);

		//add to bulletlist
		bulletList.push_back(tmpBullet);

	}


}
//create a bullet
void Player::CreateBullet(){
	//see if there is a bullet active to fire
	for(int i = 0; i < bulletList.size(); i++){

		//see if the bullet is not active
	if(bulletList[i].active == false){

		//set bullet to active
		bulletList[i].active = true;

		//use some math in the x position to get the bullet close
		//to the center of the player using player width
		bulletList[i].posRect.x = (pos_X + (posRect.w/2));

		//finish aligning to the player center using the texture width
		bulletList[i].posRect.x = (bulletList[i].posRect.x -(bulletList[i].posRect.w/2));
		bulletList[i].posRect.y = posRect.y;

		//set the x and y position of the bullets float positons
		bulletList[i].pos_X = pos_X;
		bulletList[i].pos_Y = pos_Y;

	}

	}

}

//player Joystick butotn method
void Player::OnControllerButton(const SDL_ControllerButtonEvent event){
	//if the players number is 0 and the joystick button is from joystick 0
	if(event.which == 0 && playerNum == 0){

		//if A button
		if(event.button == 0){

			cout << "Player 1 - button A" << endl;

			//create bullet
			CreateBullet();

		}

	}

	//if the players number is 1 and the joystick button is from joystick 1
	if(event.which == 1 && playerNum == 1){

		// if A button
		if(event.button == 0){

			cout << "Player 2 - button A" << endl;

			//create bullet
			CreateBullet();

		}

	}

}


void Player::OnControllerAxis(const SDL_ControllerAxisEvent event){

	//if the players number is 0 and the joystick axis from joystick 0
	if(event.which ==0 && playerNum == 0){

		if(event.axis==0){

			if(event.value < -JOYSTICK_DEAD_ZONE){
				xDir = -1.0f; //LEFT
			}
			else if(event.value > JOYSTICK_DEAD_ZONE){
				xDir = 1.0f; //RiGHT
			}
			else{
				xDir = 0.0f; //NONBE
			}

		}

		if(event.axis==1){

			if(event.value < -JOYSTICK_DEAD_ZONE){
				yDir = -1.0f; //DOWN
			}
			else if(event.value > JOYSTICK_DEAD_ZONE){
				yDir = 1.0f; //UP
			}
			else{
				yDir = 0.0f; //NONE
			}

		}



	}

	//if the players number is 0 and the joystick axis from joystick 0
		if(event.which ==1 && playerNum == 1){

			if(event.axis==0){

				if(event.value < -JOYSTICK_DEAD_ZONE){
					xDir = -1.0f; //LEFT
				}
				else if(event.value > JOYSTICK_DEAD_ZONE){
					xDir = 1.0f; //RiGHT
				}
				else{
					xDir = 0.0f; //NONBE
				}

			}

			if(event.axis==1){

				if(event.value < -JOYSTICK_DEAD_ZONE){
					yDir = -1.0f; //DOWN
				}
				else if(event.value > JOYSTICK_DEAD_ZONE){
					yDir = 1.0f; //UP
				}
				else{
					yDir = 0.0f; //NONE
				}

			}



		}

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

	//Update the players bullets
	for(int i = 0; i < bulletList.size(); i++){
		if(bulletList[i].active){

		bulletList[i].Update(deltaTime);

		}

	}

}
//player draw method
void Player::Draw(SDL_Renderer *renderer){

	SDL_RenderCopy(renderer, texture, NULL, &posRect);

	for(int i = 0; i < bulletList.size(); i++){

		if(bulletList[i].active){

		bulletList[i].Draw(renderer);

		}
	}

}

Player::~Player(){
	SDL_DestroyTexture(texture);
}
