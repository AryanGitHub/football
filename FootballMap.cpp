#include "FootballMap.h"

FootballMap::FootballMap (int initPointX , int initPointY , int len ,int  width , int goalWidth){
    this->initPointX = initPointX;
    this->initPointY = initPointY;
    this->len = len;
    this->width = width;
    this->goalWidth = goalWidth;
    initMap();
}
void FootballMap::initMap (){
Wall a( 0, 1 , initPointY , initPointX ,  initPointX + len , initPointX+ len/2 , initPointY + width /2);
Wall b( 0, -1 , initPointY + width , initPointX ,  initPointX + len , initPointX+ len/2 , initPointY - width /2);


Wall c1 ( -1 , 0, initPointX       , initPointY , initPointY + width/2 - goalWidth/2, initPointX + len/2 , initPointY + width/4 -  goalWidth/2);
Wall d1 ( -1 , 0, initPointX + len , initPointY , initPointY + width/2 - goalWidth/2, initPointX + len/2 , initPointY + width/4 -  goalWidth/2);
Wall c2 ( -1 , 0, initPointX      , initPointY+ width/2 + goalWidth/2 , initPointY + width , initPointX + len/2 , initPointY+ width/2 + goalWidth/2 + goalWidth/4);
Wall d2 ( -1 , 0, initPointX + len, initPointY+ width/2 + goalWidth/2 , initPointY + width , initPointX + len/2 , initPointY+ width/2 + goalWidth/2 + goalWidth/4);
 
map.walls.push_back(a);
map.walls.push_back(b);
map.walls.push_back(c1); // left side up wall
map.walls.push_back(d1); //right side up wall
map.walls.push_back(c2); // left side down wall
map.walls.push_back(d2); // right side down wall

}