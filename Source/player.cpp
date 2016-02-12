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

	//init score and lives cars
	oldScore = 0;
	playerScore = 0;
	oldLives = 0;
	playerLives = 3;

	//init the font system
	TTF_Init();

	//loaf the font
	font = TTF_OpenFont((audioPath+"Arial Bold Italic.ttf").c_str(), 40);

	//see if this is player 1 or 2 and create the correct x an y locations
	if(playerNum==0){
		scorePos.x = scorePos.y= 10;
		livesPos.x = 10;
		livesPos.y = 40;

	}else{
		//create the score texture x and y positions
		scorePos.x = 650;
		scorePos.y = 10;
		livesPos.x = 650;
		livesPos.y = 40;
	}

	//update score method
	UpdateScore(renderer);

	//update score method
	UpdateLives(renderer);


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

		Mix_PlayChannel(-1, laser, 0);

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

			//cout << "Player 1 - button A" << endl;
			playerScore += 10;

			playerLives -= 1;

			//create bullet
			CreateBullet();

		}

	}

	//if the players number is 1 and the joystick button is from joystick 1
	if(event.which == 1 && playerNum == 1){

		// if A button
		if(event.button == 0){

			//cout << "Player 2 - button A" << endl;
			playerScore +=10;

			playerLives -= 1;

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

//update lives
void Player::UpdateLives(SDL_Renderer *renderer){

	//fix for to_string problesm on linux
	string Result;
	ostringstream convert;
	convert << playerLives;
	Result = convert.str();

	//ceate the text fo the font texutre
	tempLives = "Player Lives: " + Result;

	if(playerNum == 0){
		//place the player 1 score info into a surface
		livesSurface = TTF_RenderText_Solid(font, tempLives.c_str(), colorP1);
	}else{
		//place the player 1 score into a surface
		livesSurface = TTF_RenderText_Solid(font, tempLives.c_str(), colorP2);

	}
	//create the plyer score texture
	livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);

	//get the width and height of the teuxtre
	SDL_QueryTexture(livesTexture, NULL, NULL, &livesPos.w, &livesPos.h);

	//free surface
	SDL_FreeSurface(livesSurface);

	//set old score
	oldLives = playerLives;

}

//update score
void Player::UpdateScore(SDL_Renderer *renderer){

	//fix for to_string problesm on linux
	string Result;
	ostringstream convert;
	convert << playerScore;
	Result = convert.str();

	//ceate the text fo the font texutre
	tempScore = "Player Score: " + Result;

	if(playerNum == 0){
		//place the player 1 score info into a surface
		scoreSurface = TTF_RenderText_Solid(font, tempScore.c_str(), colorP1);
	}else{
		//place the player 1 score into a surface
		scoreSurface = TTF_RenderText_Solid(font, tempScore.c_str(), colorP2);

	}
	//create the plyer score texture
	scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

	//get the width and height of the teuxtre
	SDL_QueryTexture(scoreTexture, NULL, NULL, &scorePos.w, &scorePos.h);

	//free surface
	SDL_FreeSurface(scoreSurface);

	//set old score
	oldScore = playerScore;

}

//[player update method
void Player::Update(float deltaTime, SDL_Renderer *renderer){

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
	//should score be updated?
	if( playerScore != oldScore ){

		UpdateScore(renderer);

	}

	//should lives be updated?
		if( playerLives != oldLives){

			UpdateLives(renderer);

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

	//draw the okayer score
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scorePos);

	//draw the okayer score
	SDL_RenderCopy(renderer, livesTexture, NULL, &livesPos);
}

Player::~Player(){
	SDL_DestroyTexture(texture);
}
