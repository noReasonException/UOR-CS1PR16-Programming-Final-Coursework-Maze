//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_GENERICRULEEXCEPTION_H
#define MAZE_GENERICRULEEXCEPTION_H

#include <exception>
#include <iostream>
#include "../Object/DynamicObject/ActionObject/Action.h"
class GenericRuleException: public std::exception{
    Action actionObject;
    std::string ruleName;
protected:
    mutable std::string *whatstr;
public:
    GenericRuleException(Action ao,std::string breakrule):actionObject(ao),ruleName(breakrule){}

    virtual ~GenericRuleException()= default;
    const Action &getActionObject() const {
        return actionObject;
    }

    const std::string &getRuleName() const {
        return ruleName;
    }

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
        std::stringstream buff;
        buff<<"GenericRuleException at object "<<this;
        buff<<" "<<ruleName<<" [ignore]";
        whatstr=new std::string(buff.str());
        return whatstr->c_str();
    }
};
/****
 *
    rules.push_back(new AvoidLevelLimits(rawMap));
    rules.push_back(new AvoidColission(rawMap));
    rules.push_back(new AvoidMoveOverOneBlockAway(rawMap));
 */

class AvoidLevelLimitsException:public GenericRuleException{
public:
    AvoidLevelLimitsException(const Action &ao) : GenericRuleException(ao,"AvoidLevelLimitsException") {}
};
class AvoidCollisionException:public GenericRuleException{
public:
    Object*collidingObject;
    AvoidCollisionException(const Action &ao,Object*_collidingObject) : GenericRuleException(ao, "AvoidCollisionException"),collidingObject(_collidingObject) {}

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override {
        std::stringstream buff;
        buff<<GenericRuleException::what();
        buff<<" with object "<<collidingObject;
        whatstr=new std::string(buff.str());
        return whatstr->c_str();
    }
};
class AvoidMoveOverOneBlockAwayException:public GenericRuleException{
public:
    AvoidMoveOverOneBlockAwayException(const Action &ao) : GenericRuleException(ao,"AvoidMoveOverOneBlockAwayException") {}
};
#endif //MAZE_GENERICRULEEXCEPTION_H
