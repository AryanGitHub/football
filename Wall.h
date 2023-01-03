#pragma once
#include <climits>
#include <iostream>

// st line in form of Ax + By + C = 0 and limits of X ,.... X belongs to [startX , endX] limit value are included 
// if B=0 then limits are of Y
// there will be two sides to the wall 
class Wall {
private:

int startX,endX;   
int sidePointX,sidePointY;

public :
int A,B,C;
Wall (int A , int B , int C , int startX , int endX , int sidePointX ,int sidePointY);
Wall (int A , int B, int C , int sidePointX, int sidePointY) ;
int getValue (int x1, int y1);
int locatePoint (int x1, int y1);

bool isOnSameSide (int x1, int y1);

};
