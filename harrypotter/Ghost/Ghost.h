//
// Created by stefan on 25/3/2017.
//

#ifndef GHOST_GHOST_H
#define GHOST_GHOST_H
#include "../Move.h"
#include "SmartGhost/Graph/Graph.h"

class Ghost {
protected:
    int WhatIAm;

    Coordinate &myPosition;
    Graph mGraphRef;
    Map &MyMap;
public:
    Ghost(int _WhatIAm,Map &refToMap,Coordinate&_refToPosition);
    Coordinate & getPosition();
    void setPosition(Coordinate &);
    int ConvertToMove(int NodeID);
    int NextMoveLocation(int dest, int *Parent,int &MoveNumber);
    int getWhatIAm(){ return this->WhatIAm;}
    int *DijKstraAlgorithm();
    virtual int getMove()=0;
    int FindClosest(int *distancePtr,bool *existInSetPtr);
    bool iAmSmart(){ return this->WhatIAm==CLEVERGHOST;}
    bool iAmFool(){ return this->WhatIAm==DUMMYGHOST;}

};

#endif //GHOST_GHOST_H
