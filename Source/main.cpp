// Example program:
// Using SDL2 to create an application window
#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#endif

#if defined(__linux__)

#include <unistd.h>

#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"

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
void UpdateBackground(){

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


int main(int argc, char* argv[]) {

#if defined(__APPLE__)
	cout << "Running on Apple" << endl;
	//get the current working directory
	string s_cwd(getcwd(NULL, 0));
	//create a string linking to the mac's images folder
	string s_cwd_images = s_cwd + "/Resources/Images/";

	cout << s_cwd_images << endl;

#endif

#if defined(__linux__)
	cout <<"Running on Linux" <<endl;
	cout <<" Added on Linux :)"<<endl;

	string s_cwd(getcwd(NULL, 0));
		//create a string linking to the mac's images folder
		string s_cwd_images = s_cwd + "/Resources/Images/";

#endif

#if defined(_WIN32) || (_WIN64)
	cout <<"Running on Windows" <<endl;

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

	SDL_Rect cursorPos, activePos;

	cursorPos.x = 0;
	cursorPos.y = 0;
	cursorPos.w = 32;
	cursorPos.h = 32;

	cursorPos.x = 32;
	cursorPos.y = 32;
	cursorPos.w = 32;
	cursorPos.h = 32;

	//var for cursor speed
	int cursorSpeed=400;

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

	//****set up Game Controller Variable*****
	SDL_GameController* gGameController = NULL;

	//*****open Came Controller*****
	gGameController = SDL_GameControllerOpen(0);

	//***Turn on Game Controller Events*****
	SDL_GameControllerEventState (SDL_ENABLE);

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

	//the window is open: could enter program loop here(see SDL_PollEvent())
	while (!quit) {
		switch (gameState) {
		////////////////CASE ONE//////////////
		case MENU:
			menu = true;

			cout << "The Game State Menu" << endl;
			cout << "Press the A Button for instructions" << endl;
			cout << "Press the B Button for 1P Game" << endl;
			cout << "PRess the X Button for 2P Game" << endl;
			cout << "PRess the Y Button for Quit Game" << endl;
			cout << endl;

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

								menu = false;
								gameState = INSTRUCTIONS;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {

								menu = false;
								gameState = PLAYERS1;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {

								menu = false;
								gameState = PLAYERS2;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {

								menu = false;
								quit = true;

							}
						}
						break;
					}
				}

				//Update
				UpdateBackground();

				//start Drawing

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);
				//Draw the title image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);
				//Draw the players1 image
				SDL_RenderCopy(renderer, players1N, NULL, &players1NPos);
				//SDL_RenderCopy(renderer, players1down, NULL, &players1Pos);
				//Draw the players2 image
				SDL_RenderCopy(renderer, players2N, NULL, &players2NPos);
				//SDL_RenderCopy(renderer, players2down, NULL, &players2downPos);
				SDL_RenderCopy(renderer, instructN, NULL, &instructNPos);
				//SDL_RenderCopy(renderer, instructdown, NULL, &instructdownPos);
				SDL_RenderCopy(renderer, quitN, NULL, &quitNPos);
				//SDL_RenderCopy(renderer, quitdown, NULL, &quitdownPos);


				//draw cursor
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
			break; /////////END MENU MENU CASE////////////////

		case INSTRUCTIONS:
			instructions = true;

			cout << "The Game State is Instructions" << endl;
			cout << "Press the A Button for Main Menu" << endl;

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
						instructions = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0) {

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								instructions = false;
								gameState = MENU;

							}

						}
						break;
					}
				}
				UpdateBackground();

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);
				//Draw the title image
				SDL_RenderCopy(renderer, title, NULL, &titlePos);
				//Draw the players1 image
				SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);
				//Draw the players1 image

				//draw cursor
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
			break; /////////END INSTRUCTINOS CASE////////////////

		case PLAYERS1:
			players1 = true;

			cout << "The Game State is 1P" << endl;
			cout << "Press the A Button for WIN" << endl;
			cout << "Press the A Button for LOSE" << endl;
			cout << endl;

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
									== SDL_CONTROLLER_BUTTON_A) {

								players1 = false;
								gameState = WIN;

							}

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								players1 = false;
								gameState = LOSE;

							}

						}
						break;
					}
				}
				UpdateBackground();

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);
				//Draw the title image
				SDL_RenderCopy(renderer, players1N, NULL, &players1NPos);
				//draw cursor
				SDL_RenderCopy(renderer, cursor, NULL, &cursorPos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break; /////////END P1 CASE////////////////

		case PLAYERS2:
			players2 = true;

			cout << "The Game State is 2P" << endl;
			cout << "Press the A Button for WIN" << endl;
			cout << "Press the A Button for LOSE" << endl;
			cout << endl;

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

						if (event.cdevice.which == 0) {

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								players2 = false;
								gameState = WIN;

							}

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								players2 = false;
								gameState = LOSE;

							}

						}
						break;
					}
				}
				UpdateBackground();

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);
				//Draw the title image
				SDL_RenderCopy(renderer, players2N, NULL, &players2NPos);
				//Draw the players1 image
				SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break; /////////END P2 CASE////////////////

		case WIN:
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

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								win = false;
								gameState = MENU;

							}

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								win = false;
								gameState = PLAYERS1;

							}

						}
						break;
					}
				}
				UpdateBackground();

				//Clear SDL renderer
				SDL_RenderClear(renderer);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

				//Draw the bkgd image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the title image
				SDL_RenderCopy(renderer, winText, NULL, &winTextPos);

				//Draw the menu image
				SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);

				//Draw the playagain image
				SDL_RenderCopy(renderer, pAgain, NULL, &pAgainPos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break; /////////WIN CASE////////////////

		case LOSE:
			lose = true;

			cout << "The Game State is LOSE" << endl;
			cout << "Press the A Button for Main Menu" << endl;
			cout << "Press the A Button for Replay Game" << endl;
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
						lose = false;
						break;
					}

					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0) {

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								lose = false;
								gameState = MENU;

							}

							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {

								lose = false;
								gameState = PLAYERS1;

							}

						}
						break;
					}
				}
				UpdateBackground();

								//Clear SDL renderer
								SDL_RenderClear(renderer);

								//Draw the bkgd image
								SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);

								//Draw the bkgd image
								SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

								//Draw the title image
								SDL_RenderCopy(renderer, loseText, NULL, &loseTextPos);

								//Draw the menu image
								SDL_RenderCopy(renderer, menuN, NULL, &menuNPos);

								//Draw the playagain image
								SDL_RenderCopy(renderer, pAgain, NULL, &pAgainPos);

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
