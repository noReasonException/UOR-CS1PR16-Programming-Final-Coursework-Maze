//
// Created by stefan on 21/04/19.
//

#ifndef MAZE_DERIVEABLEPLAYER_H
#define MAZE_DERIVEABLEPLAYER_H

#include "Player.h"

class DeriveablePlayer: public Player{
public:
    DeriveablePlayer(const RawMapPoint &initialPosition, unsigned short _lives) : Player(initialPosition, _lives) {}
    virtual ~DeriveablePlayer()= default;

    PlayerMoves yourNextMove(std::vector<std::vector<char>> fieldOfView) override {

        switch(rand()%4){
            case 0:return PM_FRONT;
            case 1:return PM_BACK;
            case 2:return PM_RIGHT;
            case 3:return PM_LEFT;
            default: return PM_STILL;
        }
    }
};
#endif //MAZE_DERIVEABLEPLAYER_H
