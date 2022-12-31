#include "Wall.h"

Wall::Wall (int A , int B , int C , int startX , int endX,int sidePointX ,int sidePointY){
    this->A = A;
    this->B = B;
    this->C = C;
    this->startX = startX;
    this->endX = endX;
    this->sidePointX = sidePointX;
    this->sidePointY = sidePointY;

}

Wall::Wall (int A , int B , int C , int sidePointX ,int sidePointY){
    this->A = A;
    this->B = B;
    this->C = C;
    this->startX = INT_MIN;
    this->endX = INT_MAX;
    this->sidePointX = sidePointX;
    this->sidePointY = sidePointY;
}

int Wall::getValue (int x1, int y1){
    return (A*x1) + (B*y1) + C ;
}

int Wall::locatePoint (int x1, int y1){
    // returns: checks limits and then  returns a point on line, above it or below it.
    
    /*
    if out of limit return -2
    if eq > 0 then returns  +1
    eq == 0 retruns 0
    eq < 0 returns -1
    */
   
    // limits are of variable x, but if B=0 then limits are of y -- very important!

        
    
        if ( B && (x1 < startX || x1 > endX)) {
            std::cout << "returning -2 1st condition" << std::endl;    
            return -2;
        }
        else if (!B && (y1 < startX || y1 > endX)) {
            std::cout << "returning -2 2nd condition" << std::endl;    
            return -2;
        }

        int value  = getValue(x1,y1);
        //std::cout << ":eq value  " <<value << std::endl;
        if (value  > 0 ) return 1;
        else if (value == 0 ) return 0;
        else return -1;
    
}

bool Wall::isOnSameSide (int x1 , int y1){
    int value1 = locatePoint( sidePointX , sidePointY );
    int value2 = locatePoint ( x1 , y1 );
     //std::cout << ":value 1 "<<value1 << std::endl;
     //std::cout << ":value 2 " <<value2 << std::endl;
    if (value1 == -2 || value2 == -2) return false;
    if (value1 == 0 || value2 == 0) return false;
    
    return value1 == value2;
}

