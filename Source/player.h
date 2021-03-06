// Example program:
// Using SDL2 to create an application window
#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#endif

//#if defined(__linux__)
//#include <unistd.h>
//#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#endif

#include <stdio.h>
#include <iostream>
#include <sstream>

using namespace std;

#include <vector>
#include "bullet.h"


class Player{

public:

	//player score and lives vars
	int playerScore, oldScore, playerLives, oldLives;

	//variable for what font t use
	TTF_Font *font;

	//font color var
	SDL_Color colorP1 = {0, 255, 0, 255};

	//font color var
	SDL_Color colorP2 = {0, 0, 255, 255};

	//surface for player score andp layer lives
	SDL_Surface *scoreSurface, *livesSurface;

	//textures for the player score and player lives
	SDL_Texture *scoreTexture, *livesTexture;

	//SDL_Rects for the player score and lives textures
	SDL_Rect scorePos, livesPos;

	//strings to hold the temp vlaues of player lives and player score
	string tempScore, tempLives;


	//audio sound effect - CHUNK
	Mix_Chunk *laser;

	//variable to hold the list of bullets
	vector<Bullet> bulletList;

	//string to hold the path to players texture
	string playerPath;

	//Integer for the players number
	int playerNum;

	//players surgce to load png into
	SDL_Surface *surface;

	//players texture to hold img
	SDL_Texture *texture;

	//players SDL_Rect for the x,y,w adn h of texure
	SDL_Rect posRect;

	//floats to hold the joystick acis (-1 to 0 to 1)
	float xDir;
	float yDir;

	//float for players spewed
	float speed;

	//float for the players position to avoid precision loss
	float pos_X, pos_Y;

	//players creation method using passed in values for renderer plater number path to the texure
	//staring position x starting position y
	Player(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y);

	//method to allo the plaer to mocve via joystick acis
	void OnControllerAxis(const SDL_ControllerAxisEvent event);

	//method to allow the playeer interect with joystick buttons
	void OnControllerButton(const SDL_ControllerButtonEvent event);

	//update the lpayer sing the passed in deltatime
	void Update(float deltaTime, SDL_Renderer *renderer);

	//draw he players main passed in renderer
	void Draw(SDL_Renderer *renderer);

	//Players destruction method
	~Player();

	//update score method
	void UpdateScore(SDL_Renderer *renderer);

	//update score method
	void UpdateLives(SDL_Renderer *renderer);

private:
	void CreateBullet();

};
