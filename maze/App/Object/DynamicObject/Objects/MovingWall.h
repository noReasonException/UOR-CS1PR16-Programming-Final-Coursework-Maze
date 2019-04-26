//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_MOVINGWALL_H
#define MAZE_MOVINGWALL_H

#include "../DynamicObject.h"

class MovingWall: public DynamicObject{
public:
    MovingWall(RawMapPoint initialPosition) : DynamicObject(initialPosition) {}
    virtual ~MovingWall()= default;
    objectType getType() override {
        return OD_MOVINGWALL;
    }

    Action nextActionObject(ActionObjectAdditionalInfo *info) override {
        return Object::standStillActionObject(this);

    }

    Action failedActionObjectHandler(Action ao,GenericRuleException&e) override {

    }
};
#endif //MAZE_MOVINGWALL_H
