//
// Created by stefan on 28/3/2017.
//

#ifndef GHOST_PLAYER_H
#define GHOST_PLAYER_H

#include <iostream>
#include <windows.h>
class Player{
private:
public:
    Player(){}
    virtual std::string getName() =0;
    virtual std::string getId() =0;
    virtual int getMove(const char **ViewAround)=0;
    virtual void init(int width,int height,int CurrentX,int CurrentY )=0;


};


#endif //GHOST_PLAYER_H
