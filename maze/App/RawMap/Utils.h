//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_UTILS_H
#define MAZE_UTILS_H

#include <string>
#include <iostream>
#include <sstream>
/***
 * A simple struct representing a RawMap point
 */
struct RawMapPoint{
    int x,y;

    RawMapPoint(int x, int y) : x(x), y(y) {}

    std::string toString(){
        std::stringstream builder;
        builder<<"RawMapPoint("<<x<<","<<y<<")";
        return builder.str();

    }
    RawMapPoint incX(int amount){
        return RawMapPoint(x+amount,y);
    }

    RawMapPoint incY(int amount){
        return RawMapPoint(x,y+amount);
    }

    bool operator==(RawMapPoint p2){
        return this->x==p2.x &&this->y==p2.y;
    }
};
#endif //MAZE_UTILS_H
