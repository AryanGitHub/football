#pragma once
#include "Player.h"
#include "FootballMap.h"
#include <SDL.h>
#include <iostream>

class Ball {

    private:
    SDL_Rect frameRect ;
    SDL_Texture *texture;
   
          // int pixel per sec^2
    int textureWidth , textureHeight;
    int radius;

    
	

    SDL_Texture *getTextureFromImage(std::string filePathLocation , SDL_Renderer *windowRenderer);
    float getDistance (int x, int y);

    
    public:
    SDL_Rect positionRect;
    float moveSpeedX,moveSpeedY;   //in pixel per sec
    float acceleration;  

    Ball (SDL_Renderer *windowRenderer , int initialPositionX, int initialPositionY , int radius, std::string ballTextureFilepath);
    
    ~Ball();
    


    void update(float deltaTime); //deltaTime is in millisec
	void draw(SDL_Renderer *renderTarget);
    void ballToPlayerCollision (Player& player);
    int getOriginX();
    int getOriginY();
    int getRadius();
    //bool isIntersecting(Player &player2);
    bool isIntersecting (int x ,int y , int radius);
    void isIntersectWithPlayer (Player& player,const Uint8 *keyState);
    bool isLeftGoal(FootballMap& fm);
    bool isRightGoal(FootballMap& fm);
    void isIntersectWithWall (FootballMap& fm);
    SDL_Texture *getTexture();
    


};