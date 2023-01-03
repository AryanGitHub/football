#include "Ball.h"
#include "Wall.h"
#include "Map.h"

#include<SDL_image.h>
#include<iostream>
using namespace std;

Ball::Ball (SDL_Renderer *windowRenderer , int initialPositionX, int initialPositionY , int radius, std::string ballTextureFilepath){

    this->texture = getTextureFromImage (ballTextureFilepath , windowRenderer);

    int querySuccess = SDL_QueryTexture(this->texture, NULL, NULL, &(this->textureWidth), &(this->textureHeight) );
    if (querySuccess < 0 ) std::cout << SDL_GetError() << std::endl;

    this->positionRect.x = initialPositionX ;
    this->positionRect.y = initialPositionY ;

    this->frameRect.x = this->frameRect.y =  0;

    this->frameRect.h = textureHeight ;
    this->frameRect.w = textureWidth ;

    this->radius = radius;
    this->positionRect.h = this->positionRect.w = 2*this->radius;


    
   

    this->moveSpeedX = this->moveSpeedY=0;
    this->acceleration = 200.0;     
}

Ball::~Ball(){
	SDL_DestroyTexture(texture);
}

int Ball::getOriginX(){ 
        return (this->positionRect.x + this->positionRect.w/2) ;
}

int Ball::getOriginY(){ 
    return (this->positionRect.y + this->positionRect.h/2) ;
}

int Ball::getRadius(){ 
    return this->radius;
}

SDL_Texture* Ball::getTexture(){
    return this->texture;
}

float Ball::getDistance ( int x, int y){
        return sqrt (pow((this->getOriginX() - x ),2) + pow( this->getOriginY() - y ,2)) ;
}



void Ball::update (float deltaTime){
    float nextSpeedX , nextSpeedY ;
    nextSpeedX = moveSpeedX + ((this->acceleration * deltaTime) * -1 * (moveSpeedX/abs(moveSpeedX)));
    nextSpeedY = moveSpeedY + ((this->acceleration * deltaTime) * -1 * (moveSpeedY/abs(moveSpeedY)));
    
    if ( (moveSpeedX!=0) && (nextSpeedX!=0) && (abs(nextSpeedX) / nextSpeedX)  == (abs(this->moveSpeedX) / this->moveSpeedX) )
    this->moveSpeedX = nextSpeedX;
    else moveSpeedX = 0;


    if ( (moveSpeedY!=0) && (nextSpeedY!=0) && (abs(nextSpeedY) / nextSpeedY)  == (abs(this->moveSpeedY) / this->moveSpeedY) )
    this->moveSpeedY = nextSpeedY;
    else moveSpeedY = 0;


    

    this->positionRect.x += (this->moveSpeedX * deltaTime) ;
    this->positionRect.y += (this->moveSpeedY * deltaTime) ;

}


void Ball::isIntersectWithWall (FootballMap& fm){
    Wall *wall = fm.map.isInside(this->getOriginX() , this->getOriginY());
    if (wall!=NULL){
        int value  = wall->locatePoint(this->getOriginX() , this->getOriginY());
        if ( value== -2){
            // goal logic
        }
        else {
            //reflect On Wall 
            
            // change direction of moveSpeedX by 180 degree on hitting with x asix walls (where B coefficient is 0)
            if (wall->B == 0){
                moveSpeedX *= -1;
                
                positionRect.x = wall->C;
                cout << "hit on x axis" << endl ;
            }
            
            if (wall->A  == 0) { // change direction of moveSpeedY by 180 degree on hitting with Y asix walls (where A coefficient is 0)
                moveSpeedY *= -1;
                
                 positionRect.y = wall->C;
                cout << "hit on y axis" << endl ;
            }
        }
    }
}

bool Ball::isLeftGoal(FootballMap& fm){
    return ( (this->getOriginX() <= fm.initPointX) && 
    (fm.map.walls[2].locatePoint(this->getOriginX() , this->getOriginY() ) == -2) && 
    (fm.map.walls[4].locatePoint(this->getOriginX() , this->getOriginY() ) == -2) );
}

bool Ball::isRightGoal(FootballMap& fm){
    return ( (this->getOriginX() >= (fm.initPointX+fm.len)) && 
    (fm.map.walls[3].locatePoint(this->getOriginX() , this->getOriginY() ) == -2) && 
    (fm.map.walls[5].locatePoint(this->getOriginX() , this->getOriginY() ) == -2) );
}


void Ball::draw (SDL_Renderer *renderTarget){
    SDL_RenderCopy(renderTarget, this->texture, &(this->frameRect), &(this->positionRect) );
}

bool Ball::isIntersecting (int x ,int y , int radius){
    return (this->getDistance(x , y) <= (this->getRadius() + radius ));
}

void Ball::isIntersectWithPlayer (Player& player,const Uint8 *keyState){
    if(this->isIntersecting(player.GetOriginX() , player.GetOriginY() , player.GetRadius() )) {
        int kickSpeedIncrement = 75;
        moveSpeedX = (keyState[player.keys[2]] * (player.moveSpeed+kickSpeedIncrement) * -1 ) + (keyState[player.keys[3]] * (player.moveSpeed+kickSpeedIncrement) * 1);
        moveSpeedY = (keyState[player.keys[0]] * (player.moveSpeed+kickSpeedIncrement) * -1 ) + (keyState[player.keys[1]] * (player.moveSpeed+kickSpeedIncrement) * 1);
    }
}

SDL_Texture* Ball::getTextureFromImage(std::string filePathLocation , SDL_Renderer *windowRenderer){

    SDL_Surface *normalSurface  = IMG_Load (filePathLocation.c_str());
    SDL_Texture *texture = NULL;
    if (normalSurface == NULL) std::cout << SDL_GetError() << std::endl;
    else {
            texture = SDL_CreateTextureFromSurface ( windowRenderer , normalSurface );
            if (texture == NULL) std::cout << SDL_GetError() << std::endl;

    }
    SDL_FreeSurface(normalSurface);
    return texture;
}