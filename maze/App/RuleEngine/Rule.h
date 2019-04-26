//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_RULE_H
#define MAZE_RULE_H

#include <cmath>
#include "../Object/DynamicObject/ActionObject/Action.h"
#include "../RawMap/RawMap.h"
#include "GenericRuleException.h"
/***
 * This is the abstract Rule Class , every rule derives from this class
 */
class Rule{

    RawMap*map;
protected:
    RawMap *getMap(){return map;}

public:
    explicit Rule(RawMap* _map):map(_map){}
    virtual ~Rule()= default;

    virtual void ruleCheck(Action &object)=0;
    virtual std::string toString()=0;
};


class AvoidMoveOverOneBlockAway:public Rule{
public:
    explicit AvoidMoveOverOneBlockAway(RawMap *_map) : Rule(_map) {}
    virtual ~AvoidMoveOverOneBlockAway()= default;
    void ruleCheck(Action &object) override{
        if(!(abs(object.from.x-object.to.x)<=1 && abs(object.from.y-object.to.y)<=1))throw AvoidMoveOverOneBlockAwayException(object);
    }

    std::string toString() override {
        return "AvoidMoveOverOneBlockAway";
    }
};
class AvoidColission:    public Rule{
public:
    explicit AvoidColission(RawMap *_map) : Rule(_map){}
    virtual ~AvoidColission()= default;
    void ruleCheck(Action &object) override {
        Object*ptr;

        if((ptr=getMap()->getPoint(object.to)) &&
        ptr->isVisible())
            throw  AvoidCollisionException(object,ptr);

    }

    std::string toString() override {
        return "AvoidColission";
    }
};

class AvoidLevelLimits:    public Rule{
public:
    explicit AvoidLevelLimits(RawMap *_map) : Rule(_map){}
    virtual ~AvoidLevelLimits()= default;
    void ruleCheck(Action &object) override {
        Object*ptr;
        if(!(object.to.x<getMap()->getLenx() && object.to.y<getMap()->getLeny() && object.to.x>=0 && object.to.y>=0))throw AvoidLevelLimitsException(object);

    }

    std::string toString() override {
        return "AvoidLevelLimits";
    }
};

#endif //MAZE_RULE_H
