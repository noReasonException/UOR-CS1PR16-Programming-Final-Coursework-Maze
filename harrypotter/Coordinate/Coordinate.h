//
// Created by stefan on 27/3/2017.
//

#ifndef GHOST_COORDINATE_H
#define GHOST_COORDINATE_H

#include <iostream>
#include <ostream>
struct Coordinate{
private:
    int x,y;
    static Coordinate *SiglentonObject ;
public:
    inline int getX() const{ return this->x;}
    inline int getY() const { return this->y;}
    inline void setX(int i){this->x=i;}
    inline void setY(int j){this->y=j;}
    inline void goUp() {
        this->x-=1;
    }
    inline void goDown() {
	this->x+=1;
    }
    inline void goLeft() {
    	
        this->y-=1;
    }
    inline void goRight() {
        this->y+=1;
    }
    Coordinate(int _x,int _y):x(_x),y(_y){}
    Coordinate(const Coordinate&);
    Coordinate():x(0),y(0){}
    bool operator ==(const Coordinate &rhs);
    static Coordinate *getNulledInstance();
    Coordinate& operator=(Coordinate &rhs);
    bool operator!=(Coordinate&rhs);
    friend std::ostream & operator<<(std::ostream& ,const Coordinate&);
};



#endif //GHOST_COORDINATE_H
