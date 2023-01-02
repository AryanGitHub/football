#pragma once
#include "Player.h"
#include <SDL.h>
#include <iostream>

class Ball {

    private:
    SDL_Rect frameRect ;
    SDL_Texture *texture;
   
    float moveSpeedX,moveSpeedY;   //in pixel per sec
    float acceleration;            // int pixel per sec^2
    int textureWidth , textureHeight;
    int radius;

    
	

    SDL_Texture *getTextureFromImage(std::string filePathLocation , SDL_Renderer *windowRenderer);
    float getDistance (int x, int y);

    
    public:
    SDL_Rect positionRect;


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
    SDL_Texture *getTexture();
    


};