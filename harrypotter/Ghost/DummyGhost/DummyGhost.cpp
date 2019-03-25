//
// Created by stefan on 25/3/2017.
//

#include "DummyGhost.h"
DummyGhost::DummyGhost(Map&refToMap,Coordinate&refToMyPosition) :Ghost(DUMMYGHOST,refToMap,refToMyPosition),iNeedNewRandomTarget(true),RandomTarget(*Coordinate::getNulledInstance()){
    srand(static_cast<unsigned int>(time(NULL)));
}
int DummyGhost::getMove() {
    if(this->iNeedNewRandomTarget)return STAND;
    if(this->RandomTarget==this->myPosition){
        this->RandomTarget=*Coordinate::getNulledInstance();
        this->iNeedNewRandomTarget=true;
        return STAND;
    }
    int *ParentList = this->DijKstraAlgorithm();
    int StepsNeeded;
    delete ParentList;
    return this->ConvertToMove(this->NextMoveLocation(this->mGraphRef.toID(this->RandomTarget.getX(),this->RandomTarget.getY()),ParentList,StepsNeeded));

}

void DummyGhost::myNewRandomTargetIs(Coordinate newTarget) {
    this->RandomTarget=newTarget;
    this->iNeedNewRandomTarget=false;

}
