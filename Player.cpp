#include<SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <iostream>
#include<cmath>
#include <Player.h>

Player::Player(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	SDL_Surface *surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x; 
	positionRect.y = y;

	textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w; 
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2; 
	originY = frameHeight / 2;

	radius = 5;

	isActive = false; 

	static int playerNumber = 0; 
	playerNumber++;

	if(playerNumber == 1)
	{
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
	}
	else
	{
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
	}

	moveSpeed = 200.0f;
}


Player::~Player()
{
	SDL_DestroyTexture(texture);
}

void Player::Update(float delta, const Uint8 *keyState)
{
		isActive = true;

	if(keyState[keys[0]] && keyState[keys[2]] && positionRect.y >0 && positionRect.x>60){
		positionRect.y -= moveSpeed * delta/sqrt(2); 
		positionRect.x -= moveSpeed * delta/sqrt(2); 
		cropRect.y = frameHeight * 3;
	}
	else if(keyState[keys[0]] && keyState[keys[3]]&& positionRect.y >0 && positionRect.x<1260){
			positionRect.y -= moveSpeed * delta/sqrt(2); 
			positionRect.x += moveSpeed * delta; 
			cropRect.y = frameHeight * 3;
	}
	else if(keyState[keys[1]] && keyState[keys[2]]&& positionRect.y <770 && positionRect.x>60){
			positionRect.y += moveSpeed * delta; 
			positionRect.x -= moveSpeed * delta/sqrt(2); 
			cropRect.y = 0;
	}
	else if(keyState[keys[1]] && keyState[keys[3]] && positionRect.y <770 && positionRect.x<1260){
			positionRect.y += moveSpeed * delta; 
			positionRect.x += moveSpeed * delta; 
			cropRect.y = 0;
	}
	else if(keyState[keys[0]] && positionRect.y >0)
	{
		positionRect.y -= (moveSpeed * delta*sqrt(1.5)); 
		cropRect.y = frameHeight * 3;
	}
	else if(keyState[keys[1]]&& positionRect.y <770)
	{
		positionRect.y += (moveSpeed * delta*sqrt(1.5)); 
		cropRect.y = 0;
	}
	else if(keyState[keys[2]]&& positionRect.x >60)
	{
		positionRect.x -= (moveSpeed * delta*sqrt(1.5)); 
		cropRect.y = frameHeight;
	}
	else if(keyState[keys[3]]&& positionRect.x <1260)
	{
		positionRect.x += (moveSpeed * delta*sqrt(1.5)); 
		cropRect.y = frameHeight * 2;
	}
	else 
		isActive = false;
	if(isActive)
	{
		frameCounter += delta; 

		if(frameCounter >= 0.25f)
		{
			frameCounter = 0; 
			cropRect.x += frameWidth; 
			if(cropRect.x >= textureWidth)
				cropRect.x = 0; 
		}
	}
	else
	{
		frameCounter = 0;
		cropRect.x = frameWidth;
	}
}

void Player::Draw(SDL_Renderer *renderTarget, SDL_Rect cameraRect)
{
	SDL_Rect drawingRect = { positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h };
	SDL_RenderCopy(renderTarget, texture, &cropRect, &drawingRect);
}

bool Player::IntersectsWith(Player &p)
{
	if(sqrt(pow(GetOriginX() - p.GetOriginX(), 2) + pow(GetOriginY() - p.GetOriginY(), 2)) >= radius + p.GetRadius())
	{
		SDL_SetTextureColorMod(texture, 255, 255, 255);
		return false;
	}
	SDL_SetTextureColorMod(texture, 255, 0, 0);
	return true;
}

int Player::GetOriginX() { return positionRect.x + originX; }
int Player::GetOriginY() { return positionRect.y + originY; }
int Player::GetRadius()  { return radius;  }
