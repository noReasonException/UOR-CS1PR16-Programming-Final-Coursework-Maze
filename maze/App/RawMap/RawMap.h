//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_RAWMAP_H
#define MAZE_RAWMAP_H


#include <iostream>
#include <vector>
#include "../Object/Object.h"
#include "../Object/DynamicObject/ActionObject/Action.h"
#include "MapException.h"
#include "Notification.h"

/***
 * This is the RawMap , a simple 2D Array List used for computations
 *
 */
class RawMap{
    int lenx,leny;
    std::vector<std::vector<Object*>> map;
    std::vector<Object*>lineOfLen(int x);
    std::vector<NotificationFunctor*> notificationCallbacks;

    /***
     * Initialization routine
     */
    void initializeEmptyMap();



public:

    /***
     * For tests , we need private access
     */
    friend class ApplyActionObjectTest;
    friend class GetPointTest;
    friend class GettersTest;
    friend class OverridePointTest;


    RawMap(int _lenx, int _leny):lenx(_lenx),leny(_leny){initializeEmptyMap();}
    virtual ~RawMap()= default;

    unsigned long subscribeToNotifications(NotificationFunctor*callback);
    std::vector<std::vector<Object*>>to2DVector();
    Object*getPoint(RawMapPoint point);
    Object*overridePoint(RawMapPoint point,Object*object);
    void applyActionObject(Action actionObject)/*throw(InvalidActionMoveException)*/;

    int getLenx() const;

    int getLeny() const;

    RawMap copy();

    void debug(){
        for (int i = 0; i < lenx; ++i) {
            for (int j = 0; j < leny; ++j) {
                std::cout<<map[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }

};


#endif //MAZE_RAWMAP_H
