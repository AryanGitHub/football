#pragma once
#include "Map.h"

class FootballMap{


public:
Map map;
int initPointX ,initPointY ;
int len,width;
int goalWidth;
FootballMap (int initPointX , int initPointY , int len ,int  width , int goalWidth);
void initMap ();

};