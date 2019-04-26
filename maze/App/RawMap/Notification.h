//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_NOTIFICATION_H
#define MAZE_NOTIFICATION_H


#include "../Object/DynamicObject/ActionObject/Action.h"
#include "../GraphicsModule/Graphics.h"
class Graphics;
/***
 * This is the Functor used by the RawMap to notify other subsystems
 */
struct NotificationFunctor {
    Graphics*notifiedGraphicsModule;

    NotificationFunctor(Graphics *notifiedGraphicsModule) : notifiedGraphicsModule(notifiedGraphicsModule) {}
    virtual ~NotificationFunctor()= default;
    Graphics *getNotifiedGraphicsModule() const {
        return notifiedGraphicsModule;
    }

    virtual void operator()(Action obj)=0;
};
#endif //MAZE_NOTIFICATION_H
