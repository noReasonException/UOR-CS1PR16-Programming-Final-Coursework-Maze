//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_WALL_H
#define MAZE_WALL_H

#include "../StaticObject.h"
enum WallType{
    BACK_WALL=0,
    BACK_ADDITIONAL,
    FORWARD_WALL,
    LEFT_WALL,
    LEFT_ADDITIONAL,
    RIGHT_WALL
};
class Wall: public StaticObject{
    WallType wallType;

public:
    Wall(RawMapPoint position,WallType type) : StaticObject(position),wallType(type) {}
    Wall(RawMapPoint position) :Wall(position,BACK_WALL) {}
    virtual ~Wall()= default;

    objectType getType() override {
        return OS_WALL;
    }
};
#endif //MAZE_WALL_H
