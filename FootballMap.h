#pragma once
#include "Map.h"

class FootballMap{

private :
int initPointX ,initPointY ;
int len,width;
int goalWidth;


public:
Map map;
FootballMap (int initPointX , int initPointY , int len ,int  width , int goalWidth);
void initMap ();

};