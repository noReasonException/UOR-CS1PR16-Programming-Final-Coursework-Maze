//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_GRAPHINGS_H
#define MAZE_GRAPHINGS_H


#include "../RawMap/Notification.h"
class Factory;

class NotificationFunctor;
/***
 * The Graphics Class
 * This class receives events from RawMap and draws it to the screen with help of SFML Library
 */
class Graphics {

private:
    Factory*difactory;
protected:
    Factory *getfactory() ;

public:
    Graphics(Factory*_difactory):difactory(_difactory){}
    virtual ~Graphics()= default;

    virtual void apply(Action &ao)=0;
    virtual NotificationFunctor*getNotificationFunctor()=0;

};


#endif //MAZE_GRAPHINGS_H
