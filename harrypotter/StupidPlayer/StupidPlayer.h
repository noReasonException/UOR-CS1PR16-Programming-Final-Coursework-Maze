//
// Created by stefstef on 31/3/2017.
//

#ifndef GHOST_STUPIDPLAYER_H
#define GHOST_STUPIDPLAYER_H


#include "../Player/Player.h"
#include "../Move.h"

using namespace std;


class StupidPlayer: public Player  {
   int x,y,d1,d2;//Current Position (x,y) , Dimensions of the Map !! 
   int mv;//Move !!  
   int tc;//Teleport Counter !!
   int sc;
    
    
public:
	
	StupidPlayer();
	int getMove(const char **ViewAround);
    void init(int width,int height,int x,int y);
    std::string getName();
    std::string getId();
	
};


#endif //GHOST_STUPIDPLAYER_H
