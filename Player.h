#pragma once

#include<SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <iostream>
#include<cmath>
class Player
{
private: 
	SDL_Rect cropRect;
	SDL_Texture *texture;
	
	float frameCounter; 
	int frameWidth, frameHeight;
	int textureWidth;
	bool isActive; 
	
	int originX, originY;
	int radius;
public:
	Player(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	void Update(float delta, const Uint8 *keyState); 
	void Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect); 
	bool IntersectsWith(Player &p);

	SDL_Rect positionRect;
	SDL_Scancode keys[4];
	float moveSpeed;
	
	int GetOriginX();
	int GetOriginY();
	int GetRadius();
};