
//
// Created by sotiris on 4/25/2017.
//

#ifndef GHOST_PLAYERMANUALY_H
#define GHOST_PLAYERMANUALY_H
#include "../Player/Player.h"
#include "../Move.h"
#include <windows.h>
#include <fstream>
#include "stdio.h"

class ManualPlayer:public Player{
public:
    ManualPlayer(){}
    
    int getMove(const char **maze){
        std::ofstream he("testlogs.txt");
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                he<<maze[i][j];
            }
            he<<"\n";
        }
        he.close();
        HANDLE  handle=GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(handle,ENABLE_PROCESSED_INPUT);
        CHAR buffer[10];
        DWORD nChars;
        ReadConsole(handle,buffer,10,&nChars,NULL);
        int input=atoi(buffer);
        switch(input) {
            case 8 :
                return UP;
            case 2:
                return DOWN;
            case 4:
                return LEFT;
            case 6:
                return RIGHT;
            case 1:
                return STAND;
            case 3:
                return TELEPORT;
        }
        return STAND;
    }
    void init(int width,int height,int currentX,int currentY){
        std::ofstream he("testlogs.txt");
        he<<"init with "<<width<<"-"<<height<<"\\-> "<<currentX<<"-"<<currentY<<std::endl;
        he.close();
    }
    std::string getName() {
        return std::string("ManualPlayer");
    }

    std::string getId() {
        return std::string("cs161111");
    }

};



#endif //GHOST_MANUALPLAYER_H
