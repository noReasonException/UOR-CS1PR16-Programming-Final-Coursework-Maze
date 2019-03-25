//
// Created by StefStef on 4/30/2017.
//

#include "Ghost.h"
#include <limits>

Ghost::Ghost(int _WhatIAm,Map&refToMap,Coordinate &_refToPosition):WhatIAm(_WhatIAm),mGraphRef(refToMap),MyMap(refToMap),myPosition(_refToPosition) {

}

int *Ghost::DijKstraAlgorithm() {
    int MinimumDistanceTree[this->mGraphRef.getSize()];
    bool HasUsedYet[this->mGraphRef.getSize()];
    //int ParentTree[this->mGraphRef.getSize()];
    int *ParentTree = new int[this->mGraphRef.getSize()];
    int minCurrent;

    for (int i = 0; i < this->mGraphRef.getSize(); ++i) {///initialization
        HasUsedYet[i]=false;
        MinimumDistanceTree[i]=INF;
        ParentTree[i]=-1;
    }
    ParentTree[this->mGraphRef.toID(this->getPosition().getX(),this->getPosition().getY())]=-1; ///The Current Location has no parent (Poor Guy :(  :P )
    MinimumDistanceTree[this->mGraphRef.toID(this->getPosition().getX(),this->getPosition().getY())]=0; ///The Distance from Current Position is ... Zeroo
    for (int j = 0; j < this->mGraphRef.getSize(); ++j) {
        minCurrent=FindClosest(MinimumDistanceTree,HasUsedYet); //βρες τον κομβο με την μικροτερη αποσταση που δεν εχει χρησιμοποιηθει :P
        HasUsedYet[minCurrent]=true;            //δηλωσε τον ως περασμενο ηδη
        for (int k = 0; k < this->mGraphRef.getSize(); ++k) {              //Σαρωσε για γειτονικους κομβους
            //  Αν ο κομβος δεν εχει ξαναπεραστει
            //       και οι δυο κομβοι ειναι συνδεδεμενοι
            //και η συνολικη αποσταση απο την αρχη συν την αποσταση συνδεσης
            //ειναι μικροτερη απο την ηδη δηλωμενη  αποσταση (απειρο στην 1 επαναληψη)
            if( this->mGraphRef.isConnected(minCurrent,k) and !HasUsedYet[k]and (MinimumDistanceTree[minCurrent]+this->mGraphRef.getAdajencyMatrix(minCurrent,k))<MinimumDistanceTree[k]){
                ParentTree[k]=minCurrent;
                MinimumDistanceTree[k]=MinimumDistanceTree[minCurrent]+this->mGraphRef.getAdajencyMatrix(minCurrent,k);

            }
        }

    }
    return ParentTree;

}
int Ghost::FindClosest(int *distancePtr,bool *existInSetPtr){
    int min=-1;
    for (int i = 0; i < this->mGraphRef.getSize(); ++i) {
        if(min!=-1){
            if(!existInSetPtr[i] and distancePtr[i]<distancePtr[min]){
                min=i;
            }
        }
        else{
            if(!existInSetPtr[i])min=i;
        }

    }
    return min;
}
Coordinate &Ghost::getPosition() {
    return this->myPosition;
}

void Ghost::setPosition(Coordinate &_position) {
    this->myPosition=_position;

}
int Ghost::ConvertToMove(int NodeID) {
    Coordinate *ptr = this->mGraphRef.toCoordinate(NodeID);
    int MoveTemp;
    if(ptr->getX()>this->getPosition().getX())MoveTemp=DOWN;
    else if(ptr->getX()<this->getPosition().getX())MoveTemp=UP;
    else if(ptr->getY()>this->getPosition().getY())MoveTemp=RIGHT;
    else if(ptr->getY()<this->getPosition().getY())MoveTemp=LEFT;
    else {
        MoveTemp=STAND;
        std::cout<<"warn STAND bot?";
    }
    delete ptr;
    return MoveTemp;
}

int Ghost::NextMoveLocation(int dest, int *Parent,int &MoveNumber){
    MoveNumber=0;
    if(dest==-1 or Parent[dest]==-1)return 10;
    while(Parent[dest]!=-1 and Parent[Parent[dest]]!=-1){
        dest=Parent[dest];
        MoveNumber+=1;
    }
    return dest;


}