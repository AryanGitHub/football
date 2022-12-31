 #include "Map.h"
 Wall* Map::isInside (int x, int y){
    //returns NULL if inside

    for (int i; i < walls.size() ; i++ ){
        if (!walls[i].isOnSameSide(x,y)) 
            return &(walls[i]);
    }
    return NULL;
}