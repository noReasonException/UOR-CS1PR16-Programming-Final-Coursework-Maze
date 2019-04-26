//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_DYNAMICOBJECT_H
#define MAZE_DYNAMICOBJECT_H


#include "../Object.h"

class DynamicObject : public Object,public actionCapable{
public:
    DynamicObject(RawMapPoint initialPosition):Object(initialPosition){}
    virtual ~DynamicObject()= default;
    static Action moveFrontActionObject(Object *object){
        return Action{
                MFRONT,
                object->getPosition(),
                object->getPosition().incY(+1),
                object
        };
    }
    static Action moveBackActionObject(Object *object){
        return Action{
                MBACK,
                object->getPosition(),
                object->getPosition().incY(-1),
                object
        };
    }
    static Action moveLeftActionObject(Object *object){
        return Action{
                MLEFT,
                object->getPosition(),
                object->getPosition().incX(-1),
                object
        };
    }
    static Action moveRightActionObject(Object *object){
        return Action{
                MRIGHT,
                object->getPosition(),
                object->getPosition().incX(+1),
                object
        };
    }
};


#endif //MAZE_DYNAMICOBJECT_H
