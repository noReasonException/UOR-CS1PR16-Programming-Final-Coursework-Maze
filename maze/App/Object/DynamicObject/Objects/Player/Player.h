//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_PLAYER_H
#define MAZE_PLAYER_H


#include "../../DynamicObject.h"
#include "../../../../Logger/Logger.h"

#define ERROR_LIVES_PENALTY (unsigned short) 1
enum PlayerMoves{
    PM_FRONT,
    PM_BACK,
    PM_LEFT,
    PM_RIGHT,
    PM_STILL
};
class Player: public DynamicObject,public Logger{
    unsigned short lives;


    unsigned short getLives() const {
        return lives;
    }

    void setLives(unsigned short lives) {
        Player::lives = lives;
    }
    bool isDead(){return isVisible()== false;}

    Action isDeadHandler(ActionObjectAdditionalInfo *info){
        return Object::standStillActionObject(this);
    }
    Action isAliveHandler(ActionObjectAdditionalInfo *info){

       auto currentFieldOfView=((PlayerAdditionalInfo*)info)->getFieldOfView();
       switch (yourNextMove(currentFieldOfView)){
           case PM_FRONT:
               return DynamicObject::moveFrontActionObject(this);
           case PM_BACK:
               return DynamicObject::moveBackActionObject(this);
           case PM_RIGHT:
               return DynamicObject::moveRightActionObject(this);
           case PM_LEFT:
               return DynamicObject::moveLeftActionObject(this);
       }
    }
    Action failedActionObjectHandler(Action ao,GenericRuleException&e) override {

        setLives(getLives() - ERROR_LIVES_PENALTY);
        if (getLives() <= 0)setVisible(false);

        if (typeid(e) == typeid(AvoidCollisionException)) {//this is not the optimal , but.
            auto error = (AvoidCollisionException &) e;
            if (error.collidingObject->getType() == OS_PRICE) {
                return Player::priceTakenActionObject(error.getActionObject().parent);
            }
        }
        return ao;
    }
    static Action priceTakenActionObject(Object *object){
        return Action{
                IPRICETAKEN,
                object->getPosition(),
                object->getPosition(),
                object
        };
    }
    Action nextActionObject(ActionObjectAdditionalInfo *info) override {
        if(!isVisible())return isDeadHandler(info);
        return isAliveHandler(info);
    }

public:
    Player(RawMapPoint initialPosition, unsigned short _lives) : DynamicObject(initialPosition),lives(_lives) {}
    virtual ~Player()= default;
    objectType getType() override {
        return OD_PLAYER;
    }
    virtual PlayerMoves yourNextMove(std::vector<std::vector<char>>fieldOfView)=0;
};
#endif //MAZE_PLAYER_H
