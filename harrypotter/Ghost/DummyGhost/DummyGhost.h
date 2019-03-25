//
// Created by stefan on 25/3/2017.
//

#ifndef GHOST_DUMMYGHOST_H
#define GHOST_DUMMYGHOST_H

#include "../Ghost.h"
#include "../../Move.h"
#include <stdlib.h>
#include <time.h>
class DummyGhost :public Ghost{
public:
    DummyGhost(Map&refToMap,Coordinate&refToCoordinate);
    bool iNeedNewRandomTarget;
    Coordinate RandomTarget;
    void myNewRandomTargetIs(Coordinate newTarget);
    virtual int getMove();
};


#endif //GHOST_DUMMYGHOST_H
