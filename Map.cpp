 #include "Map.h"
 Wall* Map::isInside (int x, int y){
    //returns NULL if inside

    for (int i=0; i < walls.size() ; i++ ){
        if (!walls[i].isOnSameSide(x,y) && walls[i].locatePoint(x,y)!=-2) 
            return &(walls[i]);
    }
    return NULL;
}