#include <iostream>
#include <limits>
#include <conio.h>
#include "Ghost/SmartGhost/SmartGhost.h"
#include "Player/Player.h"
#include "PlayerInfo/PlayerInfo.h"
#include "GameBoard/GameBoard.h"
#include "ManualPlayer/ManualPlayer.h"



int main() {
    std::vector<ObjectInfo *> PlayersVector; //vector with players engaged
    PlayersVector.push_back(new PlayerInfo(*new ManualPlayer(), 'A')); //Erase the comments to play with keyboard
    PlayersVector.push_back(new PlayerInfo(*new StupidPlayer(), 'B')); //Fool Standby player
    PlayersVector.push_back(new PlayerInfo(*new StupidPlayer(), 'C')); //Fool Standby player
    PlayersVector.push_back(new PlayerInfo(*new StupidPlayer(), 'D')); //Fool Standby player
    GameBoard *MainGameObject; //Main Game Object
    InfoBoard *ptrToInfoBoard = new InfoBoard();
    for (int j = 0; j < PlayersVector.size(); ++j) {
        ptrToInfoBoard->addPlayer(*static_cast<PlayerInfo *>(PlayersVector[j]));
    }
    std::ostringstream he;
    std::vector<std::string>*ptr = GameBoard::getMapFileNames(DEVCPP_PATH);

    for (unsigned int i = 0; i < ptr->size(); ++i) {
        he<<DEVCPP_PATH<<ptr->operator[](i);
        for (int j = 0; j < EATCH_MAP_PLAY_TIMES; ++j) {

            MainGameObject=new GameBoard(true,he.str().c_str(),PlayersVector,EXETASI_MODE,ptrToInfoBoard);
            MainGameObject->StartGame();
            delete(MainGameObject);
            getchar();

        }
        he.str("");


    }
    while(1);
}
