#pragma once
#include <iostream>
#include <vector>
#include "Wall.h"

class Map {
    
    public:
    std::vector<Wall> walls;
    Wall *isInside (int x, int y);


};