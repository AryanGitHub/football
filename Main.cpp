#include <iostream>
#include "Map.h"
#include "FootballMap.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
using namespace std;

SDL_Texture *LoadTexture (std::string filePath, SDL_Renderer *renderTarget)
{
	SDL_Texture *texture = nullptr;
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

	return texture;
}

int main(int argc, char *argv[])
{
	// Initializing and loading variables
	SDL_Window *window = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	int currentTime = 0; 
	int prevTime = 0; 
	float delta = 0.0f;
	const Uint8 *keyState;
	SDL_Rect camerRect = { 0, 0, 1365, 822 };
	FootballMap fm (60 , 10 , 1200 , 770, 300);
	int levelWidth, levelHeight;

	SDL_Init(SDL_INIT_VIDEO);
	string resourcesFolderPath = "../res/";
	string playerSpriteImageFilePath = resourcesFolderPath + "sprite.png";
	string footballFieldImageFilePath = resourcesFolderPath + "footballField.png";
	string footballImageFilePath  = resourcesFolderPath + "ball.png";
	

	int data = 10;
	window = SDL_CreateWindow("FootBall Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1365, 822, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Player player1(renderTarget, playerSpriteImageFilePath.c_str(), 550, 395, 3, 4);
	Player player2(renderTarget, playerSpriteImageFilePath.c_str(), 780, 395, 3, 4);

	Ball ball(renderTarget, (550+780)/2 , 395 ,12, footballImageFilePath.c_str());
	
	SDL_Texture *texture = LoadTexture(footballFieldImageFilePath.c_str(), renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);



	bool isRunning = true; 
	SDL_Event ev;

	while(isRunning)
	{
		prevTime = currentTime; 
		currentTime = SDL_GetTicks(); 
		delta = (currentTime - prevTime) / 1000.0f;
		while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			if(ev.type == SDL_QUIT)
				isRunning = false;
		}

		keyState = SDL_GetKeyboardState(NULL);
		if (ball.isLeftGoal(fm))  {cout << "left goal!" << endl;

			ball.positionRect.x= 665;
			ball.positionRect.y= 395;
			ball.moveSpeedX = 0;
			ball.moveSpeedY = 0;
			player1.positionRect.x= 550;
			player1.positionRect.y= 395;
			player2.positionRect.x=780;
			player2.positionRect.y= 395;

			}
		else if (ball.isRightGoal(fm))  {cout << "right goal!" << endl;
			ball.positionRect.x= 665;
			ball.positionRect.y= 395;
			ball.moveSpeedX = 0;
			ball.moveSpeedY = 0;
			player1.positionRect.x= 550;
			player1.positionRect.y= 395;
			player2.positionRect.x=780;
			player2.positionRect.y= 395;}
		
        ball.isIntersectWithPlayer(player1 , keyState);
		ball.isIntersectWithPlayer(player2 , keyState);
		
		ball.update(delta);
		ball.isIntersectWithWall(fm);
		player1.Update(delta, keyState); 
		player2.Update(delta, keyState);
		


		camerRect.x = player1.GetOriginX() - 682; 
		camerRect.y = player1.GetOriginY() - 411;

		if(camerRect.x < 0)
			camerRect.x = 0; 
		if(camerRect.y < 0)
			camerRect.y = 0;

		if(camerRect.x + camerRect.w >= levelWidth)
			camerRect.x = levelWidth - 1365; 
		if(camerRect.y + camerRect.h >= levelHeight)
			camerRect.y = levelHeight - 822;


		player1.IntersectsWith(player2);

		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, &camerRect, NULL);
		player1.Draw(renderTarget, camerRect); 
		player2.Draw(renderTarget, camerRect);
		ball.draw(renderTarget);
		SDL_RenderPresent(renderTarget);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);

	texture = nullptr;

	window = nullptr;
	renderTarget = nullptr;

	IMG_Quit();
	SDL_Quit();

	return 0;
}