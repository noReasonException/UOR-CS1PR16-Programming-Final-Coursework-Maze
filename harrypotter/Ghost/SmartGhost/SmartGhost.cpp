//
// Created by stefan on 25/3/2017.
//

#include <cstdlib>
#include <limits>
#include "SmartGhost.h"
#include "../../PlayerInfo/PlayerInfo.h"
#include "../../Errors/AllPlayersAreKilledException.h"
#include "../../DisplaySystem/Window/Window.h"
class Window;
SmartGhost::SmartGhost(int N,Map &_map, Coordinate &MyCoordinate,std::vector<ObjectInfo*> _players):
        Ghost(CLEVERGHOST,_map,MyCoordinate),
        ComparePosition(0,0) {
    for(int i=0;i<_players.size();i++){
        this->players.push_back(_players[i]);
    }

}


int SmartGhost::getMove() {
    int *ParentTree = this->DijKstraAlgorithm();
    int StepNumberTemp,MoveTemp;
    int StepNumber=INF,Move=STAND;
    for (int i = 0; i < this->players.size(); ++i) {
        if(this->players[i]->isAlive()){
            MoveTemp=this->ConvertToMove(this->NextMoveLocation(this->mGraphRef.toID(this->players[i]->getPosition().getX(),this->players[i]->getPosition().getY()), ParentTree,StepNumberTemp));
            if(StepNumberTemp<StepNumber){
                Move=MoveTemp;
                StepNumber=StepNumberTemp;

            }
        }

    }
    delete ParentTree;
    return Move;

}


std::vector<ObjectInfo *> &SmartGhost::getPlayers() {
    return this->players;
}

