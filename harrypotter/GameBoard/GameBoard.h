//
// Created by stefstef on 2/4/2017.
//

#ifndef GHOST_GAMEBOARD_H
#define GHOST_GAMEBOARD_H


#include <vector>
#include <unistd.h>
#include "../Map/Map.h"
#include "../GhostInfo/GhostInfo.h"
#include "../Ghost/SmartGhost/SmartGhost.h"
#include "../Ghost/DummyGhost/DummyGhost.h"
#include "../PlayerInfo/PlayerInfo.h"
#include "../DisplaySystem/Window/Window.h"
class Window;
class LeaderBoard;
class InfoBoard;
/***
 * Class GameBoard
 */
class GameBoard {
public:
    static std::vector<std::string>*getMapFileNames(std::string dir);
    Map PlayersMap;
    std::vector<ObjectInfo *> Players;
    std::vector<char **>PlayersGeneratedAroundView;
    std::vector<ObjectInfo *> Ghosts;
    int DebugMode;
    bool misCupHitten;
    bool misAnyoneHittenByGhost;
    Coordinate CupPosition;

    Window *ptrMainWindow;
    InfoBoard *ptrToInfoBoard;

    bool isValidMove(PlayerInfo*player,int Move);
    bool isValidMove(Coordinate &CurrentPosition,int Move);
    bool HitsGhost(Coordinate Position,int Move);
    bool HitsCup(Coordinate Position,int Move);

    char HitsPlayer(Coordinate Position,int Move)__attribute__((deprecated("use std::vector *getAllHittenPlayers(Coordinate Position,int Move) instead")));
    char ** initializeGeneratedArray();

    void initPrintAllObjects();
    void generateAroundView(Coordinate &refToCoordinate,char **PlayerGeneratedAroundView);
    void killPlayerOnInfoBoard(PlayerInfo *ptrToPlayer);
    void killPlayerByMistakeOnInfoBoard(PlayerInfo *ptrToPlayer);
    void  clearGeneratedArray(char **);
    void move(ObjectInfo *Object,int Move);
    void teleport(PlayerInfo *player);


    ObjectInfo *getPlayerByRepresent(char Avatar);
    std::string TranslateMoveToString(int Move);
    Coordinate CalculateRandomPosition(void);
    std::vector<PlayerInfo*>*getAllPlayersWhoHitsCup();
    void givePointsToEveryoneWhoHitsCup(std::vector<PlayerInfo*> *vptrtoPlayerInfo);
    void killAllHittenPlayers(std::vector<PlayerInfo*> *vptrtoPlayerInfo);
    std::vector<PlayerInfo*> *getAllHittenPlayers(void);

public:
    GameBoard(int _DebugMode,const char MapFileName[],std::vector<ObjectInfo *> __Players,int Level,InfoBoard *_ptrToInfoBoard);
    virtual ~GameBoard();
    int StartGame();

};


#endif //GHOST_GAMEBOARD_H
