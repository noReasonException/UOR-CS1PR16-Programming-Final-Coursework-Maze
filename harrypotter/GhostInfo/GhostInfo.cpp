//
// Created by sotiris on 3/23/2017.
//

#include "GhostInfo.h"
#include "../Ghost/SmartGhost/SmartGhost.h"


GhostInfo::GhostInfo(Ghost &_ghost,char avatar,Coordinate &startPosition):
        ObjectInfo(avatar, startPosition),ghost(_ghost){

}

GhostInfo::GhostInfo(Ghost &_ghost, char avatar):
        ObjectInfo(avatar),
        ghost(_ghost) {

}
Ghost& GhostInfo::getGhost() {
    return ghost;
}

