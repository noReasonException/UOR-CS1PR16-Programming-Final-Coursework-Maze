//
// Created by sotiris on 3/23/2017.
//

#ifndef HARRYPOTTER_GHOSTINFO_H
#define HARRYPOTTER_GHOSTINFO_H

#include "../Coordinate/Coordinate.h"
#include "../Ghost/Ghost.h"
#include "../ObjectInfo/ObjectInfo.h"

class GhostInfo :public ObjectInfo{

public:
    GhostInfo(Ghost &ghost,char avatar,Coordinate &startPosition);
    GhostInfo(Ghost &_ghost,char avatar);
    Ghost& getGhost();

private:

    Ghost &ghost;
};

#endif //HARRYPOTTER_GHOSTINFO_H