// Example program:
// Using SDL2 to create an application window
#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#endif



#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#endif

#if defined(_WIN32) || (_WIN64)
#include <direct.h>
#define get cwd _getcwd
#endif

#if defined(__linux__)

#include <unistd.h>

#endif

#include <stdio.h>
#include <iostream>

using namespace std;

int bkgdSpeed=100;

SDL_Rect bkgd1Pos, bkgd2Pos;

float BG1pos_X = 0, BG1pos_Y = 0;
float BG2pos_X = 0, BG2pos_Y = -768;


//code for frame rate independence
float deltaTime = 0.0;
int thisTime=0;
int lastTime=0;

//move the background
void UpdateBackground(float deltaTime){

	//Update

	//Update background 1




	BG1pos_Y+=(bkgdSpeed*1)*deltaTime;

	//set the new bkgd1 position
	bkgd1Pos.y=(int)(BG1pos_Y+0.5f);

	//reset when of the bottom of the screen
	if(bkgd1Pos.y >= 768){

		bkgd1Pos.y = -768;

		BG1pos_Y= bkgd1Pos.y;

	}
	//Update background 2
	BG2pos_Y+=(bkgdSpeed*1)*deltaTime;

	//set the new bkgd1 position
	bkgd2Pos.y=(int)(BG2pos_Y+0.5f);

	//reset when of the bottom of the screen
	if(bkgd2Pos.y >= 768){

		bkgd2Pos.y = -768;

		BG2pos_Y= bkgd2Pos.y;

	}

}

//*************NEW**************
//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//joystick direction vars
float xDir, yDir;

//cursor float vars for movement
float pos_X, pos_Y;

//creat SDL recrangle for the player graphic
SDL_Rect cursorPos, activePos;

int cursorSpeed=400;

void moveCursor(const SDL_ControllerAxisEvent event){

	if(event.which ==0){
		if(event.axis ==0){
			if(event.value < -JOYSTICK_DEAD_ZONE){
				xDir= -1.0f;
			}else if(event.value > JOYSTICK_DEAD_ZONE){
				xDir = 1.0f;
			}else{
				xDir = 0.0f;
			}
		}
		if(event.axis == 1){
			if(event.value < -JOYSTICK_DEAD_ZONE){
				yDir = -1.0f;
			}else if(event.value>JOYSTICK_DEAD_ZONE){
				yDir = 1.0f;
			}else {
				yDir = 0.0f;
			}
		}
	}
}

void UpdateCursor(float deltaTime){
	pos_X += (cursorSpeed * xDir) *deltaTime;
	pos_Y += (cursorSpeed * xDir) *deltaTime;

	cursorPos.x = (int) (pos_X+0.5f);
	cursorPos.y = (int) (pos_Y+0.5f);

	activePos.x = cursorPos.x;
	activePos.y = cursorPos.y;

	if(cursorPos.x<0){
		cursorPos.x = 0;
		pos_X = cursorPos.x;
	}
	if(cursorPos.x > 1024 - cursorPos.w){
		cursorPos.x = 1024 - cursorPos.w;
		pos_X = cursorPos.x;
	}
	if(cursorPos.y<0){
		cursorPos.y = 0;
		pos_Y=cursorPos.y;
	}
	if(cursorPos.y > 768 - cursorPos.h){
		cursorPos.y = 768 - cursorPos.h;
		pos_Y=cursorPos.y;
	}


}


//variables for all menu button over
bool players1Over= false, players2Over= false, instructionsOver= false,
		quitOver= false, menuOver=false, playOver=false;

//new

//new

//class header includes
#include "player.h"
#include "enemy.h"
#include <vector>
#include<stdlib.h>
#include<time.h>

//variable to hold the list of enemies
vector<Enemy> enemyList;

int main(int argc, char* argv[]) {

	//initialize random speed
	srand (time(NULL));

#if defined(__APPLE__)
	cout << "Running on Apple" << endl;
	//get the current working directory
	string s_cwd(getcwd(NULL, 0));
	//create a string linking to the mac's images folder
	string s_cwd_images = s_cwd + "/Resources/Images/";

	//string currentWorkingDirectory(getcwd(NULL,0));
	//string images_dir=currentWorkingDirectory+"Resources/Images/";

	cout << s_cwd_images << endl;

	string s_cwd_audio = s_cwd + "/Resources/Audio/";

#endif

#if defined(__linux__)
	cout <<"Running on Linux" <<endl;
	cout <<" Added on Linux :)"<<endl;

	string s_cwd(getcwd(NULL, 0));
	//create a string linking to the mac's images folder
	string s_cwd_images = s_cwd + "/Resources/Images/";
	string s_cwd_audio = s_cwd + "/Resources/Audio/";

#endif

#if defined(_WIN32) || (_WIN64)
	cout <<"Running on Windows" <<endl;
	string s_cwd(getcwd(NULL, 0));
	string s_cwd_images = s_cwd + "\\Resources\\Images\\";
	string s_cwd_audio = s_cwd + "\\Resources\\Audio\\";

#endif

	SDL_Window *window;                    // Declare a pointer

	SDL_Init (SDL_INIT_EVERYTHING);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow("An SDL2 window",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			1024,                               // width, in pixels
			768,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	//declare the renderer
	SDL_Renderer*renderer = NULL;

	//create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);






	//***********Create Background********


	string BKGDpath = s_cwd_images + "/temp.png";

	SDL_Surface*surface = IMG_Load(BKGDpath.c_str());

	//create a SDL texture
	SDL_Texture*bkgd1;

	//place surgace info into the texture bkgd1
	bkgd1=SDL_CreateTextureFromSurface(renderer, surface);

	//create a SDL texture
	SDL_Texture*bkgd2;

	//place surgace info into the texture bkgd1
	bkgd2=SDL_CreateTextureFromSurface(renderer, surface);

	//free the SDL surface
	SDL_FreeSurface(surface);

	//create the SDL_Recrtangle for texture


	//set the X, Y, W, and H for the Rectabngle
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 768;

	//set the X, Y, W, and H for the Rectabngle
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 768;

	//set speed for background
	//int bkgdSpeed = 100;

	//set temp variables to hold movement
	//float BG1pos_X=0, BG1pos_Y=0;

	//float BG2pos_X=0, BG2pos_Y=-768;
	//**************CREATE BACKGROUNDS- END******************

	//**************CREATE MENU BUtTONS START****************

	//******TITLE START ******
	string Titlepath = s_cwd_images + "/title.png";

	surface = IMG_Load(Titlepath.c_str());

	//create a SDL texture
	SDL_Texture*title;

	//place surgace info into the texture bkgd1
	title=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect titlePos;
	//set the X, Y, W, and H for the Rectabngle
	titlePos.x = 42;
	titlePos.y = 55;
	titlePos.w = 138;
	titlePos.h = 53;
	//*****TITLE END********
	//******1P START ******
	string Ppath = s_cwd_images + "/player1.png";

	surface = IMG_Load(Ppath.c_str());

	//create a SDL texture
	SDL_Texture*players1N;

	//place surgace info into the texture bkgd1
	players1N=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	string Pdownpath = s_cwd_images + "/player1down.png";

	surface = IMG_Load(Pdownpath.c_str());

	//create a SDL texture
	SDL_Texture*players1down;

	//place surgace info into the texture bkgd1
	players1down=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect players1NPos;
	//set the X, Y, W, and H for the Rectabngle
	players1NPos.x = 42;
	players1NPos.y = 166;
	players1NPos.w = 271;
	players1NPos.h = 67 ;
	//***************1p END*********

	//**************2P START ******
	string Ptwopath = s_cwd_images + "/player2.png";

	surface = IMG_Load(Ptwopath.c_str());

	//create a SDL texture
	SDL_Texture*players2N;

	//place surgace info into the texture bkgd1
	players2N=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	string Ptwodownpath = s_cwd_images + "/player2down.png";

	surface = IMG_Load(Ptwodownpath.c_str());

	//create a SDL texture
	SDL_Texture*players2down;

	//place surgace info into the texture bkgd1
	players2down=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect players2NPos;
	//set the X, Y, W, and H for the Rectabngle
	players2NPos.x = 42;
	players2NPos.y = 275;
	players2NPos.w = 276;
	players2NPos.h = 67 ;
	//***************1p END*********


	//*************INSTRUCTIONS START ******
	string Instpath = s_cwd_images + "/instructions.png";

	surface = IMG_Load(Instpath.c_str());

	//create a SDL texture
	SDL_Texture*instructN;

	//place surgace info into the texture bkgd1
	instructN=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	string Instdownpath = s_cwd_images + "/instructionsdown.png";

	surface = IMG_Load(Instdownpath.c_str());

	//create a SDL texture
	SDL_Texture*instructdown;

	//place surgace info into the texture bkgd1
	instructdown=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect instructNPos;
	//set the X, Y, W, and H for the Rectabngle
	instructNPos.x = 42;
	instructNPos.y = 384;
	instructNPos.w = 410;
	instructNPos.h = 53 ;
	//***************INSTRUCTIONS END*********

	//*************Quit START ******
	string Quitpath = s_cwd_images + "/quit.png";

	surface = IMG_Load(Quitpath.c_str());

	//create a SDL texture
	SDL_Texture*quitN;

	//place surgace info into the texture bkgd1
	quitN=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	string Quitdownpath = s_cwd_images + "/quitdown.png";

	surface = IMG_Load(Quitdownpath.c_str());

	//create a SDL texture
	SDL_Texture*quitdown;

	//place surgace info into the texture bkgd1
	quitdown=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect quitNPos;
	//set the X, Y, W, and H for the Rectabngle
	quitNPos.x = 42;
	quitNPos.y = 493;
	quitNPos.w = 143;
	quitNPos.h = 60 ;
	//***************quit END*********

	//******INSTRUTCTIONS MENU START ******
	string instTitlepath = s_cwd_images + "/instructtext.png";

	surface = IMG_Load(instTitlepath.c_str());

	//create a SDL texture
	SDL_Texture*instructionsText;

	//place surgace info into the texture bkgd1
	instructionsText=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect instructionsTextPos;
	//set the X, Y, W, and H for the Rectabngle
	instructionsTextPos.x = 88;
	instructionsTextPos.y = 166;
	instructionsTextPos.w = 711;
	instructionsTextPos.h = 486;
	//***** INSTRUCTINOS TITLE END********
	//******INSTRUTCTIONS MENU START ******
	string menupath = s_cwd_images + "/menu.png";

	surface = IMG_Load(menupath.c_str());

	//create a SDL texture
	SDL_Texture*menuN;

	//place surgace info into the texture bkgd1
	menuN=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	string menudpath = s_cwd_images + "/menudown.png";

	surface = IMG_Load(menudpath.c_str());

	//create a SDL texture
	SDL_Texture*menuD;

	//place surgace info into the texture bkgd1
	menuD=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect menuNPos;
	//set the X, Y, W, and H for the Rectabngle
	menuNPos.x = 737;
	menuNPos.y = 650;
	menuNPos.w = 187;
	menuNPos.h = 53;
	SDL_Rect menuDPos;
	//set the X, Y, W, and H for the Rectabngle
	menuDPos.x = 737;
	menuDPos.y = 650;
	menuDPos.w = 187;
	menuDPos.h = 53;
	//***** INSTRUCTINOS TITLE END********





	//******WIN GRAPHICS MENU START ******
	string Winpath = s_cwd_images + "/win.png";

	surface = IMG_Load(Winpath.c_str());

	//create a SDL texture
	SDL_Texture*winText;

	//place surgace info into the texture bkgd1
	winText=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect winTextPos;
	//set the X, Y, W, and H for the Rectabngle
	winTextPos.x = 150;
	winTextPos.y = 150;
	winTextPos.w = 268;
	winTextPos.h = 68;
	//***** win END********
	//******play again MENU START ******
	string papath = s_cwd_images + "/playagain.png";

	surface = IMG_Load(papath.c_str());

	//create a SDL texture
	SDL_Texture*pAgain;

	//place surgace info into the texture bkgd1
	pAgain=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	string padpath = s_cwd_images + "/playagaindown.png";

	surface = IMG_Load(padpath.c_str());

	//create a SDL texture
	SDL_Texture*pAgaindown;

	//place surgace info into the texture bkgd1
	pAgaindown=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect pAgainPos;
	//set the X, Y, W, and H for the Rectabngle
	pAgainPos.x = 150;
	pAgainPos.y = 275;
	pAgainPos.w = 292;
	pAgainPos.h = 53;
	SDL_Rect pAgaindownPos;
	//set the X, Y, W, and H for the Rectabngle
	pAgaindownPos.x = 150;
	pAgaindownPos.y = 275;
	pAgaindownPos.w = 292;
	pAgaindownPos.h = 53;
	//***** INSTRUCTINOS TITLE END********


	//****** LOSE MENU START ******
	string Losepath = s_cwd_images + "/lose.png";

	surface = IMG_Load(Losepath.c_str());

	//create a SDL texture
	SDL_Texture*loseText;

	//place surgace info into the texture bkgd1
	loseText=SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect loseTextPos;
	//set the X, Y, W, and H for the Rectabngle
	loseTextPos.x = 150;
	loseTextPos.y = 150;
	loseTextPos.w = 268;
	loseTextPos.h = 68;
	//***** LOSE END********

	//***********CREATE CURSOR***********

	//create cursor
	string CURSORpath = s_cwd_images + "/cursor2.png";

	//create a SDL surfgace tohold the cursor image
	surface = IMG_Load(CURSORpath.c_str());

	//create a SDL texture -cursor
	SDL_Texture*cursor;

	//place surface  for cursor
	cursor=SDL_CreateTextureFromSurface(renderer,surface);

	//SDL_Rect cursorPos, activePos;

	cursorPos.x = 0;
	cursorPos.y = 0;
	cursorPos.w = 32;
	cursorPos.h = 32;

	cursorPos.x = 10;
	cursorPos.y = 10;
	cursorPos.w = 32;
	cursorPos.h = 32;

	//var for cursor speed
	//int cursorSpeed=400;

	//****************CREATE CURSOR END*******************

	/*
	 //The surface contained by the window
	 SDL_Surface* screenSurface = NULL;

	 //Get window surface
	 screenSurface = SDL_GetWindowSurface( window );

	 //Fill the surface white
	 SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 42, 254 ) );

	 //Update the surface
	 SDL_UpdateWindowSurface( window );
	 */


	//***Turn on Game Controller Events*****
	SDL_GameControllerEventState (SDL_ENABLE);


	//****set up Game Controller 1 Variable*****
	SDL_GameController* gGameController0 = NULL;

	//*****open Came Controller1*****
	gGameController0 = SDL_GameControllerOpen(0);

	//****set up Game Controller 2 Variable*****
	SDL_GameController* gGameController1 = NULL;

	//*****open Came Controller2*****
	gGameController1 = SDL_GameControllerOpen(1);



	//*****SDL Event to handle input****
	SDL_Event event;

	//set up variables for the game states
	enum GameState {
		MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE
	};

	//set up the initial state
	GameState gameState = MENU;

	//boolean values to control movement through the states
	bool menu, instructions, players1, players2, win, lose, quit;



	//========================AUDIO===============================

	//open audio channel
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//load a music file
	Mix_Music *bgm = Mix_LoadMUS((s_cwd_audio + "Vir_Nocturna_-_Meta.mp3").c_str());

	//if music file isnt' playing, play it
	if(!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	//set up sound effect chunk for the button over state
	Mix_Chunk *overSound = Mix_LoadWAV((s_cwd_audio + "over.wav").c_str());

	//set up sound effect Chunk for the button pressed state
	Mix_Chunk *pressedSound = Mix_LoadWAV((s_cwd_audio + "down.wav").c_str());

	//bool value to control the other sound effect and the buttons
	bool alreadyOver =false;

	//================ END AUDIO=========================

	//CREATE PLAYER START**************************


		Player player1 = Player(renderer, 0, s_cwd_images.c_str(), s_cwd_audio.c_str(), 250.0, 500.0);
		Player player2 = Player(renderer, 2, s_cwd_images.c_str(), s_cwd_audio.c_str(), 750.0, 500.0);

		//Create player End*************



	//the window is open: could enter program loop here(see SDL_PollEvent())
	while (!quit) {
		switch (gameState) {
		////////////////CASE ONE//////////////
		case MENU:

			alreadyOver= false;

			menu = true;
/*
			cout << "The Game State Menu" << endl;
			cout << "Press the A Button for instructions" << endl;
			cout << "Press the B Button for 1P Game" << endl;
			cout << "PRess the X Button for 2P Game" << endl;
			cout << "PRess the Y Button for Quit Game" << endl;
			cout << endl;
			*/

			while (menu) {

				//set up frame rate for the section or Case
				thisTime=SDL_GetTicks();
				deltaTime=(float)(thisTime-lastTime)/1000;
				lastTime = thisTime;


				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						menu = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0) {

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								if(players1Over){
									//play the otver sound- plays fine through levels but must pause/ delay for quit
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = PLAYERS1;
									players1Over=false;

								}
								if (players2Over) {
									//play the otver sound- plays fine through levels but must pause/ delay for quit
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = PLAYERS2;
									players2Over=false;

								}
								if (instructionsOver) {
									//play the otver sound- plays fine through levels but must pause/ delay for quit
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = INSTRUCTIONS;
									instructionsOver=false;

								}
								if (quitOver) {
									//play the otver sound- plays fine through levels but must pause/ delay for quit
									Mix_PlayChannel(-1, pressedSound, 0);
									SDL_Delay(200);
									menu = false;
									quit = true;
									quitOver=false;
								}

							}
						}
						break;
						//***************** MEW ***************
					case SDL_CONTROLLERAXISMOTION:

						moveCursor(event.caxis);
						break;

					}
				}

				//Update
				UpdateBackground(deltaTime);

				UpdateCursor(deltaTime);

				players1Over=SDL_HasIntersection(&activePos, &players1NPos);
				players2Over=SDL_HasIntersection(&activePos, &players2NPos);
				instructionsOver=SDL_HasIntersection(&activePos, &instructNPos);
				quitOver = SDL_HasIntersection(&activePos, &quitNPos);

				//if the curosr is over a button play the over sound

				if(players1Over || players2Over || instructionsOver || quitOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver= true;
					}

				}

				//if the cursor is not over any button, reset the alreadyOver var
				if(!players1Over && !players2 && !instructionsOver && !quitOver){
					alreadyOver = false;
				}


				//start Drawing

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);
				//Draw the title image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);

				//*************************NEW*******************

				//Draw the players1 image
				if(players1Over){
					SDL_RenderCopy(renderer, players1down, NULL, &players1NPos);
				}else{
					SDL_RenderCopy(renderer, players1N, NULL, &players1NPos);
				}

				//Draw the players2 image
				if(players2Over){
					SDL_RenderCopy(renderer, players2down, NULL, &players2NPos);
				}else{
					SDL_RenderCopy(renderer, players2N, NULL, &players2NPos);
				}

				//draw intrustionc
				if(instructionsOver){
					SDL_RenderCopy(renderer, instructdown, NULL, &instructNPos);
				}else{
					SDL_RenderCopy(renderer, instructN, NULL, &instructNPos);
				}

				//draw quit
				if(quitOver){
					SDL_RenderCopy(renderer, quitdown, NULL, &quitNPos);
				}else{
					SDL_RenderCopy(renderer, quitN, NULL, &quitNPos);}

				// *****************NEW***************


				//draw cursor
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);


			}
			break; /////////END MENU MENU CASE////////////////

		case INSTRUCTIONS:

			alreadyOver= false;

			instructions = true;

			//cout << "The Game State is Instructions" << endl;
			//cout << "Press the A Button for Main Menu" << endl;

			cout << endl;

			while (instructions) {

				thisTime=SDL_GetTicks();
				deltaTime=(float)(thisTime-lastTime)/1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						menu = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0) {

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								if(menuOver){
									Mix_PlayChannel(-1, pressedSound, 0);
									instructions=false;
									gameState=MENU;
									menuOver=false;
								}

							}

						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
					}
				}
				UpdateBackground(deltaTime);
				UpdateCursor(deltaTime);

				//check for cursor intersection with menubuton
				menuOver= SDL_HasIntersection(&activePos, &menuNPos);

				if(menuOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver= true;
					}

				}

				//if the cursor is not over any button, reset the alreadyOver var
				if(!menuOver){
					alreadyOver = false;
				}

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);
				//Draw the title image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);
				//Draw the players1 image

				if(menuOver){
					SDL_RenderCopy(renderer, menuD, NULL, &menuNPos);
				}else{
					SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);
				}

				//draw cursor
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);


				//SDL Render present
				SDL_RenderPresent(renderer);

			}
			break; /////////END INSTRUCTINOS CASE////////////////

		case PLAYERS1:

			//alreadyOver= false;
			enemyList.clear();

			players1 = true;

			//create the enemy pool -6
			for(int i =0; i<6; i++){

				//creat the enemy
				Enemy tmpEnemy(renderer, s_cwd_images);

				// add to the enemylist
				enemyList.push_back(tmpEnemy);

			}
			/*cout << "The Game State is 1P" << endl;
			cout << "Press the A Button for WIN" << endl;
			cout << "Press the A Button for LOSE" << endl;
			cout << endl;*/

			while (players1) {

				thisTime=SDL_GetTicks();
				deltaTime=(float)(thisTime-lastTime)/1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						players1 = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0) {

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								//Mix_PlayChannel(-1, overSound, 0);
								players1 = false;
								gameState = WIN;

							}

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {
								//Mix_PlayChannel(-1, overSound, 0);
								players1 = false;
								gameState = LOSE;

							}
						}

						//send button info to player one
						player1.OnControllerButton(event.cbutton);

						break;

					case SDL_CONTROLLERAXISMOTION:
						player1.OnControllerAxis(event.caxis);
						break;
					}
				}
				UpdateBackground(deltaTime);

				player1.Update(deltaTime, renderer);

				//update the enemys
				for(int i =0; i < enemyList.size(); i++){

					//update enemy
					enemyList[i].Update(deltaTime);
				}

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//update the enemys
				for(int i =0; i < enemyList.size(); i++){

					//update enemy
					enemyList[i].Draw(renderer);
				}
				//Draw the title image
				//SDL_RenderCopy(renderer, players1N, NULL, &players1NPos);
				//draw cursor
				//SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//draw Player1
				player1.Draw(renderer);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break; /////////END P1 CASE////////////////

		case PLAYERS2:

			//clear out any old enemies
			enemyList.clear();

			//alreadyOver= false;

			players2 = true;

			//create the enemy pool -6
			for(int i =0; i<12; i++){

				//creat the enemy
				Enemy tmpEnemy(renderer, s_cwd_images);

				// add to the enemylist
				enemyList.push_back(tmpEnemy);

			}
			/*cout << "The Game State is 2P" << endl;
			cout << "Press the A Button for WIN" << endl;
			cout << "Press the A Button for LOSE" << endl;
			cout << endl;*/

			while (players2) {

				thisTime=SDL_GetTicks();
				deltaTime=(float)(thisTime-lastTime)/1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						players2 = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0  || event.cdevice.which == 1) {

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								//Mix_PlayChannel(-1, overSound, 0);
								players2 = false;
								gameState = WIN;

							}

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {
								//Mix_PlayChannel(-1, overSound, 0);
								players2 = false;
								gameState = LOSE;

							}
						}
						//send button info to player one
						player1.OnControllerButton(event.cbutton);
						//send button info to player one
						player2.OnControllerButton(event.cbutton);

						break;

					case SDL_CONTROLLERAXISMOTION:
						player2.OnControllerAxis(event.caxis);
						break;
					}
				}
				UpdateBackground(deltaTime);

				player1.Update(deltaTime, renderer);
				player2.Update(deltaTime, renderer);

				//create the enemy pool -6
				for(int i =0; i< enemyList.size(); i++){

					// add to the enemylist
					enemyList[i].Update(deltaTime);
				}

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//draw the enemies
				for(int i = 0; i <enemyList.size(); i++)
				{
					//update enemy
					enemyList[i].Draw(renderer);
				}

				//Draw the title image
				//SDL_RenderCopy(renderer, players2N, NULL, &players2NPos);
				//Draw the players1 image
				//SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);

				player1.Draw(renderer);
				player2.Draw(renderer);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break; /////////END P2 CASE////////////////

		case WIN:

			alreadyOver= false;

			win = true;

			cout << "The Game State is WIN" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << "Press the A Button for Replay" << endl;
			cout << endl;

			while (win) {

				thisTime=SDL_GetTicks();
				deltaTime=(float)(thisTime-lastTime)/1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						win = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0) {
							if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A){

								if (menuOver) {
									Mix_PlayChannel(-1, overSound, 0);
									win = false;
									gameState = MENU;
									menuOver=false;

								}

								if (playOver) {
									Mix_PlayChannel(-1, overSound, 0);
									win = false;
									gameState = PLAYERS1;
									playOver=false;

								}
							}

						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);

						break;
					}
				}
				UpdateBackground(deltaTime);
				UpdateCursor(deltaTime);

				menuOver= SDL_HasIntersection(&activePos,&menuNPos);
				playOver=SDL_HasIntersection(&activePos, &pAgainPos);

				if(menuOver || playOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver= true;
					}

				}

				//if the cursor is not over any button, reset the alreadyOver var
				if(!menuOver && !playOver){
					alreadyOver = false;
				}

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the title image
				SDL_RenderCopy(renderer, winText, NULL, &winTextPos);

				if(menuOver){
					SDL_RenderCopy(renderer, menuD, NULL, &menuNPos);
				}else{
					SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);
				}

				//Draw the playagain image
				if(playOver){
					SDL_RenderCopy(renderer, pAgaindown, NULL, &pAgainPos);
				}else{
					SDL_RenderCopy(renderer, pAgain, NULL, &pAgainPos);
				};

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break; /////////WIN CASE////////////////

		case LOSE:

			alreadyOver= false;

			lose = true;

			cout << "The Game State is LOSE" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << "Press the A Button for Replay Game" << endl;
			cout << endl;

			while (lose) {

				thisTime=SDL_GetTicks();
				deltaTime=(float)(thisTime-lastTime)/1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in window
					if (event.type == SDL_QUIT) {
						quit = true;
						lose = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0) {

							if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A){

								if (menuOver) {
									Mix_PlayChannel(-1, overSound, 0);
									lose = false;
									gameState = MENU;
									menuOver=false;

								}

								if (playOver) {
									Mix_PlayChannel(-1, overSound, 0);
									lose = false;
									gameState = PLAYERS1;
									playOver=false;

								}
							}


						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
					}
				}
				UpdateBackground(deltaTime);
				UpdateCursor(deltaTime);

				menuOver= SDL_HasIntersection(&activePos,&menuNPos);
				playOver=SDL_HasIntersection(&activePos, &pAgainPos);

				if(menuOver || playOver){
					if(alreadyOver == false){
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver= true;
					}

				}

				//if the cursor is not over any button, reset the alreadyOver var
				if(!menuOver && !playOver){
					alreadyOver = false;
				}

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the title image
				SDL_RenderCopy(renderer, loseText, NULL, &loseTextPos);

				if(menuOver){
					SDL_RenderCopy(renderer, menuD, NULL, &menuNPos);
				}else{
					SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);
				}

				//Draw the playagain image
				if(playOver){
					SDL_RenderCopy(renderer, pAgaindown, NULL, &pAgainPos);
				}else{
					SDL_RenderCopy(renderer, pAgain, NULL, &pAgainPos);
				};

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break; /////////END LOSE CASE////////////////

		}
	}

	// The window is open: could enter program loop here (see SDL_PollEvent())

	SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
