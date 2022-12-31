

#pragma once

#include <sdl2>

class Moveable {

private:
    SDL_Rect frameRect ;
    SDL_Texture *texture;
    int radius;
    float moveSpeedX , float moveSpeedY;


public:
    SDL_Rect positionRect;

};