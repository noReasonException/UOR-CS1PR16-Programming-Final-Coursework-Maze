//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_GHOST_H
#define MAZE_GHOST_H

#include "../DynamicObject.h"

class Ghost: public DynamicObject{
public:
    Ghost(RawMapPoint initialPosition) : DynamicObject(initialPosition) {}
    virtual ~Ghost()= default;
    objectType getType() override {
        return OD_GHOST;
    }

    Action nextActionObject(ActionObjectAdditionalInfo *info) override {
        switch(rand()%4){
            case 0:return DynamicObject::moveFrontActionObject(this);
            case 1:return DynamicObject::moveBackActionObject(this);
            case 2:return DynamicObject::moveRightActionObject(this);
            case 3:return DynamicObject::moveLeftActionObject(this);
            default: return Object::standStillActionObject(this);
        }
    }

    Action failedActionObjectHandler(Action ao,GenericRuleException&e) override {
        return ao;
    }
};
#endif //MAZE_GHOST_H
