//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_STATICOBJECT_H
#define MAZE_STATICOBJECT_H


#include "../Object.h"

class StaticObject : public Object{
public:
    StaticObject(RawMapPoint initialPosition):Object(initialPosition){}
    virtual ~StaticObject()= default;
};


#endif //MAZE_STATICOBJECT_H
