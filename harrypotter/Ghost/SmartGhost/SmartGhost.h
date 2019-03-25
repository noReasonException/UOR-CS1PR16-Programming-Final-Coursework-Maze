//
// Created by stefan on 25/3/2017.
//

#ifndef GHOST_SMARTGHOST_H
#define GHOST_SMARTGHOST_H

#include <vector>
#include "../Ghost.h"
#include "../../Move.h"
#include "../../Map/Map.h"
#include "../../Coordinate/Coordinate.h"
#include "../../GhostInfo/GhostInfo.h"
#include "Graph/Graph.h"

class SmartGhost :public Ghost{
public:

    std::vector<ObjectInfo*> players;
    Coordinate ComparePosition;





public:
    SmartGhost(int ,Map &,Coordinate&,std::vector<ObjectInfo*> _players);

    std::vector<ObjectInfo*> &getPlayers();
    virtual int getMove();

};


#endif

