//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_IACTIONOBJECT_H
#define MAZE_IACTIONOBJECT_H

#include <vector>
#include "../../../RawMap/Utils.h"

class GenericRuleException;
#define NOADDITIONALINFO ActionObjectAdditionalInfo()
#define EMPTY_FIELD_OF_VIEW {{'W','W','W'},{'W','W','W'},{'W','W','W'}}
#define EMPTY_FIELD_OF_VIEW_ACTIONOBJ std::vector<std::vector<char>>(EMPTY_FIELD_OF_VIEW)
class Object;
class RawMapPoint;
enum ActionType{
    //-------------------influence
    IPRICETAKEN=0,
    IPLAYERDEAD,

    //-------------------move
    MFRONT,
    MBACK,
    MRIGHT,
    MLEFT,
    MSTAND,
    MTELEPORT,

};
struct Action{
    ActionType      actionType;
    RawMapPoint     from;
    RawMapPoint     to;
    Object*  parent;


    Action(ActionType actionType, const RawMapPoint &from, const RawMapPoint &to, Object *_parent) : actionType(
    actionType), from(from), to(to), parent(_parent) {}

};

struct ActionObjectAdditionalInfo{};

struct PlayerAdditionalInfo:public ActionObjectAdditionalInfo{
    PlayerAdditionalInfo() : fieldOfView(EMPTY_FIELD_OF_VIEW) {}
    std::vector<std::vector<char>>&getFieldOfView(){ return fieldOfView;}
private:
    std::vector<std::vector<char>>fieldOfView;

};
/****
 * Implemented by All DynamicObjects
 ***/
class /*interface*/ actionCapable{
public:
    virtual Action nextActionObject(ActionObjectAdditionalInfo *info)=0;
    virtual Action failedActionObjectHandler(Action ao,GenericRuleException&e)=0;
};
#endif //MAZE_IACTIONOBJECT_H
