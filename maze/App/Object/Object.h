//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H


#include "../RawMap/Utils.h"
#include "DynamicObject/ActionObject/Action.h"

/**
 * This is the list of possible object implementations
 *
 * OS_ * = ObjectStatic_*
 * OD_*  = ObjectDynamic_*
 */
enum objectType{
    OS_WALL=0,
    OS_PRICE,
    OD_GHOST,
    OD_MOVINGWALL,
    OD_PLAYER
};
class Object {
    RawMapPoint position;
    bool visible;

public:
    bool isVisible() const {
        return visible;
    }

    /**
     * setter for visible
     * @note is a builder style setter
     * @param _isVisible true or false
     * @return the 'this' pointer
     */
    Object* setVisible(bool _isVisible){
        Object::visible = _isVisible;
        return this;
    }

    explicit Object(RawMapPoint initialPosition):position(initialPosition),visible(true){}
    virtual ~Object()= default;

    virtual objectType getType()=0;


     RawMapPoint &getPosition()  {
        return position;
    }
    /**
     * Inform object about the position change
     * @TODO move to moveCapable interface
     * @param obj the action object
     */
    void applyQualifyingActionObject(Action&obj) {
        this->position=obj.to;
    }

    /***
     * Just a builder for the 'do nothing move'
     * @param   object      the issuing object
     * @return              a Action Object
     */

    static Action standStillActionObject(Object *object){
        return Action{
                MSTAND,
                object->getPosition(),
                object->getPosition(),
                object
        };
    }
};


#endif //MAZE_OBJECT_H
